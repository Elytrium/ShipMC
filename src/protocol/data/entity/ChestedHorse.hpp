#pragma once

#include "AbstractHorse.hpp"

namespace Ship {

  class ChestedHorseMetadata : public AbstractHorseMetadata {
   private:
    bool hasChest = false;

   public:
    ChestedHorseMetadata() = default;
    ~ChestedHorseMetadata() override = default;

    static uint8_t MaximumEntries(const ProtocolVersion* version) {
      return AbstractHorseMetadata::MaximumEntries(version) + 1;
    }

    void Read(Metadata* metadata, const ProtocolVersion* version) override {
      AbstractHorseMetadata::Read(metadata, version);

      hasChest = metadata->GetBoolean(AbstractHorseMetadata::MaximumEntries(version)).value_or(false);
    }

    void Write(Metadata* metadata, const ProtocolVersion* version) override {
      AbstractHorseMetadata::Write(metadata, version);

      if (hasChest) {
        metadata->Set(AbstractHorseMetadata::MaximumEntries(version), new BooleanMetadataEntry(hasChest));
      }
    }

    [[nodiscard]] bool IsHasChest() const {
      return hasChest;
    }

    void SetHasChest(bool value) {
      hasChest = value;
    }
  };
}