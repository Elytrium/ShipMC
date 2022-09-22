#include "ItemStack.hpp"
#include "../ProtocolUtils.hpp"

namespace Ship {

  ItemStack::ItemStack() : present(false), itemID(0), itemCount(0), nbt(nullptr) {
  }

  ItemStack::ItemStack(uint32_t itemId, uint8_t itemCount, NBT* nbt) : present(true), itemID(itemId), itemCount(itemCount), nbt(nbt) {
  }

  ItemStack::~ItemStack() {
    delete nbt;
  }

  void ItemStack::Write(ByteBuffer* buffer) {
    buffer->WriteBoolean(present);
    if (present) {
      buffer->WriteVarInt(itemID);
      buffer->WriteByte(itemCount);
      if (nbt) {
        ProtocolUtils::WriteNBT(buffer, nbt);
      } else {
        buffer->WriteByte(0);
      }
    }
  }

  void ItemStack::Read(ByteBuffer* buffer) {
    present = buffer->ReadBoolean();
    if (present) {
      itemID = buffer->ReadVarInt();
      itemCount = buffer->ReadByte();
      nbt = ProtocolUtils::ReadNBT(buffer);
    } else {
      itemID = itemCount = 0;
      nbt = nullptr;
    }
  }

  uint32_t ItemStack::Size() const {
    if (present) {
      if (nbt) {
        return ByteBuffer::BOOLEAN_SIZE + ByteBuffer::VarIntBytes(itemID) + ByteBuffer::BYTE_SIZE + nbt->GetSize();
      } else {
        return ByteBuffer::BOOLEAN_SIZE + ByteBuffer::VarIntBytes(itemID) + ByteBuffer::BYTE_SIZE * 2;
      }
    } else {
      return ByteBuffer::BOOLEAN_SIZE;
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

  NBT* ItemStack::GetNBT() const {
    return nbt;
  }

  void ItemStack::SetNBT(NBT* value) {
    delete nbt;
    nbt = value;
  }
}