#pragma once

#include "AbstractFish.hpp"

namespace Ship {

  class TropicalFishMetadata : public AbstractFishMetadata {
   private:
    uint32_t variant = 0;

   public:
    TropicalFishMetadata() = default;
    ~TropicalFishMetadata() override = default;

    [[nodiscard]] static uint8_t MaximumEntries(const ProtocolVersion* version) {
      return AbstractFishMetadata::MaximumEntries(version) + 1;
    }

    void Read(Metadata* metadata, const ProtocolVersion* version) override {
      AbstractFishMetadata::Read(metadata, version);

      variant = metadata->GetVarInt(AbstractFishMetadata::MaximumEntries(version)).value_or(0);
    }

    void Write(Metadata* metadata, const ProtocolVersion* version) override {
      AbstractFishMetadata::Write(metadata, version);

      if (variant) {
        metadata->Set(AbstractFishMetadata::MaximumEntries(version), new VarIntMetadataEntry(variant));
      }
    }

    [[nodiscard]] uint32_t GetVariant() const {
      return variant;
    }

    void SetVariant(uint32_t value) {
      variant = value;
    }
  };
}