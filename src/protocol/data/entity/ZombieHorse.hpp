#pragma once

#include "AbstractHorse.hpp"

namespace Ship {

  class ZombieHorseMetadata : public AbstractHorseMetadata {
   public:
    ZombieHorseMetadata() = default;
    ~ZombieHorseMetadata() override = default;

    void Read(Metadata* metadata, const ProtocolVersion* version) override {
      AbstractHorseMetadata::Read(metadata, version);
    }

    void Write(Metadata* metadata, const ProtocolVersion* version) override {
      AbstractHorseMetadata::Write(metadata, version);
    }
  };
}