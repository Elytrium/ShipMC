#include "Connector.hpp"
#include <arpa/inet.h>
#include <sys/ioctl.h>
#include <sys/socket.h>

namespace Ship {
  thread_local char* errorBuffer = new char[64];

  UnixConnector::UnixConnector(UnixEventLoop* eventLoop) : eventLoop(eventLoop) {
  }

  Errorable<int> UnixConnector::Connect(char* bind_address, int16_t port) {
    int socketFileDescriptor = socket(AF_INET, SOCK_STREAM, 0);
    if (socketFileDescriptor == -1) {
      return ErrnoErrorable<int>(socketFileDescriptor);
    }

    if (ioctl(socketFileDescriptor, FIONBIO) == -1) {
      return ErrnoErrorable<int>(socketFileDescriptor);
    }

    sockaddr_in bindAddress {};
    bindAddress.sin_family = AF_INET;
    bindAddress.sin_port = htons(port);
    bindAddress.sin_addr.s_addr = inet_addr(bind_address);

    if (connect(socketFileDescriptor, (sockaddr*) &bindAddress, sizeof(sockaddr_in)) == -1) {
      return ErrnoErrorable<int>(socketFileDescriptor);
    }

    eventLoop->Accept(socketFileDescriptor);
    return SuccessErrorable<int>(socketFileDescriptor);
  }
}