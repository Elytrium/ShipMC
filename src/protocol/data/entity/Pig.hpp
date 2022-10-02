#pragma once

#include "Animal.hpp"

namespace Ship {
  
  class PigMetadata : public AnimalMetadata {
   private:
    bool hasSaddle = false;
    uint32_t boostTime = 0;

   public:
    PigMetadata() = default;
    ~PigMetadata() override = default;

    [[nodiscard]] static uint8_t MaximumEntries(const ProtocolVersion* version) {
      return AnimalMetadata::MaximumEntries(version) + 2;
    }
    
    void Read(Metadata* metadata, const ProtocolVersion* version) override {
      AnimalMetadata::Read(metadata, version);
      uint8_t currentIndex = AnimalMetadata::MaximumEntries(version);

      hasSaddle = metadata->GetBoolean(currentIndex).value_or(false);
      boostTime = metadata->GetVarInt(currentIndex + 1).value_or(0);
    }
    
    void Write(Metadata* metadata, const ProtocolVersion* version) override {
      AnimalMetadata::Write(metadata, version);
      uint8_t currentIndex = AnimalMetadata::MaximumEntries(version);

      if (hasSaddle) {
        metadata->Set(currentIndex, new BooleanMetadataEntry(hasSaddle));
      }

      if (boostTime) {
        metadata->Set(currentIndex + 1, new VarIntMetadataEntry(boostTime));
      }
    }

    [[nodiscard]] bool IsHasSaddle() const {
      return hasSaddle;
    }

    void SetHasSaddle(bool value) {
      hasSaddle = value;
    }

    [[nodiscard]] uint32_t GetBoostTime() const {
      return boostTime;
    }

    void SetBoostTime(uint32_t value) {
      boostTime = value;
    }
  };
}