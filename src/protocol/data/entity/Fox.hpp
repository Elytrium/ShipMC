#pragma once

#include "Animal.hpp"

namespace Ship {

  enum class FoxVariant {
    RED = 0,
    SNOW = 1,
  };

  class FoxMetadata : public AnimalMetadata {
   private:
    FoxVariant type = FoxVariant::RED;
    union {
      struct {
        uint8_t sitting : 1;
        uint8_t : 1;
        uint8_t crouching : 1;
        uint8_t interested : 1;
        uint8_t pouncing : 1;
        uint8_t sleeping : 1;
        uint8_t faceplanted : 1;
        uint8_t defending : 1;
      };

      uint8_t value;
    } flags {};
    std::optional<UUID> firstUUID;
    std::optional<UUID> secondUUID;

   public:
    FoxMetadata() = default;
    ~FoxMetadata() override = default;

    [[nodiscard]] static uint8_t MaximumEntries(const ProtocolVersion* version) {
      return AnimalMetadata::MaximumEntries(version) + 4;
    }

    void Read(Metadata* metadata, const ProtocolVersion* version) override {
      AnimalMetadata::Read(metadata, version);
      uint8_t currentIndex = AnimalMetadata::MaximumEntries(version);

      type = (FoxVariant) metadata->GetVarInt(currentIndex).value_or(0);
      flags.value = metadata->GetByte(currentIndex + 2).value_or(0);
      firstUUID = metadata->GetOptUUID(currentIndex + 3).value_or(std::nullopt);
      secondUUID = metadata->GetOptUUID(currentIndex + 4).value_or(std::nullopt);
    }

    void Write(Metadata* metadata, const ProtocolVersion* version) override {
      AnimalMetadata::Write(metadata, version);
      uint8_t currentIndex = AnimalMetadata::MaximumEntries(version);

      if (type != FoxVariant::RED) {
        metadata->Set(currentIndex, new VarIntMetadataEntry((uint32_t) type));
      }

      if (flags.value) {
        metadata->Set(currentIndex + 1, new ByteMetadataEntry(flags.value));
      }

      if (firstUUID) {
        metadata->Set(currentIndex + 2, new OptUUIDMetadataEntry(firstUUID));
      }

      if (secondUUID) {
        metadata->Set(currentIndex + 3, new OptUUIDMetadataEntry(secondUUID));
      }
    }

    [[nodiscard]] FoxVariant GetType() const {
      return type;
    }

    void SetType(FoxVariant value) {
      type = value;
    }

    [[nodiscard]] bool IsSitting() const {
      return flags.sitting;
    }

    void SetSitting(bool value) {
      flags.sitting = value;
    }

    [[nodiscard]] bool IsFoxCrouching() const {
      return flags.crouching;
    }

    void SetFoxCrouching(bool value) {
      flags.crouching = value;
    }

    [[nodiscard]] bool IsInterested() const {
      return flags.interested;
    }

    void SetInterested(bool value) {
      flags.interested = value;
    }

    [[nodiscard]] bool IsPouncing() const {
      return flags.pouncing;
    }

    void SetPouncing(bool value) {
      flags.pouncing = value;
    }

    [[nodiscard]] bool IsSleeping() const {
      return flags.sleeping;
    }

    void SetSleeping(bool value) {
      flags.sleeping = value;
    }

    [[nodiscard]] bool IsFaceplanted() const {
      return flags.faceplanted;
    }

    void SetFaceplanted(bool value) {
      flags.faceplanted = value;
    }

    [[nodiscard]] bool IsDefending() const {
      return flags.defending;
    }

    void SetDefending(bool value) {
      flags.defending = value;
    }

    [[nodiscard]] const std::optional<UUID>& GetFirstUUID() const {
      return firstUUID;
    }

    void SetFirstUUID(const std::optional<UUID>& value) {
      firstUUID = value;
    }

    [[nodiscard]] const std::optional<UUID>& GetSecondUUID() const {
      return secondUUID;
    }

    void SetSecondUUID(const std::optional<UUID>& value) {
      secondUUID = value;
    }
  };
}