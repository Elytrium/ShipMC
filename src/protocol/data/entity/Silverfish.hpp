#pragma once

#include "Monster.hpp"

namespace Ship {

  class SilverfishMetadata : public MonsterMetadata {
   public:
    SilverfishMetadata() = default;
    ~SilverfishMetadata() override = default;

    void Read(Metadata* metadata, const ProtocolVersion* version) override {
      MonsterMetadata::Read(metadata, version);
    }

    void Write(Metadata* metadata, const ProtocolVersion* version) override {
      MonsterMetadata::Write(metadata, version);
    }
  };
}