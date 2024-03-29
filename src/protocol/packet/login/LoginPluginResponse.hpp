#pragma once

#include "ShipNet/utils/ordinal/OrdinalRegistry.hpp"
#include <string>

namespace Ship {

  class LoginPluginResponse : public Packet {
   private:
    uint32_t id;
    bool success;
    ByteBuffer* data;

   public:
    static inline const uint32_t PACKET_ORDINAL = OrdinalRegistry::PacketRegistry.RegisterOrdinal();

    LoginPluginResponse() = default;

    LoginPluginResponse(uint32_t id, bool success, ByteBuffer* data) : id(id), success(success), data(data) {
    }

    static Errorable<LoginPluginResponse> Instantiate(const PacketHolder& holder) {
      ByteBuffer* buffer = holder.GetCurrentBuffer();
      ProceedErrorable(id, uint32_t, buffer->ReadVarInt(), InvalidPacketErrorable<LoginPluginResponse>(PACKET_ORDINAL))
      ProceedErrorable(success, bool, buffer->ReadBoolean(), InvalidPacketErrorable<LoginPluginResponse>(PACKET_ORDINAL))
      size_t dataLen = holder.GetExpectedSize() - ByteBuffer::VarIntBytes(id) - ByteBuffer::BOOLEAN_SIZE;
      ProceedErrorable(rawData, uint8_t*, buffer->ReadBytes(dataLen), InvalidPacketErrorable<LoginPluginResponse>(PACKET_ORDINAL))
      ByteBuffer* data = new ByteBufferImpl(rawData, dataLen);
      return SuccessErrorable<LoginPluginResponse>({id, success, data});
    }

    ~LoginPluginResponse() override {
      delete data;
    }

    Errorable<bool> Write(const ProtocolVersion* version, ByteBuffer* buffer) const override {
      buffer->WriteVarInt(id);
      buffer->WriteBoolean(success);
      buffer->WriteBytes(data, data->GetReadableBytes());
      return SuccessErrorable<bool>(true);
    }

    [[nodiscard]] uint32_t GetOrdinal() const override {
      return PACKET_ORDINAL;
    }
  };
}
