#pragma once

#include "Animal.hpp"

namespace Ship {

  class RabbitMetadata : public AnimalMetadata {
   private:
    uint32_t type = 0;

   public:
    RabbitMetadata() = default;
    ~RabbitMetadata() override = default;

    [[nodiscard]] static uint8_t MaximumEntries(const ProtocolVersion* version) {
      return AnimalMetadata::MaximumEntries(version) + 1;
    }

    void Read(Metadata* metadata, const ProtocolVersion* version) override {
      AnimalMetadata::Read(metadata, version);

      type = metadata->GetVarInt(AnimalMetadata::MaximumEntries(version)).value_or(0);
    }

    void Write(Metadata* metadata, const ProtocolVersion* version) override {
      AnimalMetadata::Write(metadata, version);

      if (type) {
        metadata->Set(AnimalMetadata::MaximumEntries(version), new VarIntMetadataEntry(type));
      }
    }

    [[nodiscard]] uint32_t GetType() const {
      return type;
    }

    void SetType(uint32_t value) {
      type = value;
    }
  };
}