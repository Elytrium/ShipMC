#include "VersionedRegistry.hpp"

namespace Ship {
  void VersionedRegistry::RegisterVersion(const ProtocolVersion* version, VersionRegistry registry) {
    versionRegistry[version->GetPacketIDOrdinal()] = std::move(registry);
  }

  void VersionedRegistry::FillVersionRegistry(const VersionRegistry& registry) {
    for (uint32_t i = ProtocolVersion::MINIMUM_VERSION.GetPacketIDOrdinal(); i <= ProtocolVersion::MAXIMUM_VERSION.GetPacketIDOrdinal(); ++i) {
      versionRegistry[i] = registry;
    }
  }

  uint32_t VersionedRegistry::GetOrdinalByID(const ProtocolVersion* version, uint32_t id) const {
    return versionRegistry[VersionToOrdinal(version)].GetOrdinalByID(id);
  }

  uint32_t VersionedRegistry::GetIDByOrdinal(const ProtocolVersion* version, uint32_t ordinal) const {
    return versionRegistry[VersionToOrdinal(version)].GetIDByOrdinal(ordinal);
  }
} // Ship