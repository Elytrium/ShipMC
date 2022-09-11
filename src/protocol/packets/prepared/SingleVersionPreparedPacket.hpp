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

    ~SingleVersionPreparedPacket() override {
      delete unknownBytes;
    }

    void Read(const ProtocolVersion* version, ByteBuffer* buffer) override {
      unknownBytes = buffer;
    }

    void Write(const ProtocolVersion* version, ByteBuffer* buffer) override {
      buffer->WriteBytes(new ByteBuffer(*unknownBytes), unknownBytes->GetReadableBytes());
    }

    uint32_t Size(const ProtocolVersion* version) override {
      return unknownBytes->GetReadableBytes();
    }

    uint32_t GetOrdinal() override {
      return PACKET_ORDINAL;
    }

    ByteBuffer* GetBytes() {
      return unknownBytes;
    }
  };
}
