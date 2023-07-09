#pragma once

#include "../../../../lib/ShipNet/src/utils/ordinal/OrdinalRegistry.hpp"
#include "../../data/ItemStack.hpp"
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

    static Errorable<InventorySlot> Instantiate(const PacketHolder& holder) {
      ByteBuffer* buffer = holder.GetCurrentBuffer();
      const ProtocolVersion* version = holder.GetVersion();
      ProceedErrorable(windowId, uint8_t, buffer->ReadByte(), InvalidPacketErrorable<>(PACKET_ORDINAL))
      if (version >= &MinecraftProtocolVersion::MINECRAFT_1_17_1) {
        ProceedErrorable(stateId, uint32_t, buffer->ReadVarInt(), InvalidPacketErrorable<>(PACKET_ORDINAL))
      }
      ProceedErrorable(slot, uint16_t, buffer->ReadShort(), InvalidPacketErrorable<>(PACKET_ORDINAL))
      item = ItemStack(version, buffer);
    }

    void Write(const ProtocolVersion* version, ByteBuffer* buffer) const override {
      buffer->WriteByte(windowId);
      if (version >= &MinecraftProtocolVersion::MINECRAFT_1_17_1) {
        buffer->WriteVarInt(stateId);
      }
      buffer->WriteShort(slot);
      item.Write(version, buffer);
    }

    uint32_t GetOrdinal() const override {
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
