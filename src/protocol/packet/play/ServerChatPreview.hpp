#pragma once


#include <optional>
#include <string>
#include <utility>

namespace Ship {

  class ServerChatPreview : public Packet {
   private:
    uint32_t queryId;
    std::optional<std::string> message; // TODO: Chat components

   public:
    static inline const uint32_t PACKET_ORDINAL = OrdinalRegistry::PacketRegistry.RegisterOrdinal();

    ServerChatPreview(uint32_t queryId, std::optional<std::string> message) : queryId(queryId), message(std::move(message)) {
    }

    ~ServerChatPreview() override = default;

    explicit ServerChatPreview(const PacketHolder& holder) {
      ByteBuffer* buffer = holder.GetCurrentBuffer();
      queryId = buffer->ReadInt();
      if (buffer->ReadBoolean()) {
        message = buffer->ReadString();
      } else {
        message.reset();
      }
    }

    void Write(const ProtocolVersion* version, ByteBuffer* buffer) const override {
      buffer->WriteInt(queryId);
      buffer->WriteBoolean(message.has_value());
      if (message) {
        buffer->WriteString(message.value());
      }
    }

    uint32_t GetOrdinal() const override {
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
