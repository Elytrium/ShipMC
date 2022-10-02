#pragma once

#include "Animal.hpp"

namespace Ship {

  class ChickenMetadata : public AnimalMetadata {
   public:
    ChickenMetadata() = default;
    ~ChickenMetadata() override = default;

    void Read(Metadata* metadata, const ProtocolVersion* version) override {
      AnimalMetadata::Read(metadata, version);
    }

    void Write(Metadata* metadata, const ProtocolVersion* version) override {
      AnimalMetadata::Write(metadata, version);
    }
  };
}