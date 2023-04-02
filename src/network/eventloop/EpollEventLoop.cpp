#ifdef __linux__
  #include "NetworkEventLoop.hpp"
  #include <cstring>
  #include <fcntl.h>
  #include <sys/epoll.h>
  #include <thread>
  #include <unistd.h>
  #include <utility>

namespace Ship {
  EpollEventLoop::EpollEventLoop(
    std::function<Connection*(EventLoop*, ReadWriteCloser *writer)> initializer, int epoll_file_descriptor, int max_events, int timeout, int buffer_size)
    : UnixEventLoop(std::move(initializer)), epollFileDescriptor(epoll_file_descriptor), maxEvents(max_events), timeout(timeout),
      buffer(new uint8_t[buffer_size]), bufferSize(buffer_size), epollEvent({EPOLLIN | EPOLLRDHUP | EPOLLET, {}}) {
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

      bool disconnected;
      for (int i = 0; i < amount; ++i) {
        event = events[i];
        auto connection = (Connection *) event.data.ptr;

        if (event.events & EPOLLRDHUP) {
          delete connection;
        } else {
          while (true) {
            Errorable<ssize_t> readRequest = connection->GetReadWriteCloser()->Read(buffer, bufferSize);

            if (readRequest.GetTypeOrdinal() == SuccessErrorable<ssize_t>::TYPE_ORDINAL) {
              connection->HandleNewBytes(buffer, (size_t) readRequest.GetValue());
            } else if (readRequest.GetTypeOrdinal() == ErrnoErrorable<ssize_t>::TYPE_ORDINAL && errno == EAGAIN) {
              break;
            } else if (readRequest.GetTypeOrdinal() == GracefulDisconnectErrorable::TYPE_ORDINAL) {
              delete connection;
              disconnected = true;
              break;
            } else {
              // TODO: Log exception via logger class
              delete connection;
              disconnected = true;
              break;
            }
          }

          if (disconnected) {
            break;
          }
        }
      }
    }
  }

  Errorable<EpollEventLoop*> EpollEventLoop::NewEventLoop(
    std::function<Connection*(EventLoop*, ReadWriteCloser*)> initializer, int max_events, int timeout, int buffer_size) {
    int epollFileDescriptor = epoll_create1(O_CLOEXEC);

    if (epollFileDescriptor == -1) {
      return ErrnoErrorable<EpollEventLoop*>(nullptr);
    }

    return SuccessErrorable<EpollEventLoop*>(new EpollEventLoop(std::move(initializer), epollFileDescriptor, max_events, timeout, buffer_size));
  }
}
#endif