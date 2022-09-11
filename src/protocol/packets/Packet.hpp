#pragma once

#include "../Protocol.hpp"

namespace Ship {

  class Packet {
   public:
    virtual ~Packet() = default;

    virtual void Read(const ProtocolVersion* version, ByteBuffer* buffer) = 0;
    virtual void Write(const ProtocolVersion* version, ByteBuffer* buffer) = 0;
    virtual uint32_t Size(const ProtocolVersion* version) = 0;
    virtual uint32_t GetOrdinal() = 0;
    virtual bool SupportsOn(const ProtocolVersion* version) {
      return true;
    }
  };
}
