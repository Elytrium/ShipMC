#pragma once

#include "AbstractMinecart.hpp"

namespace Ship {

  class MinecartSpawnerMetadata : public AbstractMinecartMetadata {
   public:
    MinecartSpawnerMetadata() = default;
    ~MinecartSpawnerMetadata() override = default;

    void Read(Metadata* metadata, const ProtocolVersion* version) override {
      AbstractMinecartMetadata::Read(metadata, version);
    }

    void Write(Metadata* metadata, const ProtocolVersion* version) override {
      AbstractMinecartMetadata::Write(metadata, version);
    }
  };
}