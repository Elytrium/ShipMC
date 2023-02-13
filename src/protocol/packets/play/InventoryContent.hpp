#pragma once

#include "../../../utils/ordinal/OrdinalRegistry.hpp"
#include "../../data/ItemStack.hpp"
#include "../Packet.hpp"
#include <string>
#include <utility>

namespace Ship {

  class InventoryContent : public Packet {
   private:
    uint8_t windowId;
    uint32_t stateId;
    std::vector<ItemStack> slots;
    ItemStack carriedItem;

   public:
    static inline const uint32_t PACKET_ORDINAL = OrdinalRegistry::PacketRegistry.RegisterOrdinal();

    InventoryContent(uint8_t windowId, uint32_t stateId, std::vector<ItemStack> slots, const ItemStack& carriedItem)
      : windowId(windowId), stateId(stateId), slots(std::move(slots)), carriedItem(carriedItem) {
    }

    ~InventoryContent() override = default;

    void Read(const ProtocolVersion* version, ByteBuffer* buffer) override {
      windowId = buffer->ReadByte();
      if (version >= &ProtocolVersion::MINECRAFT_1_17_1) {
        stateId = buffer->ReadVarInt();
        slots.resize(buffer->ReadVarInt());
      } else {
        slots.resize(buffer->ReadShort());
      }

      for (ItemStack& slot : slots) {
        slot.Read(version, buffer);
      }

      if (version >= &ProtocolVersion::MINECRAFT_1_17_1) {
        carriedItem.Read(version, buffer);
      }
    }

    void Write(const ProtocolVersion* version, ByteBuffer* buffer) override {
      buffer->WriteByte(windowId);
      if (version >= &ProtocolVersion::MINECRAFT_1_17_1) {
        buffer->WriteVarInt(stateId);
        buffer->WriteVarInt(slots.size());
      } else {
        buffer->WriteShort(slots.size());
      }

      for (ItemStack& slot : slots) {
        slot.Write(version, buffer);
      }

      if (version >= &ProtocolVersion::MINECRAFT_1_17_1) {
        carriedItem.Write(version, buffer);
      }
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

    [[nodiscard]] const std::vector<ItemStack>& GetSlots() const {
      return slots;
    }

    [[nodiscard]] const ItemStack& GetCarriedItem() const {
      return carriedItem;
    }
  };
}
