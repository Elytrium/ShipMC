#include "VillagerData.hpp"

namespace Ship {

  EnumRegistry<VillagerType> GetVillagerTypeRegistry() {
    VersionRegistry* registry = EnumRegistry<VillagerType>::NewVersionRegistry();

    // TODO: Other versions

    for (uint32_t i = ProtocolVersion::MINECRAFT_1_19.GetOrdinal(); i <= ProtocolVersion::MINECRAFT_1_19_1.GetOrdinal(); ++i) {
      registry[i].Register((uint32_t) VillagerType::DESERT, 0);
      registry[i].Register((uint32_t) VillagerType::JUNGLE, 1);
      registry[i].Register((uint32_t) VillagerType::PLAINS, 2);
      registry[i].Register((uint32_t) VillagerType::SAVANNA, 3);
      registry[i].Register((uint32_t) VillagerType::SNOW, 4);
      registry[i].Register((uint32_t) VillagerType::SWAMP, 5);
      registry[i].Register((uint32_t) VillagerType::TAIGA, 6);
    }

    return EnumRegistry<VillagerType>(registry);
  }

  EnumRegistry<VillagerProfession> GetVillagerProfessionRegistry() {
    VersionRegistry* registry = EnumRegistry<VillagerType>::NewVersionRegistry();

    // TODO: Other versions

    for (uint32_t i = ProtocolVersion::MINECRAFT_1_19.GetOrdinal(); i <= ProtocolVersion::MINECRAFT_1_19_1.GetOrdinal(); ++i) {
      registry[i].Register((uint32_t) VillagerProfession::NONE, 0);
      registry[i].Register((uint32_t) VillagerProfession::ARMORER, 1);
      registry[i].Register((uint32_t) VillagerProfession::BUTCHER, 2);
      registry[i].Register((uint32_t) VillagerProfession::CARTOGRAPHER, 3);
      registry[i].Register((uint32_t) VillagerProfession::CLERIC, 4);
      registry[i].Register((uint32_t) VillagerProfession::FARMER, 5);
      registry[i].Register((uint32_t) VillagerProfession::FISHERMAN, 6);
      registry[i].Register((uint32_t) VillagerProfession::FLETCHER, 7);
      registry[i].Register((uint32_t) VillagerProfession::LEATHERWORKER, 8);
      registry[i].Register((uint32_t) VillagerProfession::LIBRARIAN, 9);
      registry[i].Register((uint32_t) VillagerProfession::MASON, 10);
      registry[i].Register((uint32_t) VillagerProfession::NITWIT, 11);
      registry[i].Register((uint32_t) VillagerProfession::SHEPHERD, 12);
      registry[i].Register((uint32_t) VillagerProfession::TOOLSMITH, 13);
      registry[i].Register((uint32_t) VillagerProfession::WEAPONSMITH, 14);
    }

    return EnumRegistry<VillagerProfession>(registry);
  }

  const EnumRegistry<VillagerType> VILLAGER_TYPE_REGISTRY = GetVillagerTypeRegistry();
  const EnumRegistry<VillagerProfession> VILLAGER_PROFESSION_REGISTRY = GetVillagerProfessionRegistry();
}