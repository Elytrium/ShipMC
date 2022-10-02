#pragma once

#include "Monster.hpp"

namespace Ship {

  class SpiderMetadata : public MonsterMetadata {
   private:
    union {
      struct {
        uint8_t climbing : 1;
      };

      uint8_t value;
    } flags {};

   public:
    SpiderMetadata() = default;
    ~SpiderMetadata() override = default;

    [[nodiscard]] static uint8_t MaximumEntries(const ProtocolVersion* version) {
      return MonsterMetadata::MaximumEntries(version) + 1;
    }

    void Read(Metadata* metadata, const ProtocolVersion* version) override {
      MonsterMetadata::Read(metadata, version);

      flags.value = metadata->GetByte(MonsterMetadata::MaximumEntries(version)).value_or(0);
    }

    void Write(Metadata* metadata, const ProtocolVersion* version) override {
      MonsterMetadata::Write(metadata, version);

      if (flags.value) {
        metadata->Set(MonsterMetadata::MaximumEntries(version), new ByteMetadataEntry(flags.value));
      }
    }

    [[nodiscard]] bool IsClimbing() const {
      return flags.climbing;
    }

    void SetClimbing(bool value) {
      flags.climbing = value;
    }
  };
}