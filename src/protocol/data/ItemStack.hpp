#pragma once

#include "nbt/NBT.hpp"

namespace Ship {

  class ItemStack {
   private:
    bool present;
    uint32_t itemID;
    uint8_t itemCount;
    NBT* nbt;

   public:
    ItemStack();
    ItemStack(uint32_t itemId, uint8_t itemCount, NBT* nbt);

    ~ItemStack();

    void Write(ByteBuffer* buffer);
    void Read(ByteBuffer* buffer);
    [[nodiscard]] uint32_t Size() const;

    [[nodiscard]] bool IsPresent() const;
    void SetPresent(bool value);
    [[nodiscard]] uint32_t GetItemID() const;
    void SetItemId(uint32_t value);
    [[nodiscard]] uint8_t GetItemCount() const;
    void SetItemCount(uint8_t value);
    [[nodiscard]] NBT* GetNBT() const;
    void SetNBT(NBT* value);
  };
}