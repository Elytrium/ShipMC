#pragma once

#include "Entity.hpp"

namespace Ship {

  class ThrownEggMetadata : public EntityMetadata {
   private:
    ItemStack item;

   public:
    ThrownEggMetadata() = default;
    ~ThrownEggMetadata() override = default;

    [[nodiscard]] static uint8_t MaximumEntries(const ProtocolVersion* version) {
      if (version >= &MinecraftProtocolVersion::MINECRAFT_1_14) {
        return EntityMetadata::MaximumEntries(version) + 1;
      }
      return EntityMetadata::MaximumEntries(version);
    }

    void Read(Metadata* metadata, const ProtocolVersion* version) override {
      EntityMetadata::Read(metadata, version);

      if (version >= &MinecraftProtocolVersion::MINECRAFT_1_14) {
        item = metadata->GetItemStack(EntityMetadata::MaximumEntries(version)).value_or(ItemStack {});
      }
    }

    void Write(Metadata* metadata, const ProtocolVersion* version) override {
      EntityMetadata::Write(metadata, version);

      if (version >= &MinecraftProtocolVersion::MINECRAFT_1_14) {
        if (item.IsPresent()) {
          metadata->Set(EntityMetadata::MaximumEntries(version), new ItemStackMetadataEntry(item));
        }
      }
    }

    [[nodiscard]] const ItemStack& GetItem() const {
      return item;
    }

    void SetItem(const ItemStack& value) {
      item = value;
    }
  };
}