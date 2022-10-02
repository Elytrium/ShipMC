#pragma once

#include "ChestedHorse.hpp"

namespace Ship {

  class DonkeyMetadata : public ChestedHorseMetadata {
   public:
    DonkeyMetadata() = default;
    ~DonkeyMetadata() override = default;

    void Read(Metadata* metadata, const ProtocolVersion* version) override {
      ChestedHorseMetadata::Read(metadata, version);
    }

    void Write(Metadata* metadata, const ProtocolVersion* version) override {
      ChestedHorseMetadata::Write(metadata, version);
    }
  };
}