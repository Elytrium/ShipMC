#pragma once

#include "Entity.hpp"

namespace Ship {

  class FishingHookMetadata : public EntityMetadata {
   private:
    std::optional<uint32_t> hookedEntity;
    bool catchable = false;

   public:
    FishingHookMetadata() = default;
    ~FishingHookMetadata() override = default;

    [[nodiscard]] static uint8_t MaximumEntries(const ProtocolVersion* version) {
      if (version >= &MinecraftProtocolVersion::MINECRAFT_1_16_2) {
        return EntityMetadata::MaximumEntries(version) + 2;
      }
      return EntityMetadata::MaximumEntries(version) + 1;
    }

    void Read(Metadata* metadata, const ProtocolVersion* version) override {
      EntityMetadata::Read(metadata, version);

      hookedEntity = metadata->GetVarInt(EntityMetadata::MaximumEntries(version));
      if (hookedEntity) {
        if (*hookedEntity) {
          (*hookedEntity)--;
        } else {
          hookedEntity.reset();
        }
      }

      if (version >= &MinecraftProtocolVersion::MINECRAFT_1_16_2) {
        catchable = metadata->GetBoolean(EntityMetadata::MaximumEntries(version) + 1).value_or(false);
      }
    }

    void Write(Metadata* metadata, const ProtocolVersion* version) override {
      EntityMetadata::Write(metadata, version);

      if (hookedEntity) {
        metadata->Set(EntityMetadata::MaximumEntries(version), new VarIntMetadataEntry(*hookedEntity + 1));
      }

      if (version >= &MinecraftProtocolVersion::MINECRAFT_1_16_2) {
        if (catchable) {
          metadata->Set(EntityMetadata::MaximumEntries(version) + 1, new BooleanMetadataEntry(catchable));
        }
      }
    }

    [[nodiscard]] const std::optional<uint32_t>& GetHookedEntity() const {
      return hookedEntity;
    }

    void SetHookedEntity(const std::optional<uint32_t>& value) {
      hookedEntity = value;
    }

    [[nodiscard]] bool IsCatchable() const {
      return catchable;
    }

    void SetCatchable(bool value) {
      catchable = value;
    }
  };
}