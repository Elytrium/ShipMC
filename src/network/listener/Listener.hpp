#pragma once

#include "../Connection.hpp"
#include "../eventloop/EventLoop.hpp"
#include "../pipe/Pipe.hpp"
#include <functional>
#include <list>
#include <string>
#include <utility>

namespace Ship {
  class Listener {
   public:
    virtual ~Listener() = default;

    virtual void StartListening(std::string bind_address, int16_t port) = 0;
  };

  class EpollListener : public Listener {
   private:
    EpollEventLoop* eventLoop;
    int maxEvents;
    int timeout;
    char* errorBuffer = new char[64];
    int epollFileDescriptor {};
    int socketFileDescriptor {};

   public:
    ~EpollListener() override;

    EpollListener(EpollEventLoop* event_loop, int max_events, int timeout);
    void StartListening(std::string, int16_t port) override;
  };
} // namespace Ship
