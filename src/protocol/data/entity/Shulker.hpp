#pragma once

#include "AbstractGolem.hpp"

namespace Ship {

  class ShulkerMetadata : public AbstractGolemMetadata {
   private:
    Direction attachFace = Direction::DOWN;
    bool attachmentPresent = false;
    int attachmentX = 0;
    int attachmentY = 0;
    int attachmentZ = 0;
    uint8_t shieldHeight = 0;
    uint8_t color = 10;

   public:
    ShulkerMetadata() = default;
    ~ShulkerMetadata() override = default;

    [[nodiscard]] static uint8_t MaximumEntries(const ProtocolVersion* version) {
      return AbstractGolemMetadata::MaximumEntries(version) + 4;
    }

    void Read(Metadata* metadata, const ProtocolVersion* version) override {
      AbstractGolemMetadata::Read(metadata, version);
      uint8_t currentIndex = AbstractGolemMetadata::MaximumEntries(version);

      attachFace = metadata->GetDirection(currentIndex).value_or(Direction::DOWN);

      if (!metadata->GetOptPosition(currentIndex + 1, attachmentPresent, attachmentX, attachmentY, attachmentZ)) {
        attachmentPresent = false;
        attachmentX = attachmentY = attachmentZ = 0;
      }

      shieldHeight = metadata->GetByte(currentIndex + 2).value_or(0);
      color = metadata->GetByte(currentIndex + 3).value_or(10);
    }

    void Write(Metadata* metadata, const ProtocolVersion* version) override {
      AbstractGolemMetadata::Write(metadata, version);
      uint8_t currentIndex = AbstractGolemMetadata::MaximumEntries(version);

      if (attachFace != Direction::DOWN) {
        metadata->Set(currentIndex, new DirectionMetadataEntry(attachFace));
      }

      if (attachmentPresent) {
        metadata->Set(currentIndex + 1, new OptPositionMetadataEntry(attachmentX, attachmentY, attachmentZ));
      }

      if (shieldHeight) {
        metadata->Set(currentIndex + 2, new ByteMetadataEntry(shieldHeight));
      }

      if (color != 10) {
        metadata->Set(currentIndex + 3, new ByteMetadataEntry(color));
      }
    }

    [[nodiscard]] Direction GetAttachFace() const {
      return attachFace;
    }

    void SetAttachFace(Direction value) {
      attachFace = value;
    }

    [[nodiscard]] bool IsAttachmentPresent() const {
      return attachmentPresent;
    }

    void SetAttachmentPresent(bool value) {
      attachmentPresent = value;
    }

    [[nodiscard]] int GetAttachmentX() const {
      return attachmentX;
    }

    void SetAttachmentX(int value) {
      attachmentX = value;
    }

    [[nodiscard]] int GetAttachmentY() const {
      return attachmentY;
    }

    void SetAttachmentY(int value) {
      attachmentY = value;
    }

    [[nodiscard]] int GetAttachmentZ() const {
      return attachmentZ;
    }

    void SetAttachmentZ(int value) {
      attachmentZ = value;
    }

    [[nodiscard]] uint8_t GetShieldHeight() const {
      return shieldHeight;
    }

    void SetShieldHeight(uint8_t value) {
      shieldHeight = value;
    }

    [[nodiscard]] uint8_t GetColor() const {
      return color;
    }

    void SetColor(uint8_t value) {
      color = value;
    }
  };
}