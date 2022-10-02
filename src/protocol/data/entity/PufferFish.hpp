#pragma once

#include "AbstractFish.hpp"

namespace Ship {

  class PufferFishMetadata : public AbstractFishMetadata {
   private:
    uint32_t puffState = 0;

   public:
    PufferFishMetadata() = default;
    ~PufferFishMetadata() override = default;

    [[nodiscard]] static uint8_t MaximumEntries(const ProtocolVersion* version) {
      return AbstractFishMetadata::MaximumEntries(version) + 1;
    }

    void Read(Metadata* metadata, const ProtocolVersion* version) override {
      AbstractFishMetadata::Read(metadata, version);

      puffState = metadata->GetVarInt(AbstractFishMetadata::MaximumEntries(version)).value_or(0);
    }

    void Write(Metadata* metadata, const ProtocolVersion* version) override {
      AbstractFishMetadata::Write(metadata, version);

      if (puffState) {
        metadata->Set(AbstractFishMetadata::MaximumEntries(version), new VarIntMetadataEntry(puffState));
      }
    }

    [[nodiscard]] uint32_t GetPuffState() const {
      return puffState;
    }

    void SetPuffState(uint32_t value) {
      puffState = value;
    }
  };
}