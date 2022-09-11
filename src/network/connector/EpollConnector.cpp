#include "../../utils/exceptions/Exception.hpp"
#include "Connector.hpp"
#include <arpa/inet.h>
#include <cstring>
#include <sys/ioctl.h>
#include <sys/socket.h>

namespace Ship {
  EpollConnector::EpollConnector(EpollEventLoop* eventLoop) : eventLoop(eventLoop) {
  }

  void EpollConnector::Connect(char* bind_address, int16_t port) {
    int socketFileDescriptor = socket(AF_INET, SOCK_STREAM, 0);
    if (socketFileDescriptor == -1) {
      throw Exception("Error while creating socket. No permissions?");
    }

    if (ioctl(socketFileDescriptor, FIONBIO) == -1) {
      throw Exception(strerror_r(errno, errorBuffer, 64));
    }

    sockaddr_in bindAddress {};
    bindAddress.sin_family = AF_INET;
    bindAddress.sin_port = htons(port);
    bindAddress.sin_addr.s_addr = inet_addr(bind_address);

    if (connect(socketFileDescriptor, (sockaddr*) &bindAddress, sizeof(sockaddr_in)) == -1) {
      throw Exception("Error while connecting to socket. Server is down/no permissions?");
    }

    eventLoop->Accept(socketFileDescriptor);
  }
}