#pragma once

#include "VersionRegistry.hpp"
#include <set>

namespace Ship {
  class VersionedRegistry {
   private:
    uint32_t* versionToOrdinalMap = new uint32_t[ProtocolVersion::MAXIMUM_VERSION.GetOrdinal() + 1];
    VersionRegistry** versionRegistry;

   public:
    explicit VersionedRegistry(const std::set<ProtocolVersion>& versionMap);

    virtual ~VersionedRegistry() {
      if (versionRegistry) {
        for (uint32_t i = 0; i < VersionToOrdinal(&ProtocolVersion::MAXIMUM_VERSION) + 1; ++i) {
          delete versionRegistry[i];
        }
      }

      delete[] versionRegistry;
    }

    uint32_t VersionToOrdinal(const ProtocolVersion* version) const;
    uint32_t GetOrdinalByID(const ProtocolVersion* version, uint32_t id) const;
    uint32_t GetIDByOrdinal(const ProtocolVersion* version, uint32_t ordinal) const;
    void RegisterVersion(const ProtocolVersion* version, VersionRegistry* registry);
    void FillVersionRegistry(VersionRegistry* registry);
  };
} // Ship
