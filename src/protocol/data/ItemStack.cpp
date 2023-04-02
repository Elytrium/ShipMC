#include "ItemStack.hpp"
#include "../ProtocolUtils.hpp"

namespace Ship {

  ItemStack::ItemStack() : present(false), itemID(0), itemCount(0), data(0), nbt(nullptr) {
  }

  ItemStack::ItemStack(uint32_t itemId, uint8_t itemCount, uint16_t data, NBT* nbt)
    : present(true), itemID(itemId), itemCount(itemCount), data(data), nbt(nbt) {
  }

  ItemStack::ItemStack(uint32_t itemId, uint8_t itemCount, NBT* nbt) : present(true), itemID(itemId), itemCount(itemCount), data(0), nbt(nbt) {
  }

  ItemStack::ItemStack(uint32_t itemId, uint8_t itemCount) : present(true), itemID(itemId), itemCount(itemCount), data(0), nbt(nullptr) {
  }

  ItemStack::ItemStack(const ProtocolVersion* version, ByteBuffer* buffer) : ItemStack() {
    if (version >= &ProtocolVersion::MINECRAFT_1_13_2) {
      ProceedErrorable(present, bool, buffer->ReadBoolean(), InvalidPacketErrorable<>(PACKET_ORDINAL))
    } else {
      present = buffer->ReadShort() != (uint16_t) -1;
    }

    delete nbt;
    if (present) {
      if (version < &ProtocolVersion::MINECRAFT_1_13_2) { // TODO: Mappings
        ProceedErrorable(itemID, uint16_t, buffer->ReadShort(), InvalidPacketErrorable<>(PACKET_ORDINAL))
      } else {
        ProceedErrorable(itemID, uint32_t, buffer->ReadVarInt(), InvalidPacketErrorable<>(PACKET_ORDINAL))
      }

      ProceedErrorable(itemCount, uint8_t, buffer->ReadByte(), InvalidPacketErrorable<>(PACKET_ORDINAL))

      if (version < &ProtocolVersion::MINECRAFT_1_13) {
        ProceedErrorable(data, uint16_t, buffer->ReadShort(), InvalidPacketErrorable<>(PACKET_ORDINAL))
      }

      nbt = ProtocolUtils::ReadNBT(buffer);
    } else {
      itemID = itemCount = data = 0;
      nbt = nullptr;
    }
  }

  ItemStack::~ItemStack() {
    delete nbt;
  }

  void ItemStack::Write(const ProtocolVersion* version, ByteBuffer* buffer) const {
    if (version >= &ProtocolVersion::MINECRAFT_1_13_2) {
      buffer->WriteBoolean(present);
    }

    if (!present && version < &ProtocolVersion::MINECRAFT_1_13_2) {
      buffer->WriteShort(-1);
    }

    if (present) {
      if (version < &ProtocolVersion::MINECRAFT_1_13_2) { // TODO: Mappings
        buffer->WriteShort(itemID);
      } else {
        buffer->WriteVarInt(itemID);
      }

      buffer->WriteByte(itemCount);

      if (version < &ProtocolVersion::MINECRAFT_1_13) {
        buffer->WriteShort(data);
      }

      if (nbt) {
        ProtocolUtils::WriteNBT(buffer, nbt);
      } else {
        buffer->WriteByte(0);
      }
    }
  }

  bool ItemStack::IsPresent() const {
    return present;
  }

  void ItemStack::SetPresent(bool value) {
    present = value;
  }

  uint32_t ItemStack::GetItemID() const {
    return itemID;
  }

  void ItemStack::SetItemId(uint32_t value) {
    itemID = value;
  }

  uint8_t ItemStack::GetItemCount() const {
    return itemCount;
  }

  void ItemStack::SetItemCount(uint8_t value) {
    itemCount = value;
  }

  uint16_t ItemStack::GetData() const {
    return data;
  }

  void ItemStack::SetData(uint16_t value) {
    data = value;
  }

  NBT* ItemStack::GetNBT() const {
    return nbt;
  }

  void ItemStack::SetNBT(NBT* value) {
    delete nbt;
    nbt = value;
  }

  OptionalItemStack::OptionalItemStack(const ProtocolVersion* version, ByteBuffer* buffer) {
    if (buffer->ReadBoolean()) {
      itemStack = ItemStack(version, buffer);
    } else {
      itemStack = std::nullopt;
    }
  }

  void OptionalItemStack::Write(const ProtocolVersion* version, ByteBuffer* buffer) const {
    buffer->WriteBoolean(itemStack.has_value());
    if (itemStack.has_value()) {
      itemStack->Write(version, buffer);
    }
  }
}