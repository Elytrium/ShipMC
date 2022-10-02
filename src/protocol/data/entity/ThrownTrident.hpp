#pragma once

#include "AbstractArrow.hpp"

namespace Ship {

  class ThrownTridentMetadata : public AbstractArrowMetadata {
   private:
    uint32_t loyaltyLevel = 0;
    bool hasEnchantmentGlint = false;

   public:
    ThrownTridentMetadata() = default;
    ~ThrownTridentMetadata() override = default;

    [[nodiscard]] static uint8_t MaximumEntries(const ProtocolVersion* version) {
      if (version >= &ProtocolVersion::MINECRAFT_1_15) {
        return AbstractArrowMetadata::MaximumEntries(version) + 2;
      }
      return AbstractArrowMetadata::MaximumEntries(version) + 1;
    }

    void Read(Metadata* metadata, const ProtocolVersion* version) override {
      AbstractArrowMetadata::Read(metadata, version);
      uint8_t currentIndex = AbstractArrowMetadata::MaximumEntries(version);

      loyaltyLevel = metadata->GetVarInt(currentIndex).value_or(0);
      if (version >= &ProtocolVersion::MINECRAFT_1_15) {
        hasEnchantmentGlint = metadata->GetBoolean(currentIndex + 1).value_or(false);
      }
    }

    void Write(Metadata* metadata, const ProtocolVersion* version) override {
      AbstractArrowMetadata::Write(metadata, version);
      uint8_t currentIndex = AbstractArrowMetadata::MaximumEntries(version);

      if (loyaltyLevel) {
        metadata->Set(currentIndex, new VarIntMetadataEntry(loyaltyLevel));
      }

      if (version >= &ProtocolVersion::MINECRAFT_1_15) {
        if (hasEnchantmentGlint) {
          metadata->Set(currentIndex + 1, new BooleanMetadataEntry(hasEnchantmentGlint));
        }
      }
    }

    [[nodiscard]] uint32_t GetLoyaltyLevel() const {
      return loyaltyLevel;
    }

    void SetLoyaltyLevel(uint32_t value) {
      loyaltyLevel = value;
    }

    [[nodiscard]] bool IsHasEnchantmentGlint() const {
      return hasEnchantmentGlint;
    }

    void SetHasEnchantmentGlint(bool value) {
      hasEnchantmentGlint = value;
    }
  };
}