#pragma once

#include "VersionRegistry.hpp"

namespace Ship {

  template<typename T>
  class EnumRegistry : public VersionedRegistry {
   public:
    uint32_t VersionToOrdinal(const ProtocolVersion* version) const override {
      return version->GetOrdinal();
    }

    T GetValue(const ProtocolVersion* version, uint32_t id) const {
      return (T) GetOrdinalByID(version, id);
    }

    uint32_t GetID(const ProtocolVersion* version, const T& value) const {
      return GetIDByOrdinal(version, (uint32_t) value);
    }
  };
}