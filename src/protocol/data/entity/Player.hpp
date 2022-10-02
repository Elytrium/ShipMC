#pragma once

#include "LivingEntity.hpp"

namespace Ship {

  class PlayerMetadata : public LivingEntityMetadata {
   private:
    float additionalHearts = 0;
    uint32_t score = 0;
    union {
      struct {
        uint8_t capeEnabled : 1;
        uint8_t jacketEnabled : 1;
        uint8_t leftSleeveEnabled : 1;
        uint8_t rightSleeveEnabled : 1;
        uint8_t leftLegEnabled : 1;
        uint8_t rightLegEnabled : 1;
        uint8_t hatEnabled : 1;
      };

      uint8_t value;
    } displayedSkinParts {};
    uint8_t mainHand = 1;
    NBT* leftShoulderEntity = nullptr;
    NBT* rightShoulderEntity = nullptr;

   public:
    PlayerMetadata() = default;
    ~PlayerMetadata() override = default;

    static uint8_t MaximumEntries(const ProtocolVersion* version) {
      return LivingEntityMetadata::MaximumEntries(version) + 6;
    }

    void Read(Metadata* metadata, const ProtocolVersion* version) override {
      LivingEntityMetadata::Read(metadata, version);
      delete leftShoulderEntity;
      delete rightShoulderEntity;

      uint8_t currentIndex = LivingEntityMetadata::MaximumEntries(version);
      additionalHearts = metadata->GetFloat(currentIndex).value_or(0);
      score = metadata->GetVarInt(currentIndex + 1).value_or(0);
      displayedSkinParts.value = metadata->GetByte(currentIndex + 2).value_or(0);
      mainHand = metadata->GetByte(currentIndex + 3).value_or(1);
      leftShoulderEntity = metadata->GetNBT(currentIndex + 4).value_or(nullptr);
      rightShoulderEntity = metadata->GetNBT(currentIndex + 5).value_or(nullptr);
    }

    void Write(Metadata* metadata, const ProtocolVersion* version) override {
      LivingEntityMetadata::Write(metadata, version);
      uint8_t currentIndex = LivingEntityMetadata::MaximumEntries(version);

      if (additionalHearts != 0) {
        metadata->Set(currentIndex, new FloatMetadataEntry(additionalHearts));
      }

      if (score) {
        metadata->Set(currentIndex + 1, new VarIntMetadataEntry(score));
      }

      if (displayedSkinParts.value) {
        metadata->Set(currentIndex + 2, new ByteMetadataEntry(displayedSkinParts.value));
      }

      if (mainHand != 1) {
        metadata->Set(currentIndex + 3, new ByteMetadataEntry(mainHand));
      }

      if (leftShoulderEntity) {
        metadata->Set(currentIndex + 4, new NBTMetadataEntry(leftShoulderEntity));
      }

      if (rightShoulderEntity) {
        metadata->Set(currentIndex + 5, new NBTMetadataEntry(rightShoulderEntity));
      }
    }

    [[nodiscard]] float GetAdditionalHearts() const {
      return additionalHearts;
    }

    void SetAdditionalHearts(float value) {
      additionalHearts = value;
    }

    [[nodiscard]] uint32_t GetScore() const {
      return score;
    }

    void SetScore(uint32_t value) {
      score = value;
    }

    [[nodiscard]] uint8_t GetDisplayedSkinParts() const {
      return displayedSkinParts.value;
    }

    void SetDisplayedSkinParts(uint8_t value) {
      displayedSkinParts.value = value;
    }

    [[nodiscard]] bool IsCapeEnabled() const {
      return displayedSkinParts.capeEnabled;
    }

    void SetCapeEnabled(bool value) {
      displayedSkinParts.capeEnabled = value;
    }

    [[nodiscard]] bool IsJackedEnabled() const {
      return displayedSkinParts.jacketEnabled;
    }

    void SetJackedEnabled(bool value) {
      displayedSkinParts.jacketEnabled = value;
    }

    [[nodiscard]] bool IsLeftSleeveEnabled() const {
      return displayedSkinParts.leftSleeveEnabled;
    }

    void SetLeftSleeveEnabled(bool value) {
      displayedSkinParts.leftSleeveEnabled = value;
    }

    [[nodiscard]] bool IsRightSleeveEnabled() const {
      return displayedSkinParts.rightSleeveEnabled;
    }

    void SetRightSleeveEnabled(bool value) {
      displayedSkinParts.rightSleeveEnabled = value;
    }

    [[nodiscard]] bool IsLeftLegEnabled() const {
      return displayedSkinParts.leftLegEnabled;
    }

    void SetLeftLegEnabled(bool value) {
      displayedSkinParts.leftLegEnabled = value;
    }

    [[nodiscard]] bool IsRightLegEnabled() const {
      return displayedSkinParts.rightLegEnabled;
    }

    void SetRightLegEnabled(bool value) {
      displayedSkinParts.rightLegEnabled = value;
    }

    [[nodiscard]] bool IsHatEnabled() const {
      return displayedSkinParts.hatEnabled;
    }

    void SetHatEnabled(bool value) {
      displayedSkinParts.hatEnabled = value;
    }

    [[nodiscard]] uint8_t GetMainHand() const {
      return mainHand;
    }

    void SetMainHand(uint8_t value) {
      mainHand = value;
    }

    [[nodiscard]] NBT* GetLeftShoulderEntity() const {
      return leftShoulderEntity;
    }

    void SetLeftShoulderEntity(NBT* value) {
      leftShoulderEntity = value;
    }

    [[nodiscard]] NBT* GetRightShoulderEntity() const {
      return rightShoulderEntity;
    }

    void SetRightShoulderEntity(NBT* value) {
      rightShoulderEntity = value;
    }
  };
}