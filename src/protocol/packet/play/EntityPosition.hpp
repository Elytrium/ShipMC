#pragma once


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

    explicit EntityPosition(const PacketHolder& holder) {
      ByteBuffer* buffer = holder.GetCurrentBuffer();
      entityId = buffer->ReadVarInt();
      deltaX = buffer->ReadShort();
      deltaY = buffer->ReadShort();
      deltaZ = buffer->ReadShort();
      onGround = buffer->ReadBoolean();
    }

    void Write(const ProtocolVersion* version, ByteBuffer* buffer) const override {
      buffer->WriteVarInt(entityId);
      buffer->WriteShort(deltaX);
      buffer->WriteShort(deltaY);
      buffer->WriteShort(deltaZ);
      buffer->WriteBoolean(onGround);
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

    [[nodiscard]] bool IsOnGround() const {
      return onGround;
    }
  };
}
