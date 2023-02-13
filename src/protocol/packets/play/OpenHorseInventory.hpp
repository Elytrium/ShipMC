#pragma once

#include "../../../utils/ordinal/OrdinalRegistry.hpp"
#include "../Packet.hpp"
#include <string>

namespace Ship {

  class OpenHorseInventory : public Packet {
   private:
    uint8_t windowId;
    uint32_t slotCount;
    uint32_t entityId;

   public:
    static inline const uint32_t PACKET_ORDINAL = OrdinalRegistry::PacketRegistry.RegisterOrdinal();

    OpenHorseInventory(uint8_t windowId, uint32_t slotCount, uint32_t entityId) : windowId(windowId), slotCount(slotCount), entityId(entityId) {
    }

    ~OpenHorseInventory() override = default;

    void Read(const ProtocolVersion* version, ByteBuffer* buffer) override {
      windowId = buffer->ReadByte();
      slotCount = buffer->ReadVarInt();
      entityId = buffer->ReadInt();
    }

    void Write(const ProtocolVersion* version, ByteBuffer* buffer) override {
      buffer->WriteByte(windowId);
      buffer->WriteVarInt(slotCount);
      buffer->WriteInt(entityId);
    }

    uint32_t Size(const ProtocolVersion* version) override {
      return ByteBuffer::BYTE_SIZE + ByteBuffer::VarIntBytes(slotCount) + ByteBuffer::INT_SIZE;
    }

    uint32_t GetOrdinal() override {
      return PACKET_ORDINAL;
    }

    [[nodiscard]] uint8_t GetWindowId() const {
      return windowId;
    }

    [[nodiscard]] uint32_t GetSlotCount() const {
      return slotCount;
    }

    [[nodiscard]] uint32_t GetEntityId() const {
      return entityId;
    }
  };
}
