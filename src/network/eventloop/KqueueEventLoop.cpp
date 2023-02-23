#ifdef __APPLE__
#include "../../utils/exceptions/ErrnoException.hpp"
#include "EventLoop.hpp"
#include <sys/fcntl.h>
#include <unistd.h>

namespace Ship {
  KqueueEventLoop::KqueueEventLoop(std::function<Connection*(ReadWriteCloser* writer)> initializer, int max_events, const timespec* timeout, int buffer_size)
    : UnixEventLoop(std::move(initializer)), maxEvents(max_events), timeout(timeout), buffer(new uint8_t[buffer_size]), bufferSize(buffer_size) {
    kqueueFileDescriptor = ::kqueue();
    if (kqueueFileDescriptor == -1) {
      throw ErrnoException(errorBuffer, 64);
    }

    int flags = fcntl(kqueueFileDescriptor, F_GETFL, 0);
    fcntl(kqueueFileDescriptor, F_SETFL, flags | O_CLOEXEC);

    EV_SET(&kevent, 0, EVFILT_READ, EV_ADD, 0, 0, NULL);

    if (::kevent(kqueueFileDescriptor, &kevent, 1, nullptr, 0, nullptr) == -1) {
      throw ErrnoException(errorBuffer, 64);
    }
  }

  KqueueEventLoop::~KqueueEventLoop() {
    close(kqueueFileDescriptor);
    delete[] buffer;
    delete[] errorBuffer;
  }

  void KqueueEventLoop::Accept(int fileDescriptor) {
    EV_SET(&kevent, fileDescriptor, EVFILT_READ, EV_ADD, 0, 0, nullptr);
    kevent.udata = NewConnection(new UnixReadWriteCloser(fileDescriptor));
    if (::kevent(kqueueFileDescriptor, &kevent, 1, nullptr, 0, nullptr) == -1) {
      auto connection = (Connection*) kevent.udata;
      connection->GetReadWriteCloser()->Close();
      delete connection;
    }
  }

  [[noreturn]] void KqueueEventLoop::StartLoop() {
    struct kevent events[maxEvents];
    struct kevent event; // NOLINT(cppcoreguidelines-pro-type-member-init)

    while (true) {
      ProceedTasks();
      int amount = ::kevent(kqueueFileDescriptor, nullptr, 0, events, maxEvents, timeout);

      for (int i = 0; i < amount; ++i) {
        event = events[i];
        bool shouldClose = false;
        auto connection = (Connection*) event.udata;

        if (event.flags & EV_EOF) {
          shouldClose = true;
        } else {
          while (true) {
            ssize_t count = connection->GetReadWriteCloser()->Read(buffer, bufferSize);

            if (count == -1) {
              if (errno != EAGAIN) {
                throw ErrnoException(errorBuffer, 64);
              }

              break;
            } else if (count == 0) {
              shouldClose = true;
            } else {
              connection->HandleNewBytes(buffer, (size_t) count);
            }
          }
        }

        if (shouldClose) {
          connection->GetReadWriteCloser()->Close();
          delete connection;
        }
      }
    }
  }
}
#endif