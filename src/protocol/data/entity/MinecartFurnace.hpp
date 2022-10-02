#pragma once

#include "AbstractMinecart.hpp"

namespace Ship {

  class MinecartFurnaceMetadata : public AbstractMinecartMetadata {
   private:
    bool hasFuel = false;

   public:
    MinecartFurnaceMetadata() = default;
    ~MinecartFurnaceMetadata() override = default;

    [[nodiscard]] static uint8_t MaximumEntries(const ProtocolVersion* version) {
      return AbstractMinecartMetadata::MaximumEntries(version) + 1;
    }

    void Read(Metadata* metadata, const ProtocolVersion* version) override {
      AbstractMinecartMetadata::Read(metadata, version);

      hasFuel = metadata->GetBoolean(AbstractMinecartMetadata::MaximumEntries(version)).value_or(false);
    }

    void Write(Metadata* metadata, const ProtocolVersion* version) override {
      AbstractMinecartMetadata::Write(metadata, version);

      if (hasFuel) {
        metadata->Set(AbstractMinecartMetadata::MaximumEntries(version), new BooleanMetadataEntry(hasFuel));
      }
    }

    [[nodiscard]] bool IsHasFuel() const {
      return hasFuel;
    }

    void SetHasFuel(bool value) {
      hasFuel = value;
    }
  };
}