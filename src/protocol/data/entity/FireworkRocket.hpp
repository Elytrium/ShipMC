#pragma once

#include "Entity.hpp"

namespace Ship {

  class FireworkRocketMetadata : public EntityMetadata {
   private:
    ItemStack firework;
    std::optional<uint32_t> entity;
    bool shotAtAngle = false;

   public:
    FireworkRocketMetadata() = default;
    ~FireworkRocketMetadata() override = default;

    static uint8_t MaximumEntries(const ProtocolVersion* version) {
      if (version >= &MinecraftProtocolVersion::MINECRAFT_1_14) {
        return EntityMetadata::MaximumEntries(version) + 3;
      }
      return EntityMetadata::MaximumEntries(version) + 2;
    }

    void Read(Metadata* metadata, const ProtocolVersion* version) override {
      EntityMetadata::Read(metadata, version);

      uint8_t currentIndex = EntityMetadata::MaximumEntries(version);

      firework = metadata->GetItemStack(currentIndex).value_or(ItemStack {});
      if (version >= &MinecraftProtocolVersion::MINECRAFT_1_16_2) {
        entity = metadata->GetOptVarInt(currentIndex + 1).value_or(std::nullopt);
      } else {
        entity = metadata->GetVarInt(currentIndex + 1).value_or(0);
      }
      if (version >= &MinecraftProtocolVersion::MINECRAFT_1_14) {
        shotAtAngle = metadata->GetBoolean(currentIndex + 2).value_or(false);
      }
    }

    void Write(Metadata* metadata, const ProtocolVersion* version) override {
      EntityMetadata::Write(metadata, version);

      uint8_t currentIndex = EntityMetadata::MaximumEntries(version);

      if (firework.IsPresent()) {
        metadata->Set(currentIndex, new ItemStackMetadataEntry(firework));
      }

      if (entity) {
        if (version >= &MinecraftProtocolVersion::MINECRAFT_1_16_2) {
          metadata->Set(currentIndex + 1, new OptVarIntMetadataEntry(entity));
        } else {
          metadata->Set(currentIndex + 1, new VarIntMetadataEntry(entity.value()));
        }
      }

      if (version >= &MinecraftProtocolVersion::MINECRAFT_1_14) {
        if (shotAtAngle) {
          metadata->Set(currentIndex + 2, new BooleanMetadataEntry(shotAtAngle));
        }
      }
    }

    [[nodiscard]] const ItemStack& GetFirework() const {
      return firework;
    }

    void SetFirework(const ItemStack& value) {
      firework = value;
    }

    [[nodiscard]] const std::optional<uint32_t>& GetEntity() const {
      return entity;
    }

    void SetEntity(const std::optional<uint32_t>& value) {
      entity = value;
    }

    [[nodiscard]] bool IsShotAtAngle() const {
      return shotAtAngle;
    }

    void SetShotAtAngle(bool value) {
      shotAtAngle = value;
    }
  };
}