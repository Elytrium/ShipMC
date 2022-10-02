#pragma once

#include "AbstractGolem.hpp"

namespace Ship {

  class IronGolemMetadata : public AbstractGolemMetadata {
   private:
    union {
      struct {
        uint8_t playerCreated : 1;
      };

      uint8_t value;
    } flags {};

   public:
    IronGolemMetadata() = default;
    ~IronGolemMetadata() override = default;

    [[nodiscard]] static uint8_t MaximumEntries(const ProtocolVersion* version) {
      return AbstractGolemMetadata::MaximumEntries(version) + 1;
    }

    void Read(Metadata* metadata, const ProtocolVersion* version) override {
      AbstractGolemMetadata::Read(metadata, version);

      flags.value = metadata->GetByte(AbstractGolemMetadata::MaximumEntries(version)).value_or(0);
    }

    void Write(Metadata* metadata, const ProtocolVersion* version) override {
      AbstractGolemMetadata::Write(metadata, version);

      if (flags.value) {
        metadata->Set(AbstractGolemMetadata::MaximumEntries(version), new ByteMetadataEntry(flags.value));
      }
    }

    [[nodiscard]] bool IsPlayerCreated() const {
      return flags.playerCreated;
    }

    void SetPlayerCreated(bool value) {
      flags.playerCreated = value;
    }
  };
}