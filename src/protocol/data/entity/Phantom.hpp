#pragma once

#include "Flying.hpp"

namespace Ship {

  class PhantomMetadata : public FlyingMetadata {
   private:
    uint32_t size = 0;

   public:
    PhantomMetadata() = default;
    ~PhantomMetadata() override = default;

    [[nodiscard]] static uint8_t MaximumEntries(const ProtocolVersion* version) {
      return FlyingMetadata::MaximumEntries(version) + 1;
    }

    void Read(Metadata* metadata, const ProtocolVersion* version) override {
      FlyingMetadata::Read(metadata, version);

      size = metadata->GetVarInt(FlyingMetadata::MaximumEntries(version)).value_or(0);
    }

    void Write(Metadata* metadata, const ProtocolVersion* version) override {
      FlyingMetadata::Write(metadata, version);

      if (size) {
        metadata->Set(FlyingMetadata::MaximumEntries(version), new VarIntMetadataEntry(size));
      }
    }

    [[nodiscard]] uint32_t GetSize() const {
      return size;
    }

    void SetSize(uint32_t value) {
      size = value;
    }
  };
}