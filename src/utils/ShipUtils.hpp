#pragma once
#include <chrono>

namespace Ship {
  class ShipUtils {
   public:
    static uint64_t GetCurrentMillis() {
      using namespace std::chrono;
      return (uint64_t) duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    }
  };
}
