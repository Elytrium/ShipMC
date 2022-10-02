#pragma once

#include "Entity.hpp"

namespace Ship {

  class ThrownExperienceBottleMetadata : public EntityMetadata {
   private:
    ItemStack item;

   public:
    ThrownExperienceBottleMetadata() = default;
    ~ThrownExperienceBottleMetadata() override = default;

    [[nodiscard]] static uint8_t MaximumEntries(const ProtocolVersion* version) {
      return EntityMetadata::MaximumEntries(version) + 1;
    }

    void Read(Metadata* metadata, const ProtocolVersion* version) override {
      EntityMetadata::Read(metadata, version);

      item = metadata->GetItemStack(EntityMetadata::MaximumEntries(version)).value_or(ItemStack {});
    }

    void Write(Metadata* metadata, const ProtocolVersion* version) override {
      EntityMetadata::Write(metadata, version);

      if (item.IsPresent()) {
        metadata->Set(EntityMetadata::MaximumEntries(version), new ItemStackMetadataEntry(item));
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