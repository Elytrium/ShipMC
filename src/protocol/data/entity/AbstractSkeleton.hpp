#pragma once

#include "Monster.hpp"

namespace Ship {

  class AbstractSkeletonMetadata : public MonsterMetadata {
   private:
    bool swingingArms = false;

   public:
    AbstractSkeletonMetadata() = default;
    ~AbstractSkeletonMetadata() override = default;

    [[nodiscard]] static uint8_t MaximumEntries(const ProtocolVersion* version) {
      if (version <= &ProtocolVersion::MINECRAFT_1_13_2) {
        return MonsterMetadata::MaximumEntries(version) + 1;
      }
      return MonsterMetadata::MaximumEntries(version);
    }

    void Read(Metadata* metadata, const ProtocolVersion* version) override {
      MonsterMetadata::Read(metadata, version);

      if (version <= &ProtocolVersion::MINECRAFT_1_13_2) {
        swingingArms = metadata->GetBoolean(MonsterMetadata::MaximumEntries(version)).value_or(false);
      }
    }

    void Write(Metadata* metadata, const ProtocolVersion* version) override {
      MonsterMetadata::Write(metadata, version);

      if (version <= &ProtocolVersion::MINECRAFT_1_13_2) {
        metadata->Set(MonsterMetadata::MaximumEntries(version), new BooleanMetadataEntry(swingingArms));
      }
    }

    [[nodiscard]] bool IsSwingingArms() const {
      return swingingArms;
    }

    void SetSwingingArms(bool value) {
      swingingArms = value;
    }
  };
}