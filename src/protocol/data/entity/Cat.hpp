#pragma once

#include "TameableAnimal.hpp"

namespace Ship {

  class CatMetadata : public TameableAnimalMetadata {
   private:
    CatVariant type = CatVariant::BLACK;
    bool lying = false;
    bool relaxed = false;
    uint32_t collarColor = 14;

   public:
    CatMetadata() = default;
    ~CatMetadata() override = default;

    static uint8_t MaximumEntries(const ProtocolVersion* version) {
      return TameableAnimalMetadata::MaximumEntries(version) + 4;
    }

    void Read(Metadata* metadata, const ProtocolVersion* version) override {
      TameableAnimalMetadata::Read(metadata, version);
      uint8_t currentIndex = TameableAnimalMetadata::MaximumEntries(version);

      type = (CatVariant) metadata->GetVarInt(currentIndex).value_or(1);
      lying = metadata->GetBoolean(currentIndex + 1).value_or(false);
      relaxed = metadata->GetBoolean(currentIndex + 2).value_or(false);
      collarColor = metadata->GetVarInt(currentIndex + 3).value_or(14);
    }

    void Write(Metadata* metadata, const ProtocolVersion* version) override {
      TameableAnimalMetadata::Write(metadata, version);
      uint8_t currentIndex = TameableAnimalMetadata::MaximumEntries(version);

      if (type != CatVariant::BLACK) {
        metadata->Set(currentIndex, new VarIntMetadataEntry((uint32_t) type));
      }

      if (lying) {
        metadata->Set(currentIndex + 1, new BooleanMetadataEntry(lying));
      }

      if (relaxed) {
        metadata->Set(currentIndex + 2, new BooleanMetadataEntry(relaxed));
      }

      if (collarColor != 14) {
        metadata->Set(currentIndex + 3, new VarIntMetadataEntry(collarColor));
      }
    }

    [[nodiscard]] CatVariant GetType() const {
      return type;
    }

    void SetType(CatVariant value) {
      type = value;
    }

    [[nodiscard]] bool IsLying() const {
      return lying;
    }

    void SetLying(bool value) {
      lying = value;
    }

    [[nodiscard]] bool IsRelaxed() const {
      return relaxed;
    }

    void SetRelaxed(bool value) {
      relaxed = value;
    }

    [[nodiscard]] uint32_t GetCollarColor() const {
      return collarColor;
    }

    void SetCollarColor(uint32_t value) {
      collarColor = value;
    }
  };
}