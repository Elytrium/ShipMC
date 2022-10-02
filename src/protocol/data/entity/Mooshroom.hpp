#pragma once

#include "Cow.hpp"

namespace Ship {

  class MooshroomMetadata : public CowMetadata {
   private:
    std::string variant = "red";

   public:
    MooshroomMetadata() = default;
    ~MooshroomMetadata() override = default;

    [[nodiscard]] static uint8_t MaximumEntries(const ProtocolVersion* version) {
      return CowMetadata::MaximumEntries(version) + 1;
    }

    void Read(Metadata* metadata, const ProtocolVersion* version) override {
      CowMetadata::Read(metadata, version);

      variant = metadata->GetString(CowMetadata::MaximumEntries(version)).value_or("red");
    }

    void Write(Metadata* metadata, const ProtocolVersion* version) override {
      CowMetadata::Write(metadata, version);

      if (variant != "red") {
        metadata->Set(CowMetadata::MaximumEntries(version), new StringMetadataEntry(variant));
      }
    }

    [[nodiscard]] const std::string& GetVariant() const {
      return variant;
    }

    void SetVariant(const std::string& value) {
      variant = value;
    }
  };
}