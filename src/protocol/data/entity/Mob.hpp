#pragma once

#include "LivingEntity.hpp"

namespace Ship {

  class MobMetadata : public LivingEntityMetadata {
   private:
    union {
      struct {
        uint8_t noAI : 1;
        uint8_t leftHanded : 1;
        uint8_t aggressive : 1;
      };

      uint8_t value;
    } flags {};

   public:
    MobMetadata() = default;
    ~MobMetadata() override = default;

    static uint8_t MaximumEntries(const ProtocolVersion* version) {
      return LivingEntityMetadata::MaximumEntries(version) + 1;
    }

    void Read(Metadata* metadata, const ProtocolVersion* version) override {
      LivingEntityMetadata::Read(metadata, version);

      flags.value = metadata->GetByte(LivingEntityMetadata::MaximumEntries(version)).value_or(0);
    }

    void Write(Metadata* metadata, const ProtocolVersion* version) override {
      LivingEntityMetadata::Write(metadata, version);

      if (flags.value) {
        metadata->Set(LivingEntityMetadata::MaximumEntries(version), new ByteMetadataEntry(flags.value));
      }
    }

    [[nodiscard]] bool IsHasNoAI() const {
      return flags.noAI;
    }

    void SetHasNoAI(bool value) {
      flags.noAI = value;
    }

    [[nodiscard]] bool IsLeftHanded() const {
      return flags.leftHanded;
    }

    void SetLeftHanded(bool value) {
      flags.leftHanded = value;
    }

    [[nodiscard]] bool IsAggressive() const {
      return flags.aggressive;
    }

    void SetAggressive(bool value) {
      flags.aggressive = value;
    }
  };

  typedef MobMetadata InsentientMetadata;
}