#pragma once

#include "Entity.hpp"

namespace Ship {

  class PaintingMetadata : public EntityMetadata {
   private:
    PaintingVariant type = PaintingVariant::KEBAB;

   public:
    PaintingMetadata() = default;
    ~PaintingMetadata() override = default;

    [[nodiscard]] static uint8_t MaximumEntries(const ProtocolVersion* version) {
      return EntityMetadata::MaximumEntries(version) + 1;
    }

    void Read(Metadata* metadata, const ProtocolVersion* version) override {
      EntityMetadata::Read(metadata, version);

      type = metadata->GetPaintingVariant(EntityMetadata::MaximumEntries(version)).value_or(PaintingVariant::KEBAB);
    }

    void Write(Metadata* metadata, const ProtocolVersion* version) override {
      EntityMetadata::Write(metadata, version);

      if (type != PaintingVariant::KEBAB) {
        metadata->Set(EntityMetadata::MaximumEntries(version), new PaintingVariantMetadataEntry(type));
      }
    }

    [[nodiscard]] PaintingVariant GetType() const {
      return type;
    }

    void SetType(PaintingVariant value) {
      type = value;
    }
  };
}