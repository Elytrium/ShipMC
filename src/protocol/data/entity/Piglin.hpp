#pragma once

#include "BasePiglin.hpp"

namespace Ship {

  class PiglinMetadata : public BasePiglinMetadata {
   private:
    bool baby = false;
    bool chargingCrossbow = false;
    bool dancing = false;

   public:
    PiglinMetadata() = default;
    ~PiglinMetadata() override = default;

    [[nodiscard]] static uint8_t MaximumEntries(const ProtocolVersion* version) {
      return BasePiglinMetadata::MaximumEntries(version) + 3;
    }

    void Read(Metadata* metadata, const ProtocolVersion* version) override {
      BasePiglinMetadata::Read(metadata, version);
      uint8_t currentIndex = BasePiglinMetadata::MaximumEntries(version);

      baby = metadata->GetBoolean(currentIndex).value_or(false);
      chargingCrossbow = metadata->GetBoolean(currentIndex + 1).value_or(false);
      dancing = metadata->GetBoolean(currentIndex + 2).value_or(false);
    }

    void Write(Metadata* metadata, const ProtocolVersion* version) override {
      BasePiglinMetadata::Write(metadata, version);
      uint8_t currentIndex = BasePiglinMetadata::MaximumEntries(version);

      if (baby) {
        metadata->Set(currentIndex, new BooleanMetadataEntry(baby));
      }

      if (chargingCrossbow) {
        metadata->Set(currentIndex + 1, new BooleanMetadataEntry(chargingCrossbow));
      }

      if (dancing) {
        metadata->Set(currentIndex + 2, new BooleanMetadataEntry(dancing));
      }
    }

    [[nodiscard]] bool IsBaby() const {
      return baby;
    }

    void SetBaby(bool value) {
      baby = value;
    }

    [[nodiscard]] bool IsChargingCrossbow() const {
      return chargingCrossbow;
    }

    void SetChargingCrossbow(bool value) {
      chargingCrossbow = value;
    }

    [[nodiscard]] bool IsDancing() const {
      return dancing;
    }

    void SetDancing(bool value) {
      dancing = value;
    }
  };
}