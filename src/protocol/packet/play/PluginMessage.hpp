#pragma once

#include "../../../../lib/ShipNet/src/utils/ordinal/OrdinalRegistry.hpp"
#include <string>
#include <utility>

namespace Ship {

  class PluginMessage : public Packet {
   private:
    std::string channel;
    ByteBuffer* data{};

   public:
    static inline const uint32_t PACKET_ORDINAL = OrdinalRegistry::PacketRegistry.RegisterOrdinal();

    PluginMessage() = default;
    PluginMessage(std::string channel, ByteBuffer* data) : channel(std::move(channel)), data(data) {
    }

    ~PluginMessage() override {
      delete data;
    }

    static Errorable<PluginMessage> Instantiate(const PacketHolder& holder) {
      ByteBuffer* buffer = holder.GetCurrentBuffer();
      ProceedErrorable(channel, std::string, buffer->ReadString(), InvalidPacketErrorable<PluginMessage>(PACKET_ORDINAL))
      uint32_t size = buffer->GetReadableBytes();
      ProceedErrorable(bytes, uint8_t*, buffer->ReadBytes(size), InvalidPacketErrorable<PluginMessage>(PACKET_ORDINAL))
      ByteBuffer* data = new ByteBufferImpl(bytes, size);
      return SuccessErrorable<PluginMessage>(PluginMessage(channel, data));
    }

    Errorable<bool> Write(const ProtocolVersion* version, ByteBuffer* buffer) const override {
      buffer->WriteString(channel);
      buffer->WriteBytes(buffer, buffer->GetReadableBytes());
      return SuccessErrorable<bool>(true);
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
