#pragma once

#include "Monster.hpp"

namespace Ship {

  class GiantMetadata : public MonsterMetadata {
   public:
    GiantMetadata() = default;
    ~GiantMetadata() override = default;

    void Read(Metadata* metadata, const ProtocolVersion* version) override {
      MonsterMetadata::Read(metadata, version);
    }

    void Write(Metadata* metadata, const ProtocolVersion* version) override {
      MonsterMetadata::Write(metadata, version);
    }
  };
}