#pragma once

#include "Animal.hpp"

namespace Ship {

  class PandaMetadata : public AnimalMetadata {
   private:
    uint32_t breedTimer = 0;
    uint32_t sneezeTimer = 0;
    uint32_t eatTimer = 0;
    uint8_t mainGene = 0;
    uint8_t hiddenGene = 0;
    union {
      struct {
        uint8_t : 1;
        uint8_t sneezing : 1;
        uint8_t rolling : 1;
        uint8_t sitting : 1;
        uint8_t onBack : 1;
      };

      uint8_t value;
    } flags {};

   public:
    PandaMetadata() = default;
    ~PandaMetadata() override = default;

    [[nodiscard]] static uint8_t MaximumEntries(const ProtocolVersion* version) {
      return AnimalMetadata::MaximumEntries(version) + 6;
    }

    void Read(Metadata* metadata, const ProtocolVersion* version) override {
      AnimalMetadata::Read(metadata, version);
      uint8_t currentIndex = AnimalMetadata::MaximumEntries(version);

      breedTimer = metadata->GetVarInt(currentIndex).value_or(0);
      sneezeTimer = metadata->GetVarInt(currentIndex + 1).value_or(0);
      eatTimer = metadata->GetVarInt(currentIndex + 2).value_or(0);
      mainGene = metadata->GetByte(currentIndex + 3).value_or(0);
      hiddenGene = metadata->GetByte(currentIndex + 4).value_or(0);
      flags.value = metadata->GetByte(currentIndex + 5).value_or(0);
    }

    void Write(Metadata* metadata, const ProtocolVersion* version) override {
      AnimalMetadata::Write(metadata, version);
      uint8_t currentIndex = AnimalMetadata::MaximumEntries(version);

      if (breedTimer) {
        metadata->Set(currentIndex, new VarIntMetadataEntry(breedTimer));
      }

      if (sneezeTimer) {
        metadata->Set(currentIndex + 1, new VarIntMetadataEntry(sneezeTimer));
      }

      if (eatTimer) {
        metadata->Set(currentIndex + 2, new VarIntMetadataEntry(eatTimer));
      }

      if (mainGene) {
        metadata->Set(currentIndex + 3, new ByteMetadataEntry(mainGene));
      }

      if (hiddenGene) {
        metadata->Set(currentIndex + 4, new ByteMetadataEntry(hiddenGene));
      }

      if (flags.value) {
        metadata->Set(currentIndex + 5, new ByteMetadataEntry(flags.value));
      }
    }

    [[nodiscard]] uint32_t GetBreedTimer() const {
      return breedTimer;
    }

    void SetBreedTimer(uint32_t value) {
      breedTimer = value;
    }

    [[nodiscard]] uint32_t GetSneezeTimer() const {
      return sneezeTimer;
    }

    void SetSneezeTimer(uint32_t value) {
      sneezeTimer = value;
    }

    [[nodiscard]] uint32_t GetEatTimer() const {
      return eatTimer;
    }

    void SetEatTimer(uint32_t value) {
      eatTimer = value;
    }

    [[nodiscard]] uint8_t GetMainGene() const {
      return mainGene;
    }

    void SetMainGene(uint8_t value) {
      mainGene = value;
    }

    [[nodiscard]] uint8_t GetHiddenGene() const {
      return hiddenGene;
    }

    void SetHiddenGene(uint8_t value) {
      hiddenGene = value;
    }

    [[nodiscard]] bool IsSneezing() const {
      return flags.sneezing;
    }

    void SetSneezing(bool value) {
      flags.sneezing = value;
    }

    [[nodiscard]] bool IsRolling() const {
      return flags.rolling;
    }

    void SetRolling(bool value) {
      flags.rolling = value;
    }

    [[nodiscard]] bool IsSitting() const {
      return flags.sitting;
    }

    void SetSitting(bool value) {
      flags.sitting = value;
    }

    [[nodiscard]] bool IsOnBack() const {
      return flags.onBack;
    }

    void SetOnBack(bool value) {
      flags.onBack = value;
    }
  };
}