#pragma once

#include "../../../utils/ordinal/OrdinalRegistry.hpp"
#include "../Packet.hpp"
#include <string>

namespace Ship {

  class EntityEvent : public Packet {
   private:
    uint32_t entityId;
    uint8_t entityStatus;

   public:
    static inline const uint32_t PACKET_ORDINAL = OrdinalRegistry::PacketRegistry.RegisterOrdinal();

    EntityEvent(uint32_t entityId, uint8_t entityStatus) : entityId(entityId), entityStatus(entityStatus) {
    }

    ~EntityEvent() override = default;

    static Errorable<EntityEvent> Instantiate(const PacketHolder& holder) {
      ByteBuffer* buffer = holder.GetCurrentBuffer();
      entityId = buffer->ReadInt();
      ProceedErrorable(entityStatus, uint8_t, buffer->ReadByte(), InvalidPacketErrorable<>(PACKET_ORDINAL))
    }

    void Write(const ProtocolVersion* version, ByteBuffer* buffer) const override {
      buffer->WriteInt(entityId);
      buffer->WriteByte(entityStatus);
    }

    [[nodiscard]] uint32_t GetOrdinal() const override {
      return PACKET_ORDINAL;
    }

    [[nodiscard]] uint32_t GetEntityId() const {
      return entityId;
    }

    [[nodiscard]] uint8_t GetEntityStatus() const {
      return entityStatus;
    }
  };
}
