#include "EventLoop.hpp"
#include <ctime>
#include <utility>

namespace Ship {
  EventLoop::EventLoop(std::function<Connection*(ReadWriteCloser*)> initializer) : initializer(std::move(initializer)) {
  }

  void EventLoop::Execute(const std::function<void()>& function) {
    immediateTasks.push(function);
  }

  void EventLoop::Delay(const std::function<void()>& function, time_t millis) {
    delayedTasks.emplace(std::time(nullptr) + millis, function);
  }

  Connection* EventLoop::NewConnection(ReadWriteCloser* writer) {
    return initializer(writer);
  }

  void EventLoop::ProceedTasks() {
    while (!immediateTasks.empty()) {
      immediateTasks.front()();
      immediateTasks.pop();
    }

    if (!delayedTasks.empty()) {
      time_t currentTime = std::time(nullptr);

      for (const auto& i : delayedTasks) {
        if (i.first <= currentTime) {
          i.second();
        } else {
          break;
        }
      }
    }
  }
}