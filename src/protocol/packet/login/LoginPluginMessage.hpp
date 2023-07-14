#pragma once

#include "ShipNet/utils/ordinal/OrdinalRegistry.hpp"
#include <string>
#include <utility>

namespace Ship {

  class LoginPluginMessage : public Packet {
   private:
    uint32_t id{};
    std::string channel;
    ByteBuffer* data{};
   public:
    static inline const uint32_t PACKET_ORDINAL = OrdinalRegistry::PacketRegistry.RegisterOrdinal();

    LoginPluginMessage() = default;

    LoginPluginMessage(uint32_t id, std::string channel, ByteBuffer* data) : id(id), channel(std::move(channel)), data(data) {
    }

    static Errorable<LoginPluginMessage> Instantiate(const PacketHolder& holder) {
      ByteBuffer* buffer = holder.GetCurrentBuffer();
      ProceedErrorable(id, uint32_t, buffer->ReadVarInt(), InvalidPacketErrorable<LoginPluginMessage>(PACKET_ORDINAL))
      ProceedErrorable(channel, std::string, buffer->ReadString(), InvalidPacketErrorable<LoginPluginMessage>(PACKET_ORDINAL))
      size_t dataLen = holder.GetExpectedSize() - ByteBuffer::VarIntBytes(id) - ByteBuffer::StringBytes(channel);
      ProceedErrorable(dataBytes, uint8_t*, buffer->ReadBytes(dataLen), InvalidPacketErrorable<LoginPluginMessage>(PACKET_ORDINAL))
      ByteBuffer* data = new ByteBufferImpl(dataBytes, dataLen);
      return SuccessErrorable<LoginPluginMessage>(LoginPluginMessage(id, channel, data));
    }

    ~LoginPluginMessage() override {
      delete data;
    }

    Errorable<bool> Write(const ProtocolVersion* version, ByteBuffer* buffer) const override {
      buffer->WriteVarInt(id);
      buffer->WriteString(channel);
      buffer->WriteBytes(data, data->GetReadableBytes());
      return SuccessErrorable<bool>(true);
    }

    [[nodiscard]] uint32_t GetOrdinal() const override {
      return PACKET_ORDINAL;
    }
  };
}
