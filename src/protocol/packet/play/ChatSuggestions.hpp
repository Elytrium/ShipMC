#pragma once

#include "../../../../lib/ShipNet/src/utils/ordinal/OrdinalRegistry.hpp"
#include <string>
#include <utility>

namespace Ship {

  class ChatSuggestions : public Packet {
   private:
    uint32_t action;
    std::vector<std::string> entries;

   public:
    static inline const uint32_t PACKET_ORDINAL = OrdinalRegistry::PacketRegistry.RegisterOrdinal();

    ChatSuggestions(uint32_t action, std::vector<std::string> entries) : action(action), entries(std::move(entries)) {
    }

    ~ChatSuggestions() override = default;

    static Errorable<ChatSuggestions> Instantiate(const PacketHolder& holder) {
      ByteBuffer* buffer = holder.GetCurrentBuffer();
      ProceedErrorable(action, uint32_t, buffer->ReadVarInt(), InvalidPacketErrorable<>(PACKET_ORDINAL))
      uint32_t ProceedErrorable(vectorSize, uint32_t, buffer->ReadVarInt(), InvalidPacketErrorable<>(PACKET_ORDINAL))
      for (int i = 0; i < vectorSize; ++i) {
         entries.push_back(buffer->ReadString());
      }
    }

    Errorable<bool> Write(const ProtocolVersion* version, ByteBuffer* buffer) const override {
      buffer->WriteVarInt(action);
      buffer->WriteVarInt(entries.size());
      for (const std::string& entry : entries) {
        buffer->WriteString(entry);
      }
      return SuccessErrorable<bool>(true);
    }

    uint32_t GetOrdinal() const override {
      return PACKET_ORDINAL;
    }

    [[nodiscard]] uint32_t GetAction() const {
      return action;
    }

    [[nodiscard]] const std::vector<std::string>& GetEntries() const {
      return entries;
    }
  };
}
