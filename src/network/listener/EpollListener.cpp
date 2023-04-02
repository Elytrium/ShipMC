#ifdef __linux__
  #include "Listener.hpp"
  #include <arpa/inet.h>
  #include <cstring>
  #include <fcntl.h>
  #include <sys/epoll.h>
  #include <sys/ioctl.h>
  #include <sys/socket.h>
  #include <thread>
  #include <unistd.h>

namespace Ship {
  EpollListener::EpollListener(EpollEventLoop* event_loop, int max_events, int timeout) : eventLoop(event_loop), maxEvents(max_events), timeout(timeout) {
  }

  EpollListener::~EpollListener() {
    close(epollFileDescriptor);
    close(socketFileDescriptor);
    delete eventLoop;
  }

  Errorable<int> EpollListener::Bind(SocketAddress address) {
    socketFileDescriptor = socket(AF_INET, SOCK_STREAM, 0);
    if (socketFileDescriptor == -1) {
      return ErrnoErrorable<int>(socketFileDescriptor);
    }

    int fionbioValue = true;
    if (ioctl(socketFileDescriptor, FIONBIO, &fionbioValue) == -1) {
      return ErrnoErrorable<int>(socketFileDescriptor);
    }

    sockaddr_in bindAddress {};
    bindAddress.sin_family = AF_INET;
    bindAddress.sin_port = htons(address.GetPort());
    bindAddress.sin_addr.s_addr = inet_addr(address.GetHostname().c_str());

    if (bind(socketFileDescriptor, (sockaddr*) &bindAddress, sizeof(sockaddr_in)) == -1) {
      return ErrnoErrorable<int>(socketFileDescriptor);
    }

    if (listen(socketFileDescriptor, SOMAXCONN) == -1) {
      return ErrnoErrorable<int>(socketFileDescriptor);
    }

    epollFileDescriptor = epoll_create1(O_CLOEXEC);

    if (epollFileDescriptor == -1) {
      return ErrnoErrorable<int>(epollFileDescriptor);
    }

    epoll_event ctlEvent {};
    ctlEvent.data.fd = socketFileDescriptor;
    ctlEvent.events = EPOLLIN | EPOLLET;

    if (epoll_ctl(epollFileDescriptor, EPOLL_CTL_ADD, socketFileDescriptor, &ctlEvent) == -1) {
      return ErrnoErrorable<int>(epollFileDescriptor);
    }

    return SuccessErrorable<int>(epollFileDescriptor);
  }

  Errorable<int> Accept(int socketFileDescriptor, sockaddr* connectionAddress, socklen_t* length, int flags) {
    int receivedFileDescriptor = accept4(socketFileDescriptor, connectionAddress, length, flags);
    if (receivedFileDescriptor == -1) {
      return ErrnoErrorable<int>(receivedFileDescriptor);
    }

    return SuccessErrorable<int>(receivedFileDescriptor);
  }

  [[noreturn]] void EpollListener::StartListening() {
    epoll_event events[maxEvents];
    epoll_event event; // NOLINT(cppcoreguidelines-pro-type-member-init)
    while (true) {
      int amount = epoll_wait(epollFileDescriptor, events, maxEvents, timeout);
      for (int i = 0; i < amount; ++i) {
        event = events[i];
        while (true) {
          sockaddr connectionAddress {};
          socklen_t length = sizeof(sockaddr);

          Errorable<int> receivedFileDescriptor = Accept(socketFileDescriptor, &connectionAddress, &length, SOCK_NONBLOCK | SOCK_CLOEXEC);
          if (receivedFileDescriptor.GetTypeOrdinal() == ErrnoErrorable<int>::TYPE_ORDINAL && errno == EAGAIN) {
            break;
          } else if (!receivedFileDescriptor.IsSuccess()) {
            // Log Exception
            close(event.data.fd);
            close(epollFileDescriptor);
            break;
          } else {
            eventLoop->Accept(receivedFileDescriptor.GetValue());
          }
        }
      }
    }
  }
}
#endif