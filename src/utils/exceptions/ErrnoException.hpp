#pragma once

#include "Exception.hpp"
#include <cstring>

namespace Ship {

  class ErrnoException : Exception {
   public:
    ErrnoException(char* errorBuffer, size_t bufferSize) : Exception({}) {
#ifdef __APPLE__
      strerror_r(errno, errorBuffer, bufferSize);
      text = errorBuffer;
#else
      text = strerror_r(errno, errorBuffer, bufferSize);
#endif
    }
  };
}
