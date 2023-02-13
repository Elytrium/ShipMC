#pragma once

#include "../../../utils/ordinal/OrdinalRegistry.hpp"
#include "../Packet.hpp"
#include <string>

namespace Ship {

  class InventorySlot : public Packet {
   private:
    uint8_t windowId;
    uint32_t stateId;
    uint16_t slot;
    ItemStack item;

   public:
    static inline const uint32_t PACKET_ORDINAL = OrdinalRegistry::PacketRegistry.RegisterOrdinal();

    InventorySlot(uint8_t windowId, uint32_t stateId, uint16_t slot, const ItemStack& item)
      : windowId(windowId), stateId(stateId), slot(slot), item(item) {
    }

    ~InventorySlot() override = default;

    void Read(const ProtocolVersion* version, ByteBuffer* buffer) override {
      windowId = buffer->ReadByte();
      if (version >= &ProtocolVersion::MINECRAFT_1_17_1) {
        stateId = buffer->ReadVarInt();
      }
      slot = buffer->ReadShort();
      item.Read(version, buffer);
    }

    void Write(const ProtocolVersion* version, ByteBuffer* buffer) override {
      buffer->WriteByte(windowId);
      if (version >= &ProtocolVersion::MINECRAFT_1_17_1) {
        buffer->WriteVarInt(stateId);
      }
      buffer->WriteShort(slot);
      item.Write(version, buffer);
    }

    uint32_t GetOrdinal() override {
      return PACKET_ORDINAL;
    }

    [[nodiscard]] uint8_t GetWindowId() const {
      return windowId;
    }

    [[nodiscard]] uint32_t GetStateId() const {
      return stateId;
    }

    [[nodiscard]] uint16_t GetSlot() const {
      return slot;
    }

    [[nodiscard]] const ItemStack& GetItem() const {
      return item;
    }
  };
}
