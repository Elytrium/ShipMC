#pragma once

#include "Guardian.hpp"

namespace Ship {

  class ElderGuardianMetadata : public GuardianMetadata {
   public:
    ElderGuardianMetadata() = default;
    ~ElderGuardianMetadata() override = default;

    void Read(Metadata* metadata, const ProtocolVersion* version) override {
      GuardianMetadata::Read(metadata, version);
    }

    void Write(Metadata* metadata, const ProtocolVersion* version) override {
      GuardianMetadata::Write(metadata, version);
    }
  };
}