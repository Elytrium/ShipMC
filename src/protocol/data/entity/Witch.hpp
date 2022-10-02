#pragma once

#include "Raider.hpp"

namespace Ship {

  class WitchMetadata : public RaiderMetadata {
   private:
    bool drinkingPotion = false;

   public:
    WitchMetadata() = default;
    ~WitchMetadata() override = default;

    [[nodiscard]] static uint8_t MaximumEntries(const ProtocolVersion* version) {
      return RaiderMetadata::MaximumEntries(version) + 1;
    }

    void Read(Metadata* metadata, const ProtocolVersion* version) override {
      RaiderMetadata::Read(metadata, version);

      drinkingPotion = metadata->GetBoolean(RaiderMetadata::MaximumEntries(version)).value_or(false);
    }

    void Write(Metadata* metadata, const ProtocolVersion* version) override {
      RaiderMetadata::Write(metadata, version);

      if (drinkingPotion) {
        metadata->Set(RaiderMetadata::MaximumEntries(version), new BooleanMetadataEntry(drinkingPotion));
      }
    }

    [[nodiscard]] bool IsDrinkingPotion() const {
      return drinkingPotion;
    }

    void SetDrinkingPotion(bool value) {
      drinkingPotion = value;
    }
  };
}