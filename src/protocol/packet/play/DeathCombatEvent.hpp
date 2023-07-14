#pragma once

#include "ShipNet/utils/ordinal/OrdinalRegistry.hpp"
#include <string>
#include <utility>

namespace Ship {

  class DeathCombatEvent : public Packet {
   private:
    uint32_t playerId{};
    uint32_t entityId{};
    std::string message;

   public:
    static inline const uint32_t PACKET_ORDINAL = OrdinalRegistry::PacketRegistry.RegisterOrdinal();

    DeathCombatEvent() = default;
    DeathCombatEvent(uint32_t playerId, uint32_t entityId, std::string message) : playerId(playerId), entityId(entityId), message(std::move(message)) {
    }

    ~DeathCombatEvent() override = default;

    static Errorable<DeathCombatEvent> Instantiate(const PacketHolder& holder) {
      ByteBuffer* buffer = holder.GetCurrentBuffer();
      ProceedErrorable(playerId, uint32_t, buffer->ReadVarInt(), InvalidPacketErrorable<DeathCombatEvent>(PACKET_ORDINAL))
      ProceedErrorable(entityId, uint32_t, buffer->ReadInt(), InvalidPacketErrorable<DeathCombatEvent>(PACKET_ORDINAL))
      ProceedErrorable(message, std::string, buffer->ReadString(), InvalidPacketErrorable<DeathCombatEvent>(PACKET_ORDINAL))
      return SuccessErrorable<DeathCombatEvent>(DeathCombatEvent(playerId, entityId, message));
    }

    Errorable<bool> Write(const ProtocolVersion* version, ByteBuffer* buffer) const override {
      buffer->WriteVarInt(playerId);
      buffer->WriteInt(entityId);
      buffer->WriteString(message);
      return SuccessErrorable<bool>(true);
    }

    [[nodiscard]] uint32_t GetOrdinal() const override {
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
