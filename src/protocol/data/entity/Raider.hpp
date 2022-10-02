#pragma once

#include "Monster.hpp"

namespace Ship {

  class RaiderMetadata : public MonsterMetadata {
   private:
    bool celebrating = false; // hasTarget in 1.13

   public:
    RaiderMetadata() = default;
    ~RaiderMetadata() override = default;

    [[nodiscard]] static uint8_t MaximumEntries(const ProtocolVersion* version) {
      return MonsterMetadata::MaximumEntries(version) + 1;
    }

    void Read(Metadata* metadata, const ProtocolVersion* version) override {
      MonsterMetadata::Read(metadata, version);

      celebrating = metadata->GetBoolean(MonsterMetadata::MaximumEntries(version)).value_or(false);
    }

    void Write(Metadata* metadata, const ProtocolVersion* version) override {
      MonsterMetadata::Write(metadata, version);

      if (celebrating) {
        metadata->Set(MonsterMetadata::MaximumEntries(version), new BooleanMetadataEntry(celebrating));
      }
    }

    [[nodiscard]] bool IsCelebrating() const {
      return celebrating;
    }

    void SetCelebrating(bool value) {
      celebrating = value;
    }

    [[nodiscard]] bool hasTarget() const {
      return celebrating;
    }

    void SetHasTarget(bool value) {
      celebrating = value;
    }
  };
}