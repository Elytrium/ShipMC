#pragma once

#include "Entity.hpp"

namespace Ship {

  class ItemFrameMetadata : public EntityMetadata {
   private:
    ItemStack item;
    uint32_t rotation = 0;

   public:
    ItemFrameMetadata() = default;
    ~ItemFrameMetadata() override = default;

    static uint8_t MaximumEntries(const ProtocolVersion* version) {
      return EntityMetadata::MaximumEntries(version) + 2;
    }

    void Read(Metadata* metadata, const ProtocolVersion* version) override {
      EntityMetadata::Read(metadata, version);

      uint8_t currentIndex = EntityMetadata::MaximumEntries(version);
      item = metadata->GetItemStack(currentIndex).value_or(ItemStack {});
      rotation = metadata->GetVarInt(currentIndex + 1).value_or(0);
    }

    void Write(Metadata* metadata, const ProtocolVersion* version) override {
      EntityMetadata::Write(metadata, version);

      uint8_t currentIndex = EntityMetadata::MaximumEntries(version);

      if (item.IsPresent()) {
        metadata->Set(currentIndex, new ItemStackMetadataEntry(item));
      }

      if (rotation) {
        metadata->Set(currentIndex + 1, new VarIntMetadataEntry(rotation));
      }
    }

    [[nodiscard]] const ItemStack& GetItem() const {
      return item;
    }

    void SetItem(const ItemStack& value) {
      item = value;
    }

    [[nodiscard]] uint32_t GetRotation() const {
      return rotation;
    }

    void SetRotation(uint32_t value) {
      rotation = value;
    }
  };
}