#pragma once

#include "Zombie.hpp"

namespace Ship {

  class ZombieVillagerMetadata : public ZombieMetadata {
   private:
    bool converting = false;
    VillagerType type = VillagerType::PLAINS;
    VillagerProfession profession = VillagerProfession::NONE;
    uint32_t level = 1;

   public:
    ZombieVillagerMetadata() = default;
    ~ZombieVillagerMetadata() override = default;

    static uint8_t MaximumEntries(const ProtocolVersion* version) {
      return ZombieMetadata::MaximumEntries(version) + 2;
    }

    void Read(Metadata* metadata, const ProtocolVersion* version) override {
      ZombieMetadata::Read(metadata, version);
      uint8_t currentIndex = ZombieMetadata::MaximumEntries(version);

      converting = metadata->GetBoolean(currentIndex).value_or(false);
      if (!metadata->GetVillagerData(currentIndex + 1, type, profession, level)) {
        type = VillagerType::PLAINS;
        profession = VillagerProfession::NONE;
        level = 1;
      }
    }

    void Write(Metadata* metadata, const ProtocolVersion* version) override {
      ZombieMetadata::Write(metadata, version);
      uint8_t currentIndex = ZombieMetadata::MaximumEntries(version);

      if (converting) {
        metadata->Set(currentIndex, new BooleanMetadataEntry(converting));
      }

      if (type != VillagerType::PLAINS || profession != VillagerProfession::NONE || level != 1) {
        metadata->Set(currentIndex + 1, new VillagerDataMetadataEntry(type, profession, level));
      }
    }

    [[nodiscard]] bool IsConverting() const {
      return converting;
    }

    void SetConverting(bool value) {
      converting = value;
    }

    [[nodiscard]] VillagerType GetVillagerType() const {
      return type;
    }

    void SetVillagerType(VillagerType value) {
      type = value;
    }

    [[nodiscard]] VillagerProfession GetProfession() const {
      return profession;
    }

    void SetProfession(VillagerProfession value) {
      profession = value;
    }

    [[nodiscard]] uint32_t GetLevel() const {
      return level;
    }

    void SetLevel(uint32_t value) {
      level = value;
    }
  };
}