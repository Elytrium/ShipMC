#pragma once

#include "Monster.hpp"

namespace Ship {

  class GuardianMetadata : public MonsterMetadata {
   private:
    bool retractingSpikes = false;
    uint32_t targetEntity = 0;

   public:
    GuardianMetadata() = default;
    ~GuardianMetadata() override = default;

    [[nodiscard]] static uint8_t MaximumEntries(const ProtocolVersion* version) {
      return MonsterMetadata::MaximumEntries(version) + 2;
    }

    void Read(Metadata* metadata, const ProtocolVersion* version) override {
      MonsterMetadata::Read(metadata, version);
      uint8_t currentIndex = MonsterMetadata::MaximumEntries(version);

      retractingSpikes = metadata->GetBoolean(currentIndex).value_or(false);
      targetEntity = metadata->GetVarInt(currentIndex + 1).value_or(0);
    }

    void Write(Metadata* metadata, const ProtocolVersion* version) override {
      MonsterMetadata::Write(metadata, version);
      uint8_t currentIndex = MonsterMetadata::MaximumEntries(version);

      if (retractingSpikes) {
        metadata->Set(currentIndex, new BooleanMetadataEntry(retractingSpikes));
      }

      if (targetEntity) {
        metadata->Set(currentIndex + 1, new VarIntMetadataEntry(targetEntity));
      }
    }

    [[nodiscard]] bool IsRetractingSpikes() const {
      return retractingSpikes;
    }

    void SetRetractingSpikes(bool value) {
      retractingSpikes = value;
    }

    [[nodiscard]] uint32_t GetTargetEntity() const {
      return targetEntity;
    }

    void SetTargetEntity(uint32_t value) {
      targetEntity = value;
    }
  };
}