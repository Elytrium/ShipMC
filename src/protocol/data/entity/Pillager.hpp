#pragma once

#include "AbstractIllager.hpp"

namespace Ship {

  class PillagerMetadata : public AbstractIllagerMetadata {
   private:
    bool charging = false;

   public:
    PillagerMetadata() = default;
    ~PillagerMetadata() override = default;

    [[nodiscard]] static uint8_t MaximumEntries(const ProtocolVersion* version) {
      if (version >= &ProtocolVersion::MINECRAFT_1_17) {
        return AbstractIllagerMetadata::MaximumEntries(version) + 1;
      }
      return AbstractIllagerMetadata::MaximumEntries(version);
    }

    void Read(Metadata* metadata, const ProtocolVersion* version) override {
      AbstractIllagerMetadata::Read(metadata, version);

      if (version >= &ProtocolVersion::MINECRAFT_1_17) {
        charging = metadata->GetBoolean(AbstractIllagerMetadata::MaximumEntries(version)).value_or(false);
      }
    }

    void Write(Metadata* metadata, const ProtocolVersion* version) override {
      AbstractIllagerMetadata::Write(metadata, version);

      if (version >= &ProtocolVersion::MINECRAFT_1_17) {
        if (charging) {
          metadata->Set(AbstractIllagerMetadata::MaximumEntries(version), new BooleanMetadataEntry(charging));
        }
      }
    }

    [[nodiscard]] bool IsCharging() const {
      return charging;
    }

    void SetCharging(bool value) {
      charging = value;
    }
  };
}