#pragma once

#include "AmbientCreature.hpp"

namespace Ship {

  class BatMetadata : public AmbientCreatureMetadata {
   private:
    union {
      struct {
        uint8_t hanging : 1;
      };

      uint8_t value;
    } flags {};

   public:
    BatMetadata() = default;
    ~BatMetadata() override = default;

    static uint8_t MaximumEntries(const ProtocolVersion* version) {
      return AmbientCreatureMetadata::MaximumEntries(version) + 1;
    }

    void Read(Metadata* metadata, const ProtocolVersion* version) override {
      AmbientCreatureMetadata::Read(metadata, version);

      flags.value = metadata->GetByte(AmbientCreatureMetadata::MaximumEntries(version)).value_or(0);
    }

    void Write(Metadata* metadata, const ProtocolVersion* version) override {
      AmbientCreatureMetadata::Write(metadata, version);

      if (flags.value) {
        metadata->Set(AmbientCreatureMetadata::MaximumEntries(version), new ByteMetadataEntry(flags.value));
      }
    }

    [[nodiscard]] bool IsHanging() const {
      return flags.hanging;
    }

    void SetHanging(bool value) {
      flags.hanging = value;
    }
  };
}