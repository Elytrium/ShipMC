#pragma once

#include "Monster.hpp"

namespace Ship {

  class ZoglinMetadata : public MonsterMetadata {
   private:
    bool baby = false;

   public:
    ZoglinMetadata() = default;
    ~ZoglinMetadata() override = default;

    static uint8_t MaximumEntries(const ProtocolVersion* version) {
      return MonsterMetadata::MaximumEntries(version) + 1;
    }

    void Read(Metadata* metadata, const ProtocolVersion* version) override {
      MonsterMetadata::Read(metadata, version);

      baby = metadata->GetBoolean(MonsterMetadata::MaximumEntries(version)).value_or(false);
    }

    void Write(Metadata* metadata, const ProtocolVersion* version) override {
      MonsterMetadata::Write(metadata, version);

      if (baby) {
        metadata->Set(MonsterMetadata::MaximumEntries(version), new BooleanMetadataEntry(baby));
      }
    }

    [[nodiscard]] bool IsBaby() const {
      return baby;
    }

    void SetBaby(bool value) {
      baby = value;
    }
  };
}