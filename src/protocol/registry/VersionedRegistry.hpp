#pragma once

#include "VersionRegistry.hpp"
#include <bits/stdint-uintn.h>

namespace Ship {
  class VersionedRegistry {
   private:
    VersionRegistry* versionRegistry = new VersionRegistry[VersionToOrdinal(&ProtocolVersion::MAXIMUM_VERSION) + 1];

   public:
    virtual ~VersionedRegistry() {
      delete[] versionRegistry;
    }

    virtual uint32_t VersionToOrdinal(const ProtocolVersion* version) const = 0;
    uint32_t GetOrdinalByID(const ProtocolVersion* version, uint32_t id) const;
    uint32_t GetIDByOrdinal(const ProtocolVersion* version, uint32_t ordinal) const;
    void RegisterVersion(const ProtocolVersion* version, VersionRegistry registry);
    void FillVersionRegistry(const VersionRegistry& registry);
  };
} // Ship
