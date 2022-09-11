#pragma once

#include "../Connection.hpp"
#include "../eventloop/EventLoop.hpp"

namespace Ship {
  class Connector {
   public:
    virtual void Connect(char* bind_address, int16_t port) = 0;
  };

  class EpollConnector {
   private:
    EpollEventLoop* eventLoop;
    char* errorBuffer = new char[64];

   public:
    explicit EpollConnector(EpollEventLoop* eventLoop);
    void Connect(char* bind_address, int16_t port);
  };
}