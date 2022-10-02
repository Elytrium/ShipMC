#pragma once

#include "Metadata.hpp"

namespace Ship {

  class ParsedMetadata {
   public:
    virtual ~ParsedMetadata() = default;

    virtual void Read(Metadata* metadata, const ProtocolVersion* version) = 0;
    virtual void Write(Metadata* metadata, const ProtocolVersion* version) = 0;
  };
}