#pragma once

#include "Monster.hpp"

namespace Ship {

  class VindicationIllagerMetadata : public MonsterMetadata {
   private:
    union {
      struct {
        bool hasTarget : 1;
      };

      uint8_t value;
    } flags {};

   public:
    VindicationIllagerMetadata() = default;
    ~VindicationIllagerMetadata() override = default;

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

    [[nodiscard]] bool IsHasTarget() const {
      return flags.hasTarget;
    }

    void SetHasTarget(bool value) {
      flags.hasTarget = value;
    }
  };
}