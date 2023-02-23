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

#ifdef __linux__
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

  typedef EpollListener SystemListener;
#endif

#ifdef __APPLE__
  class KqueueListener : public Listener {
   private:
    KqueueEventLoop* eventLoop;
    int maxEvents;
    const timespec* timeout;
    char* errorBuffer = new char[64];
    int kqueueFileDescriptor;
    int socketFileDescriptor;

   public:
    ~KqueueListener() override;

    KqueueListener(KqueueEventLoop* event_loop, int max_events, const timespec* timeout);
    void StartListening(std::string, int16_t port) override;
  };

  typedef KqueueListener SystemListener;
#endif
} // namespace Ship
