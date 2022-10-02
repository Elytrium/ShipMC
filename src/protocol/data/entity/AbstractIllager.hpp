#pragma once

#include "Raider.hpp"

namespace Ship {

  class AbstractIllagerMetadata : public RaiderMetadata {
   public:
    AbstractIllagerMetadata() = default;
    ~AbstractIllagerMetadata() override = default;

    void Read(Metadata* metadata, const ProtocolVersion* version) override {
      RaiderMetadata::Read(metadata, version);
    }

    void Write(Metadata* metadata, const ProtocolVersion* version) override {
      RaiderMetadata::Write(metadata, version);
    }
  };
}