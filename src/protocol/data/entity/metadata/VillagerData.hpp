#pragma once

#include "../../../registry/EnumRegistry.hpp"

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

  extern const EnumRegistry<VillagerType> VILLAGER_TYPE_REGISTRY;
  extern const EnumRegistry<VillagerProfession> VILLAGER_PROFESSION_REGISTRY;
}