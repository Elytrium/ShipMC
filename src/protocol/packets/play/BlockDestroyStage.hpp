#pragma once

#include "../../../utils/ordinal/OrdinalRegistry.hpp"
#include "../Packet.hpp"
#include <string>

namespace Ship {

  class BlockDestroyStage : public Packet {
   private:
    uint32_t entityId;
    int locationX;
    int locationY;
    int locationZ;
    uint8_t destroyStage;

   public:
    static inline const uint32_t PACKET_ORDINAL = OrdinalRegistry::PacketRegistry.RegisterOrdinal();

    BlockDestroyStage(uint32_t entityId, int locationX, int locationY, int locationZ, uint8_t destroyStage)
      : entityId(entityId), locationX(locationX), locationY(locationY), locationZ(locationZ), destroyStage(destroyStage) {
    }

    explicit BlockDestroyStage(const PacketHolder& holder) {
      ByteBuffer* buffer = holder.GetCurrentBuffer();
      entityId = buffer->ReadVarInt();
      buffer->ReadPosition(locationX, locationY, locationZ);
      destroyStage = buffer->ReadByte();
    }

    ~BlockDestroyStage() override = default;

    void Write(const ProtocolVersion* version, ByteBuffer* buffer) const override {
      buffer->WriteVarInt(entityId);
      buffer->WritePosition(locationX, locationY, locationZ);
      buffer->WriteByte(destroyStage);
    }

    uint32_t GetOrdinal() const override {
      return PACKET_ORDINAL;
    }

    [[nodiscard]] uint32_t GetEntityId() const {
      return entityId;
    }

    [[nodiscard]] int GetLocationX() const {
      return locationX;
    }

    [[nodiscard]] int GetLocationY() const {
      return locationY;
    }

    [[nodiscard]] int GetLocationZ() const {
      return locationZ;
    }

    [[nodiscard]] uint8_t GetDestroyStage() const {
      return destroyStage;
    }
  };
}
