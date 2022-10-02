#pragma once

#include "PathfinderMob.hpp"

namespace Ship {

  class WaterAnimalMetadata : public PathfinderMobMetadata {
   public:
    WaterAnimalMetadata() = default;
    ~WaterAnimalMetadata() override = default;

    void Read(Metadata* metadata, const ProtocolVersion* version) override {
      PathfinderMobMetadata::Read(metadata, version);
    }

    void Write(Metadata* metadata, const ProtocolVersion* version) override {
      PathfinderMobMetadata::Write(metadata, version);
    }
  };
}