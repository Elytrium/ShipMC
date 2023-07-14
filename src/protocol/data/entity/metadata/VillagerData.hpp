#pragma once

#include "../../../../../lib/ShipNet/src/protocol/registry/EnumRegistry.hpp"

namespace Ship {

  enum class VillagerType : uint32_t {
    DESERT,
    JUNGLE,
    PLAINS,
    SAVANNA,
    SNOW,
    SWAMP,
    TAIGA,
  };

  enum class VillagerProfession : uint32_t {
    NONE,
    ARMORER,
    BUTCHER,
    CARTOGRAPHER,
    CLERIC,
    FARMER,
    FISHERMAN,
    FLETCHER,
    LEATHERWORKER,
    LIBRARIAN,
    MASON,
    NITWIT,
    SHEPHERD,
    TOOLSMITH,
    WEAPONSMITH,
  };

  class VillagerData {
   private:
    VillagerType type{};
    VillagerProfession profession{};
    uint32_t level{};
   public:
    VillagerData() = default;

    VillagerData(VillagerType type, VillagerProfession profession, uint32_t level);

    [[nodiscard]] VillagerType GetType() const;
    void SetType(VillagerType type);
    [[nodiscard]] VillagerProfession GetProfession() const;
    void SetProfession(VillagerProfession profession);
    [[nodiscard]] uint32_t GetLevel() const;
    void SetLevel(uint32_t level);
  };

  extern const EnumRegistry<VillagerType> VILLAGER_TYPE_REGISTRY;
  extern const EnumRegistry<VillagerProfession> VILLAGER_PROFESSION_REGISTRY;
}