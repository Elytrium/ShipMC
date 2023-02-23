#include "VillagerData.hpp"

namespace Ship {

  EnumRegistry<VillagerType> GetVillagerTypeRegistry() {
    EnumRegistry<VillagerType> villagerRegistry({
      // TODO: Other versions
      ProtocolVersion::MINECRAFT_1_19,
      ProtocolVersion::MINECRAFT_1_19_3,
    });

    villagerRegistry.RegisterVersion(
      &ProtocolVersion::MINECRAFT_1_19, new VersionRegistry(std::vector<VillagerType>({VillagerType::DESERT, VillagerType::JUNGLE, VillagerType::PLAINS,
                                          VillagerType::SAVANNA, VillagerType::SNOW, VillagerType::SWAMP, VillagerType::TAIGA})));

    return villagerRegistry;
  }

  EnumRegistry<VillagerProfession> GetVillagerProfessionRegistry() {
    EnumRegistry<VillagerProfession> professionRegistry({
      // TODO: Other versions
      ProtocolVersion::MINECRAFT_1_19,
      ProtocolVersion::MINECRAFT_1_19_3,
    });

    professionRegistry.RegisterVersion(&ProtocolVersion::MINECRAFT_1_19,
      new VersionRegistry(std::vector<VillagerProfession>({VillagerProfession::NONE, VillagerProfession::ARMORER, VillagerProfession::BUTCHER,
        VillagerProfession::CARTOGRAPHER, VillagerProfession::CLERIC, VillagerProfession::FARMER, VillagerProfession::FISHERMAN,
        VillagerProfession::FLETCHER, VillagerProfession::LEATHERWORKER, VillagerProfession::LIBRARIAN, VillagerProfession::MASON,
        VillagerProfession::NITWIT, VillagerProfession::SHEPHERD, VillagerProfession::TOOLSMITH, VillagerProfession::WEAPONSMITH})));

    return professionRegistry;
  }

  const EnumRegistry<VillagerType> VILLAGER_TYPE_REGISTRY = GetVillagerTypeRegistry();
  const EnumRegistry<VillagerProfession> VILLAGER_PROFESSION_REGISTRY = GetVillagerProfessionRegistry();
}