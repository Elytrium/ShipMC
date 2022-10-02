#pragma once

#include "Zombie.hpp"

namespace Ship {

  class ZombifiedPiglinMetadata : public ZombieMetadata {
   public:
    ZombifiedPiglinMetadata() = default;
    ~ZombifiedPiglinMetadata() override = default;

    void Read(Metadata* metadata, const ProtocolVersion* version) override {
      ZombieMetadata::Read(metadata, version);
    }

    void Write(Metadata* metadata, const ProtocolVersion* version) override {
      ZombieMetadata::Write(metadata, version);
    }
  };
}