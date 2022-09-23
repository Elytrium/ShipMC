#pragma once

#include "VersionRegistry.hpp"

namespace Ship {

  template<typename T>
  class EnumRegistry {
   private:
    const VersionRegistry* versionRegistry = NewVersionRegistry();

   public:
    static VersionRegistry* NewVersionRegistry() {
      return new VersionRegistry[ProtocolVersion::MAXIMUM_VERSION.GetOrdinal() + 1];
    }

    ~EnumRegistry() {
      delete[] versionRegistry;
    }

    explicit EnumRegistry(VersionRegistry* version_registry) : versionRegistry(version_registry) {
    }

    T GetValue(const ProtocolVersion* version, uint32_t id) const {
      return (T) versionRegistry[version->GetOrdinal()].GetOrdinalByID(id);
    }

    uint32_t GetID(const ProtocolVersion* version, const T& value) const {
      return versionRegistry[version->GetOrdinal()].GetIDByOrdinal((uint32_t) value);
    }
  };
}