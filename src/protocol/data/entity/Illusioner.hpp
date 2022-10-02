#pragma once

#include "SpellcasterIllager.hpp"

namespace Ship {

  class IllusionerMetadata : public SpellcasterIllagerMetadata {
   public:
    IllusionerMetadata() = default;
    ~IllusionerMetadata() override = default;

    void Read(Metadata* metadata, const ProtocolVersion* version) override {
      SpellcasterIllagerMetadata::Read(metadata, version);
    }

    void Write(Metadata* metadata, const ProtocolVersion* version) override {
      SpellcasterIllagerMetadata::Write(metadata, version);
    }
  };
}