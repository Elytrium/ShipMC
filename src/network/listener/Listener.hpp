#pragma once

#include "../eventloop/NetworkEventLoop.hpp"
#include "../Connection.hpp"
#include "../SocketAddress.hpp"
#include "../pipe/Pipe.hpp"
#include <functional>
#include <list>
#include <string>
#include <utility>

namespace Ship {
  class Listener {
   public:
    virtual ~Listener() = default;

    virtual Errorable<int> Bind(SocketAddress address) = 0;
    virtual void StartListening() = 0;
  };

#ifdef __linux__
  class EpollListener : public Listener {
   private:
    EpollEventLoop* eventLoop;
    int maxEvents;
    int timeout;
    int epollFileDescriptor {};
    int socketFileDescriptor {};

   public:
    ~EpollListener() override;

    EpollListener(EpollEventLoop* event_loop, int max_events, int timeout);
    Errorable<int> Bind(SocketAddress address) override;
    [[noreturn]] void StartListening() override;
  };

  typedef EpollListener SystemListener;
#endif

#if defined(__APPLE__) || defined(__FreeBSD__)
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
    void StartListening(SocketAddress address) override;
  };

  typedef KqueueListener SystemListener;
#endif
} // namespace Ship
