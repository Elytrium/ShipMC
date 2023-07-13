#pragma once

#include "nbt/NBT.hpp"
#include <utility>

namespace Ship {

  class ItemStack : public Serializable {
   private:
    bool present;
    uint32_t itemID;
    uint8_t itemCount;
    uint16_t data;
    NBT* nbt;

   public:
    ItemStack();
    ItemStack(uint32_t itemId, uint8_t itemCount, uint16_t data, NBT* nbt);
    ItemStack(uint32_t itemId, uint8_t itemCount, NBT* nbt);
    ItemStack(uint32_t itemId, uint8_t itemCount);
    static Errorable<ItemStack> Instantiate(const ProtocolVersion* version, ByteBuffer* buffer);

    ~ItemStack() override;

    Errorable<bool> Write(const ProtocolVersion* version, ByteBuffer* buffer) const override;

    [[nodiscard]] bool IsPresent() const;
    void SetPresent(bool value);
    [[nodiscard]] uint32_t GetItemID() const;
    void SetItemId(uint32_t value);
    [[nodiscard]] uint8_t GetItemCount() const;
    void SetItemCount(uint8_t value);
    [[nodiscard]] uint16_t GetData() const;
    void SetData(uint16_t value);
    [[nodiscard]] NBT* GetNBT() const;
    void SetNBT(NBT* value);
  };

  class OptionalItemStack : public Serializable {
   private:
    std::optional<ItemStack> itemStack;

   public:
    OptionalItemStack() = default;
    explicit OptionalItemStack(std::optional<ItemStack> itemStack);
    static Errorable<OptionalItemStack> Instantiate(const ProtocolVersion* version, ByteBuffer* buffer);
    Errorable<bool> Write(const ProtocolVersion* version, ByteBuffer* buffer) const override;
  };

  CreateInvalidArgumentErrorable(InvalidItemStack, ItemStack, "Invalid ItemStack read");
  CreateInvalidArgumentErrorable(InvalidOptionalItemStack, OptionalItemStack, "Invalid OptionalItemStack read");
}