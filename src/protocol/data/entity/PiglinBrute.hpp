#pragma once

#include "BasePiglin.hpp"

namespace Ship {

  class PiglinBruteMetadata : public BasePiglinMetadata {
   public:
    PiglinBruteMetadata() = default;
    ~PiglinBruteMetadata() override = default;

    void Read(Metadata* metadata, const ProtocolVersion* version) override {
      BasePiglinMetadata::Read(metadata, version);
    }

    void Write(Metadata* metadata, const ProtocolVersion* version) override {
      BasePiglinMetadata::Write(metadata, version);
    }
  };
}