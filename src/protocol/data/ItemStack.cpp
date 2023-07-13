#include "ItemStack.hpp"
#include "../MinecraftProtocol.hpp"
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

  Errorable<ItemStack> ItemStack::Instantiate(const Ship::ProtocolVersion* version, Ship::ByteBuffer* buffer) {
    bool present;
    uint16_t itemID;

    if (version >= &MinecraftProtocolVersion::MINECRAFT_1_13_2) {
      SetFromErrorable(present, bool, buffer->ReadBoolean(), InvalidItemStack(buffer->GetReadableBytes()))
    } else {
      SetFromErrorable(itemID, uint16_t, buffer->ReadShort(), InvalidItemStack(buffer->GetReadableBytes()))
      present = itemID != (uint16_t) -1;
    }

    if (present) {
      uint8_t itemCount;
      uint16_t data = 0;

      // TODO: ItemID Mappings
      if (version >= &MinecraftProtocolVersion::MINECRAFT_1_13_2) { 
        SetFromErrorable(itemID, uint32_t, buffer->ReadVarInt(), InvalidItemStack(buffer->GetReadableBytes()))
      }

      SetFromErrorable(itemCount, uint8_t, buffer->ReadByte(), InvalidItemStack(buffer->GetReadableBytes()))

      if (version < &MinecraftProtocolVersion::MINECRAFT_1_13) {
          SetFromErrorable(data, uint16_t, buffer->ReadShort(), InvalidItemStack(buffer->GetReadableBytes()))
      }

      ProceedErrorable(nbt, NBT*, ProtocolUtils::ReadNBT(buffer), InvalidItemStack(buffer->GetReadableBytes()))
      return SuccessErrorable<ItemStack>({itemID, itemCount, data, nbt});
    } else {
      return SuccessErrorable<ItemStack>({});
    }
  }

  ItemStack::~ItemStack() {
    delete nbt;
  }

  Errorable<bool> ItemStack::Write(const ProtocolVersion* version, ByteBuffer* buffer) const {
    if (version >= &MinecraftProtocolVersion::MINECRAFT_1_13_2) {
      buffer->WriteBoolean(present);
    }

    if (!present && version < &MinecraftProtocolVersion::MINECRAFT_1_13_2) {
      buffer->WriteShort(-1);
    }

    if (present) {
      if (version < &MinecraftProtocolVersion::MINECRAFT_1_13_2) { // TODO: Mappings
        buffer->WriteShort(itemID);
      } else {
        buffer->WriteVarInt(itemID);
      }

      buffer->WriteByte(itemCount);

      if (version < &MinecraftProtocolVersion::MINECRAFT_1_13) {
        buffer->WriteShort(data);
      }

      if (nbt) {
        ProtocolUtils::WriteNBT(buffer, nbt);
      } else {
        buffer->WriteByte(0);
      }
    }
    return SuccessErrorable<bool>(true);
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

  Errorable<OptionalItemStack> OptionalItemStack::Instantiate(const Ship::ProtocolVersion* version, Ship::ByteBuffer* buffer) {
    ProceedErrorable(hasItemStack, bool, buffer->ReadBoolean(), InvalidOptionalItemStack(buffer->GetReadableBytes()))
    if (hasItemStack) {
      ProceedErrorable(itemStack, ItemStack, ItemStack::Instantiate(version, buffer), InvalidOptionalItemStack(buffer->GetReadableBytes()))
      return SuccessErrorable<OptionalItemStack>(OptionalItemStack(itemStack));
    } else {
      return SuccessErrorable<OptionalItemStack>(OptionalItemStack(std::nullopt));
    }
  }

  Errorable<bool> OptionalItemStack::Write(const ProtocolVersion* version, ByteBuffer* buffer) const {
    buffer->WriteBoolean(itemStack.has_value());
    if (itemStack.has_value()) {
      itemStack->Write(version, buffer);
    }
    return SuccessErrorable<bool>(true);
  }

  OptionalItemStack::OptionalItemStack(std::optional<ItemStack> itemStack) : itemStack(std::move(itemStack)) {}
}