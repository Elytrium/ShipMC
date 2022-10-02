#pragma once

#include "AbstractMinecart.hpp"

namespace Ship {

  class AbstractMinecartContainerMetadata : public AbstractMinecartMetadata {
   public:
    AbstractMinecartContainerMetadata() = default;
    ~AbstractMinecartContainerMetadata() override = default;

    void Read(Metadata* metadata, const ProtocolVersion* version) override {
      AbstractMinecartMetadata::Read(metadata, version);
    }

    void Write(Metadata* metadata, const ProtocolVersion* version) override {
      AbstractMinecartMetadata::Write(metadata, version);
    }
  };
}