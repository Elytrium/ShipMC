#pragma once

#include "Animal.hpp"

namespace Ship {

  class OcelotMetadata : public AnimalMetadata {
   private:
    bool trusting = false;

   public:
    OcelotMetadata() = default;
    ~OcelotMetadata() override = default;

    [[nodiscard]] static uint8_t MaximumEntries(const ProtocolVersion* version) {
      return AnimalMetadata::MaximumEntries(version) + 1;
    }

    void Read(Metadata* metadata, const ProtocolVersion* version) override {
      AnimalMetadata::Read(metadata, version);

      trusting = metadata->GetBoolean(AnimalMetadata::MaximumEntries(version)).value_or(false);
    }

    void Write(Metadata* metadata, const ProtocolVersion* version) override {
      AnimalMetadata::Write(metadata, version);

      if (trusting) {
        metadata->Set(AnimalMetadata::MaximumEntries(version), new BooleanMetadataEntry(trusting));
      }
    }

    [[nodiscard]] bool IsTrusting() const {
      return trusting;
    }

    void SetTrusting(bool value) {
      trusting = value;
    }
  };
}