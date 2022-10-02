#pragma once

#include "Monster.hpp"

namespace Ship {
  
  class WitherMetadata : public MonsterMetadata {
   private:
    uint32_t centerHeadTarget = 0;
    uint32_t leftHeadTarget = 0;
    uint32_t rightHeadTarget = 0;
    uint32_t invulnerableTime = 0;

   public:
    WitherMetadata() = default;
    ~WitherMetadata() override = default;

    [[nodiscard]] static uint8_t MaximumEntries(const ProtocolVersion* version) {
      return MonsterMetadata::MaximumEntries(version) + 4;
    }
    
    void Read(Metadata* metadata, const ProtocolVersion* version) override {
      MonsterMetadata::Read(metadata, version);
      uint8_t currentIndex = MonsterMetadata::MaximumEntries(version);

      centerHeadTarget = metadata->GetVarInt(currentIndex).value_or(0);
      leftHeadTarget = metadata->GetVarInt(currentIndex + 1).value_or(0);
      rightHeadTarget = metadata->GetVarInt(currentIndex + 2).value_or(0);
      invulnerableTime = metadata->GetVarInt(currentIndex + 3).value_or(0);
    }
    
    void Write(Metadata* metadata, const ProtocolVersion* version) override {
      MonsterMetadata::Write(metadata, version);
      uint8_t currentIndex = MonsterMetadata::MaximumEntries(version);

      if (centerHeadTarget) {
        metadata->Set(currentIndex, new VarIntMetadataEntry(centerHeadTarget));
      }

      if (leftHeadTarget) {
        metadata->Set(currentIndex + 1, new VarIntMetadataEntry(leftHeadTarget));
      }

      if (rightHeadTarget) {
        metadata->Set(currentIndex + 2, new VarIntMetadataEntry(rightHeadTarget));
      }

      if (invulnerableTime) {
        metadata->Set(currentIndex + 3, new VarIntMetadataEntry(invulnerableTime));
      }
    }

    [[nodiscard]] uint32_t GetCenterHeadTarget() const {
      return centerHeadTarget;
    }

    void SetCenterHeadTarget(uint32_t value) {
      centerHeadTarget = value;
    }

    [[nodiscard]] uint32_t GetLeftHeadTarget() const {
      return leftHeadTarget;
    }

    void SetLeftHeadTarget(uint32_t value) {
      leftHeadTarget = value;
    }

    [[nodiscard]] uint32_t GetRightHeadTarget() const {
      return rightHeadTarget;
    }

    void SetRightHeadTarget(uint32_t value) {
      rightHeadTarget = value;
    }

    [[nodiscard]] uint32_t GetInvulnerableTime() const {
      return invulnerableTime;
    }

    void SetInvulnerableTime(uint32_t value) {
      invulnerableTime = value;
    }
  };
}