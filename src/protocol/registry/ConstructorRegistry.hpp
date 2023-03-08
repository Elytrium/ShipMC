#pragma once

#include "VersionRegistry.hpp"
#include "VersionedRegistry.hpp"
#include <functional>

namespace Ship {

  template<typename T>
  inline std::function<T*(const ProtocolVersion* version, ByteBuffer* buffer)> CreateConstructor() {
    return [=](const ProtocolVersion* version, ByteBuffer* buffer) {
      return new T(version, buffer);
    };
  }

  template<typename T>
  class ConstructorRegistry : public VersionedRegistry {
   private:
    std::vector<std::function<T*(const ProtocolVersion* version, ByteBuffer* buffer)>> ordinalToObjectMap;

   public:
    explicit ConstructorRegistry(const std::set<ProtocolVersion>& versionMap) : VersionedRegistry(versionMap) {}

    void RegisterConstructor(uint32_t ordinal, const std::function<T*(const ProtocolVersion* version, ByteBuffer* buffer)>& constructor) {
      OrdinalVector::ResizeVectorAndSet(ordinalToObjectMap, ordinal, constructor);
    }

    T* GetObjectByID(const ProtocolVersion* version, uint32_t id, ByteBuffer* buffer) const {
      uint32_t ordinal = GetOrdinalByID(version, id);
      if (ordinal >= ordinalToObjectMap.size()) {
        return nullptr;
      }

      std::function<T*(const ProtocolVersion* version, ByteBuffer* buffer)> constructor = ordinalToObjectMap[ordinal];
      if (constructor) {
        return constructor(version, buffer);
      } else {
        return nullptr;
      }
    }

    [[nodiscard]] size_t GetConstructorCount() const {
      return ordinalToObjectMap.size();
    }
  };
}