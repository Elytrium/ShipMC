#pragma once

#include "Monster.hpp"

namespace Ship {

  class WardenMetadata : public MonsterMetadata {
   private:
    uint32_t angerLevel = 0;

   public:
    WardenMetadata() = default;
    ~WardenMetadata() override = default;

    [[nodiscard]] static uint8_t MaximumEntries(const ProtocolVersion* version) {
      return MonsterMetadata::MaximumEntries(version) + 1;
    }

    void Read(Metadata* metadata, const ProtocolVersion* version) override {
      MonsterMetadata::Read(metadata, version);

      angerLevel = metadata->GetVarInt(MonsterMetadata::MaximumEntries(version)).value_or(0);
    }

    void Write(Metadata* metadata, const ProtocolVersion* version) override {
      MonsterMetadata::Write(metadata, version);

      if (angerLevel) {
        metadata->Set(MonsterMetadata::MaximumEntries(version), new VarIntMetadataEntry(angerLevel));
      }
    }

    [[nodiscard]] uint32_t GetAngerLevel() const {
      return angerLevel;
    }

    void SetAngerLevel(uint32_t value) {
      angerLevel = value;
    }
  };
}