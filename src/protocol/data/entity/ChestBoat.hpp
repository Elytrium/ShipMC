#pragma once

#include "Boat.hpp"

namespace Ship {

  class ChestBoatMetadata : public BoatMetadata {
   public:
    ChestBoatMetadata() = default;
    ~ChestBoatMetadata() override = default;

    void Read(Metadata* metadata, const ProtocolVersion* version) override {
      BoatMetadata::Read(metadata, version);
    }

    void Write(Metadata* metadata, const ProtocolVersion* version) override {
      BoatMetadata::Write(metadata, version);
    }
  };
}