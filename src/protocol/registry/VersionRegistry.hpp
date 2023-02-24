#pragma once

#include "../../utils/ordinal/OrdinalRegistry.hpp"
#include "../../utils/ordinal/OrdinalVector.hpp"
#include "../Protocol.hpp"
#include <vector>

namespace Ship {
  class VersionRegistry {
   private:
    std::vector<uint32_t> ordinalToIDMap = std::vector<uint32_t>();
    std::vector<uint32_t> idToOrdinalMap = std::vector<uint32_t>();
    int latestRegisteredID = -1;

   public:
    VersionRegistry() = default;

    template<typename T>
    explicit VersionRegistry(const std::vector<T>& ordinals) {
      uint32_t index = 0;
      for (const T& ordinal : ordinals) {
        idToOrdinalMap.push_back((uint32_t) ordinal);
        OrdinalVector::ResizeVectorAndSet(ordinalToIDMap, (uint32_t) ordinal, index++);
      }
    }

    explicit VersionRegistry(const std::vector<uint32_t>& ordinals);

    void Register(uint32_t ordinal);
    void Register(uint32_t ordinal, uint32_t id);
    [[nodiscard]] uint32_t GetOrdinalByID(uint32_t id) const;
    [[nodiscard]] uint32_t GetIDByOrdinal(uint32_t ordinal) const;
  };
}