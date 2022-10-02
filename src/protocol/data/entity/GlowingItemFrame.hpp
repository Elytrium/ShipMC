#pragma once

#include "ItemFrame.hpp"

namespace Ship {

  class GlowingItemFrameMetadata : public ItemFrameMetadata {
   public:
    GlowingItemFrameMetadata() = default;
    ~GlowingItemFrameMetadata() override = default;

    void Read(Metadata* metadata, const ProtocolVersion* version) override {
      ItemFrameMetadata::Read(metadata, version);
    }

    void Write(Metadata* metadata, const ProtocolVersion* version) override {
      ItemFrameMetadata::Write(metadata, version);
    }
  };
}