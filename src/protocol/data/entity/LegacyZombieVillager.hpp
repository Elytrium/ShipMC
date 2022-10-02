#pragma once

#include "Zombie.hpp"
#include "LegacyVillager.hpp"

namespace Ship {

  class LegacyZombieVillagerMetadata : public ZombieMetadata {
   private:
    bool converting = false;
    LegacyVillagerProfession profession = LegacyVillagerProfession::FARMER;

   public:
    LegacyZombieVillagerMetadata() = default;
    ~LegacyZombieVillagerMetadata() override = default;

    [[nodiscard]] static uint8_t MaximumEntries(const ProtocolVersion* version) {
      return ZombieMetadata::MaximumEntries(version) + 2;
    }

    void Read(Metadata* metadata, const ProtocolVersion* version) override {
      ZombieMetadata::Read(metadata, version);
      uint8_t currentIndex = ZombieMetadata::MaximumEntries(version);

      converting = metadata->GetBoolean(currentIndex).value_or(false);
      profession = (LegacyVillagerProfession) metadata->GetVarInt(currentIndex + 1).value_or(0);
    }

    void Write(Metadata* metadata, const ProtocolVersion* version) override {
      ZombieMetadata::Write(metadata, version);
      uint8_t currentIndex = ZombieMetadata::MaximumEntries(version);

      if (converting) {
        metadata->Set(currentIndex, new BooleanMetadataEntry(converting));
      }

      if (profession != LegacyVillagerProfession::FARMER) {
        metadata->Set(currentIndex + 1, new VarIntMetadataEntry((uint32_t) profession));
      }
    }
  };
}