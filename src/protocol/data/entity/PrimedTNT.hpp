#pragma once

#include "Entity.hpp"

namespace Ship {

  class PrimedTNTMetadata : public EntityMetadata {
   private:
    uint32_t fuseTime = 80;

   public:
    PrimedTNTMetadata() = default;
    ~PrimedTNTMetadata() override = default;

    [[nodiscard]] static uint8_t MaximumEntries(const ProtocolVersion* version) {
      return EntityMetadata::MaximumEntries(version) + 1;
    }

    void Read(Metadata* metadata, const ProtocolVersion* version) override {
      EntityMetadata::Read(metadata, version);

      fuseTime = metadata->GetVarInt(EntityMetadata::MaximumEntries(version)).value_or(80);
    }

    void Write(Metadata* metadata, const ProtocolVersion* version) override {
      EntityMetadata::Write(metadata, version);

      if (fuseTime != 80) {
        metadata->Set(EntityMetadata::MaximumEntries(version), new VarIntMetadataEntry(fuseTime));
      }
    }

    [[nodiscard]] uint32_t GetFuseTime() const {
      return fuseTime;
    }

    void SetFuseTime(uint32_t value) {
      fuseTime = value;
    }
  };
}