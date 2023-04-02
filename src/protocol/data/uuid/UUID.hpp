#pragma once

#include <string>

namespace Ship {

  class UUID {
   private:
    uint64_t mostSignificant;
    uint64_t leastSignificant;

   public:
    UUID() = default;

    explicit UUID(const std::string& uuid);

    explicit UUID(const char* chars);

    UUID(uint64_t mostSignificant, uint64_t leastSignificant);

    [[nodiscard]] uint64_t GetMostSignificant() const;

    [[nodiscard]] uint64_t GetLeastSignificant() const;

    [[nodiscard]] std::string ToUndashedString() const;

    [[nodiscard]] std::string ToString() const;
  };

} // Ship
