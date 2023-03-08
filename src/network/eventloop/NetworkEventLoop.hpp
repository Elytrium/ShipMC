#pragma once

#include "../../utils/threads/EventLoop.hpp"
#include "../Connection.hpp"

#ifdef __linux__
  #include <sys/epoll.h>
#endif

#if defined(__APPLE__) || defined(__FreeBSD__)
  #include <sys/event.h>
#endif

namespace Ship {

  class GracefulDisconnectException : public Exception {
   public:
    GracefulDisconnectException() : Exception("Gracefully disconnected") {
    }
  };

  class NetworkEventLoop : public EventLoop {
   private:
    std::function<Connection*(EventLoop*, ReadWriteCloser*)> initializer;

   public:
    explicit NetworkEventLoop(std::function<Connection*(EventLoop*, ReadWriteCloser*)> initializer) : initializer(std::move(initializer)) {
    }

    ~NetworkEventLoop() override = default;
    inline Connection* NewConnection(ReadWriteCloser* writer) {
      return initializer(this, writer);
    }
  };

  class UnixEventLoop : public NetworkEventLoop {
   public:
    explicit UnixEventLoop(std::function<Connection*(EventLoop*, ReadWriteCloser*)> initializer) : NetworkEventLoop(std::move(initializer)) {
    }

    ~UnixEventLoop() override = default;

    virtual void Accept(int fileDescriptor) = 0;
  };

#ifdef __linux__
  class EpollEventLoop : public UnixEventLoop {
   private:
    int epollFileDescriptor;
    int maxEvents;
    int timeout;
    uint8_t* buffer;
    int bufferSize;
    epoll_event epollEvent {};

   public:
    EpollEventLoop(std::function<Connection*(EventLoop*, ReadWriteCloser*)> initializer, int max_events, int timeout, int buffer_size);

    ~EpollEventLoop() override;

    void Accept(int fileDescriptor) override;

    [[noreturn]] void StartLoop() override;
  };

  static const int NO_TIMEOUT = -1;
  typedef EpollEventLoop SystemEventLoop;
#endif

#if defined(__APPLE__) || defined(__FreeBSD__)
  class KqueueEventLoop : public UnixEventLoop {
   private:
    int kqueueFileDescriptor;
    int maxEvents;
    const timespec* timeout;
    char* errorBuffer = new char[64];
    uint8_t* buffer;
    int bufferSize;
    struct kevent kevent {};

   public:
    KqueueEventLoop(std::function<Connection*(EventLoop*, ReadWriteCloser*)> initializer, int max_events, const timespec* timeout, int buffer_size);

    ~KqueueEventLoop() override;

    void Accept(int fileDescriptor) override;

    [[noreturn]] void StartLoop() override;
  };

  static const timespec* NO_TIMEOUT = nullptr;
  typedef KqueueEventLoop SystemEventLoop;
#endif
}