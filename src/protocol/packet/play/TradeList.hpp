#pragma once

#include "../../../../lib/ShipNet/src/utils/ordinal/OrdinalRegistry.hpp"
#include <string>
#include <utility>

namespace Ship {

  class Trade {
   private:
    const ItemStack firstInputItem;
    const ItemStack outputItem;
    const OptionalItemStack secondInputItem;
    bool tradeDisabled;
    uint32_t tradeUses;
    uint32_t maxTradeUses;
    uint32_t xp;
    uint32_t specialPrice;
    float priceMultiplier;
    uint32_t demand;

   public:
    Trade(const ItemStack& firstInputItem, const ItemStack& outputItem, OptionalItemStack secondInputItem, bool tradeDisabled, uint32_t tradeUses,
      uint32_t maxTradeUses, uint32_t xp, uint32_t specialPrice, float priceMultiplier, uint32_t demand)
      : firstInputItem(firstInputItem), outputItem(outputItem), secondInputItem(std::move(secondInputItem)), tradeDisabled(tradeDisabled),
        tradeUses(tradeUses), maxTradeUses(maxTradeUses), xp(xp), specialPrice(specialPrice), priceMultiplier(priceMultiplier), demand(demand) {
    }

    Trade() : Trade({}, {}, {}, false, 0, 0, 0, 0, 0, 0) {
    }

    Trade(const ProtocolVersion* version, ByteBuffer* buffer)
      : firstInputItem(ItemStack(version, buffer)), outputItem(ItemStack(version, buffer)), secondInputItem(OptionalItemStack(version, buffer)),
        tradeDisabled(buffer->ReadBoolean()), tradeUses(buffer->ReadInt()), maxTradeUses(buffer->ReadInt()), xp(buffer->ReadInt()),
        specialPrice(buffer->ReadInt()), priceMultiplier(buffer->ReadFloat()), demand(buffer->ReadInt()) {
    }

    [[nodiscard]] ItemStack& GetFirstInputItem() const {
      return const_cast<ItemStack&>(firstInputItem);
    }

    [[nodiscard]] ItemStack& GetOutputItem() const {
      return const_cast<ItemStack&>(outputItem);
    }

    [[nodiscard]] std::optional<ItemStack>& GetSecondInputItem() const {
      return (std::optional<ItemStack>&) secondInputItem;
    }

    [[nodiscard]] bool IsTradeDisabled() const {
      return tradeDisabled;
    }

    [[nodiscard]] uint32_t GetTradeUses() const {
      return tradeUses;
    }

    [[nodiscard]] uint32_t GetMaxTradeUses() const {
      return maxTradeUses;
    }

    [[nodiscard]] uint32_t GetXp() const {
      return xp;
    }

    [[nodiscard]] uint32_t GetSpecialPrice() const {
      return specialPrice;
    }

    [[nodiscard]] float GetPriceMultiplier() const {
      return priceMultiplier;
    }

    [[nodiscard]] uint32_t GetDemand() const {
      return demand;
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

    static Errorable<TradeList> Instantiate(const PacketHolder& holder) {
      ByteBuffer* buffer = holder.GetCurrentBuffer();
      const ProtocolVersion* version = holder.GetVersion();
      ProceedErrorable(windowId, uint32_t, buffer->ReadVarInt(), InvalidPacketErrorable<>(PACKET_ORDINAL))
      uint32_t vectorSize;
      if (version >= &MinecraftProtocolVersion::MINECRAFT_1_19) {
        ProceedErrorable(vectorSize, uint32_t, buffer->ReadVarInt(), InvalidPacketErrorable<>(PACKET_ORDINAL))
      } else {
        ProceedErrorable(vectorSize, uint8_t, buffer->ReadByte(), InvalidPacketErrorable<>(PACKET_ORDINAL))
      }
      for (int i = 0; i < vectorSize; ++i) {
        trades.emplace_back(version, buffer);
      }
      ProceedErrorable(villagerLevel, uint32_t, buffer->ReadVarInt(), InvalidPacketErrorable<>(PACKET_ORDINAL))
      ProceedErrorable(experience, uint32_t, buffer->ReadVarInt(), InvalidPacketErrorable<>(PACKET_ORDINAL))
      ProceedErrorable(regularVillager, bool, buffer->ReadBoolean(), InvalidPacketErrorable<>(PACKET_ORDINAL))
      ProceedErrorable(canRestock, bool, buffer->ReadBoolean(), InvalidPacketErrorable<>(PACKET_ORDINAL))
    }

    void Write(const ProtocolVersion* version, ByteBuffer* buffer) const override {
      buffer->WriteVarInt(windowId);
      if (version >= &MinecraftProtocolVersion::MINECRAFT_1_19) {
        buffer->WriteVarInt(trades.size());
      } else {
        buffer->WriteByte(trades.size());
      }
      for (const Trade& trade : trades) {
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

    uint32_t GetOrdinal() const override {
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
