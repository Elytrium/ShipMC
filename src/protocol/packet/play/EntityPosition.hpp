#pragma once

#include "../../../../lib/ShipNet/src/utils/ordinal/OrdinalRegistry.hpp"
#include <string>

namespace Ship {

  class EntityPosition : public Packet {
   private:
    uint32_t entityId{};
    uint16_t deltaX{};
    uint16_t deltaY{};
    uint16_t deltaZ{};
    bool onGround{};

   public:
    static inline const uint32_t PACKET_ORDINAL = OrdinalRegistry::PacketRegistry.RegisterOrdinal();

    EntityPosition() = default;
    EntityPosition(uint32_t entityId, uint16_t deltaX, uint16_t deltaY, uint16_t deltaZ, bool onGround)
      : entityId(entityId), deltaX(deltaX), deltaY(deltaY), deltaZ(deltaZ), onGround(onGround) {
    }

    ~EntityPosition() override = default;

    static Errorable<EntityPosition> Instantiate(const PacketHolder& holder) {
      ByteBuffer* buffer = holder.GetCurrentBuffer();
      ProceedErrorable(entityId, uint32_t, buffer->ReadVarInt(), InvalidPacketErrorable<EntityPosition>(PACKET_ORDINAL))
      ProceedErrorable(deltaX, uint16_t, buffer->ReadShort(), InvalidPacketErrorable<EntityPosition>(PACKET_ORDINAL))
      ProceedErrorable(deltaY, uint16_t, buffer->ReadShort(), InvalidPacketErrorable<EntityPosition>(PACKET_ORDINAL))
      ProceedErrorable(deltaZ, uint16_t, buffer->ReadShort(), InvalidPacketErrorable<EntityPosition>(PACKET_ORDINAL))
      ProceedErrorable(onGround, bool, buffer->ReadBoolean(), InvalidPacketErrorable<EntityPosition>(PACKET_ORDINAL))
      return SuccessErrorable<EntityPosition>(EntityPosition(entityId, deltaX, deltaY, deltaZ, onGround));
    }

    Errorable<bool> Write(const ProtocolVersion* version, ByteBuffer* buffer) const override {
      buffer->WriteVarInt(entityId);
      buffer->WriteShort(deltaX);
      buffer->WriteShort(deltaY);
      buffer->WriteShort(deltaZ);
      buffer->WriteBoolean(onGround);
      return SuccessErrorable<bool>(true);
    }

    [[nodiscard]] uint32_t GetOrdinal() const override {
      return PACKET_ORDINAL;
    }

    [[nodiscard]] uint32_t GetEntityId() const {
      return entityId;
    }

    [[nodiscard]] uint16_t GetDeltaX() const {
      return deltaX;
    }

    [[nodiscard]] uint16_t GetDeltaY() const {
      return deltaY;
    }

    [[nodiscard]] uint16_t GetDeltaZ() const {
      return deltaZ;
    }

    [[nodiscard]] bool IsOnGround() const {
      return onGround;
    }
  };
}
