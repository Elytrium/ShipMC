#pragma once

#include "AbstractSkeleton.hpp"

namespace Ship {

  class WitherSkeletonMetadata : public AbstractSkeletonMetadata {
   public:
    WitherSkeletonMetadata() = default;
    ~WitherSkeletonMetadata() override = default;

    void Read(Metadata* metadata, const ProtocolVersion* version) override {
      AbstractSkeletonMetadata::Read(metadata, version);
    }

    void Write(Metadata* metadata, const ProtocolVersion* version) override {
      AbstractSkeletonMetadata::Write(metadata, version);
    }
  };
}