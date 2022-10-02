#pragma once

#include "WaterAnimal.hpp"

namespace Ship {

  class AbstractFishMetadata : public WaterAnimalMetadata {
   private:
    bool fromBucket = false;

   public:
    AbstractFishMetadata() = default;
    ~AbstractFishMetadata() override = default;

    [[nodiscard]] static uint8_t MaximumEntries(const ProtocolVersion* version) {
      return WaterAnimalMetadata::MaximumEntries(version) + 1;
    }

    void Read(Metadata* metadata, const ProtocolVersion* version) override {
      WaterAnimalMetadata::Read(metadata, version);

      fromBucket = metadata->GetBoolean(WaterAnimalMetadata::MaximumEntries(version)).value_or(false);
    }

    void Write(Metadata* metadata, const ProtocolVersion* version) override {
      WaterAnimalMetadata::Write(metadata, version);

      if (fromBucket) {
        metadata->Set(WaterAnimalMetadata::MaximumEntries(version), new BooleanMetadataEntry(fromBucket));
      }
    }

    [[nodiscard]] bool IsFromBucket() const {
      return fromBucket;
    }

    void SetFromBucket(bool value) {
      fromBucket = value;
    }
  };
}