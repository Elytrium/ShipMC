#pragma once

#include "../../../utils/ordinal/OrdinalRegistry.hpp"
#include "../Packet.hpp"
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

    EntityAnimation(const ProtocolVersion* version, ByteBuffer* buffer) {
      entityId = buffer->ReadVarInt();
      animationId = buffer->ReadByte();
    }

    void Write(const ProtocolVersion* version, ByteBuffer* buffer) const override {
      buffer->WriteVarInt(entityId);
      buffer->WriteByte(animationId);
    }

    uint32_t GetOrdinal() const override {
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
