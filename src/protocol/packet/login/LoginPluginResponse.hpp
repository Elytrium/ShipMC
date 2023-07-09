#pragma once


#include <string>

namespace Ship {

  class LoginPluginResponse : public Packet {
   private:
    uint32_t id;
    bool success;
    ByteBuffer* data;

   public:
    static inline const uint32_t PACKET_ORDINAL = OrdinalRegistry::PacketRegistry.RegisterOrdinal();

    LoginPluginResponse(uint32_t id, bool success, ByteBuffer* data) : id(id), success(success), data(data) {
    }

    explicit LoginPluginResponse(const PacketHolder& holder) {
      ByteBuffer* buffer = holder.GetCurrentBuffer();
      id = buffer->ReadVarInt();
      success = buffer->ReadBoolean();
      size_t dataLen = holder.GetExpectedSize() - ByteBuffer::VarIntBytes(id) - ByteBuffer::BOOLEAN_SIZE;
      data = new ByteBufferImpl(buffer->ReadBytes(dataLen), dataLen);
    }

    ~LoginPluginResponse() override {
      delete data;
    }

    void Write(const ProtocolVersion* version, ByteBuffer* buffer) const override {
      buffer->WriteVarInt(id);
      buffer->WriteBoolean(success);
      buffer->WriteBytes(data, data->GetReadableBytes());
    }

    uint32_t GetOrdinal() const override {
      return PACKET_ORDINAL;
    }
  };
}
