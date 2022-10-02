#pragma once

#include "Zombie.hpp"

namespace Ship {

  class DrownedMetadata : public ZombieMetadata {
   public:
    DrownedMetadata() = default;
    ~DrownedMetadata() override = default;

    void Read(Metadata* metadata, const ProtocolVersion* version) override {
      ZombieMetadata::Read(metadata, version);
    }

    void Write(Metadata* metadata, const ProtocolVersion* version) override {
      ZombieMetadata::Write(metadata, version);
    }
  };
}