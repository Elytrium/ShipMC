#pragma once


#include <string>
#include <utility>

namespace Ship {

  class LoginPluginMessage : public Packet {
   private:
    uint32_t id;
    std::string channel;
    ByteBuffer* data;
   public:
    static inline const uint32_t PACKET_ORDINAL = OrdinalRegistry::PacketRegistry.RegisterOrdinal();

    LoginPluginMessage(uint32_t id, std::string  channel, ByteBuffer* data) : id(id), channel(std::move(channel)), data(data) {
    }

    explicit LoginPluginMessage(const PacketHolder& holder) {
      ByteBuffer* buffer = holder.GetCurrentBuffer();
      id = buffer->ReadVarInt();
      channel = buffer->ReadString();
      size_t dataLen = holder.GetExpectedSize() - ByteBuffer::VarIntBytes(id) - ByteBuffer::StringBytes(channel);
      data = new ByteBufferImpl(buffer->ReadBytes(dataLen), dataLen);
    }


    ~LoginPluginMessage() override {
    }

    void Write(const ProtocolVersion* version, ByteBuffer* buffer) const override {
      buffer->WriteVarInt(id);
      buffer->WriteString(channel);
      buffer->WriteBytes(data, data->GetReadableBytes());
    }

    uint32_t GetOrdinal() const override {
      return PACKET_ORDINAL;
    }
  };
}
