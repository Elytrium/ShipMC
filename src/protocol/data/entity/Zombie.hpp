#pragma once

#include "Monster.hpp"

namespace Ship {

  class ZombieMetadata : public MonsterMetadata {
   private:
    bool baby = false;
    uint32_t type = 0; // Unused
    bool handsHeldUp = false;
    bool becomingDrowned = false;

   public:
    ZombieMetadata() = default;
    ~ZombieMetadata() override = default;

    static uint8_t MaximumEntries(const ProtocolVersion* version) {
      if (version >= &ProtocolVersion::MINECRAFT_1_13 && version <= &ProtocolVersion::MINECRAFT_1_13_2) {
        return MonsterMetadata::MaximumEntries(version) + 4;
      }
      return MonsterMetadata::MaximumEntries(version) + 3;
    }

    void Read(Metadata* metadata, const ProtocolVersion* version) override {
      MonsterMetadata::Read(metadata, version);
      uint8_t currentIndex = MonsterMetadata::MaximumEntries(version);

      baby = metadata->GetBoolean(currentIndex).value_or(false);
      type = metadata->GetVarInt(currentIndex + 1).value_or(0);
      if (version <= &ProtocolVersion::MINECRAFT_1_12_2) {
        handsHeldUp = metadata->GetBoolean(currentIndex + 2).value_or(false);
      } else if (version <= &ProtocolVersion::MINECRAFT_1_13_2) {
        handsHeldUp = metadata->GetBoolean(currentIndex + 2).value_or(false);
        becomingDrowned = metadata->GetBoolean(currentIndex + 3).value_or(false);
      } else {
        becomingDrowned = metadata->GetBoolean(currentIndex + 2).value_or(false);
      }
    }

    void Write(Metadata* metadata, const ProtocolVersion* version) override {
      MonsterMetadata::Write(metadata, version);
      uint8_t currentIndex = MonsterMetadata::MaximumEntries(version);

      if (baby) {
        metadata->Set(currentIndex, new BooleanMetadataEntry(baby));
      }

      if (type) {
        metadata->Set(currentIndex + 1, new VarIntMetadataEntry(type));
      }

      if (version <= &ProtocolVersion::MINECRAFT_1_12_2) {
        if (handsHeldUp) {
          metadata->Set(currentIndex + 2, new BooleanMetadataEntry(handsHeldUp));
        }
      } else if (version <= &ProtocolVersion::MINECRAFT_1_13_2) {
        if (handsHeldUp) {
          metadata->Set(currentIndex + 2, new BooleanMetadataEntry(handsHeldUp));
        }

        if (becomingDrowned) {
          metadata->Set(currentIndex + 3, new BooleanMetadataEntry(becomingDrowned));
        }
      } else {
        if (becomingDrowned) {
          metadata->Set(currentIndex + 2, new BooleanMetadataEntry(becomingDrowned));
        }
      }
    }

    [[nodiscard]] bool IsBaby() const {
      return baby;
    }

    void SetBaby(bool value) {
      baby = value;
    }

    [[nodiscard]] uint32_t GetType() const {
      return type;
    }

    void SetType(uint32_t value) {
      type = value;
    }

    [[nodiscard]] bool AreHandsHeldUp() const {
      return handsHeldUp;
    }

    void SetHandsHeldUp(bool value) {
      handsHeldUp = value;
    }

    [[nodiscard]] bool IsBecomingDrowned() const {
      return becomingDrowned;
    }

    void SetBecomingDrowned(bool value) {
      becomingDrowned = value;
    }
  };
}