#pragma once

#include "../Protocol.hpp"

namespace Ship {

  class PacketHolder {
   private:
    uint32_t ordinal;
    const ProtocolVersion* version;
    ByteBuffer* currentBuffer;
    uint32_t expectedSize;

   public:
    PacketHolder(uint32_t ordinal, const ProtocolVersion* version, ByteBuffer* currentBuffer, uint32_t expectedSize)
      : ordinal(ordinal), version(version), currentBuffer(currentBuffer), expectedSize(expectedSize) {
    }

    uint32_t GetOrdinal() const {
      return ordinal;
    }

    const ProtocolVersion* GetVersion() const {
      return version;
    }

    ByteBuffer* GetCurrentBuffer() const {
      return currentBuffer;
    }

    uint32_t GetExpectedSize() const {
      return expectedSize;
    }
  };

  class Packet : public Serializable {
   public:
    ~Packet() override = default;

    virtual uint32_t GetOrdinal() const = 0;
    virtual bool SupportsOn(const ProtocolVersion* version) {
      // TODO: possibly we should do it in registry
      return true;
    }
  };
}
