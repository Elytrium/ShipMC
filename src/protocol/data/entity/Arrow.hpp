#pragma once

#include "AbstractArrow.hpp"

namespace Ship {

  class ArrowMetadata : public AbstractArrowMetadata {
   private:
    uint32_t color = -1;

   public:
    ArrowMetadata() = default;
    ~ArrowMetadata() override = default;

    [[nodiscard]] static uint8_t MaximumEntries(const ProtocolVersion* version) {
      return AbstractArrowMetadata::MaximumEntries(version) + 1;
    }

    void Read(Metadata* metadata, const ProtocolVersion* version) override {
      AbstractArrowMetadata::Read(metadata, version);

      color = metadata->GetVarInt(AbstractArrowMetadata::MaximumEntries(version)).value_or(-1);
    }

    void Write(Metadata* metadata, const ProtocolVersion* version) override {
      AbstractArrowMetadata::Write(metadata, version);

      if (color != -1) {
        metadata->Set(AbstractArrowMetadata::MaximumEntries(version), new VarIntMetadataEntry(color));
      }
    }

    [[nodiscard]] uint32_t GetColor() const {
      return color;
    }

    void SetColor(uint32_t value) {
      color = value;
    }
  };

  typedef ArrowMetadata TippedArrowMetadata;
}