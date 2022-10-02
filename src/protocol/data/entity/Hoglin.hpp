#pragma once

#include "Animal.hpp"

namespace Ship {

  class HoglinMetadata : public AnimalMetadata {
   private:
    bool immuneToZombification = false;

   public:
    HoglinMetadata() = default;
    ~HoglinMetadata() override = default;

    [[nodiscard]] static uint8_t MaximumEntries(const ProtocolVersion* version) {
      return AnimalMetadata::MaximumEntries(version) + 1;
    }

    void Read(Metadata* metadata, const ProtocolVersion* version) override {
      AnimalMetadata::Read(metadata, version);

      immuneToZombification = metadata->GetBoolean(AnimalMetadata::MaximumEntries(version)).value_or(false);
    }

    void Write(Metadata* metadata, const ProtocolVersion* version) override {
      AnimalMetadata::Write(metadata, version);

      if (immuneToZombification) {
        metadata->Set(AnimalMetadata::MaximumEntries(version), new BooleanMetadataEntry(immuneToZombification));
      }
    }

    [[nodiscard]] bool IsImmuneToZombification() const {
      return immuneToZombification;
    }

    void SetImmuneToZombification(bool value) {
      immuneToZombification = value;
    }
  };
}