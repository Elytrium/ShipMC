#pragma once

#include "Entity.hpp"

namespace Ship {

  class WitherSkullMetadata : public EntityMetadata {
   private:
    bool invulnerable = false;

   public:
    WitherSkullMetadata() = default;
    ~WitherSkullMetadata() override = default;

    static uint8_t MaximumEntries(const ProtocolVersion* version) {
      return EntityMetadata::MaximumEntries(version) + 1;
    }

    void Read(Metadata* metadata, const ProtocolVersion* version) override {
      EntityMetadata::Read(metadata, version);

      invulnerable = metadata->GetBoolean(EntityMetadata::MaximumEntries(version)).value_or(false);
    }

    void Write(Metadata* metadata, const ProtocolVersion* version) override {
      EntityMetadata::Write(metadata, version);

      if (invulnerable) {
        metadata->Set(EntityMetadata::MaximumEntries(version), new BooleanMetadataEntry(invulnerable));
      }
    }

    [[nodiscard]] bool IsInvulnerable() const {
      return invulnerable;
    }

    void SetInvulnerable(bool value) {
      invulnerable = value;
    }
  };
}