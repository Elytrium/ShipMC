#pragma once

#include "ShipNet/utils/ordinal/OrdinalRegistry.hpp"
#include "../../data/ItemStack.hpp"
#include <string>

namespace Ship {

  class InventorySlot : public Packet {
   private:
    uint8_t windowId{};
    uint32_t stateId{};
    uint16_t slot{};
    ItemStack item;

   public:
    static inline const uint32_t PACKET_ORDINAL = OrdinalRegistry::PacketRegistry.RegisterOrdinal();

    InventorySlot() = default;
    InventorySlot(uint8_t windowId, uint32_t stateId, uint16_t slot, const ItemStack& item)
      : windowId(windowId), stateId(stateId), slot(slot), item(item) {
    }

    ~InventorySlot() override = default;

    static Errorable<InventorySlot> Instantiate(const PacketHolder& holder) {
      ByteBuffer* buffer = holder.GetCurrentBuffer();
      const ProtocolVersion* version = holder.GetVersion();
      ProceedErrorable(windowId, uint8_t, buffer->ReadByte(), InvalidPacketErrorable<InventorySlot>(PACKET_ORDINAL))
      uint32_t stateId;
      if (version >= &MinecraftProtocolVersion::MINECRAFT_1_17_1) {
        SetFromErrorable(stateId, uint32_t, buffer->ReadVarInt(), InvalidPacketErrorable<InventorySlot>(PACKET_ORDINAL))
      }
      ProceedErrorable(slot, uint16_t, buffer->ReadShort(), InvalidPacketErrorable<InventorySlot>(PACKET_ORDINAL))
      ProceedErrorable(item, ItemStack, ItemStack::Instantiate(version, buffer), InvalidPacketErrorable<InventorySlot>(PACKET_ORDINAL))
      return SuccessErrorable<InventorySlot>(InventorySlot(windowId, stateId, slot, item));
    }

    Errorable<bool> Write(const ProtocolVersion* version, ByteBuffer* buffer) const override {
      buffer->WriteByte(windowId);
      if (version >= &MinecraftProtocolVersion::MINECRAFT_1_17_1) {
        buffer->WriteVarInt(stateId);
      }
      buffer->WriteShort(slot);
      item.Write(version, buffer);
      return SuccessErrorable<bool>(true);
    }

    [[nodiscard]] uint32_t GetOrdinal() const override {
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
