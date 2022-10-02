#pragma once

#include "Entity.hpp"

namespace Ship {

  class AbstractMinecartMetadata : public EntityMetadata {
   private:
    uint32_t shakingPower = 0;
    uint32_t shakingDirection = 1;
    float shakingMultiplier = 0;
    uint32_t customBlock = 0;
    uint32_t customBlockY = 6;
    bool showCustomBlock = false;

   public:
    AbstractMinecartMetadata() = default;
    ~AbstractMinecartMetadata() override = default;

    [[nodiscard]] static uint8_t MaximumEntries(const ProtocolVersion* version) {
      return EntityMetadata::MaximumEntries(version) + 6;
    }

    void Read(Metadata* metadata, const ProtocolVersion* version) override {
      EntityMetadata::Read(metadata, version);
      uint8_t currentIndex = EntityMetadata::MaximumEntries(version);

      shakingPower = metadata->GetVarInt(currentIndex).value_or(0);
      shakingDirection = metadata->GetVarInt(currentIndex + 1).value_or(1);
      shakingMultiplier = metadata->GetFloat(currentIndex + 2).value_or(0);
      customBlock = metadata->GetVarInt(currentIndex + 3).value_or(0);
      customBlockY = metadata->GetVarInt(currentIndex + 4).value_or(6);
      showCustomBlock = metadata->GetBoolean(currentIndex + 5).value_or(false);
    }

    void Write(Metadata* metadata, const ProtocolVersion* version) override {
      EntityMetadata::Write(metadata, version);
      uint8_t currentIndex = EntityMetadata::MaximumEntries(version);

      if (shakingPower) {
        metadata->Set(currentIndex, new VarIntMetadataEntry(shakingPower));
      }

      if (shakingDirection != 1) {
        metadata->Set(currentIndex + 1, new VarIntMetadataEntry(shakingDirection));
      }

      if (shakingMultiplier != 0) {
        metadata->Set(currentIndex + 2, new FloatMetadataEntry(shakingMultiplier));
      }

      if (customBlock) {
        metadata->Set(currentIndex + 3, new VarIntMetadataEntry(customBlock));
      }

      if (customBlockY != 6) {
        metadata->Set(currentIndex + 4, new VarIntMetadataEntry(customBlockY));
      }

      if (showCustomBlock) {
        metadata->Set(currentIndex + 5, new BooleanMetadataEntry(showCustomBlock));
      }
    }

    [[nodiscard]] uint32_t GetShakingPower() const {
      return shakingPower;
    }

    void SetShakingPower(uint32_t value) {
      shakingPower = value;
    }

    [[nodiscard]] uint32_t GetShakingDirection() const {
      return shakingDirection;
    }

    void SetShakingDirection(uint32_t value) {
      shakingDirection = value;
    }

    [[nodiscard]] float GetShakingMultiplier() const {
      return shakingMultiplier;
    }

    void SetShakingMultiplier(float value) {
      shakingMultiplier = value;
    }

    [[nodiscard]] uint32_t GetCustomBlock() const {
      return customBlock;
    }

    void SetCustomBlock(uint32_t value) {
      customBlock = value;
    }

    [[nodiscard]] uint32_t GetCustomBlockY() const {
      return customBlockY;
    }

    void SetCustomBlockY(uint32_t value) {
      customBlockY = value;
    }

    [[nodiscard]] bool IsShowCustomBlock() const {
      return showCustomBlock;
    }

    void SetShowCustomBlock(bool value) {
      showCustomBlock = value;
    }
  };
}