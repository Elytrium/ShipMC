#pragma once

#include "../Connection.hpp"
#include <map>
#include <queue>
#include <sys/epoll.h>

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

  class EpollEventLoop : public EventLoop {
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

    void Accept(int fileDescriptor);

    [[noreturn]] void StartLoop() override;
  };
}
