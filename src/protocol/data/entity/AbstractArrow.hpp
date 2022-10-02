#pragma once

#include "Entity.hpp"

namespace Ship {

  class AbstractArrowMetadata : public EntityMetadata {
   private:
    union {
      struct {
        uint8_t critical : 1;
        uint8_t noclip : 1;
      };

      uint8_t value;
    } flags {};
    uint8_t piercingLevel = 0;
    std::optional<UUID> shooter;

   public:
    AbstractArrowMetadata() = default;
    ~AbstractArrowMetadata() override = default;

    [[nodiscard]] static uint8_t MaximumEntries(const ProtocolVersion* version) {
      if (version >= &ProtocolVersion::MINECRAFT_1_16_2) {
        return EntityMetadata::MaximumEntries(version) + 2;
      } else if (version >= &ProtocolVersion::MINECRAFT_1_14) {
        return EntityMetadata::MaximumEntries(version) + 3;
      } else if (version <= &ProtocolVersion::MINECRAFT_1_12_2) {
        return EntityMetadata::MaximumEntries(version) + 1;
      }
      return EntityMetadata::MaximumEntries(version) + 2;
    }

    void Read(Metadata* metadata, const ProtocolVersion* version) override {
      EntityMetadata::Read(metadata, version);
      uint8_t currentIndex = EntityMetadata::MaximumEntries(version);

      flags.value = metadata->GetByte(currentIndex).value_or(0);

      if (version >= &ProtocolVersion::MINECRAFT_1_16_2) {
        piercingLevel = metadata->GetByte(currentIndex + 1).value_or(0);
      } else if (version >= &ProtocolVersion::MINECRAFT_1_13) {
        shooter = metadata->GetOptUUID(currentIndex + 1).value_or(std::nullopt);
        if (version >= &ProtocolVersion::MINECRAFT_1_14) {
          piercingLevel = metadata->GetByte(currentIndex + 2).value_or(0);
        }
      }
    }

    void Write(Metadata* metadata, const ProtocolVersion* version) override {
      EntityMetadata::Write(metadata, version);
      uint8_t currentIndex = EntityMetadata::MaximumEntries(version);

      if (flags.value) {
        metadata->Set(currentIndex, new ByteMetadataEntry(flags.value));
      }

      if (version >= &ProtocolVersion::MINECRAFT_1_16_2) {
        if (piercingLevel) {
          metadata->Set(currentIndex + 1, new ByteMetadataEntry(piercingLevel));
        }
      } else if (version >= &ProtocolVersion::MINECRAFT_1_13) {
        if (shooter) {
          metadata->Set(currentIndex + 1, new OptUUIDMetadataEntry(shooter));
        }
        if (version >= &ProtocolVersion::MINECRAFT_1_14) {
          if (piercingLevel) {
            metadata->Set(currentIndex + 2, new ByteMetadataEntry(piercingLevel));
          }
        }
      }
    }

    [[nodiscard]] bool IsCritical() const {
      return flags.critical;
    }

    void SetCritical(bool value) {
      flags.critical = value;
    }

    [[nodiscard]] bool IsNoclip() const {
      return flags.noclip;
    }

    void SetNoclip(bool value) {
      flags.noclip = value;
    }

    void SetPiercingLevel(uint8_t value) {
      piercingLevel = value;
    }

    [[nodiscard]] uint8_t GetPiercingLevel() const {
      return piercingLevel;
    }

    [[nodiscard]] const std::optional<UUID>& GetShooter() const {
      return shooter;
    }

    void SetShooter(const std::optional<UUID>& value) {
      shooter = value;
    }
  };
}