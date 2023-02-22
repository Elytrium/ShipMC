#pragma once

#include "VersionedRegistry.hpp"

namespace Ship {

  template<typename T>
  class EnumRegistry : public VersionedRegistry {
   public:
    explicit EnumRegistry(const std::set<ProtocolVersion>& versionMap) : VersionedRegistry(versionMap) {}

    T GetValue(const ProtocolVersion* version, uint32_t id) const {
      return (T) GetOrdinalByID(version, id);
    }

    uint32_t GetID(const ProtocolVersion* version, const T& value) const {
      return GetIDByOrdinal(version, (uint32_t) value);
    }
  };
}