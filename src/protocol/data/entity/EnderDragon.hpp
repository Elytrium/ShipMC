#pragma once

#include "Mob.hpp"

namespace Ship {

  enum class EnderDragonPhase {
    CIRCLING = 0,
    STRAFING = 1,
    FLYING_TO_LAND = 2,
    LANDING_ON_PORTAL = 3,
    TAKING_OFF_FROM_PORTAL = 4,
    PERFORMING_BREATH_ATTACK = 5,
    LOOKING_FOR_PLAYER = 6,
    ROARING = 7,
    CHARGING_PLAYER = 8,
    FLYING_TO_DIE = 9,
    HOVERING = 10,
  };

  class EnderDragonMetadata : public MobMetadata {
   private:
    EnderDragonPhase phase = EnderDragonPhase::HOVERING;

   public:
    EnderDragonMetadata() = default;
    ~EnderDragonMetadata() override = default;

    static uint8_t MaximumEntries(const ProtocolVersion* version) {
      return MobMetadata::MaximumEntries(version) + 1;
    }

    void Read(Metadata* metadata, const ProtocolVersion* version) override {
      MobMetadata::Read(metadata, version);

      phase = (EnderDragonPhase) metadata->GetVarInt(MobMetadata::MaximumEntries(version)).value_or(10);
    }

    void Write(Metadata* metadata, const ProtocolVersion* version) override {
      MobMetadata::Write(metadata, version);

      if (phase != EnderDragonPhase::HOVERING) {
        metadata->Set(MobMetadata::MaximumEntries(version), new VarIntMetadataEntry((uint32_t) phase));
      }
    }

    [[nodiscard]] EnderDragonPhase GetPhase() const {
      return phase;
    }

    void SetPhase(EnderDragonPhase value) {
      phase = value;
    }
  };
}