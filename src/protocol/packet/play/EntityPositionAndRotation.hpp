#pragma once

#include "../../../../lib/ShipNet/src/utils/ordinal/OrdinalRegistry.hpp"
#include <string>

namespace Ship {

  class EntityPositionAndRotation : public Packet {
   private:
    uint32_t entityId;
    uint16_t deltaX;
    uint16_t deltaY;
    uint16_t deltaZ;
    float yaw;
    float pitch;
    bool onGround;

   public:
    static inline const uint32_t PACKET_ORDINAL = OrdinalRegistry::PacketRegistry.RegisterOrdinal();

    EntityPositionAndRotation(uint32_t entityId, short deltaX, short deltaY, short deltaZ, float yaw, float pitch, bool onGround)
      : entityId(entityId), deltaX(deltaX), deltaY(deltaY), deltaZ(deltaZ), yaw(yaw), pitch(pitch), onGround(onGround) {
    }

    ~EntityPositionAndRotation() override = default;

    static Errorable<EntityPositionAndRotation> Instantiate(const PacketHolder& holder) {
      ByteBuffer* buffer = holder.GetCurrentBuffer();
      ProceedErrorable(entityId, uint32_t, buffer->ReadVarInt(), InvalidPacketErrorable<>(PACKET_ORDINAL))
      ProceedErrorable(deltaX, uint16_t, buffer->ReadShort(), InvalidPacketErrorable<>(PACKET_ORDINAL))
      ProceedErrorable(deltaY, uint16_t, buffer->ReadShort(), InvalidPacketErrorable<>(PACKET_ORDINAL))
      ProceedErrorable(deltaZ, uint16_t, buffer->ReadShort(), InvalidPacketErrorable<>(PACKET_ORDINAL))
      yaw = buffer->ReadAngle();
      pitch = buffer->ReadAngle();
      ProceedErrorable(onGround, bool, buffer->ReadBoolean(), InvalidPacketErrorable<>(PACKET_ORDINAL))
    }

    Errorable<bool> Write(const ProtocolVersion* version, ByteBuffer* buffer) const override {
      buffer->WriteVarInt(entityId);
      buffer->WriteShort(deltaX);
      buffer->WriteShort(deltaY);
      buffer->WriteShort(deltaZ);
      buffer->WriteAngle(yaw);
      buffer->WriteAngle(pitch);
      buffer->WriteBoolean(onGround);
      return SuccessErrorable<bool>(true);
    }

    uint32_t GetOrdinal() const override {
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

    [[nodiscard]] float GetYaw() const {
      return yaw;
    }

    [[nodiscard]] float GetPitch() const {
      return pitch;
    }

    [[nodiscard]] bool IsOnGround() const {
      return onGround;
    }
  };
}
