#include "VillagerData.hpp"
#include "../../../MinecraftProtocol.hpp"

namespace Ship {

  EnumRegistry<VillagerType> GetVillagerTypeRegistry() {
    EnumRegistry<VillagerType> villagerRegistry(MinecraftProtocolVersion::VERSIONS, {MinecraftProtocolVersion::MINECRAFT_1_14});

    villagerRegistry.RegisterVersion(
      &MinecraftProtocolVersion::MINECRAFT_1_14, new VersionRegistry(std::vector<VillagerType>({VillagerType::DESERT, VillagerType::JUNGLE, VillagerType::PLAINS,
                                          VillagerType::SAVANNA, VillagerType::SNOW, VillagerType::SWAMP, VillagerType::TAIGA})));

    return villagerRegistry;
  }

  EnumRegistry<VillagerProfession> GetVillagerProfessionRegistry() {
    EnumRegistry<VillagerProfession> professionRegistry(MinecraftProtocolVersion::VERSIONS, {MinecraftProtocolVersion::MINECRAFT_1_12_2, MinecraftProtocolVersion::MINECRAFT_1_14});

    professionRegistry.RegisterVersion(&MinecraftProtocolVersion::MINECRAFT_1_12_2,
      new VersionRegistry(std::vector<VillagerProfession>({VillagerProfession::FARMER, VillagerProfession::LIBRARIAN, VillagerProfession::CLERIC,
        VillagerProfession::ARMORER, VillagerProfession::BUTCHER, VillagerProfession::NITWIT})));

    professionRegistry.RegisterVersion(&MinecraftProtocolVersion::MINECRAFT_1_14,
      new VersionRegistry(std::vector<VillagerProfession>({VillagerProfession::NONE, VillagerProfession::ARMORER, VillagerProfession::BUTCHER,
        VillagerProfession::CARTOGRAPHER, VillagerProfession::CLERIC, VillagerProfession::FARMER, VillagerProfession::FISHERMAN,
        VillagerProfession::FLETCHER, VillagerProfession::LEATHERWORKER, VillagerProfession::LIBRARIAN, VillagerProfession::MASON,
        VillagerProfession::NITWIT, VillagerProfession::SHEPHERD, VillagerProfession::TOOLSMITH, VillagerProfession::WEAPONSMITH})));

    return professionRegistry;
  }

  const EnumRegistry<VillagerType> VILLAGER_TYPE_REGISTRY = GetVillagerTypeRegistry();
  const EnumRegistry<VillagerProfession> VILLAGER_PROFESSION_REGISTRY = GetVillagerProfessionRegistry();

  VillagerData::VillagerData(VillagerType type, VillagerProfession profession, uint32_t level) : type(type), profession(profession), level(level) {
  }

  VillagerType VillagerData::GetType() const {
    return type;
  }

  void VillagerData::SetType(VillagerType newType) {
    VillagerData::type = newType;
  }

  VillagerProfession VillagerData::GetProfession() const {
    return profession;
  }

  void VillagerData::SetProfession(VillagerProfession newProfession) {
    VillagerData::profession = newProfession;
  }

  uint32_t VillagerData::GetLevel() const {
    return level;
  }

  void VillagerData::SetLevel(uint32_t newLevel) {
    VillagerData::level = newLevel;
  }
}