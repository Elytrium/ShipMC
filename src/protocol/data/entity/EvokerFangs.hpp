#pragma once

#include "Entity.hpp"

namespace Ship {

  class EvokerFangsMetadata : public EntityMetadata {
   public:
    EvokerFangsMetadata() = default;
    ~EvokerFangsMetadata() override = default;

    void Read(Metadata* metadata, const ProtocolVersion* version) override {
      EntityMetadata::Read(metadata, version);
    }

    void Write(Metadata* metadata, const ProtocolVersion* version) override {
      EntityMetadata::Write(metadata, version);
    }
  };
}