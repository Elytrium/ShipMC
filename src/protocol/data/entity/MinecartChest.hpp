#pragma once

#include "AbstractMinecartContainer.hpp"

namespace Ship {

  class MinecartChestMetadata : public AbstractMinecartContainerMetadata {
   public:
    MinecartChestMetadata() = default;
    ~MinecartChestMetadata() override = default;

    void Read(Metadata* metadata, const ProtocolVersion* version) override {
      AbstractMinecartContainerMetadata::Read(metadata, version);
    }

    void Write(Metadata* metadata, const ProtocolVersion* version) override {
      AbstractMinecartContainerMetadata::Write(metadata, version);
    }
  };
}