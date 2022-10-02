#pragma once

#include "Animal.hpp"

namespace Ship {

  class GoatMetadata : public AnimalMetadata {
   private:
    bool screaming = false;
    bool hasLeftHorn = true;
    bool hasRightHorn = true;

   public:
    GoatMetadata() = default;
    ~GoatMetadata() override = default;

    [[nodiscard]] static uint8_t MaximumEntries(const ProtocolVersion* version) {
      return AnimalMetadata::MaximumEntries(version) + 3;
    }

    void Read(Metadata* metadata, const ProtocolVersion* version) override {
      AnimalMetadata::Read(metadata, version);
      uint8_t currentIndex = AnimalMetadata::MaximumEntries(version);

      screaming = metadata->GetBoolean(currentIndex).value_or(false);
      hasLeftHorn = metadata->GetBoolean(currentIndex + 1).value_or(true);
      hasRightHorn = metadata->GetBoolean(currentIndex + 2).value_or(true);
    }

    void Write(Metadata* metadata, const ProtocolVersion* version) override {
      AnimalMetadata::Write(metadata, version);
      uint8_t currentIndex = AnimalMetadata::MaximumEntries(version);

      if (screaming) {
        metadata->Set(currentIndex, new BooleanMetadataEntry(screaming));
      }

      if (!hasLeftHorn) {
        metadata->Set(currentIndex + 1, new BooleanMetadataEntry(hasLeftHorn));
      }

      if (!hasRightHorn) {
        metadata->Set(currentIndex + 2, new BooleanMetadataEntry(hasRightHorn));
      }
    }

    [[nodiscard]] bool IsScreaming() const {
      return screaming;
    }

    void SetScreaming(bool value) {
      screaming = value;
    }

    [[nodiscard]] bool IsHasLeftHorn() const {
      return hasLeftHorn;
    }

    void SetHasLeftHorn(bool value) {
      hasLeftHorn = value;
    }

    [[nodiscard]] bool IsHasRightHorn() const {
      return hasRightHorn;
    }

    void SetHasRightHorn(bool value) {
      hasRightHorn = value;
    }
  };
}