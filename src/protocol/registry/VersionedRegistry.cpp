#include "VersionedRegistry.hpp"

namespace Ship {
  VersionedRegistry::VersionedRegistry(const std::set<ProtocolVersion>& versionMap) {
    int ordinal = 0;

    auto previousIt = versionMap.begin();
    for (auto it = versionMap.begin()++; it != versionMap.end(); it++) {
      std::fill(versionToOrdinalMap + previousIt->GetOrdinal(), versionToOrdinalMap + it->GetOrdinal(), ordinal++);
      previousIt = it;
    }

    std::fill(versionToOrdinalMap + previousIt->GetOrdinal(), versionToOrdinalMap + ProtocolVersion::MAXIMUM_VERSION.GetOrdinal() + 1, ordinal);
    versionRegistry = new VersionRegistry*[VersionToOrdinal(&ProtocolVersion::MAXIMUM_VERSION) + 1];
  }

  void VersionedRegistry::RegisterVersion(const ProtocolVersion* version, VersionRegistry* registry) {
    versionRegistry[VersionToOrdinal(version)] = registry;
  }

  void VersionedRegistry::FillVersionRegistry(VersionRegistry* registry) {
    for (uint32_t i = VersionToOrdinal(&ProtocolVersion::MINIMUM_VERSION); i <= VersionToOrdinal(&ProtocolVersion::MAXIMUM_VERSION); ++i) {
      versionRegistry[i] = registry;
    }
  }

  uint32_t VersionedRegistry::GetOrdinalByID(const ProtocolVersion* version, uint32_t id) const {
    return versionRegistry[VersionToOrdinal(version)]->GetOrdinalByID(id);
  }

  uint32_t VersionedRegistry::GetIDByOrdinal(const ProtocolVersion* version, uint32_t ordinal) const {
    return versionRegistry[VersionToOrdinal(version)]->GetIDByOrdinal(ordinal);
  }

  uint32_t VersionedRegistry::VersionToOrdinal(const ProtocolVersion* version) const {
    if (version == &ProtocolVersion::UNKNOWN) {
      version = &ProtocolVersion::MAXIMUM_VERSION;
    }

    return versionToOrdinalMap[version->GetOrdinal()];
  }
} // Ship