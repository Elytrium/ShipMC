#pragma once

#include "../../../utils/ordinal/OrdinalRegistry.hpp"
#include "../Packet.hpp"
#include <string>

namespace Ship {

  class EntityRotation : public Packet {
   private:
    uint32_t entityId;
    float yaw;
    float pitch;
    bool onGround;

   public:
    static inline const uint32_t PACKET_ORDINAL = OrdinalRegistry::PacketRegistry.RegisterOrdinal();

    EntityRotation(uint32_t entityId, float yaw, float pitch, bool onGround) : entityId(entityId), yaw(yaw), pitch(pitch), onGround(onGround) {
    }

    ~EntityRotation() override = default;

    void Read(const ProtocolVersion* version, ByteBuffer* buffer) override {
      entityId = buffer->ReadVarInt();
      yaw = buffer->ReadAngle();
      pitch = buffer->ReadAngle();
      onGround = buffer->ReadBoolean();
    }

    void Write(const ProtocolVersion* version, ByteBuffer* buffer) override {
      buffer->WriteVarInt(entityId);
      buffer->WriteAngle(yaw);
      buffer->WriteAngle(pitch);
      buffer->WriteBoolean(onGround);
    }

    uint32_t GetOrdinal() override {
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
