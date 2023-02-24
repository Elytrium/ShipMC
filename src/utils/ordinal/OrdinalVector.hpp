#pragma once

#include <cstdint>
#include <vector>

namespace Ship {
  class OrdinalVector {
   public:
    template<typename T>
    static void ResizeVectorAndSet(std::vector<T>& vector, uint32_t at, T value) {
      if (at >= vector.size()) {
        vector.resize(at + 8);
      }

      vector.at(at) = value;
    }
  };
} // Ship
