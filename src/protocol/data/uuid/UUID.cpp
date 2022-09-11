#include "UUID.hpp"

namespace Ship {
  UUID::UUID(const std::string& uuid) {
    std::string inputUUID = uuid;

    if (uuid.size() == 36) {
      std::string tempString;
      tempString.reserve(32);
      int cnt = 0;

      for (int i = 0; i < 8; ++i) {
        tempString[cnt++] = uuid[i];
      }

      for (int i = 8; i < 13; ++i) {
        tempString[cnt++] = uuid[i];
      }

      for (int i = 13; i < 18; ++i) {
        tempString[cnt++] = uuid[i];
      }

      for (int i = 18; i < 23; ++i) {
        tempString[cnt++] = uuid[i];
      }

      for (int i = 23; i < 36; ++i) {
        tempString[cnt++] = uuid[i];
      }

      inputUUID = tempString;
    }

    if (inputUUID.size() == 32) {
      const char* chars = inputUUID.c_str();
      char* end;
      this->mostSignificant = strtoull(chars, &end, 16);
      this->leastSignificant = strtoull(end, nullptr, 16);
    } else {
      throw InvalidArgumentException("Invalid UUID size: ", inputUUID.size());
    }
  }
  UUID::UUID(const char* chars) {
    char* end;
    this->mostSignificant = strtoull(chars, &end, 16);
    this->leastSignificant = strtoull(end, nullptr, 16);
  }
  UUID::UUID(uint64_t mostSignificant, uint64_t leastSignificant) : mostSignificant(mostSignificant), leastSignificant(leastSignificant) {
  }
  std::string UUID::ToUndashedString() const {
    return std::to_string(mostSignificant) + std::to_string(leastSignificant);
  }
  std::string UUID::ToString() const {
    std::string uuid = ToUndashedString();
    uuid.insert(20, "-");
    uuid.insert(16, "-");
    uuid.insert(12, "-");
    uuid.insert(8, "-");
    return uuid;
  }
  uint64_t UUID::GetMostSignificant() const {
    return this->mostSignificant;
  }
  uint64_t UUID::GetLeastSignificant() const {
    return this->leastSignificant;
  }
} // Ship