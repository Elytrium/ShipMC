#pragma once

#include "AbstractMinecart.hpp"

namespace Ship {

  class MinecartMetadata : public AbstractMinecartMetadata {
   public:
    MinecartMetadata() = default;
    ~MinecartMetadata() override = default;

    void Read(Metadata* metadata, const ProtocolVersion* version) override {
      AbstractMinecartMetadata::Read(metadata, version);
    }

    void Write(Metadata* metadata, const ProtocolVersion* version) override {
      AbstractMinecartMetadata::Write(metadata, version);
    }
  };
}