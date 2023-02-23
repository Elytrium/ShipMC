#pragma once

#include "../Connection.hpp"
#include <map>
#include <queue>

#ifdef __linux__
#include <sys/epoll.h>
#endif

#if defined(__APPLE__) || defined(__FreeBSD__)
#include <sys/event.h>
#endif

namespace Ship {
  class EventLoop {
   private:
    std::function<Connection*(ReadWriteCloser*)> initializer;
    std::queue<std::function<void()>> immediateTasks;
    std::multimap<time_t, std::function<void()>> delayedTasks;

   public:
    virtual ~EventLoop() = default;

    explicit EventLoop(std::function<Connection*(ReadWriteCloser*)> initializer);
    void Execute(const std::function<void()>& function);
    void Delay(const std::function<void()>& function, time_t millis);
    void ProceedTasks();

    Connection* NewConnection(ReadWriteCloser* writer);

    virtual void StartLoop() {
    }
  };

  class GracefulDisconnectException : public Exception {
   public:
    GracefulDisconnectException() : Exception("Gracefully disconnected") {}
  };

  class UnixEventLoop : public EventLoop {
   public:
    explicit UnixEventLoop(std::function<Connection*(ReadWriteCloser*)> initializer)
      : EventLoop(std::move(initializer)) {}

    ~UnixEventLoop() override = default;

    virtual void Accept(int fileDescriptor) = 0;
  };

#ifdef __linux__
  class EpollEventLoop : public UnixEventLoop {
   private:
    int epollFileDescriptor;
    int maxEvents;
    int timeout;
    char* errorBuffer = new char[64];
    uint8_t* buffer;
    int bufferSize;
    epoll_event epollEvent {};

   public:
    EpollEventLoop(std::function<Connection*(ReadWriteCloser*)> initializer, int max_events, int timeout, int buffer_size);

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
    KqueueEventLoop(std::function<Connection*(ReadWriteCloser*)> initializer, int max_events, const timespec* timeout, int buffer_size);

    ~KqueueEventLoop() override;

    void Accept(int fileDescriptor) override;

    [[noreturn]] void StartLoop() override;
  };

  static const timespec* NO_TIMEOUT = nullptr;
  typedef KqueueEventLoop SystemEventLoop;
#endif
}
