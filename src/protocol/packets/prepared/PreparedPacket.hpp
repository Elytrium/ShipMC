#pragma once

#include "../../../utils/ordinal/OrdinalRegistry.hpp"
#include "../Packet.hpp"
#include <string>

namespace Ship {

  class PreparedPacket : public Packet {
   private:
    ByteBuffer** unknownBytes = new ByteBuffer*[ProtocolVersion::MAXIMUM_VERSION.GetOrdinal() + 1];

   public:
    static inline const uint32_t PACKET_ORDINAL = OrdinalRegistry::PacketRegistry.RegisterOrdinal();

    ~PreparedPacket() override {
      for (int i = 0; i <= ProtocolVersion::MAXIMUM_VERSION.GetOrdinal(); ++i) {
        delete unknownBytes[i];
      }

      delete[] unknownBytes;
    }

    void Read(const ProtocolVersion* version, ByteBuffer* buffer) override {
      unknownBytes[version->GetOrdinal()] = buffer;
    }

    void Write(const ProtocolVersion* version, ByteBuffer* buffer) override {
      auto* temp = new ByteBuffer(*unknownBytes[version->GetOrdinal()]);
      buffer->WriteBytes(temp, temp->GetReadableBytes());
    }

    uint32_t Size(const ProtocolVersion* version) override {
      return unknownBytes[version->GetOrdinal()]->GetReadableBytes();
    }

    uint32_t GetOrdinal() override {
      return PACKET_ORDINAL;
    }

    ByteBuffer* GetBytes(const ProtocolVersion* version) {
      return new ByteBuffer(*unknownBytes[version->GetOrdinal()]);
    }
  };
}
