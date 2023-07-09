#pragma once

#include "Entity.hpp"

namespace Ship {

  class LivingEntityMetadata : public EntityMetadata {
   private:
    union {
      struct {
        uint8_t handActive : 1;
        uint8_t activeHand : 1;
        uint8_t inRiptideSpinAttack : 1;
      };

      uint8_t value;
    } handState {};
    float health = 1;
    uint32_t potionEffectColor = 0;
    bool ambientPotionEffect = false;
    uint32_t arrowsCount = 0;
    uint32_t beeStingersCount = 0;
    bool bedLocationPresent = false;
    int bedLocationX = 0;
    int bedLocationY = 0;
    int bedLocationZ = 0;

   public:
    LivingEntityMetadata() = default;
    ~LivingEntityMetadata() override = default;

    static uint8_t MaximumEntries(const ProtocolVersion* version) {
      if (version >= &MinecraftProtocolVersion::MINECRAFT_1_14) {
        if (version >= &MinecraftProtocolVersion::MINECRAFT_1_15) {
          return EntityMetadata::MaximumEntries(version) + 7;
        }
        return EntityMetadata::MaximumEntries(version) + 6;
      }
      return EntityMetadata::MaximumEntries(version) + 5;
    }

    void Read(Metadata* metadata, const ProtocolVersion* version) override {
      EntityMetadata::Read(metadata, version);

      uint8_t currentIndex = EntityMetadata::MaximumEntries(version);
      handState.value = metadata->GetByte(currentIndex).value_or(0);
      health = metadata->GetFloat(currentIndex + 1).value_or(1);
      potionEffectColor = metadata->GetVarInt(currentIndex + 2).value_or(0);
      ambientPotionEffect = metadata->GetBoolean(currentIndex + 3).value_or(false);
      arrowsCount = metadata->GetVarInt(currentIndex + 4).value_or(0);
      if (version >= &MinecraftProtocolVersion::MINECRAFT_1_14) {
        if (version >= &MinecraftProtocolVersion::MINECRAFT_1_15) {
          beeStingersCount = metadata->GetVarInt(currentIndex + 5).value_or(0);
          if (!metadata->GetOptPosition(currentIndex + 6, bedLocationPresent, bedLocationX, bedLocationY, bedLocationZ)) {
            bedLocationPresent = false;
            bedLocationX = bedLocationY = bedLocationZ = 0;
          }
        } else {
          if (!metadata->GetOptPosition(currentIndex + 5, bedLocationPresent, bedLocationX, bedLocationY, bedLocationZ)) {
            bedLocationPresent = false;
            bedLocationX = bedLocationY = bedLocationZ = 0;
          }
        }
      }
    }

    void Write(Metadata* metadata, const ProtocolVersion* version) override {
      EntityMetadata::Write(metadata, version);

      uint8_t currentIndex = EntityMetadata::MaximumEntries(version);

      if (handState.value) {
        metadata->Set(currentIndex, new ByteMetadataEntry(handState.value));
      }

      if (health != 1) {
        metadata->Set(currentIndex + 1, new FloatMetadataEntry(health));
      }

      if (potionEffectColor) {
        metadata->Set(currentIndex + 2, new VarIntMetadataEntry(potionEffectColor));
      }

      if (ambientPotionEffect) {
        metadata->Set(currentIndex + 3, new BooleanMetadataEntry(ambientPotionEffect));
      }

      if (arrowsCount) {
        metadata->Set(currentIndex + 4, new VarIntMetadataEntry(arrowsCount));
      }

      if (version >= &MinecraftProtocolVersion::MINECRAFT_1_14) {
        if (version >= &MinecraftProtocolVersion::MINECRAFT_1_15) {
          if (beeStingersCount) {
            metadata->Set(currentIndex + 5, new VarIntMetadataEntry(beeStingersCount));
          }

          if (bedLocationPresent) {
            metadata->Set(currentIndex + 6, new OptPositionMetadataEntry(bedLocationX, bedLocationY, bedLocationZ));
          }
        } else {
          if (bedLocationPresent) {
            metadata->Set(currentIndex + 5, new OptPositionMetadataEntry(bedLocationX, bedLocationY, bedLocationZ));
          }
        }
      }
    }

    [[nodiscard]] bool IsHandActive() const {
      return handState.handActive;
    }

    void SetHandActive(bool value) {
      handState.handActive = value;
    }

    [[nodiscard]] bool IsOffhandActive() const {
      return handState.activeHand;
    }

    void SetOffhandActive(bool value) {
      handState.activeHand = value;
    }

    [[nodiscard]] bool IsInRiptideSpinAttack() const {
      return handState.inRiptideSpinAttack;
    }

    void SetIsInRiptideSpinAttack(bool value) {
      handState.inRiptideSpinAttack = value;
    }

    [[nodiscard]] float GetHealth() const {
      return health;
    }

    void SetHealth(float value) {
      health = value;
    }

    [[nodiscard]] uint32_t GetPotionEffectColor() const {
      return potionEffectColor;
    }

    void SetPotionEffectColor(uint32_t value) {
      potionEffectColor = value;
    }

    [[nodiscard]] bool IsAmbientPotionEffect() const {
      return ambientPotionEffect;
    }

    void SetAmbientPotionEffect(bool value) {
      ambientPotionEffect = value;
    }

    [[nodiscard]] uint32_t GetArrowsCount() const {
      return arrowsCount;
    }

    void SetArrowsCount(uint32_t value) {
      arrowsCount = value;
    }

    [[nodiscard]] uint32_t GetBeeStingersCount() const {
      return beeStingersCount;
    }

    void SetBeeStingersCount(uint32_t value) {
      beeStingersCount = value;
    }

    [[nodiscard]] bool IsBedLocationPresent() const {
      return bedLocationPresent;
    }

    void SetBedLocationPresent(bool value) {
      bedLocationPresent = value;
    }

    [[nodiscard]] int GetBedLocationX() const {
      return bedLocationX;
    }

    void SetBedLocationX(int value) {
      bedLocationX = value;
    }

    [[nodiscard]] int GetBedLocationY() const {
      return bedLocationY;
    }

    void SetBedLocationY(int value) {
      bedLocationY = value;
    }

    [[nodiscard]] int GetBedLocationZ() const {
      return bedLocationZ;
    }

    void SetBedLocationZ(int value) {
      bedLocationZ = value;
    }
  };
}