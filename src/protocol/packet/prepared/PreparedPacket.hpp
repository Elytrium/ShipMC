#pragma once

#include "ShipNet/protocol/Protocol.hpp"
#include "ShipNet/protocol/packet/Packet.hpp"
#include "ShipNet/utils/ordinal/OrdinalRegistry.hpp"
#include "../../MinecraftProtocol.hpp"
#include <string>

namespace Ship {

  class PreparedPacket : public Packet {
   private:
    ByteBuffer** unknownBytes = new ByteBuffer*[MinecraftProtocolVersion::VERSIONS.GetMaximumVersion().GetOrdinal() + 1];

   public:
    static inline const uint32_t PACKET_ORDINAL = OrdinalRegistry::PacketRegistry.RegisterOrdinal();

    ~PreparedPacket() override {
      for (int i = 0; i <= MinecraftProtocolVersion::VERSIONS.GetMaximumVersion().GetOrdinal(); ++i) {
        delete unknownBytes[i];
      }

      delete[] unknownBytes;
    }

    static Errorable<PreparedPacket> Instantiate(const PacketHolder& holder) {
      // ByteBuffer* buffer = holder.GetCurrentBuffer();
      // const ProtocolVersion* version = holder.GetVersion();
      // unknownBytes[version->GetOrdinal()] = buffer;
      return SuccessErrorable<PreparedPacket>({}); // TODO: should we instantiate prepared packet?
    }

    Errorable<bool> Write(const ProtocolVersion* version, ByteBuffer* buffer) const override {
      auto* temp = new ByteBufferImpl(unknownBytes[version->GetOrdinal()]);
      buffer->WriteBytes(temp, temp->GetReadableBytes());
      return SuccessErrorable<bool>(true);
    }

    uint32_t Size(const ProtocolVersion* version) const override {
      return unknownBytes[version->GetOrdinal()]->GetReadableBytes();
    }

    [[nodiscard]] uint32_t GetOrdinal() const override {
      return PACKET_ORDINAL;
    }

    ByteBuffer* GetBytes(const ProtocolVersion* version) {
      return new ByteBufferImpl(unknownBytes[version->GetOrdinal()]);
    }
  };
}
