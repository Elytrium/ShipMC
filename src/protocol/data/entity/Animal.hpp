#pragma once

#include "AgeableMob.hpp"

namespace Ship {

  class AnimalMetadata : public AgeableMobMetadata {
   public:
    AnimalMetadata() = default;
    ~AnimalMetadata() override = default;

    void Read(Metadata* metadata, const ProtocolVersion* version) override {
      AgeableMobMetadata::Read(metadata, version);
    }

    void Write(Metadata* metadata, const ProtocolVersion* version) override {
      AgeableMobMetadata::Write(metadata, version);
    }
  };
}