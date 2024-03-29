#pragma once

#include "ShipNet/utils/ordinal/OrdinalRegistry.hpp"
#include <string>

namespace Ship {

  class EntityRotation : public Packet {
   private:
    uint32_t entityId{};
    float yaw{};
    float pitch{};
    bool onGround{};

   public:
    static inline const uint32_t PACKET_ORDINAL = OrdinalRegistry::PacketRegistry.RegisterOrdinal();

    EntityRotation() = default;
    EntityRotation(uint32_t entityId, float yaw, float pitch, bool onGround) : entityId(entityId), yaw(yaw), pitch(pitch), onGround(onGround) {
    }

    ~EntityRotation() override = default;

    static Errorable<EntityRotation> Instantiate(const PacketHolder& holder) {
      ByteBuffer* buffer = holder.GetCurrentBuffer();
      ProceedErrorable(entityId, uint32_t, buffer->ReadVarInt(), InvalidPacketErrorable<EntityRotation>(PACKET_ORDINAL))
      ProceedErrorable(yaw, float, buffer->ReadAngle(), InvalidPacketErrorable<EntityRotation>(PACKET_ORDINAL));
      ProceedErrorable(pitch, float, buffer->ReadAngle(), InvalidPacketErrorable<EntityRotation>(PACKET_ORDINAL));
      ProceedErrorable(onGround, bool, buffer->ReadBoolean(), InvalidPacketErrorable<EntityRotation>(PACKET_ORDINAL))
      return SuccessErrorable<EntityRotation>(EntityRotation(entityId, yaw, pitch, onGround));
    }

    Errorable<bool> Write(const ProtocolVersion* version, ByteBuffer* buffer) const override {
      buffer->WriteVarInt(entityId);
      buffer->WriteAngle(yaw);
      buffer->WriteAngle(pitch);
      buffer->WriteBoolean(onGround);
      return SuccessErrorable<bool>(true);
    }

    [[nodiscard]] uint32_t GetOrdinal() const override {
      return PACKET_ORDINAL;
    }

    [[nodiscard]] uint32_t GetEntityId() const {
      return entityId;
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
