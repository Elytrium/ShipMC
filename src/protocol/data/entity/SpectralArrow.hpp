#pragma once

#include "AbstractArrow.hpp"

namespace Ship {

  class SpectralArrowMetadata : public AbstractArrowMetadata {
   public:
    SpectralArrowMetadata() = default;
    ~SpectralArrowMetadata() override = default;

    void Read(Metadata* metadata, const ProtocolVersion* version) override {
      AbstractArrowMetadata::Read(metadata, version);
    }

    void Write(Metadata* metadata, const ProtocolVersion* version) override {
      AbstractArrowMetadata::Write(metadata, version);
    }
  };
}