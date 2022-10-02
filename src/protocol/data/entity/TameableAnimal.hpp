#pragma once

#include "Animal.hpp"

namespace Ship {

  class TameableAnimalMetadata : public AnimalMetadata {
   private:
    union {
      struct {
        uint8_t sitting : 1;
        uint8_t angry : 1;
        uint8_t tamed : 1;
      };

      uint8_t value;
    } flags {};
    std::optional<UUID> owner;

   public:
    TameableAnimalMetadata() = default;
    ~TameableAnimalMetadata() override = default;

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

    [[nodiscard]] bool IsSitting() const {
      return flags.sitting;
    }

    void SetSitting(bool value) {
      flags.sitting = value;
    }

    [[nodiscard]] bool IsAngry() const {
      return flags.angry;
    }

    void SetAngry(bool value) {
      flags.angry = value;
    }

    [[nodiscard]] bool IsTamed() const {
      return flags.tamed;
    }

    void SetTamed(bool value) {
      flags.tamed = value;
    }

    [[nodiscard]] const std::optional<UUID>& GetOwner() const {
      return owner;
    }

    void SetOwner(const std::optional<UUID>& value) {
      owner = value;
    }
  };
}