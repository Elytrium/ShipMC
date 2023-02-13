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
    Read(version, buffer);
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

  void ItemStack::Read(const ProtocolVersion* version, ByteBuffer* buffer) {
    if (version >= &ProtocolVersion::MINECRAFT_1_13_2) {
      present = buffer->ReadBoolean();
    } else {
      present = buffer->ReadShort() != (uint16_t) -1;
    }

    delete nbt;
    if (present) {
      if (version < &ProtocolVersion::MINECRAFT_1_13_2) { // TODO: Mappings
        itemID = buffer->ReadShort();
      } else {
        itemID = buffer->ReadVarInt();
      }

      itemCount = buffer->ReadByte();

      if (version < &ProtocolVersion::MINECRAFT_1_13) {
        data = buffer->ReadShort();
      }

      nbt = ProtocolUtils::ReadNBT(buffer);
    } else {
      itemID = itemCount = data = 0;
      nbt = nullptr;
    }
  }

  uint32_t ItemStack::Size(const ProtocolVersion* version) const {
    if (present) {
      uint32_t size = ByteBuffer::BYTE_SIZE;
      if (version < &ProtocolVersion::MINECRAFT_1_13_2) {
        size += ByteBuffer::SHORT_SIZE;
      } else {
        size += ByteBuffer::VarIntBytes(itemID); // TODO: Mappings
      }

      if (version < &ProtocolVersion::MINECRAFT_1_13) {
        size += ByteBuffer::SHORT_SIZE;
      }

      return size + ProtocolUtils::NBTSize(nbt);
    } else {
      if (version >= &ProtocolVersion::MINECRAFT_1_13_2) {
        return ByteBuffer::BOOLEAN_SIZE;
      } else {
        return ByteBuffer::SHORT_SIZE;
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
}