#pragma once

#include "AbstractMinecartContainer.hpp"

namespace Ship {

  class MinecartHopperMetadata : public AbstractMinecartContainerMetadata {
   public:
    MinecartHopperMetadata() = default;
    ~MinecartHopperMetadata() override = default;

    void Read(Metadata* metadata, const ProtocolVersion* version) override {
      AbstractMinecartContainerMetadata::Read(metadata, version);
    }

    void Write(Metadata* metadata, const ProtocolVersion* version) override {
      AbstractMinecartContainerMetadata::Write(metadata, version);
    }
  };
}