#pragma once

#include "Animal.hpp"

namespace Ship {

  class PolarBearMetadata : public AnimalMetadata {
   private:
    bool standingUp = false;

   public:
    PolarBearMetadata() = default;
    ~PolarBearMetadata() override = default;

    [[nodiscard]] static uint8_t MaximumEntries(const ProtocolVersion* version) {
      return AnimalMetadata::MaximumEntries(version) + 1;
    }

    void Read(Metadata* metadata, const ProtocolVersion* version) override {
      AnimalMetadata::Read(metadata, version);

      standingUp = metadata->GetBoolean(AnimalMetadata::MaximumEntries(version)).value_or(false);
    }

    void Write(Metadata* metadata, const ProtocolVersion* version) override {
      AnimalMetadata::Write(metadata, version);

      if (standingUp) {
        metadata->Set(AnimalMetadata::MaximumEntries(version), new BooleanMetadataEntry(standingUp));
      }
    }

    [[nodiscard]] bool IsStandingUp() const {
      return standingUp;
    }

    void SetStandingUp(bool value) {
      standingUp = value;
    }
  };
}