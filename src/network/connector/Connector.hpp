#pragma once

#include "../eventloop/NetworkEventLoop.hpp"
#include "../Connection.hpp"

namespace Ship {
  class Connector {
   public:
    virtual void Connect(char* bind_address, int16_t port) = 0;
  };

  class UnixConnector : Connector {
   private:
    UnixEventLoop* eventLoop;

   public:
    explicit UnixConnector(UnixEventLoop* eventLoop);
    void Connect(char* bind_address, int16_t port) override;
  };
}