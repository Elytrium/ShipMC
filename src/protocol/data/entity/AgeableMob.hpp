#pragma once

#include "PathfinderMob.hpp"

namespace Ship {

  class AgeableMobMetadata : public PathfinderMobMetadata {
   private:
    bool baby = false;

   public:
    AgeableMobMetadata() = default;
    ~AgeableMobMetadata() override = default;

    [[nodiscard]] static uint8_t MaximumEntries(const ProtocolVersion* version) {
      return PathfinderMobMetadata::MaximumEntries(version) + 1;
    }

    void Read(Metadata* metadata, const ProtocolVersion* version) override {
      PathfinderMobMetadata::Read(metadata, version);

      baby = metadata->GetBoolean(PathfinderMobMetadata::MaximumEntries(version)).value_or(false);
    }

    void Write(Metadata* metadata, const ProtocolVersion* version) override {
      PathfinderMobMetadata::Write(metadata, version);

      if (baby) {
        metadata->Set(PathfinderMobMetadata::MaximumEntries(version), new BooleanMetadataEntry(baby));
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