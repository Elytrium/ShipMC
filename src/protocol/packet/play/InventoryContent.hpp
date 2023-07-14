#pragma once

#include "../../../../lib/ShipNet/src/utils/ordinal/OrdinalRegistry.hpp"
#include "../../data/ItemStack.hpp"
#include <string>
#include <utility>

namespace Ship {

  class InventoryContent : public Packet {
   private:
    uint8_t windowId{};
    uint32_t stateId{};
    std::vector<ItemStack> slots;
    ItemStack carriedItem;

   public:
    static inline const uint32_t PACKET_ORDINAL = OrdinalRegistry::PacketRegistry.RegisterOrdinal();

    InventoryContent() = default;
    InventoryContent(uint8_t windowId, uint32_t stateId, std::vector<ItemStack> slots, const ItemStack& carriedItem)
      : windowId(windowId), stateId(stateId), slots(std::move(slots)), carriedItem(carriedItem) {
    }

    ~InventoryContent() override = default;

    static Errorable<InventoryContent> Instantiate(const PacketHolder& holder) {
      ByteBuffer* buffer = holder.GetCurrentBuffer();
      const ProtocolVersion* version = holder.GetVersion();
      ProceedErrorable(windowId, uint8_t, buffer->ReadByte(), InvalidPacketErrorable<InventoryContent>(PACKET_ORDINAL))
      uint32_t stateId, vectorSize;
      if (version >= &MinecraftProtocolVersion::MINECRAFT_1_17_1) {
        SetFromErrorable(stateId, uint32_t, buffer->ReadVarInt(), InvalidPacketErrorable<InventoryContent>(PACKET_ORDINAL))
        SetFromErrorable(vectorSize, uint32_t, buffer->ReadVarInt(), InvalidPacketErrorable<InventoryContent>(PACKET_ORDINAL))
      } else {
        SetFromErrorable(vectorSize, uint16_t, buffer->ReadShort(), InvalidPacketErrorable<InventoryContent>(PACKET_ORDINAL))
      }

      std::vector<ItemStack> slots;
      for (int i = 0; i < vectorSize; ++i) {
        ProceedErrorable(slot, ItemStack, ItemStack::Instantiate(version, buffer), InvalidPacketErrorable<InventoryContent>(PACKET_ORDINAL))
        slots.push_back(slot);
      }

      ItemStack carriedItem;
      if (version >= &MinecraftProtocolVersion::MINECRAFT_1_17_1) {
        SetFromErrorable(carriedItem, ItemStack, ItemStack::Instantiate(version, buffer), InvalidPacketErrorable<InventoryContent>(PACKET_ORDINAL))
      }

      return SuccessErrorable<InventoryContent>(InventoryContent(windowId, stateId, slots, carriedItem));
    }

    Errorable<bool> Write(const ProtocolVersion* version, ByteBuffer* buffer) const override {
      buffer->WriteByte(windowId);
      if (version >= &MinecraftProtocolVersion::MINECRAFT_1_17_1) {
        buffer->WriteVarInt(stateId);
        buffer->WriteVarInt(slots.size());
      } else {
        buffer->WriteShort(slots.size());
      }

      for (const ItemStack& slot : slots) {
        slot.Write(version, buffer);
      }

      if (version >= &MinecraftProtocolVersion::MINECRAFT_1_17_1) {
        carriedItem.Write(version, buffer);
      }
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

    [[nodiscard]] const std::vector<ItemStack>& GetSlots() const {
      return slots;
    }

    [[nodiscard]] const ItemStack& GetCarriedItem() const {
      return carriedItem;
    }
  };
}
