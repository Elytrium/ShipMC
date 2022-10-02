#pragma once

#include "WaterAnimal.hpp"

namespace Ship {

  class SquidMetadata : public WaterAnimalMetadata {
   public:
    SquidMetadata() = default;
    ~SquidMetadata() override = default;

    void Read(Metadata* metadata, const ProtocolVersion* version) override {
      WaterAnimalMetadata::Read(metadata, version);
    }

    void Write(Metadata* metadata, const ProtocolVersion* version) override {
      WaterAnimalMetadata::Write(metadata, version);
    }
  };
}