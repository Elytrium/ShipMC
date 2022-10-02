#pragma once

#include "Entity.hpp"

namespace Ship {

  enum class BoatType {
    OAK = 0,
    SPRUCE = 1,
    BIRCH = 2,
    JUNGLE = 3,
    ACACIA = 4,
    DARK_OAK = 5,
  };

  class BoatMetadata : public EntityMetadata {
   private:
    uint32_t lastHitTime = 0;
    uint32_t forwardDirection = 1;
    float damageTaken = 0;
    BoatType type = BoatType::OAK;
    bool leftPaddleTurning = false;
    bool rightPaddleTurning = false;
    uint32_t splashTimer = 0;

   public:
    BoatMetadata() = default;
    ~BoatMetadata() override = default;

    [[nodiscard]] static uint8_t MaximumEntries(const ProtocolVersion* version) {
      if (version >= &ProtocolVersion::MINECRAFT_1_13) {
        return EntityMetadata::MaximumEntries(version) + 7;
      }
      return EntityMetadata::MaximumEntries(version) + 6;
    }

    void Read(Metadata* metadata, const ProtocolVersion* version) override {
      EntityMetadata::Read(metadata, version);

      uint8_t currentIndex = EntityMetadata::MaximumEntries(version);
      lastHitTime = metadata->GetVarInt(currentIndex).value_or(0);
      forwardDirection = metadata->GetVarInt(currentIndex + 1).value_or(1);
      damageTaken = metadata->GetFloat(currentIndex + 2).value_or(0);
      type = (BoatType) metadata->GetVarInt(currentIndex + 3).value_or(0);
      leftPaddleTurning = metadata->GetBoolean(currentIndex + 4).value_or(false);
      rightPaddleTurning = metadata->GetBoolean(currentIndex + 5).value_or(false);

      if (version >= &ProtocolVersion::MINECRAFT_1_13) {
        splashTimer = metadata->GetVarInt(currentIndex + 6).value_or(0);
      }
    }

    void Write(Metadata* metadata, const ProtocolVersion* version) override {
      EntityMetadata::Write(metadata, version);

      uint8_t currentIndex = EntityMetadata::MaximumEntries(version);

      if (lastHitTime) {
        metadata->Set(currentIndex, new VarIntMetadataEntry(lastHitTime));
      }

      if (forwardDirection != 1) {
        metadata->Set(currentIndex + 1, new VarIntMetadataEntry(forwardDirection));
      }

      if (damageTaken != 0) {
        metadata->Set(currentIndex + 2, new FloatMetadataEntry(damageTaken));
      }

      if (type != BoatType::OAK) {
        metadata->Set(currentIndex + 3, new VarIntMetadataEntry((uint32_t) type));
      }

      if (leftPaddleTurning) {
        metadata->Set(currentIndex + 4, new BooleanMetadataEntry(leftPaddleTurning));
      }

      if (rightPaddleTurning) {
        metadata->Set(currentIndex + 5, new BooleanMetadataEntry(rightPaddleTurning));
      }

      if (version >= &ProtocolVersion::MINECRAFT_1_13) {
        if (splashTimer) {
          metadata->Set(currentIndex + 6, new VarIntMetadataEntry(splashTimer));
        }
      }
    }

    [[nodiscard]] uint32_t GetLastHitTime() const {
      return lastHitTime;
    }

    void SetLastHitTime(uint32_t value) {
      lastHitTime = value;
    }

    [[nodiscard]] uint32_t GetForwardDirection() const {
      return forwardDirection;
    }

    void SetForwardDirection(uint32_t value) {
      forwardDirection = value;
    }

    [[nodiscard]] float GetDamageTaken() const {
      return damageTaken;
    }

    void SetDamageTaken(float value) {
      damageTaken = value;
    }

    [[nodiscard]] BoatType GetType() const {
      return type;
    }

    void SetType(BoatType value) {
      type = value;
    }

    [[nodiscard]] bool IsLeftPaddleTurning() const {
      return leftPaddleTurning;
    }

    void SetLeftPaddleTurning(bool value) {
      leftPaddleTurning = value;
    }

    [[nodiscard]] bool IsRightPaddleTurning() const {
      return rightPaddleTurning;
    }

    void SetRightPaddleTurning(bool value) {
      rightPaddleTurning = value;
    }

    [[nodiscard]] uint32_t GetSplashTimer() const {
      return splashTimer;
    }

    void SetSplashTimer(uint32_t value) {
      splashTimer = value;
    }
  };
}