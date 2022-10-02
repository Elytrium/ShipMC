#pragma once

#include "AbstractMinecart.hpp"

namespace Ship {

  class MinecartTNTMetadata : public AbstractMinecartMetadata {
   public:
    MinecartTNTMetadata() = default;
    ~MinecartTNTMetadata() override = default;

    void Read(Metadata* metadata, const ProtocolVersion* version) override {
      AbstractMinecartMetadata::Read(metadata, version);
    }

    void Write(Metadata* metadata, const ProtocolVersion* version) override {
      AbstractMinecartMetadata::Write(metadata, version);
    }
  };
}