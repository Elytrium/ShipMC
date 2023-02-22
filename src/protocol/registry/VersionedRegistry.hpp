#pragma once

#include "VersionRegistry.hpp"
#include <bits/stdint-uintn.h>
#include <set>

namespace Ship {
  class VersionedRegistry {
   private:
    uint32_t* versionToOrdinalMap = new uint32_t[ProtocolVersion::MAXIMUM_VERSION.GetOrdinal() + 1];
    VersionRegistry* versionRegistry = new VersionRegistry[VersionToOrdinal(&ProtocolVersion::MAXIMUM_VERSION) + 1];

   public:
    explicit VersionedRegistry(const std::set<ProtocolVersion>& versionMap);

    virtual ~VersionedRegistry() {
      delete[] versionRegistry;
    }

    uint32_t VersionToOrdinal(const ProtocolVersion* version) const;
    uint32_t GetOrdinalByID(const ProtocolVersion* version, uint32_t id) const;
    uint32_t GetIDByOrdinal(const ProtocolVersion* version, uint32_t ordinal) const;
    void RegisterVersion(const ProtocolVersion* version, VersionRegistry registry);
    void FillVersionRegistry(const VersionRegistry& registry);
  };
} // Ship
