#ifdef __linux__
  #include "../../utils/exceptions/ErrnoException.hpp"
  #include "../readwritecloser/ReadWriteCloser.hpp"
  #include "EventLoop.hpp"
  #include <cstring>
  #include <fcntl.h>
  #include <sys/epoll.h>
  #include <thread>
  #include <unistd.h>
  #include <utility>

namespace Ship {
  thread_local char* eventLoopErrorBuffer = new char[64];

  EpollEventLoop::EpollEventLoop(std::function<Connection*(ReadWriteCloser* writer)> initializer, int max_events, int timeout, int buffer_size)
    : UnixEventLoop(std::move(initializer)), maxEvents(max_events), timeout(timeout), buffer(new uint8_t[buffer_size]), bufferSize(buffer_size) {
    epollEvent.events = EPOLLIN | EPOLLRDHUP | EPOLLET;
    epollFileDescriptor = epoll_create1(O_CLOEXEC);

    if (epollFileDescriptor == -1) {
      throw Exception("Error while creating epoll. Old kernel/no permissions?");
    }
  }

  EpollEventLoop::~EpollEventLoop() {
    close(epollFileDescriptor);
    delete[] buffer;
  }

  void EpollEventLoop::Accept(int fileDescriptor) {
    epollEvent.data.ptr = NewConnection(new UnixReadWriteCloser(fileDescriptor));

    if (epoll_ctl(epollFileDescriptor, EPOLL_CTL_ADD, fileDescriptor, (epoll_event*) &epollEvent) == -1) {
      auto connection = (Connection*) epollEvent.data.ptr;
      delete connection;
    }
  }

  [[noreturn]] void EpollEventLoop::StartLoop() {
    epoll_event events[maxEvents];
    epoll_event event; // NOLINT(cppcoreguidelines-pro-type-member-init)

    while (true) {
      ProceedTasks();
      int amount = epoll_wait(epollFileDescriptor, (epoll_event*) events, maxEvents, timeout);

      for (int i = 0; i < amount; ++i) {
        event = events[i];
        auto connection = (Connection*) event.data.ptr;

        try {
          if (!(event.events & EPOLLIN) || (event.events & EPOLLERR) || (event.events & EPOLLHUP)) {
            throw InvalidArgumentException("Got unknown epoll events: ", event.events);
          } else if (event.events & EPOLLRDHUP) {
            throw GracefulDisconnectException();
          } else {
            while (true) {
              ssize_t count = connection->GetReadWriteCloser()->Read(buffer, bufferSize);

              if (count == -1) {
                if (errno != EAGAIN) {
                  throw ErrnoException(eventLoopErrorBuffer, 64);
                }

                break;
              } else if (count == 0) {
                throw GracefulDisconnectException();
              } else {
                connection->HandleNewBytes(buffer, (size_t) count);
              }
            }
          }
        } catch (const GracefulDisconnectException& exception) {
          delete connection;
        }
        /* catch (const std::exception& exception) {
          delete connection;
          // TODO: Log exception via logger class
        } */
      }
    }
  }
}
#endif