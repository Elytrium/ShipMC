#pragma once

#include "AgeableMob.hpp"

namespace Ship {

  class AbstractVillagerMetadata : public AgeableMobMetadata {
   private:
    uint32_t headShakeTimer = 0;

   public:
    AbstractVillagerMetadata() = default;
    ~AbstractVillagerMetadata() override = default;

    [[nodiscard]] static uint8_t MaximumEntries(const ProtocolVersion* version) {
      return AgeableMobMetadata::MaximumEntries(version) + 1;
    }

    void Read(Metadata* metadata, const ProtocolVersion* version) override {
      AgeableMobMetadata::Read(metadata, version);

      headShakeTimer = metadata->GetVarInt(AgeableMobMetadata::MaximumEntries(version)).value_or(0);
    }

    void Write(Metadata* metadata, const ProtocolVersion* version) override {
      AgeableMobMetadata::Write(metadata, version);

      if (headShakeTimer) {
        metadata->Set(AgeableMobMetadata::MaximumEntries(version), new VarIntMetadataEntry(headShakeTimer));
      }
    }

    [[nodiscard]] uint32_t GetHeadShakeTimer() const {
      return headShakeTimer;
    }

    void SetHeadShakeTimer(uint32_t value) {
      headShakeTimer = value;
    }
  };
}