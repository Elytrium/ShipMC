#pragma once

#include "../../Ship.hpp"
#include "../ordinal/OrdinalRegistry.hpp"
#include <cstdint>
#include <cstring>
#include <ostream>

#define CreateInvalidArgumentErrorable(name, T, justification)                                            \
  class name : public InvalidArgumentErrorable<T> {                                                       \
   public:                                                                                                \
    static inline const uint32_t TYPE_ORDINAL = OrdinalRegistry::ErrorableTypeRegistry.RegisterOrdinal(); \
    explicit name(uint64_t argument) : InvalidArgumentErrorable<T>(TYPE_ORDINAL, {}, argument) {          \
    }                                                                                                     \
    void Print(std::ostream o) {                                                                          \
      o << justification << ": " << this->GetErrorCode();                                                 \
    }                                                                                                     \
  }

#define ProceedErrorable(variable, T, errorable, exception) \
  T variable;                                               \
  SetFromErrorable(variable, T, errorable, exception)

#define SetFromErrorable(variable, T, errorable, exception) \
  {                                                         \
    Errorable<T> variable_err = errorable;                  \
    if (!variable_err.IsSuccess()) {                        \
      return exception;                                     \
    }                                                       \
    variable = variable_err.GetValue();                     \
  }

namespace Ship {
  template<typename T>
  class Errorable {
   private:
    uint32_t typeOrdinal;
    T value;
    uint64_t errorCode;

   public:
    Errorable(uint32_t typeOrdinal, T value, uint64_t errorCode) : typeOrdinal(typeOrdinal), value(value), errorCode(errorCode) {
    }

    [[nodiscard]] uint32_t GetTypeOrdinal() const {
      return typeOrdinal;
    }

    T GetValue() const {
      return value;
    }

    [[nodiscard]] uint64_t GetErrorCode() const {
      return errorCode;
    }

    bool IsSuccess();
  };

  template<typename T>
  class SuccessErrorable : public Errorable<T> {
   public:
    static inline const uint32_t TYPE_ORDINAL = OrdinalRegistry::ErrorableTypeRegistry.RegisterOrdinal();

    explicit SuccessErrorable(T value) : Errorable<T>(TYPE_ORDINAL, value, 0L) {
    }

    void Print(std::ostream o) {
    }
  };

  template<typename T>
  class ErrnoErrorable : public Errorable<T> {
   public:
    static thread_local char strerrorBuffer[STRERROR_BUFFER_LENGTH];
    static inline const uint32_t TYPE_ORDINAL = OrdinalRegistry::ErrorableTypeRegistry.RegisterOrdinal();

    explicit ErrnoErrorable(T value) : Errorable<T>(TYPE_ORDINAL, value, errno) {
    }

    void Print(std::ostream o) {
#if defined(__APPLE__) || defined(__FreeBSD__)
      strerror_r(this->GetErrorCode(), errorBuffer, bufferSize);
      o << errorBuffer;
#else
      o << strerror_r(this->GetErrorCode(), strerrorBuffer, STRERROR_BUFFER_LENGTH);
#endif
    }
  };

  template<typename T>
  class InvalidArgumentErrorable : public Errorable<T> {
   public:
    InvalidArgumentErrorable(uint32_t typeOrdinal, T value, uint64_t argument) : Errorable<T>(typeOrdinal, value, argument) {
    }
  };

  template<typename T>
  bool Errorable<T>::IsSuccess() {
    return typeOrdinal == SuccessErrorable<T>::TYPE_ORDINAL;
  }
}