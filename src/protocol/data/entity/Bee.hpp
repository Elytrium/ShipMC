#pragma once

#include "Animal.hpp"

namespace Ship {

  class BeeMetadata : public AnimalMetadata {
   private:
    union {
      struct {
        uint8_t : 1;
        uint8_t angry : 1;
        uint8_t hasStung : 1;
        uint8_t hasNectar : 1;
      };

      uint8_t value;
    } flags {};
    uint32_t angerTime = 0;

   public:
    BeeMetadata() = default;
    ~BeeMetadata() override = default;

    static uint8_t MaximumEntries(const ProtocolVersion* version) {
      return AnimalMetadata::MaximumEntries(version) + 2;
    }

    void Read(Metadata* metadata, const ProtocolVersion* version) override {
      AnimalMetadata::Read(metadata, version);
      uint8_t currentIndex = AnimalMetadata::MaximumEntries(version);

      flags.value = metadata->GetByte(currentIndex).value_or(0);
      angerTime = metadata->GetVarInt(currentIndex + 1).value_or(0);
    }

    void Write(Metadata* metadata, const ProtocolVersion* version) override {
      AnimalMetadata::Write(metadata, version);
      uint8_t currentIndex = AnimalMetadata::MaximumEntries(version);

      if (flags.value) {
        metadata->Set(currentIndex, new ByteMetadataEntry(flags.value));
      }

      if (angerTime) {
        metadata->Set(currentIndex + 1, new VarIntMetadataEntry(angerTime));
      }
    }

    [[nodiscard]] bool IsAngry() const {
      return flags.angry;
    }

    void SetAngry(bool value) {
      flags.angry = value;
    }

    [[nodiscard]] bool IsHasStung() const {
      return flags.hasStung;
    }

    void SetHasStung(bool value) {
      flags.hasStung = value;
    }

    [[nodiscard]] bool IsHasNectar() const {
      return flags.hasNectar;
    }

    void SetHasNectar(bool value) {
      flags.hasNectar = value;
    }

    [[nodiscard]] uint32_t GetAngerTime() const {
      return angerTime;
    }

    void SetAngerTime(uint32_t value) {
      angerTime = value;
    }
  };
}