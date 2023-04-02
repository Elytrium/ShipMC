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

    static Errorable<PluginMessage> Instantiate(const PacketHolder& holder) {
      ByteBuffer* buffer = holder.GetCurrentBuffer();
      ProceedErrorable(channel, std::string, buffer->ReadString(), InvalidPacketErrorable<>(PACKET_ORDINAL))
      delete data;
      uint32_t size = buffer->GetReadableBytes();
      data = new ByteBufferImpl(buffer->ReadBytes(size), size);
    }

    void Write(const ProtocolVersion* version, ByteBuffer* buffer) const override {
      buffer->WriteString(channel);
      buffer->WriteBytes(buffer, buffer->GetReadableBytes());
    }

    [[nodiscard]] uint32_t GetOrdinal() const override {
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
