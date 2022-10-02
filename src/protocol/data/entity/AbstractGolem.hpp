#pragma once

#include "PathfinderMob.hpp"

namespace Ship {

  class AbstractGolemMetadata : public PathfinderMobMetadata {
   public:
    AbstractGolemMetadata() = default;
    ~AbstractGolemMetadata() override = default;

    void Read(Metadata* metadata, const ProtocolVersion* version) override {
      PathfinderMobMetadata::Read(metadata, version);
    }

    void Write(Metadata* metadata, const ProtocolVersion* version) override {
      PathfinderMobMetadata::Write(metadata, version);
    }
  };
}