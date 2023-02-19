#include "VersionRegistry.hpp"

namespace Ship {

  VersionRegistry::VersionRegistry() {
  }

  VersionRegistry::VersionRegistry(const std::vector<uint32_t>& ordinals) {
    idToOrdinalMap = ordinals;

    int index = 0;
    for (const auto& ordinal : ordinals) {
      ordinalToIDMap[ordinal] = index++;
    }
  }

  uint32_t VersionRegistry::GetOrdinalByID(uint32_t id) const {
    if (id >= idToOrdinalMap.size()) {
      return UINT32_MAX;
    }

    return idToOrdinalMap[id];
  }

  uint32_t VersionRegistry::GetIDByOrdinal(uint32_t ordinal) const {
    if (ordinal >= ordinalToIDMap.size()) {
      throw InvalidArgumentException("Invalid (unregistered) packet: ordinal ", ordinal);
    }

    return ordinalToIDMap[ordinal];
  }

  void VersionRegistry::Register(uint32_t ordinal) {
    Register(ordinal, ++latestRegisteredID);
  }

  void VersionRegistry::Register(uint32_t ordinal, uint32_t id) {
    ResizeVectorAndSet(ordinalToIDMap, ordinal, id);
    ResizeVectorAndSet(idToOrdinalMap, id, ordinal);
  }
}