#pragma once

#include "metadata/ParsedMetadata.hpp"

namespace Ship {

  class TraderLlamaMetadata : public ParsedMetadata {
   public:
    TraderLlamaMetadata() = default;
    ~TraderLlamaMetadata() override = default;

    [[nodiscard]] static uint8_t MaximumEntries(const ProtocolVersion* version) {
      return 0;
    }

    void Read(Metadata* metadata, const ProtocolVersion* version) override {
    }

    void Write(Metadata* metadata, const ProtocolVersion* version) override {
    }
  };
}