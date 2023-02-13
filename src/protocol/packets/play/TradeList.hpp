#pragma once

#include "../../../utils/ordinal/OrdinalRegistry.hpp"
#include "../Packet.hpp"
#include <string>
#include <utility>

namespace Ship {

  class Trade {
   private:
    ItemStack firstInputItem;
    ItemStack outputItem;
    std::optional<ItemStack> secondInputItem;
    bool tradeDisabled;
    uint32_t tradeUses;
    uint32_t maxTradeUses;
    uint32_t xp;
    uint32_t specialPrice;
    float priceMultiplier;
    uint32_t demand;

   public:
    Trade(const ItemStack& firstInputItem, const ItemStack& outputItem, std::optional<ItemStack> secondInputItem, bool tradeDisabled, uint32_t tradeUses,
      uint32_t maxTradeUses, uint32_t xp, uint32_t specialPrice, float priceMultiplier, uint32_t demand)
      : firstInputItem(firstInputItem), outputItem(outputItem), secondInputItem(std::move(secondInputItem)), tradeDisabled(tradeDisabled),
        tradeUses(tradeUses), maxTradeUses(maxTradeUses), xp(xp), specialPrice(specialPrice), priceMultiplier(priceMultiplier), demand(demand) {
    }

    Trade() : Trade({}, {}, std::nullopt, false, 0, 0, 0, 0, 0, 0) {
    }

    [[nodiscard]] ItemStack& GetFirstInputItem() {
      return firstInputItem;
    }

    void SetFirstInputItem(const ItemStack& value) {
      firstInputItem = value;
    }

    [[nodiscard]] ItemStack& GetOutputItem() {
      return outputItem;
    }

    void SetOutputItem(const ItemStack& value) {
      outputItem = value;
    }

    [[nodiscard]] std::optional<ItemStack>& GetSecondInputItem() {
      return secondInputItem;
    }

    void SetSecondInputItem(const std::optional<ItemStack>& value) {
      secondInputItem = value;
    }

    [[nodiscard]] bool IsTradeDisabled() const {
      return tradeDisabled;
    }

    void SetTradeDisabled(bool value) {
      tradeDisabled = value;
    }

    [[nodiscard]] uint32_t GetTradeUses() const {
      return tradeUses;
    }

    void SetTradeUses(uint32_t value) {
      tradeUses = value;
    }

    [[nodiscard]] uint32_t GetMaxTradeUses() const {
      return maxTradeUses;
    }

    void SetMaxTradeUses(uint32_t value) {
      maxTradeUses = value;
    }

    [[nodiscard]] uint32_t GetXp() const {
      return xp;
    }

    void SetXp(uint32_t value) {
      xp = value;
    }

    [[nodiscard]] uint32_t GetSpecialPrice() const {
      return specialPrice;
    }

    void SetSpecialPrice(uint32_t value) {
      specialPrice = value;
    }

    [[nodiscard]] float GetPriceMultiplier() const {
      return priceMultiplier;
    }

    void SetPriceMultiplier(float value) {
      priceMultiplier = value;
    }

    [[nodiscard]] uint32_t GetDemand() const {
      return demand;
    }

    void SetDemand(uint32_t value) {
      demand = value;
    }
  };

  class TradeList : public Packet {
   private:
    uint32_t windowId;
    std::vector<Trade> trades;
    uint32_t villagerLevel;
    uint32_t experience;
    bool regularVillager;
    bool canRestock;

   public:
    static inline const uint32_t PACKET_ORDINAL = OrdinalRegistry::PacketRegistry.RegisterOrdinal();

    TradeList(uint32_t windowId, std::vector<Trade> trades, uint32_t villagerLevel, uint32_t experience, bool regularVillager, bool canRestock)
      : windowId(windowId), trades(std::move(trades)), villagerLevel(villagerLevel), experience(experience), regularVillager(regularVillager),
        canRestock(canRestock) {
    }

    ~TradeList() override = default;

    void Read(const ProtocolVersion* version, ByteBuffer* buffer) override {
      windowId = buffer->ReadVarInt();
      if (version >= &ProtocolVersion::MINECRAFT_1_19) {
        trades.resize(buffer->ReadVarInt());
      } else {
        trades.resize(buffer->ReadByte());
      }
      for (Trade& trade : trades) {
        trade.SetFirstInputItem(ItemStack(version, buffer));
        trade.SetOutputItem(ItemStack(version, buffer));
        if (buffer->ReadBoolean()) {
          trade.SetSecondInputItem(ItemStack(version, buffer));
        } else {
          trade.SetSecondInputItem(std::nullopt);
        }
        trade.SetTradeDisabled(buffer->ReadBoolean());
        trade.SetTradeUses(buffer->ReadInt());
        trade.SetMaxTradeUses(buffer->ReadInt());
        trade.SetXp(buffer->ReadInt());
        trade.SetSpecialPrice(buffer->ReadInt());
        trade.SetPriceMultiplier(buffer->ReadFloat());
        trade.SetDemand(buffer->ReadInt());
      }
      villagerLevel = buffer->ReadVarInt();
      experience = buffer->ReadVarInt();
      regularVillager = buffer->ReadBoolean();
      canRestock = buffer->ReadBoolean();
    }

    void Write(const ProtocolVersion* version, ByteBuffer* buffer) override {
      buffer->WriteVarInt(windowId);
      if (version >= &ProtocolVersion::MINECRAFT_1_19) {
        buffer->WriteVarInt(trades.size());
      } else {
        buffer->WriteByte(trades.size());
      }
      for (Trade& trade : trades) {
        trade.GetFirstInputItem().Write(version, buffer);
        trade.GetOutputItem().Write(version, buffer);
        if (trade.GetSecondInputItem()) {
          trade.GetSecondInputItem()->Write(version, buffer);
        }
        buffer->WriteBoolean(trade.IsTradeDisabled());
        buffer->WriteInt(trade.GetTradeUses());
        buffer->WriteInt(trade.GetMaxTradeUses());
        buffer->WriteInt(trade.GetXp());
        buffer->WriteInt(trade.GetSpecialPrice());
        buffer->WriteFloat(trade.GetPriceMultiplier());
        buffer->WriteInt(trade.GetDemand());
      }
      buffer->WriteVarInt(villagerLevel);
      buffer->WriteVarInt(experience);
      buffer->WriteBoolean(regularVillager);
      buffer->WriteBoolean(canRestock);
    }

    uint32_t GetOrdinal() override {
      return PACKET_ORDINAL;
    }

    [[nodiscard]] uint32_t GetWindowId() const {
      return windowId;
    }

    [[nodiscard]] const std::vector<Trade>& GetTrades() const {
      return trades;
    }

    [[nodiscard]] uint32_t GetVillagerLevel() const {
      return villagerLevel;
    }

    [[nodiscard]] uint32_t GetExperience() const {
      return experience;
    }

    [[nodiscard]] bool IsRegularVillager() const {
      return regularVillager;
    }

    [[nodiscard]] bool IsCanRestock() const {
      return canRestock;
    }
  };
}
