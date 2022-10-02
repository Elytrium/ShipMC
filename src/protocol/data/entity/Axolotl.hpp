#pragma once

#include "Animal.hpp"

namespace Ship {

  enum class AxolotlVariant {
    LUCY = 0,
    WILD = 1,
    GOLD = 2,
    CYAN = 3,
    BLUE = 4,
  };

  class AxolotlMetadata : public AnimalMetadata {
   private:
    AxolotlVariant variant = AxolotlVariant::LUCY;
    bool playingDead = false;
    bool fromBucket = false;

   public:
    AxolotlMetadata() = default;
    ~AxolotlMetadata() override = default;

    static uint8_t MaximumEntries(const ProtocolVersion* version) {
      return AnimalMetadata::MaximumEntries(version) + 3;
    }

    void Read(Metadata* metadata, const ProtocolVersion* version) override {
      AnimalMetadata::Read(metadata, version);
      uint8_t currentIndex = AnimalMetadata::MaximumEntries(version);

      variant = (AxolotlVariant) metadata->GetVarInt(currentIndex).value_or(0);
      playingDead = metadata->GetBoolean(currentIndex + 1).value_or(false);
      fromBucket = metadata->GetBoolean(currentIndex + 2).value_or(false);
    }

    void Write(Metadata* metadata, const ProtocolVersion* version) override {
      AnimalMetadata::Write(metadata, version);
      uint8_t currentIndex = AnimalMetadata::MaximumEntries(version);

      if (variant != AxolotlVariant::LUCY) {
        metadata->Set(currentIndex, new VarIntMetadataEntry((uint32_t) variant));
      }

      if (playingDead) {
        metadata->Set(currentIndex + 1, new BooleanMetadataEntry(playingDead));
      }

      if (fromBucket) {
        metadata->Set(currentIndex + 2, new BooleanMetadataEntry(fromBucket));
      }
    }

    [[nodiscard]] AxolotlVariant GetVariant() const {
      return variant;
    }

    void SetVariant(AxolotlVariant value) {
      variant = value;
    }

    [[nodiscard]] bool IsPlayingDead() const {
      return playingDead;
    }

    void SetPlayingDead(bool value) {
      playingDead = value;
    }

    [[nodiscard]] bool IsFromBucket() const {
      return fromBucket;
    }

    void SetFromBucket(bool value) {
      fromBucket = value;
    }
  };
}