#pragma once

#include "AbstractFish.hpp"

namespace Ship {

  class CodMetadata : public AbstractFishMetadata {
   public:
    CodMetadata() = default;
    ~CodMetadata() override = default;

    void Read(Metadata* metadata, const ProtocolVersion* version) override {
      AbstractFishMetadata::Read(metadata, version);
    }

    void Write(Metadata* metadata, const ProtocolVersion* version) override {
      AbstractFishMetadata::Write(metadata, version);
    }
  };
}