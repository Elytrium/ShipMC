#pragma once

#include "AbstractSkeleton.hpp"

namespace Ship {

  class SkeletonMetadata : public AbstractSkeletonMetadata {
   public:
    SkeletonMetadata() = default;
    ~SkeletonMetadata() override = default;

    void Read(Metadata* metadata, const ProtocolVersion* version) override {
      AbstractSkeletonMetadata::Read(metadata, version);
    }

    void Write(Metadata* metadata, const ProtocolVersion* version) override {
      AbstractSkeletonMetadata::Write(metadata, version);
    }
  };
}