#pragma once

#include "LivingEntity.hpp"

namespace Ship {

  class ArmorStandMetadata : public LivingEntityMetadata {
   private:
    union {
      struct {
        uint8_t small : 1;
        uint8_t hasArms : 1;
        uint8_t hasNoBasePlate : 1;
        uint8_t marker : 1;
      };

      uint8_t value;
    } flags {};
    float headRotationX = 0;
    float headRotationY = 0;
    float headRotationZ = 0;
    float bodyRotationX = 0;
    float bodyRotationY = 0;
    float bodyRotationZ = 0;
    float leftArmRotationX = -10;
    float leftArmRotationY = 0;
    float leftArmRotationZ = -10;
    float rightArmRotationX = -15;
    float rightArmRotationY = 0;
    float rightArmRotationZ = 10;
    float leftLegRotationX = -1;
    float leftLegRotationY = 0;
    float leftLegRotationZ = -1;
    float rightLegRotationX = 1;
    float rightLegRotationY = 0;
    float rightLegRotationZ = 1;

   public:
    ArmorStandMetadata() = default;
    ~ArmorStandMetadata() override = default;

    static uint8_t MaximumEntries(const ProtocolVersion* version) {
      return LivingEntityMetadata::MaximumEntries(version) + 7;
    }

    void Read(Metadata* metadata, const ProtocolVersion* version) override {
      LivingEntityMetadata::Read(metadata, version);
      uint8_t currentIndex = LivingEntityMetadata::MaximumEntries(version);

      flags.value = metadata->GetByte(currentIndex).value_or(0);
      if (!metadata->GetRotation(currentIndex + 1, headRotationX, headRotationY, headRotationZ)) {
        headRotationX = headRotationY = headRotationZ = 0;
      }

      if (!metadata->GetRotation(currentIndex + 2, bodyRotationX, bodyRotationY, bodyRotationZ)) {
        bodyRotationX = bodyRotationY = bodyRotationZ = 0;
      }

      if (!metadata->GetRotation(currentIndex + 3, leftArmRotationX, leftArmRotationY, leftArmRotationZ)) {
        leftArmRotationX = leftArmRotationZ = -10;
        leftArmRotationY = 0;
      }

      if (!metadata->GetRotation(currentIndex + 4, rightArmRotationX, rightArmRotationY, rightArmRotationZ)) {
        rightArmRotationX = -15;
        rightArmRotationY = 0;
        rightArmRotationZ = 10;
      }

      if (!metadata->GetRotation(currentIndex + 5, leftLegRotationX, leftLegRotationY, leftLegRotationZ)) {
        leftLegRotationX = leftLegRotationZ = -1;
        leftLegRotationY = 0;
      }

      if (!metadata->GetRotation(currentIndex + 6, rightLegRotationX, rightLegRotationY, rightLegRotationZ)) {
        rightLegRotationX = rightLegRotationZ = 1;
        rightLegRotationY = 0;
      }
    }

    void Write(Metadata* metadata, const ProtocolVersion* version) override {
      LivingEntityMetadata::Write(metadata, version);
      uint8_t currentIndex = LivingEntityMetadata::MaximumEntries(version);

      if (flags.value) {
        metadata->Set(currentIndex, new ByteMetadataEntry(flags.value));
      }

      if (headRotationX != 0 || headRotationY != 0 || headRotationZ != 0) {
        metadata->Set(currentIndex + 1, new RotationMetadataEntry(headRotationX, headRotationY, headRotationZ));
      }

      if (bodyRotationX != 0 || bodyRotationY != 0 || bodyRotationZ != 0) {
        metadata->Set(currentIndex + 2, new RotationMetadataEntry(bodyRotationX, bodyRotationY, bodyRotationZ));
      }

      if (leftArmRotationX != -10 || leftArmRotationY != 0 || leftArmRotationZ != -10) {
        metadata->Set(currentIndex + 3, new RotationMetadataEntry(leftArmRotationX, leftArmRotationY, leftArmRotationZ));
      }

      if (rightArmRotationX != -15 || rightArmRotationY != 0 || rightArmRotationZ != 10) {
        metadata->Set(currentIndex + 4, new RotationMetadataEntry(rightArmRotationX, rightArmRotationY, rightArmRotationZ));
      }

      if (leftLegRotationX != -1 || leftLegRotationY != 0 || leftLegRotationZ != -1) {
        metadata->Set(currentIndex + 5, new RotationMetadataEntry(leftLegRotationX, leftLegRotationY, leftLegRotationZ));
      }

      if (rightLegRotationX != 1 || rightLegRotationY != 0 || rightLegRotationZ != 1) {
        metadata->Set(currentIndex + 6, new RotationMetadataEntry(rightLegRotationX, rightLegRotationY, rightLegRotationZ));
      }
    }

    [[nodiscard]] bool IsSmall() const {
      return flags.small;
    }

    void SetSmall(bool value) {
      flags.small = value;
    }

    [[nodiscard]] bool IsHasArms() const {
      return flags.hasArms;
    }

    void SetHasArms(bool value) {
      flags.hasArms = value;
    }

    [[nodiscard]] bool IsHasNoBasePlate() const {
      return flags.hasNoBasePlate;
    }

    void SetHasNoBasePlate(bool value) {
      flags.hasNoBasePlate = value;
    }

    [[nodiscard]] bool IsMarker() const {
      return flags.marker;
    }

    void SetMarker(bool value) {
      flags.marker = value;
    }

    [[nodiscard]] float GetHeadRotationX() const {
      return headRotationX;
    }

    void SetHeadRotationX(float value) {
      headRotationX = value;
    }

    [[nodiscard]] float GetHeadRotationY() const {
      return headRotationY;
    }

    void SetHeadRotationY(float value) {
      headRotationY = value;
    }

    [[nodiscard]] float GetHeadRotationZ() const {
      return headRotationZ;
    }

    void SetHeadRotationZ(float value) {
      headRotationZ = value;
    }

    [[nodiscard]] float GetBodyRotationX() const {
      return bodyRotationX;
    }

    void SetBodyRotationX(float value) {
      bodyRotationX = value;
    }

    [[nodiscard]] float GetBodyRotationY() const {
      return bodyRotationY;
    }

    void SetBodyRotationY(float value) {
      bodyRotationY = value;
    }

    [[nodiscard]] float GetBodyRotationZ() const {
      return bodyRotationZ;
    }

    void SetBodyRotationZ(float value) {
      bodyRotationZ = value;
    }

    [[nodiscard]] float GetLeftArmRotationX() const {
      return leftArmRotationX;
    }

    void SetLeftArmRotationX(float value) {
      leftArmRotationX = value;
    }

    [[nodiscard]] float GetLeftArmRotationY() const {
      return leftArmRotationY;
    }

    void SetLeftArmRotationY(float value) {
      leftArmRotationY = value;
    }

    [[nodiscard]] float GetLeftArmRotationZ() const {
      return leftArmRotationZ;
    }

    void SetLeftArmRotationZ(float value) {
      leftArmRotationZ = value;
    }

    [[nodiscard]] float GetRightArmRotationX() const {
      return rightArmRotationX;
    }

    void SetRightArmRotationX(float value) {
      rightArmRotationX = value;
    }

    [[nodiscard]] float GetRightArmRotationY() const {
      return rightArmRotationY;
    }

    void SetRightArmRotationY(float value) {
      rightArmRotationY = value;
    }

    [[nodiscard]] float GetRightArmRotationZ() const {
      return rightArmRotationZ;
    }

    void SetRightArmRotationZ(float value) {
      rightArmRotationZ = value;
    }

    [[nodiscard]] float GetLeftLegRotationX() const {
      return leftLegRotationX;
    }

    void SetLeftLegRotationX(float value) {
      leftLegRotationX = value;
    }

    [[nodiscard]] float GetLeftLegRotationY() const {
      return leftLegRotationY;
    }

    void SetLeftLegRotationY(float value) {
      leftLegRotationY = value;
    }

    [[nodiscard]] float GetLeftLegRotationZ() const {
      return leftLegRotationZ;
    }

    void SetLeftLegRotationZ(float value) {
      leftLegRotationZ = value;
    }

    [[nodiscard]] float GetRightLegRotationX() const {
      return rightLegRotationX;
    }

    void SetRightLegRotationX(float value) {
      rightLegRotationX = value;
    }

    [[nodiscard]] float GetRightLegRotationY() const {
      return rightLegRotationY;
    }

    void SetRightLegRotationY(float value) {
      rightLegRotationY = value;
    }

    [[nodiscard]] float GetRightLegRotationZ() const {
      return rightLegRotationZ;
    }

    void SetRightLegRotationZ(float value) {
      rightLegRotationZ = value;
    }
  };
}