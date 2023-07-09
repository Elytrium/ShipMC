#pragma once

#include "Monster.hpp"

namespace Ship {

  class EndermanMetadata : public MonsterMetadata {
   private:
    uint32_t carriedBlock = 0;
    bool screaming = false;
    bool staring = false;

   public:
    EndermanMetadata() = default;
    ~EndermanMetadata() override = default;

    static uint8_t MaximumEntries(const ProtocolVersion* version) {
      if (version >= &MinecraftProtocolVersion::MINECRAFT_1_15) {
        return MobMetadata::MaximumEntries(version) + 3;
      }
      return MobMetadata::MaximumEntries(version) + 2;
    }

    void Read(Metadata* metadata, const ProtocolVersion* version) override {
      MonsterMetadata::Read(metadata, version);
      uint8_t currentIndex = MonsterMetadata::MaximumEntries(version);

      carriedBlock = metadata->GetBlockID(currentIndex).value_or(0);
      screaming = metadata->GetBoolean(currentIndex + 1).value_or(false);

      if (version >= &MinecraftProtocolVersion::MINECRAFT_1_15) {
        staring = metadata->GetBoolean(currentIndex + 2).value_or(false);
      }
    }

    void Write(Metadata* metadata, const ProtocolVersion* version) override {
      MonsterMetadata::Write(metadata, version);
      uint8_t currentIndex = MonsterMetadata::MaximumEntries(version);

      if (carriedBlock) {
        metadata->Set(currentIndex, new BlockIDMetadataEntry(carriedBlock));
      }

      if (screaming) {
        metadata->Set(currentIndex + 1, new BooleanMetadataEntry(screaming));
      }

      if (version >= &MinecraftProtocolVersion::MINECRAFT_1_15) {
        if (staring) {
          metadata->Set(currentIndex + 2, new BooleanMetadataEntry(staring));
        }
      }
    }

    [[nodiscard]] uint32_t GetCarriedBlock() const {
      return carriedBlock;
    }

    void SetCarriedBlock(uint32_t value) {
      carriedBlock = value;
    }

    [[nodiscard]] bool IsScreaming() const {
      return screaming;
    }

    void SetScreaming(bool value) {
      screaming = value;
    }

    [[nodiscard]] bool IsStaring() const {
      return staring;
    }

    void SetStaring(bool value) {
      staring = value;
    }
  };
}