#pragma once

#include "Raider.hpp"

namespace Ship {

  class RavangerMetadata : public RaiderMetadata {
   public:
    RavangerMetadata() = default;
    ~RavangerMetadata() override = default;

    void Read(Metadata* metadata, const ProtocolVersion* version) override {
      RaiderMetadata::Read(metadata, version);
    }

    void Write(Metadata* metadata, const ProtocolVersion* version) override {
      RaiderMetadata::Write(metadata, version);
    }
  };
}