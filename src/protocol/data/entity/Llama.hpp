#pragma once

#include "ChestedHorse.hpp"

namespace Ship {

  enum class LlamaVariant {
    CREAMY = 0,
    WHITE = 1,
    BROWN = 2,
    GRAY = 3,
  };

  class LlamaMetadata : public ChestedHorseMetadata {
   private:
    uint32_t strength = 0;
    uint32_t carpetColor = -1;
    LlamaVariant variant = LlamaVariant::CREAMY;

   public:
    LlamaMetadata() = default;
    ~LlamaMetadata() override = default;

    [[nodiscard]] static uint8_t MaximumEntries(const ProtocolVersion* version) {
      return ChestedHorseMetadata::MaximumEntries(version) + 3;
    }

    void Read(Metadata* metadata, const ProtocolVersion* version) override {
      ChestedHorseMetadata::Read(metadata, version);
      uint8_t currentIndex = ChestedHorseMetadata::MaximumEntries(version);

      strength = metadata->GetVarInt(currentIndex).value_or(0);
      carpetColor = metadata->GetVarInt(currentIndex + 1).value_or(-1);
      variant = (LlamaVariant) metadata->GetVarInt(currentIndex + 2).value_or(0);
    }

    void Write(Metadata* metadata, const ProtocolVersion* version) override {
      ChestedHorseMetadata::Write(metadata, version);
      uint8_t currentIndex = ChestedHorseMetadata::MaximumEntries(version);
      
      if (strength) {
        metadata->Set(currentIndex, new VarIntMetadataEntry(strength));
      }
      
      if (carpetColor != -1) {
        metadata->Set(currentIndex + 1, new VarIntMetadataEntry(carpetColor));
      }
      
      if (variant != LlamaVariant::CREAMY) {
        metadata->Set(currentIndex + 2, new VarIntMetadataEntry((uint32_t) variant));
      }
    }

    [[nodiscard]] uint32_t GetStrength() const {
      return strength;
    }

    void SetStrength(uint32_t value) {
      strength = value;
    }

    [[nodiscard]] uint32_t GetCarpetColor() const {
      return carpetColor;
    }

    void SetCarpetColor(uint32_t value) {
      carpetColor = value;
    }

    [[nodiscard]] LlamaVariant GetVariant() const {
      return variant;
    }

    void SetVariant(LlamaVariant value) {
      variant = value;
    }
  };
}