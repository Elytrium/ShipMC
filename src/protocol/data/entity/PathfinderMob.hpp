#pragma once

#include "Mob.hpp"

namespace Ship {

  class PathfinderMobMetadata : public MobMetadata {
   public:
    PathfinderMobMetadata() = default;
    ~PathfinderMobMetadata() override = default;

    void Read(Metadata* metadata, const ProtocolVersion* version) override {
      MobMetadata::Read(metadata, version);
    }

    void Write(Metadata* metadata, const ProtocolVersion* version) override {
      MobMetadata::Write(metadata, version);
    }
  };
}