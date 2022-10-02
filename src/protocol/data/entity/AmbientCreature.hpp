#pragma once

#include "Mob.hpp"

namespace Ship {

  class AmbientCreatureMetadata : public MobMetadata {
   public:
    AmbientCreatureMetadata() = default;
    ~AmbientCreatureMetadata() override = default;

    void Read(Metadata* metadata, const ProtocolVersion* version) override {
      MobMetadata::Read(metadata, version);
    }

    void Write(Metadata* metadata, const ProtocolVersion* version) override {
      MobMetadata::Write(metadata, version);
    }
  };
}