#pragma once

#include "ShipNet/utils/ordinal/OrdinalRegistry.hpp"
#include <optional>
#include <string>
#include <utility>

namespace Ship {

  class ClientChatPreview : public Packet {
   private:
    uint32_t queryId{};
    std::string message;

   public:
    static inline const uint32_t PACKET_ORDINAL = OrdinalRegistry::PacketRegistry.RegisterOrdinal();

    ClientChatPreview() = default;
    ClientChatPreview(uint32_t queryId, std::string message) : queryId(queryId), message(std::move(message)) {
    }

    ~ClientChatPreview() override = default;

    static Errorable<ClientChatPreview> Instantiate(const PacketHolder& holder) {
      ByteBuffer* buffer = holder.GetCurrentBuffer();
      ProceedErrorable(queryId, uint32_t, buffer->ReadInt(), InvalidPacketErrorable<ClientChatPreview>(PACKET_ORDINAL));
      ProceedErrorable(message, std::string, buffer->ReadString(), InvalidPacketErrorable<ClientChatPreview>(PACKET_ORDINAL))
      return SuccessErrorable<ClientChatPreview>(ClientChatPreview(queryId, message));
    }

    Errorable<bool> Write(const ProtocolVersion* version, ByteBuffer* buffer) const override {
      buffer->WriteInt(queryId);
      buffer->WriteString(message);
      return SuccessErrorable<bool>(true);
    }

    [[nodiscard]] uint32_t GetOrdinal() const override {
      return PACKET_ORDINAL;
    }

    [[nodiscard]] uint32_t GetQueryId() const {
      return queryId;
    }

    [[nodiscard]] const std::string& GetMessage() const {
      return message;
    }
  };
}
