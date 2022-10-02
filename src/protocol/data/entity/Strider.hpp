#pragma once

#include "Animal.hpp"

namespace Ship {

  class StriderMetadata : public AnimalMetadata {
   private:
    uint32_t boostTime = 0;
    bool shaking = false;
    bool hasSaddle = false;

   public:
    StriderMetadata() = default;
    ~StriderMetadata() override = default;

    [[nodiscard]] static uint8_t MaximumEntries(const ProtocolVersion* version) {
      return AnimalMetadata::MaximumEntries(version) + 3;
    }

    void Read(Metadata* metadata, const ProtocolVersion* version) override {
      AnimalMetadata::Read(metadata, version);
      uint8_t currentIndex = AnimalMetadata::MaximumEntries(version);

      boostTime = metadata->GetVarInt(currentIndex).value_or(0);
      shaking = metadata->GetBoolean(currentIndex + 1).value_or(0);
      hasSaddle = metadata->GetBoolean(currentIndex + 2).value_or(0);
    }

    void Write(Metadata* metadata, const ProtocolVersion* version) override {
      AnimalMetadata::Write(metadata, version);
      uint8_t currentIndex = AnimalMetadata::MaximumEntries(version);

      if (boostTime) {
        metadata->Set(currentIndex, new VarIntMetadataEntry(boostTime));
      }

      if (shaking) {
        metadata->Set(currentIndex + 1, new BooleanMetadataEntry(shaking));
      }

      if (hasSaddle) {
        metadata->Set(currentIndex + 2, new BooleanMetadataEntry(hasSaddle));
      }
    }

    [[nodiscard]] uint32_t GetBoostTime() const {
      return boostTime;
    }

    void SetBoostTime(uint32_t value) {
      boostTime = value;
    }

    [[nodiscard]] bool IsShaking() const {
      return shaking;
    }

    void SetShaking(bool value) {
      shaking = value;
    }

    [[nodiscard]] bool IsHasSaddle() const {
      return hasSaddle;
    }

    void SetHasSaddle(bool value) {
      hasSaddle = value;
    }
  };
}