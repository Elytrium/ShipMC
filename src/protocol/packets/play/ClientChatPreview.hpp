#pragma once

#include "../../../utils/ordinal/OrdinalRegistry.hpp"
#include "../Packet.hpp"
#include <optional>
#include <string>
#include <utility>

namespace Ship {

  class ClientChatPreview : public Packet {
   private:
    uint32_t queryId;
    std::string message;

   public:
    static inline const uint32_t PACKET_ORDINAL = OrdinalRegistry::PacketRegistry.RegisterOrdinal();

    ClientChatPreview(uint32_t queryId, std::string message) : queryId(queryId), message(std::move(message)) {
    }

    ~ClientChatPreview() override = default;

    void Read(const ProtocolVersion* version, ByteBuffer* buffer) override {
      queryId = buffer->ReadInt();
      message = buffer->ReadString();
    }

    void Write(const ProtocolVersion* version, ByteBuffer* buffer) override {
      buffer->WriteInt(queryId);
      buffer->WriteString(message);
    }

    uint32_t GetOrdinal() override {
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
