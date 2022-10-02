#pragma once

#include "Animal.hpp"

namespace Ship {

  class SheepMetadata : public AnimalMetadata {
   private:
    union {
      struct {
        uint8_t color : 4;
        uint8_t sheared : 1;
      };

      uint8_t value;
    } bitfield {};

   public:
    SheepMetadata() = default;
    ~SheepMetadata() override = default;

    [[nodiscard]] static uint8_t MaximumEntries(const ProtocolVersion* version) {
      return AnimalMetadata::MaximumEntries(version) + 1;
    }

    void Read(Metadata* metadata, const ProtocolVersion* version) override {
      AnimalMetadata::Read(metadata, version);

      bitfield.value = metadata->GetByte(AnimalMetadata::MaximumEntries(version)).value_or(0);
    }

    void Write(Metadata* metadata, const ProtocolVersion* version) override {
      AnimalMetadata::Write(metadata, version);

      if (bitfield.value) {
        metadata->Set(AnimalMetadata::MaximumEntries(version), new ByteMetadataEntry(bitfield.value));
      }
    }

    [[nodiscard]] uint8_t GetColor() const {
      return bitfield.color;
    }

    void SetColor(uint8_t value) {
      bitfield.color = value & 0xF;
    }

    [[nodiscard]] bool IsSheared() const {
      return bitfield.sheared;
    }

    void SetSheared(bool value) {
      bitfield.sheared = value;
    }
  };
}