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
    delete[] errorBuffer;
  }

  void EpollEventLoop::Accept(int fileDescriptor) {
    epollEvent.data.ptr = NewConnection(new UnixReadWriteCloser(fileDescriptor));

    if (epoll_ctl(epollFileDescriptor, EPOLL_CTL_ADD, fileDescriptor, (epoll_event*) &epollEvent) == -1) {
      auto connection = (Connection*) epollEvent.data.ptr;
      connection->GetReadWriteCloser()->Close();
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
        bool shouldClose = false;
        auto connection = (Connection*) event.data.ptr;

        if (!(event.events & EPOLLIN) || (event.events & EPOLLERR) || (event.events & EPOLLHUP)) {
          // TODO: Log error
          shouldClose = true;
        } else if (event.events & EPOLLRDHUP) {
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