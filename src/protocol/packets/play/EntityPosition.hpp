#pragma once

#include "../../../utils/ordinal/OrdinalRegistry.hpp"
#include "../Packet.hpp"
#include <string>

namespace Ship {

  class EntityPosition : public Packet {
   private:
    uint32_t entityId;
    uint16_t deltaX;
    uint16_t deltaY;
    uint16_t deltaZ;
    bool onGround;

   public:
    static inline const uint32_t PACKET_ORDINAL = OrdinalRegistry::PacketRegistry.RegisterOrdinal();

    EntityPosition(uint32_t entityId, uint16_t deltaX, uint16_t deltaY, uint16_t deltaZ, bool onGround)
      : entityId(entityId), deltaX(deltaX), deltaY(deltaY), deltaZ(deltaZ), onGround(onGround) {
    }

    ~EntityPosition() override = default;

    void Read(const ProtocolVersion* version, ByteBuffer* buffer) override {
      entityId = buffer->ReadVarInt();
      deltaX = buffer->ReadShort();
      deltaY = buffer->ReadShort();
      deltaZ = buffer->ReadShort();
      onGround = buffer->ReadBoolean();
    }

    void Write(const ProtocolVersion* version, ByteBuffer* buffer) override {
      buffer->WriteVarInt(entityId);
      buffer->WriteShort(deltaX);
      buffer->WriteShort(deltaY);
      buffer->WriteShort(deltaZ);
      buffer->WriteBoolean(onGround);
    }

    uint32_t Size(const ProtocolVersion* version) override {
      return ByteBuffer::VarIntBytes(entityId) + ByteBuffer::SHORT_SIZE + ByteBuffer::SHORT_SIZE + ByteBuffer::SHORT_SIZE + ByteBuffer::BOOLEAN_SIZE;
    }

    uint32_t GetOrdinal() override {
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
