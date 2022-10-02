#pragma once

#include "TameableAnimal.hpp"

namespace Ship {

  enum class LegacyOcelotVariant {
    UNTAMED = 0,
    TUXEDO = 1,
    TABBY = 2,
    SIAMESE = 3,
  };

  class LegacyOcelotMetadata : public TameableAnimalMetadata {
   private:
    LegacyOcelotVariant type = LegacyOcelotVariant::UNTAMED;

   public:
    LegacyOcelotMetadata() = default;
    ~LegacyOcelotMetadata() override = default;

    [[nodiscard]] static uint8_t MaximumEntries(const ProtocolVersion* version) {
      return TameableAnimalMetadata::MaximumEntries(version) + 1;
    }

    void Read(Metadata* metadata, const ProtocolVersion* version) override {
      TameableAnimalMetadata::Read(metadata, version);

      type = (LegacyOcelotVariant) metadata->GetVarInt(TameableAnimalMetadata::MaximumEntries(version)).value_or(0);
    }

    void Write(Metadata* metadata, const ProtocolVersion* version) override {
      TameableAnimalMetadata::Write(metadata, version);

      metadata->Set(TameableAnimalMetadata::MaximumEntries(version), new VarIntMetadataEntry((uint32_t) type));
    }
  };
}