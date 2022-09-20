#pragma once

#include "VersionRegistry.hpp"
#include <functional>

namespace Ship {

  template<typename T>
  class DataTypeRegistry {
   private:
    std::vector<std::function<T*()>> ordinalToObjectMap;
    const VersionRegistry* versionRegistry = NewVersionRegistry();

   public:
    static VersionRegistry* NewVersionRegistry() {
      return new VersionRegistry[ProtocolVersion::MAXIMUM_VERSION.GetOrdinal() + 1];
    }

    ~DataTypeRegistry() {
      delete[] versionRegistry;
    }

    explicit DataTypeRegistry(VersionRegistry* version_registry) : versionRegistry(version_registry) {
    }

    void RegisterConstructor(uint32_t ordinal, const std::function<T*()>& constructor) {
      ResizeVectorAndSet(ordinalToObjectMap, ordinal, constructor);
    }

    T* GetObjectByID(const ProtocolVersion* version, uint32_t id) const {
      uint32_t ordinal = versionRegistry[version->GetOrdinal()].GetOrdinalByID(id);
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

    uint32_t GetIDByOrdinal(const ProtocolVersion* version, uint32_t ordinal) const {
      return versionRegistry[version->GetOrdinal()].GetIDByOrdinal(ordinal);
    }
  };
}