#pragma once

#include "TameableAnimal.hpp"

namespace Ship {

  enum class ParrotVariant {
    RED_BLUE = 0,
    BLUE = 1,
    GREEN = 2,
    YELLOW_BLUE = 3,
    GREY = 4,
  };

  class ParrotMetadata : public TameableAnimalMetadata {
   private:
    ParrotVariant variant = ParrotVariant::RED_BLUE;

   public:
    ParrotMetadata() = default;
    ~ParrotMetadata() override = default;

    [[nodiscard]] static uint8_t MaximumEntries(const ProtocolVersion* version) {
      return TameableAnimalMetadata::MaximumEntries(version) + 1;
    }

    void Read(Metadata* metadata, const ProtocolVersion* version) override {
      TameableAnimalMetadata::Read(metadata, version);

      variant = (ParrotVariant) metadata->GetVarInt(TameableAnimalMetadata::MaximumEntries(version)).value_or(0);
    }

    void Write(Metadata* metadata, const ProtocolVersion* version) override {
      TameableAnimalMetadata::Write(metadata, version);

      if (variant != ParrotVariant::RED_BLUE) {
        metadata->Set(TameableAnimalMetadata::MaximumEntries(version), new VarIntMetadataEntry((uint32_t) variant));
      }
    }

    [[nodiscard]] ParrotVariant GetVariant() const {
      return variant;
    }

    void SetVariant(ParrotVariant value) {
      variant = value;
    }
  };
}