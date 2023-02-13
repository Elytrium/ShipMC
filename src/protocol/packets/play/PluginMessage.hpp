#pragma once

#include "../../../utils/ordinal/OrdinalRegistry.hpp"
#include "../Packet.hpp"
#include <string>
#include <utility>

namespace Ship {

  class PluginMessage : public Packet {
   private:
    std::string channel;
    ByteBuffer* data;

   public:
    static inline const uint32_t PACKET_ORDINAL = OrdinalRegistry::PacketRegistry.RegisterOrdinal();

    PluginMessage(std::string channel, ByteBuffer* data) : channel(std::move(channel)), data(data) {
    }

    ~PluginMessage() override {
      delete data;
    }

    void Read(const ProtocolVersion* version, ByteBuffer* buffer) override {
      channel = buffer->ReadString();
      delete data;
      uint32_t size = buffer->GetReadableBytes();
      data = new ByteBuffer(buffer->ReadBytes(size), size);
    }

    void Write(const ProtocolVersion* version, ByteBuffer* buffer) override {
      buffer->WriteString(channel);
      buffer->WriteBytes(buffer, buffer->GetReadableBytes());
    }

    uint32_t Size(const ProtocolVersion* version) override {
      return ByteBuffer::StringBytes(channel) + data->GetReadableBytes();
    }

    uint32_t GetOrdinal() override {
      return PACKET_ORDINAL;
    }

    [[nodiscard]] const std::string& GetChannel() const {
      return channel;
    }

    [[nodiscard]] ByteBuffer* GetData() const {
      return data;
    }
  };
}
