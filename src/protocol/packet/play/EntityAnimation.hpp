#pragma once

#include "../../../../lib/ShipNet/src/utils/ordinal/OrdinalRegistry.hpp"
#include <string>

namespace Ship {

  class EntityAnimation : public Packet {
   private:
    uint32_t entityId;
    uint8_t animationId;

   public:
    static inline const uint32_t PACKET_ORDINAL = OrdinalRegistry::PacketRegistry.RegisterOrdinal();

    EntityAnimation(uint32_t entityId, uint8_t animationId) : entityId(entityId), animationId(animationId) {
    }

    ~EntityAnimation() override = default;

    static Errorable<EntityAnimation> Instantiate(const PacketHolder& holder) {
      ByteBuffer* buffer = holder.GetCurrentBuffer();
      ProceedErrorable(entityId, uint32_t, buffer->ReadVarInt(), InvalidPacketErrorable<>(PACKET_ORDINAL))
      ProceedErrorable(animationId, uint8_t, buffer->ReadByte(), InvalidPacketErrorable<>(PACKET_ORDINAL))
    }

    Errorable<bool> Write(const ProtocolVersion* version, ByteBuffer* buffer) const override {
      buffer->WriteVarInt(entityId);
      buffer->WriteByte(animationId);
      return SuccessErrorable<bool>(true);
    }

    [[nodiscard]] uint32_t GetOrdinal() const override {
      return PACKET_ORDINAL;
    }

    [[nodiscard]] uint32_t GetEntityId() const {
      return entityId;
    }

    [[nodiscard]] uint8_t GetAnimationId() const {
      return animationId;
    }
  };
}
