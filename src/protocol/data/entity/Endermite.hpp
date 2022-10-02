#pragma once

#include "Monster.hpp"

namespace Ship {

  class EndermiteMetadata : public MonsterMetadata {
   public:
    EndermiteMetadata() = default;
    ~EndermiteMetadata() override = default;

    void Read(Metadata* metadata, const ProtocolVersion* version) override {
      MonsterMetadata::Read(metadata, version);
    }

    void Write(Metadata* metadata, const ProtocolVersion* version) override {
      MonsterMetadata::Write(metadata, version);
    }
  };
}