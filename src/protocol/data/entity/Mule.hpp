#pragma once

#include "ChestedHorse.hpp"

namespace Ship {

  class MuleMetadata : public ChestedHorseMetadata {
   public:
    MuleMetadata() = default;
    ~MuleMetadata() override = default;

    void Read(Metadata* metadata, const ProtocolVersion* version) override {
      ChestedHorseMetadata::Read(metadata, version);
    }

    void Write(Metadata* metadata, const ProtocolVersion* version) override {
      ChestedHorseMetadata::Write(metadata, version);
    }
  };
}