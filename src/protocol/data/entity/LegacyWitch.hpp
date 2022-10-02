#pragma once

#include "Monster.hpp"

namespace Ship {

  class LegacyWitchMetadata : public MonsterMetadata {
   private:
    bool aggressive = false;

   public:
    LegacyWitchMetadata() = default;
    ~LegacyWitchMetadata() override = default;

    [[nodiscard]] static uint8_t MaximumEntries(const ProtocolVersion* version) {
      return MonsterMetadata::MaximumEntries(version) + 1;
    }

    void Read(Metadata* metadata, const ProtocolVersion* version) override {
      MonsterMetadata::Read(metadata, version);

      aggressive = metadata->GetBoolean(MonsterMetadata::MaximumEntries(version)).value_or(false);
    }

    void Write(Metadata* metadata, const ProtocolVersion* version) override {
      MonsterMetadata::Write(metadata, version);

      if (aggressive) {
        metadata->Set(MonsterMetadata::MaximumEntries(version), new BooleanMetadataEntry(aggressive));
      }
    }

    [[nodiscard]] bool IsWitchAggressive() const {
      return aggressive;
    }

    void SetWitchAggressive(bool value) {
      aggressive = value;
    }
  };
}