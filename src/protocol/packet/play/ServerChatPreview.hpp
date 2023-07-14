#pragma once

#include "../../../../lib/ShipNet/src/utils/ordinal/OrdinalRegistry.hpp"
#include <optional>
#include <string>
#include <utility>

namespace Ship {

  class ServerChatPreview : public Packet {
   private:
    uint32_t queryId{};
    std::optional<std::string> message; // TODO: Chat components

   public:
    static inline const uint32_t PACKET_ORDINAL = OrdinalRegistry::PacketRegistry.RegisterOrdinal();

    ServerChatPreview() = default;
    ServerChatPreview(uint32_t queryId, std::optional<std::string> message) : queryId(queryId), message(std::move(message)) {
    }

    ~ServerChatPreview() override = default;

    static Errorable<ServerChatPreview> Instantiate(const PacketHolder& holder) {
      ByteBuffer* buffer = holder.GetCurrentBuffer();
      ProceedErrorable(queryId, uint32_t, buffer->ReadInt(), InvalidPacketErrorable<ServerChatPreview>(PACKET_ORDINAL))
      ProceedErrorable(hasMessage, bool, buffer->ReadBoolean(), InvalidPacketErrorable<ServerChatPreview>(PACKET_ORDINAL))

      std::optional<std::string> message;
      if (hasMessage) {
        SetFromErrorable(message, std::string, buffer->ReadString(), InvalidPacketErrorable<ServerChatPreview>(PACKET_ORDINAL))
      }

      return SuccessErrorable<ServerChatPreview>(ServerChatPreview(queryId, message));
    }

    Errorable<bool> Write(const ProtocolVersion* version, ByteBuffer* buffer) const override {
      buffer->WriteInt(queryId);
      buffer->WriteBoolean(message.has_value());
      if (message) {
        buffer->WriteString(message.value());
      }
      return SuccessErrorable<bool>(true);
    }

    [[nodiscard]] uint32_t GetOrdinal() const override {
      return PACKET_ORDINAL;
    }

    [[nodiscard]] uint32_t GetQueryId() const {
      return queryId;
    }

    [[nodiscard]] const std::optional<std::string>& GetMessage() const {
      return message;
    }
  };
}
