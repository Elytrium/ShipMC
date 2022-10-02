#pragma once

#include "AbstractIllager.hpp"

namespace Ship {

  class VindicatorMetadata : public AbstractIllagerMetadata {
   public:
    VindicatorMetadata() = default;
    ~VindicatorMetadata() override = default;

    void Read(Metadata* metadata, const ProtocolVersion* version) override {
      AbstractIllagerMetadata::Read(metadata, version);
    }

    void Write(Metadata* metadata, const ProtocolVersion* version) override {
      AbstractIllagerMetadata::Write(metadata, version);
    }
  };
}