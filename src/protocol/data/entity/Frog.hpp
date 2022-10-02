#pragma once

#include "Animal.hpp"

namespace Ship {

  class FrogMetadata : public AnimalMetadata {
   private:
    FrogVariant variant = FrogVariant::TEMPERATE;
    std::optional<uint32_t> tongueTarget;

   public:
    FrogMetadata() = default;
    ~FrogMetadata() override = default;

    [[nodiscard]] static uint8_t MaximumEntries(const ProtocolVersion* version) {
      return AnimalMetadata::MaximumEntries(version) + 2;
    }

    void Read(Metadata* metadata, const ProtocolVersion* version) override {
      AnimalMetadata::Read(metadata, version);
      uint8_t currentIndex = AnimalMetadata::MaximumEntries(version);

      variant = metadata->GetFrogVariant(currentIndex).value_or(FrogVariant::TEMPERATE);
      tongueTarget = metadata->GetOptVarInt(currentIndex + 1).value_or(std::nullopt);
    }

    void Write(Metadata* metadata, const ProtocolVersion* version) override {
      AnimalMetadata::Write(metadata, version);
      uint8_t currentIndex = AnimalMetadata::MaximumEntries(version);

      if (variant != FrogVariant::TEMPERATE) {
        metadata->Set(currentIndex, new FrogVariantMetadataEntry(variant));
      }

      if (tongueTarget) {
        metadata->Set(currentIndex + 2, new OptVarIntMetadataEntry(tongueTarget));
      }
    }

    [[nodiscard]] FrogVariant GetVariant() const {
      return variant;
    }

    void SetVariant(FrogVariant value) {
      variant = value;
    }

    [[nodiscard]] const std::optional<uint32_t>& GetTongueTarget() const {
      return tongueTarget;
    }

    void SetTongueTarget(const std::optional<uint32_t>& value) {
      tongueTarget = value;
    }
  };
}