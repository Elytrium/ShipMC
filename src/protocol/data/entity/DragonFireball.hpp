#pragma once

#include "Entity.hpp"

namespace Ship {

  class DragonFireballMetadata : public EntityMetadata {
   public:
    DragonFireballMetadata() = default;
    ~DragonFireballMetadata() override = default;

    void Read(Metadata* metadata, const ProtocolVersion* version) override {
      EntityMetadata::Read(metadata, version);
    }

    void Write(Metadata* metadata, const ProtocolVersion* version) override {
      EntityMetadata::Write(metadata, version);
    }
  };
}