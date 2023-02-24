#pragma once

#include "VersionRegistry.hpp"
#include "VersionedRegistry.hpp"
#include <functional>

namespace Ship {

  template<typename T, typename... A>
  inline std::function<T*()> CreateConstructor(const A&... args) {
    return [=]() {
      return new T(args...);
    };
  }

  template<typename T>
  class ConstructorRegistry : public VersionedRegistry {
   private:
    std::vector<std::function<T*()>> ordinalToObjectMap;

   public:
    explicit ConstructorRegistry(const std::set<ProtocolVersion>& versionMap) : VersionedRegistry(versionMap) {}

    void RegisterConstructor(uint32_t ordinal, const std::function<T*()>& constructor) {
      OrdinalVector::ResizeVectorAndSet(ordinalToObjectMap, ordinal, constructor);
    }

    T* GetObjectByID(const ProtocolVersion* version, uint32_t id) const {
      uint32_t ordinal = GetOrdinalByID(version, id);
      if (ordinal >= ordinalToObjectMap.size()) {
        return nullptr;
      }

      std::function<T*()> constructor = ordinalToObjectMap[ordinal];
      if (constructor) {
        return constructor();
      } else {
        return nullptr;
      }
    }

    [[nodiscard]] size_t GetConstructorCount() const {
      return ordinalToObjectMap.size();
    }
  };
}