#pragma once

#include "Monster.hpp"

namespace Ship {

  class CreeperMetadata : public MonsterMetadata {
   private:
    uint32_t state = -1;
    bool charged = false;
    bool ignited = false;

   public:
    CreeperMetadata() = default;
    ~CreeperMetadata() override = default;

    static uint8_t MaximumEntries(const ProtocolVersion* version) {
      return MonsterMetadata::MaximumEntries(version) + 3;
    }

    void Read(Metadata* metadata, const ProtocolVersion* version) override {
      MonsterMetadata::Read(metadata, version);
      uint8_t currentIndex = MonsterMetadata::MaximumEntries(version);

      state = metadata->GetVarInt(currentIndex).value_or(-1);
      charged = metadata->GetBoolean(currentIndex + 1).value_or(false);
      ignited = metadata->GetBoolean(currentIndex + 2).value_or(false);
    }

    void Write(Metadata* metadata, const ProtocolVersion* version) override {
      MonsterMetadata::Write(metadata, version);
      uint8_t currentIndex = MonsterMetadata::MaximumEntries(version);

      if (state != -1) {
        metadata->Set(currentIndex, new VarIntMetadataEntry(state));
      }

      if (charged) {
        metadata->Set(currentIndex + 1, new BooleanMetadataEntry(charged));
      }

      if (ignited) {
        metadata->Set(currentIndex + 2, new BooleanMetadataEntry(ignited));
      }
    }

    [[nodiscard]] uint32_t GetState() const {
      return state;
    }

    void SetState(uint32_t value) {
      state = value;
    }

    [[nodiscard]] bool IsCharged() const {
      return charged;
    }

    void SetCharged(bool value) {
      charged = value;
    }

    [[nodiscard]] bool IsIgnited() const {
      return ignited;
    }

    void SetIgnited(bool value) {
      ignited = value;
    }
  };
}