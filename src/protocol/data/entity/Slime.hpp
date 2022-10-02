#pragma once

#include "Mob.hpp"

namespace Ship {

  class SlimeMetadata : public MobMetadata {
   private:
    uint32_t size = 1;

   public:
    SlimeMetadata() = default;
    ~SlimeMetadata() override = default;

    [[nodiscard]] static uint8_t MaximumEntries(const ProtocolVersion* version) {
      return MobMetadata::MaximumEntries(version) + 1;
    }

    void Read(Metadata* metadata, const ProtocolVersion* version) override {
      MobMetadata::Read(metadata, version);

      size = metadata->GetVarInt(MobMetadata::MaximumEntries(version)).value_or(0);
    }

    void Write(Metadata* metadata, const ProtocolVersion* version) override {
      MobMetadata::Write(metadata, version);

      if (size != 1) {
        metadata->Set(MobMetadata::MaximumEntries(version), new VarIntMetadataEntry(size));
      }
    }

    [[nodiscard]] uint32_t GetSize() const {
      return size;
    }

    void SetSize(uint32_t value) {
      size = value;
    }
  };
}