#pragma once

#include "TameableAnimal.hpp"

namespace Ship {

  class WolfMetadata : public TameableAnimalMetadata {
   private:
    float damageTaken = 1;
    bool begging = false;
    uint32_t collarColor = 14;
    uint32_t angerTime = 0;

   public:
    WolfMetadata() = default;
    ~WolfMetadata() override = default;

    static uint8_t MaximumEntries(const ProtocolVersion* version) {
      if (version >= &ProtocolVersion::MINECRAFT_1_15 && version <= &ProtocolVersion::MINECRAFT_1_15_2) {
        return TameableAnimalMetadata::MaximumEntries(version) + 2;
      }
      return TameableAnimalMetadata::MaximumEntries(version) + 3;
    }

    void Read(Metadata* metadata, const ProtocolVersion* version) override {
      TameableAnimalMetadata::Read(metadata, version);
      uint8_t currentIndex = TameableAnimalMetadata::MaximumEntries(version);

      if (version <= &ProtocolVersion::MINECRAFT_1_12_2) {
        damageTaken = metadata->GetFloat(currentIndex).value_or(1);
        begging = metadata->GetBoolean(currentIndex + 1).value_or(false);
        collarColor = metadata->GetVarInt(currentIndex + 2).value_or(14);
        angerTime = 0;
      } else {
        begging = metadata->GetBoolean(currentIndex).value_or(false);
        collarColor = metadata->GetVarInt(currentIndex + 1).value_or(14);
        if (version >= &ProtocolVersion::MINECRAFT_1_16_2) {
          angerTime = metadata->GetVarInt(currentIndex + 2).value_or(0);
        }
        damageTaken = 1;
      }
    }

    void Write(Metadata* metadata, const ProtocolVersion* version) override {
      TameableAnimalMetadata::Write(metadata, version);
      uint8_t currentIndex = TameableAnimalMetadata::MaximumEntries(version);

      if (version <= &ProtocolVersion::MINECRAFT_1_12_2) {
        if (damageTaken != 1) {
          metadata->Set(currentIndex, new FloatMetadataEntry(damageTaken));
        }

        if (begging) {
          metadata->Set(currentIndex + 1, new BooleanMetadataEntry(begging));
        }

        if (collarColor != 14) {
          metadata->Set(currentIndex + 2, new VarIntMetadataEntry(collarColor));
        }
      } else {
        if (begging) {
          metadata->Set(currentIndex, new BooleanMetadataEntry(begging));
        }

        if (collarColor != 14) {
          metadata->Set(currentIndex + 1, new VarIntMetadataEntry(collarColor));
        }

        if (version >= &ProtocolVersion::MINECRAFT_1_16_2) {
          if (angerTime) {
            metadata->Set(currentIndex + 2, new VarIntMetadataEntry(angerTime));
          }
        }
      }
    }

    [[nodiscard]] float GetDamageTaken() const {
      return damageTaken;
    }

    void SetDamageTaken(float value) {
      damageTaken = value;
    }

    [[nodiscard]] bool IsBegging() const {
      return begging;
    }

    void SetBegging(bool value) {
      begging = value;
    }

    [[nodiscard]] uint32_t GetCollarColor() const {
      return collarColor;
    }

    void SetCollarColor(uint32_t value) {
      collarColor = value;
    }

    [[nodiscard]] uint32_t GetAngerTime() const {
      return angerTime;
    }

    void SetAngerTime(uint32_t value) {
      angerTime = value;
    }
  };
}