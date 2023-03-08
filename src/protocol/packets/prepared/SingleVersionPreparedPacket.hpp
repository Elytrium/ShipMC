#pragma once

#include "../../../utils/ordinal/OrdinalRegistry.hpp"
#include "../Packet.hpp"
#include <string>

namespace Ship {

  class SingleVersionPreparedPacket : public Packet {
   private:
    ByteBuffer* unknownBytes;

   public:
    static inline const uint32_t PACKET_ORDINAL = OrdinalRegistry::PacketRegistry.RegisterOrdinal();

    SingleVersionPreparedPacket(const ProtocolVersion* version, ByteBuffer* buffer) {
      unknownBytes = buffer;
    }

    ~SingleVersionPreparedPacket() override {
      delete unknownBytes;
    }

    void Write(const ProtocolVersion* version, ByteBuffer* buffer) const override {
      buffer->WriteBytes(new ByteBufferImpl(unknownBytes), unknownBytes->GetReadableBytes());
    }

    uint32_t Size(const ProtocolVersion* version) const override {
      return unknownBytes->GetReadableBytes();
    }

    uint32_t GetOrdinal() const override {
      return PACKET_ORDINAL;
    }

    ByteBuffer* GetBytes() {
      return unknownBytes;
    }
  };
}
