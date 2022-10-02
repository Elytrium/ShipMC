#pragma once

#include "Monster.hpp"

namespace Ship {

  class BasePiglinMetadata : public MonsterMetadata {
   private:
    bool immuneToZombification = false;

   public:
    BasePiglinMetadata() = default;
    ~BasePiglinMetadata() override = default;

    static uint8_t MaximumEntries(const ProtocolVersion* version) {
      return MonsterMetadata::MaximumEntries(version) + 1;
    }

    void Read(Metadata* metadata, const ProtocolVersion* version) override {
      MonsterMetadata::Read(metadata, version);
      uint8_t currentIndex = MonsterMetadata::MaximumEntries(version);

      immuneToZombification = metadata->GetBoolean(currentIndex).value_or(false);
    }

    void Write(Metadata* metadata, const ProtocolVersion* version) override {
      MonsterMetadata::Write(metadata, version);
      uint8_t currentIndex = MonsterMetadata::MaximumEntries(version);

      if (immuneToZombification) {
        metadata->Set(currentIndex, new BooleanMetadataEntry(immuneToZombification));
      }
    }

    [[nodiscard]] bool IsImmuneToZombification() const {
      return immuneToZombification;
    }

    void SetImmuneToZombification(bool value) {
      immuneToZombification = value;
    }
  };
}