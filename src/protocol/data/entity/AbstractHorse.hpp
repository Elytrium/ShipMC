#pragma once

#include "Animal.hpp"

namespace Ship {

  class AbstractHorseMetadata : public AnimalMetadata {
   private:
    union {
      struct {
        uint8_t : 1;
        uint8_t tame : 1;
        uint8_t saddled : 1;
        uint8_t hasBred : 1;
        uint8_t eating : 1;
        uint8_t rearing : 1;
        uint8_t mouthOpen : 1;
      };

      uint8_t value;
    } flags {}; // TODO: Legacy flags (1.12.2)
    std::optional<UUID> owner;

   public:
    AbstractHorseMetadata() = default;
    ~AbstractHorseMetadata() override = default;

    [[nodiscard]] static uint8_t MaximumEntries(const ProtocolVersion* version) {
      return AnimalMetadata::MaximumEntries(version) + 2;
    }

    void Read(Metadata* metadata, const ProtocolVersion* version) override {
      AnimalMetadata::Read(metadata, version);
      uint8_t currentIndex = AnimalMetadata::MaximumEntries(version);

      flags.value = metadata->GetByte(currentIndex).value_or(0);
      owner = metadata->GetOptUUID(currentIndex + 1).value_or(std::nullopt);
    }

    void Write(Metadata* metadata, const ProtocolVersion* version) override {
      AnimalMetadata::Write(metadata, version);
      uint8_t currentIndex = AnimalMetadata::MaximumEntries(version);

      if (flags.value) {
        metadata->Set(currentIndex, new ByteMetadataEntry(flags.value));
      }

      if (owner) {
        metadata->Set(currentIndex + 1, new OptUUIDMetadataEntry(owner));
      }
    }

    [[nodiscard]] bool IsTame() const {
      return flags.tame;
    }

    void SetTame(bool value) {
      flags.tame = value;
    }

    [[nodiscard]] bool IsSaddled() const {
      return flags.saddled;
    }

    void SetSaddled(bool value) {
      flags.saddled = value;
    }

    [[nodiscard]] bool IsHasBred() const {
      return flags.hasBred;
    }

    void SetHasBred(bool value) {
      flags.hasBred = value;
    }

    [[nodiscard]] bool IsEating() const {
      return flags.eating;
    }

    void SetEating(bool value) {
      flags.eating = value;
    }

    [[nodiscard]] bool IsRearing() const {
      return flags.rearing;
    }

    void SetRearing(bool value) {
      flags.rearing = value;
    }

    [[nodiscard]] bool IsMouthOpen() const {
      return flags.mouthOpen;
    }

    void SetMouthOpen(bool value) {
      flags.mouthOpen = value;
    }

    [[nodiscard]] const std::optional<UUID>& GetOwner() const {
      return owner;
    }

    void SetOwner(const std::optional<UUID>& value) {
      owner = value;
    }
  };
}