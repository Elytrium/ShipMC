#pragma once

#include "../../../utils/ordinal/OrdinalRegistry.hpp"
#include "../Packet.hpp"
#include <string>
#include <utility>

namespace Ship {

  class DeathCombatEvent : public Packet {
   private:
    uint32_t playerId;
    uint32_t entityId;
    std::string message;

   public:
    static inline const uint32_t PACKET_ORDINAL = OrdinalRegistry::PacketRegistry.RegisterOrdinal();

    DeathCombatEvent(uint32_t playerId, uint32_t entityId, std::string message) : playerId(playerId), entityId(entityId), message(std::move(message)) {
    }

    ~DeathCombatEvent() override = default;

    void Read(const ProtocolVersion* version, ByteBuffer* buffer) override {
      playerId = buffer->ReadVarInt();
      entityId = buffer->ReadInt();
      message = buffer->ReadString();
    }

    void Write(const ProtocolVersion* version, ByteBuffer* buffer) override {
      buffer->WriteVarInt(playerId);
      buffer->WriteInt(entityId);
      buffer->WriteString(message);
    }

    uint32_t Size(const ProtocolVersion* version) override {
      return ByteBuffer::VarIntBytes(playerId) + ByteBuffer::INT_SIZE + ByteBuffer::StringBytes(message);
    }

    uint32_t GetOrdinal() override {
      return PACKET_ORDINAL;
    }

    [[nodiscard]] uint32_t GetPlayerId() const {
      return playerId;
    }

    [[nodiscard]] uint32_t GetEntityId() const {
      return entityId;
    }

    [[nodiscard]] const std::string& GetMessage() const {
      return message;
    }
  };
}
