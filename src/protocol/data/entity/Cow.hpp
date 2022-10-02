#pragma once

#include "Animal.hpp"

namespace Ship {

  class CowMetadata : public AnimalMetadata {
   public:
    CowMetadata() = default;
    ~CowMetadata() override = default;

    void Read(Metadata* metadata, const ProtocolVersion* version) override {
      AnimalMetadata::Read(metadata, version);
    }

    void Write(Metadata* metadata, const ProtocolVersion* version) override {
      AnimalMetadata::Write(metadata, version);
    }
  };
}