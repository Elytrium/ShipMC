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

    void Read(const ProtocolVersion* version, ByteBuffer* buffer) override {
      buffer->WriteVarInt(entityId);
      buffer->WriteByte(animationId);
    }

    void Write(const ProtocolVersion* version, ByteBuffer* buffer) override {
      entityId = buffer->ReadVarInt();
      animationId = buffer->ReadByte();
    }

    uint32_t GetOrdinal() override {
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
