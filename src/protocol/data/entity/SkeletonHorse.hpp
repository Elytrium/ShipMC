#pragma once

#include "AbstractHorse.hpp"

namespace Ship {

  class SkeletonHorseMetadata : public AbstractHorseMetadata {
   public:
    SkeletonHorseMetadata() = default;
    ~SkeletonHorseMetadata() override = default;

    void Read(Metadata* metadata, const ProtocolVersion* version) override {
      AbstractHorseMetadata::Read(metadata, version);
    }

    void Write(Metadata* metadata, const ProtocolVersion* version) override {
      AbstractHorseMetadata::Write(metadata, version);
    }
  };
}