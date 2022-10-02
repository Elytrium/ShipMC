#pragma once

#include "Entity.hpp"

namespace Ship {

  class ThrownPotionMetadata : public EntityMetadata {
   private:
    ItemStack potion;

   public:
    ThrownPotionMetadata() = default;
    ~ThrownPotionMetadata() override = default;

    [[nodiscard]] static uint8_t MaximumEntries(const ProtocolVersion* version) {
      return EntityMetadata::MaximumEntries(version) + 1;
    }

    void Read(Metadata* metadata, const ProtocolVersion* version) override {
      EntityMetadata::Read(metadata, version);

      potion = metadata->GetItemStack(EntityMetadata::MaximumEntries(version)).value_or(ItemStack {});
    }

    void Write(Metadata* metadata, const ProtocolVersion* version) override {
      EntityMetadata::Write(metadata, version);

      if (potion.IsPresent()) {
        metadata->Set(EntityMetadata::MaximumEntries(version), new ItemStackMetadataEntry(potion));
      }
    }

    [[nodiscard]] const ItemStack& GetPotion() const {
      return potion;
    }

    void SetPotion(const ItemStack& value) {
      potion = value;
    }
  };
}