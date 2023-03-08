#pragma once

#include <functional>
#include <map>
#include <queue>

namespace Ship {
  class EventLoop {
   private:
    std::queue<std::function<void()>> immediateTasks;
    std::multimap<time_t, std::function<void()>> delayedTasks;

   public:
    virtual ~EventLoop() = default;

    void Execute(const std::function<void()>& function);
    void Delay(const std::function<void()>& function, time_t millis);
    void ProceedTasks();

    virtual void StartLoop() {
    }
  };
}
