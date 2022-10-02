#pragma once

#include "AbstractFish.hpp"

namespace Ship {

  class SalmonMetadata : public AbstractFishMetadata {
   public:
    SalmonMetadata() = default;
    ~SalmonMetadata() override = default;

    void Read(Metadata* metadata, const ProtocolVersion* version) override {
      AbstractFishMetadata::Read(metadata, version);
    }

    void Write(Metadata* metadata, const ProtocolVersion* version) override {
      AbstractFishMetadata::Write(metadata, version);
    }
  };
}