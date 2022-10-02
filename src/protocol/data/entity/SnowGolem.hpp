#pragma once

#include "AbstractGolem.hpp"

namespace Ship {

  class SnowGolemMetadata : public AbstractGolemMetadata {
   private:
    union {
      struct {
        uint8_t : 4;
        uint8_t hasPumpkinHat : 1;
      };

      uint8_t value;
    } flags {.hasPumpkinHat = true};

   public:
    SnowGolemMetadata() = default;
    ~SnowGolemMetadata() override = default;

    [[nodiscard]] static uint8_t MaximumEntries(const ProtocolVersion* version) {
      return AbstractGolemMetadata::MaximumEntries(version) + 1;
    }

    void Read(Metadata* metadata, const ProtocolVersion* version) override {
      AbstractGolemMetadata::Read(metadata, version);

      flags.value = metadata->GetByte(AbstractGolemMetadata::MaximumEntries(version)).value_or(0x10);
    }

    void Write(Metadata* metadata, const ProtocolVersion* version) override {
      AbstractGolemMetadata::Write(metadata, version);

      if (flags.value) {
        metadata->Set(AbstractGolemMetadata::MaximumEntries(version), new ByteMetadataEntry(flags.value));
      }
    }

    [[nodiscard]] bool IsHasPumpkinHat() const {
      return flags.hasPumpkinHat;
    }

    void SetHasPumpkinHat(bool value) {
      flags.hasPumpkinHat = value;
    }
  };
}