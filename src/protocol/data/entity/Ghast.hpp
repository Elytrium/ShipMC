#pragma once

#include "Flying.hpp"

namespace Ship {

  class GhastMetadata : public FlyingMetadata {
   private:
    bool attacking = false;

   public:
    GhastMetadata() = default;
    ~GhastMetadata() override = default;

    [[nodiscard]] static uint8_t MaximumEntries(const ProtocolVersion* version) {
      return FlyingMetadata::MaximumEntries(version) + 1;
    }

    void Read(Metadata* metadata, const ProtocolVersion* version) override {
      FlyingMetadata::Read(metadata, version);

      attacking = metadata->GetBoolean(FlyingMetadata::MaximumEntries(version)).value_or(false);
    }

    void Write(Metadata* metadata, const ProtocolVersion* version) override {
      FlyingMetadata::Write(metadata, version);

      if (attacking) {
        metadata->Set(FlyingMetadata::MaximumEntries(version), new BooleanMetadataEntry(attacking));
      }
    }

    [[nodiscard]] bool IsAttacking() const {
      return attacking;
    }

    void SetAttacking(bool value) {
      attacking = value;
    }
  };
}