#pragma once

#include "AgeableMob.hpp"

namespace Ship {

  enum class LegacyVillagerProfession {
    FARMER = 0,
    LIBRARIAN = 1,
    PRIEST = 2,
    BLACKSMITH = 3,
    BUTCHER = 4,
    NITWIT = 5,
  };

  class LegacyVillagerMetadata : public AgeableMobMetadata {
   private:
    LegacyVillagerProfession profession = LegacyVillagerProfession::FARMER;

   public:
    LegacyVillagerMetadata() = default;
    ~LegacyVillagerMetadata() override = default;

    [[nodiscard]] static uint8_t MaximumEntries(const ProtocolVersion* version) {
      return AgeableMobMetadata::MaximumEntries(version) + 1;
    }

    void Read(Metadata* metadata, const ProtocolVersion* version) override {
      AgeableMobMetadata::Read(metadata, version);

      profession = (LegacyVillagerProfession) metadata->GetVarInt(AgeableMobMetadata::MaximumEntries(version)).value_or(0);
    }

    void Write(Metadata* metadata, const ProtocolVersion* version) override {
      AgeableMobMetadata::Write(metadata, version);

      if (profession != LegacyVillagerProfession::FARMER) {
        metadata->Set(AgeableMobMetadata::MaximumEntries(version), new VarIntMetadataEntry((uint32_t) profession));
      }
    }
  };
}