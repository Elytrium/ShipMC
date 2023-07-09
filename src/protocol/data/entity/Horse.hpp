#pragma once

#include "AbstractHorse.hpp"

namespace Ship {

  class HorseMetadata : public AbstractHorseMetadata {
   private:
    uint32_t variant = 0;
    uint32_t armor = 0;
    
   public:
    HorseMetadata() = default;
    ~HorseMetadata() override = default;

    [[nodiscard]] static uint8_t MaximumEntries(const ProtocolVersion* version) {
      if (version <= &MinecraftProtocolVersion::MINECRAFT_1_12_2) {
        return AbstractHorseMetadata::MaximumEntries(version) + 2;
      }
      return AbstractHorseMetadata::MaximumEntries(version) + 1;
    }

    void Read(Metadata* metadata, const ProtocolVersion* version) override {
      AbstractHorseMetadata::Read(metadata, version);
      uint8_t currentIndex = AbstractHorseMetadata::MaximumEntries(version);

      variant = metadata->GetVarInt(currentIndex).value_or(0);
      if (version <= &MinecraftProtocolVersion::MINECRAFT_1_12_2) {
        armor = metadata->GetVarInt(currentIndex + 1).value_or(0);
      }
    }

    void Write(Metadata* metadata, const ProtocolVersion* version) override {
      AbstractHorseMetadata::Write(metadata, version);
      uint8_t currentIndex = AbstractHorseMetadata::MaximumEntries(version);

      if (variant) {
        metadata->Set(currentIndex, new VarIntMetadataEntry(variant));
      }

      if (version <= &MinecraftProtocolVersion::MINECRAFT_1_12_2) {
        if (armor) {
          metadata->Set(currentIndex + 1, new VarIntMetadataEntry(armor));
        }
      }
    }

    [[nodiscard]] uint32_t GetVariant() const {
      return variant;
    }

    void SetVariant(uint32_t value) {
      variant = value;
    }

    [[nodiscard]] uint32_t GetArmor() const {
      return armor;
    }

    void SetArmor(uint32_t value) {
      armor = value;
    }
  };
}