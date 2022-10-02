#pragma once

#include "AbstractIllager.hpp"

namespace Ship {

  enum class SpellType {
    NONE = 0,
    SUMMON_VEX = 1,
    ATTACK = 2,
    WOLOLO = 3,
    DISAPPEAR = 4,
    BLINDNESS = 5,
  };

  class SpellcasterIllagerMetadata : public AbstractIllagerMetadata {
   private:
    SpellType spell = SpellType::NONE;

   public:
    SpellcasterIllagerMetadata() = default;
    ~SpellcasterIllagerMetadata() override = default;

    [[nodiscard]] static uint8_t MaximumEntries(const ProtocolVersion* version) {
      return AbstractIllagerMetadata::MaximumEntries(version) + 1;
    }

    void Read(Metadata* metadata, const ProtocolVersion* version) override {
      AbstractIllagerMetadata::Read(metadata, version);

      spell = (SpellType) metadata->GetByte(AbstractIllagerMetadata::MaximumEntries(version)).value_or(0);
    }

    void Write(Metadata* metadata, const ProtocolVersion* version) override {
      AbstractIllagerMetadata::Write(metadata, version);

      if (spell != SpellType::NONE) {
        metadata->Set(AbstractIllagerMetadata::MaximumEntries(version), new ByteMetadataEntry((uint8_t) spell));
      }
    }

    [[nodiscard]] SpellType GetSpell() const {
      return spell;
    }

    void SetSpell(SpellType value) {
      spell = value;
    }
  };
}