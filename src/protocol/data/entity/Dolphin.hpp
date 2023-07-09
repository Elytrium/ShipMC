#pragma once

#include "WaterAnimal.hpp"

namespace Ship {

  class DolphinMetadata : public WaterAnimalMetadata {
   private:
    int treasureX = 0;
    int treasureY = 0;
    int treasureZ = 0;
    bool canFindTreasure = false;
    bool hasFish = false;
    uint32_t moistureLevel = 2400;

   public:
    DolphinMetadata() = default;
    ~DolphinMetadata() override = default;

    static uint8_t MaximumEntries(const ProtocolVersion* version) {
      return WaterAnimalMetadata::MaximumEntries(version) + 3;
    }

    void Read(Metadata* metadata, const ProtocolVersion* version) override {
      WaterAnimalMetadata::Read(metadata, version);
      uint8_t currentIndex = WaterAnimalMetadata::MaximumEntries(version);

      if (!metadata->GetPosition(currentIndex, treasureX, treasureY, treasureZ)) {
        treasureX = treasureY = treasureZ = 0;
      }

      if (version <= &MinecraftProtocolVersion::MINECRAFT_1_16_4) {
        canFindTreasure = metadata->GetBoolean(currentIndex + 1).value_or(false);
        hasFish = metadata->GetBoolean(currentIndex + 2).value_or(false);
        moistureLevel = 2400;
      } else {
        hasFish = metadata->GetBoolean(currentIndex + 1).value_or(false);
        moistureLevel = metadata->GetVarInt(currentIndex + 2).value_or(2400);
        canFindTreasure = false;
      }
    }

    void Write(Metadata* metadata, const ProtocolVersion* version) override {
      WaterAnimalMetadata::Write(metadata, version);
      uint8_t currentIndex = WaterAnimalMetadata::MaximumEntries(version);

      if (treasureX || treasureY || treasureZ) {
        metadata->Set(currentIndex, new PositionMetadataEntry(treasureX, treasureY, treasureZ));
      }

      if (version <= &MinecraftProtocolVersion::MINECRAFT_1_16_4) {
        if (canFindTreasure) {
          metadata->Set(currentIndex + 1, new BooleanMetadataEntry(canFindTreasure));
        }

        if (hasFish) {
          metadata->Set(currentIndex + 2, new BooleanMetadataEntry(hasFish));
        }
      } else {
        if (hasFish) {
          metadata->Set(currentIndex + 1, new BooleanMetadataEntry(hasFish));
        }

        if (moistureLevel != 2400) {
          metadata->Set(currentIndex + 2, new VarIntMetadataEntry(moistureLevel));
        }
      }
    }

    [[nodiscard]] int GetTreasureX() const {
      return treasureX;
    }

    void SetTreasureX(int value) {
      treasureX = value;
    }

    [[nodiscard]] int GetTreasureY() const {
      return treasureY;
    }

    void SetTreasureY(int value) {
      treasureY = value;
    }

    [[nodiscard]] int GetTreasureZ() const {
      return treasureZ;
    }

    void SetTreasureZ(int value) {
      treasureZ = value;
    }

    [[nodiscard]] bool IsCanFindTreasure() const {
      return canFindTreasure;
    }

    void SetCanFindTreasure(bool value) {
      canFindTreasure = value;
    }

    [[nodiscard]] bool IsHasFish() const {
      return hasFish;
    }

    void SetHasFish(bool value) {
      hasFish = value;
    }

    [[nodiscard]] uint32_t GetMoistureLevel() const {
      return moistureLevel;
    }

    void SetMoistureLevel(uint32_t value) {
      moistureLevel = value;
    }
  };
}