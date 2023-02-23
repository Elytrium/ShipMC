#ifdef __APPLE__
#include "../../utils/exceptions/ErrnoException.hpp"
#include "Listener.hpp"
#include <arpa/inet.h>
#include <sys/event.h>
#include <sys/fcntl.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <unistd.h>

namespace Ship {

  KqueueListener::KqueueListener(KqueueEventLoop* event_loop, int max_events, const timespec* timeout)
    : eventLoop(event_loop), maxEvents(max_events), timeout(timeout) {
  }

  KqueueListener::~KqueueListener() {
    close(kqueueFileDescriptor);
    close(socketFileDescriptor);
    delete eventLoop;
    delete[] errorBuffer;
  }

  void KqueueListener::StartListening(std::string bind_address, int16_t port) {
    socketFileDescriptor = socket(AF_INET, SOCK_STREAM, 0);
    if (socketFileDescriptor == -1) {
      throw Exception("Error while creating socket. No permissions?");
    }

    int fionbioValue = true;
    if (ioctl(socketFileDescriptor, FIONBIO, &fionbioValue) == -1) {
      throw ErrnoException(errorBuffer, 64);
    }

    sockaddr_in bindAddress {};
    bindAddress.sin_family = AF_INET;
    bindAddress.sin_port = htons(port);
    bindAddress.sin_addr.s_addr = inet_addr(bind_address.c_str());

    if (bind(socketFileDescriptor, (sockaddr*) &bindAddress, sizeof(sockaddr_in)) == -1) {
      throw ErrnoException(errorBuffer, 64);
    }

    if (listen(socketFileDescriptor, SOMAXCONN) == -1) {
      throw ErrnoException(errorBuffer, 64);
    }

    kqueueFileDescriptor = kqueue();

    if (kqueueFileDescriptor == -1) {
      throw ErrnoException(errorBuffer, 64);
    }

    struct kevent ctlEvent {};
    EV_SET(&ctlEvent, socketFileDescriptor, EVFILT_READ | EVFILT_WRITE, EV_ADD, 0, 0, NULL);

    if (::kevent(kqueueFileDescriptor, &ctlEvent, 1, nullptr, 0, nullptr) == -1) {
      throw ErrnoException(errorBuffer, 64);
    }

    struct kevent events[maxEvents];
    struct kevent event; // NOLINT(cppcoreguidelines-pro-type-member-init)
    while (true) {
      int amount = kevent(kqueueFileDescriptor, nullptr, 0, events, maxEvents, timeout);

      for (int i = 0; i < amount; ++i) {
        event = events[i];
        try {
          while (true) {
            if (!(event.flags & EVFILT_READ)) {
              throw ErrnoException(errorBuffer, 64);
            } else {
              sockaddr connectionAddress {};
              socklen_t length = sizeof(sockaddr);

              int receivedFileDescriptor = accept(socketFileDescriptor, &connectionAddress, &length);
              if (receivedFileDescriptor == -1) {
                if (errno != EAGAIN) {
                  throw ErrnoException(errorBuffer, 64);
                }

                break;
              }

              int flags = fcntl(receivedFileDescriptor, F_GETFL, 0);
              fcntl(receivedFileDescriptor, F_SETFL, flags | O_NONBLOCK | O_CLOEXEC);

              eventLoop->Accept(receivedFileDescriptor);
            }
          }
        } catch (std::exception& e) {
          close((int) event.ident);
          close(kqueueFileDescriptor);
          throw;
        }
      }
    }
  }
}
#endif