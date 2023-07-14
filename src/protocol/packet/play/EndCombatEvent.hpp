#pragma once

#include "../../../../lib/ShipNet/src/utils/ordinal/OrdinalRegistry.hpp"
#include <string>

namespace Ship {

  class EndCombatEvent : public Packet {
   private:
    uint32_t duration{};
    uint32_t entityId{};

   public:
    static inline const uint32_t PACKET_ORDINAL = OrdinalRegistry::PacketRegistry.RegisterOrdinal();

    EndCombatEvent() = default;
    EndCombatEvent(uint32_t duration, uint32_t entityId) : duration(duration), entityId(entityId) {
    }

    ~EndCombatEvent() override = default;

    static Errorable<EndCombatEvent> Instantiate(const PacketHolder& holder) {
      ByteBuffer* buffer = holder.GetCurrentBuffer();
      ProceedErrorable(duration, uint32_t, buffer->ReadVarInt(), InvalidPacketErrorable<EndCombatEvent>(PACKET_ORDINAL))
      ProceedErrorable(entityId, uint32_t, buffer->ReadInt(), InvalidPacketErrorable<EndCombatEvent>(PACKET_ORDINAL))
      return SuccessErrorable<EndCombatEvent>(EndCombatEvent(duration, entityId));
    }

    Errorable<bool> Write(const ProtocolVersion* version, ByteBuffer* buffer) const override {
      buffer->WriteVarInt(duration);
      buffer->WriteInt(entityId);
      return SuccessErrorable<bool>(true);
    }

    [[nodiscard]] uint32_t GetOrdinal() const override {
      return PACKET_ORDINAL;
    }

    [[nodiscard]] uint32_t GetDuration() const {
      return duration;
    }

    [[nodiscard]] uint32_t GetEntityId() const {
      return entityId;
    }
  };
}
