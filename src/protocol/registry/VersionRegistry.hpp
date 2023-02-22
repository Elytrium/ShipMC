#pragma once

#include "../../utils/ordinal/OrdinalRegistry.hpp"
#include "../Protocol.hpp"

namespace Ship {

  template<typename T>
  inline void ResizeVectorAndSet(std::vector<T>& vector, uint32_t at, T value) {
    if (at >= vector.size()) {
      vector.resize(at + 8);
    }

    vector.at(at) = value;
  }

  class VersionRegistry {
   private:
    std::vector<uint32_t> ordinalToIDMap = std::vector<uint32_t>(OrdinalRegistry::PacketRegistry.GetLastOrdinal() + 1);
    std::vector<uint32_t> idToOrdinalMap = std::vector<uint32_t>();
    int latestRegisteredID = -1;

   public:
    VersionRegistry() = default;

    template<typename T>
    explicit VersionRegistry(const std::vector<T>& ordinals);
    explicit VersionRegistry(const std::vector<uint32_t>& ordinals);

    void Register(uint32_t ordinal);
    void Register(uint32_t ordinal, uint32_t id);
    [[nodiscard]] uint32_t GetOrdinalByID(uint32_t id) const;
    [[nodiscard]] uint32_t GetIDByOrdinal(uint32_t ordinal) const;
  };
}