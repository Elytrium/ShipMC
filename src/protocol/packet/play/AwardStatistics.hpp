#pragma once

#include "../../../../lib/ShipNet/src/utils/ordinal/OrdinalRegistry.hpp"
#include <string>
#include <utility>

namespace Ship {

  class Statistic {
   private:
    std::string name;
    uint32_t categoryId {};
    uint32_t statisticId {};
    uint32_t value {};

   public:
    explicit Statistic(std::string name) : name(std::move(name)) {
    }

    Statistic(uint32_t categoryId, uint32_t statisticId, uint32_t value) : categoryId(categoryId), statisticId(statisticId), value(value) {
    }

    Statistic(std::string name, uint32_t categoryId, uint32_t statisticId, uint32_t value)
      : name(std::move(name)), categoryId(categoryId), statisticId(statisticId), value(value) {
    }

    Statistic() : Statistic(0, 0, 0) {
    }

    static Errorable<Statistic> Instantiate(const PacketHolder& holder);

    [[nodiscard]] uint32_t GetCategoryId() const {
      return categoryId;
    }

    void SetCategoryId(uint32_t newValue) {
      categoryId = newValue;
    }

    [[nodiscard]] uint32_t GetStatisticId() const {
      return statisticId;
    }

    void SetStatisticId(uint32_t newValue) {
      statisticId = newValue;
    }

    [[nodiscard]] uint32_t GetValue() const {
      return value;
    }

    void SetValue(uint32_t newValue) {
      value = newValue;
    }

    [[nodiscard]] const std::string& GetName() const {
      return name;
    }

    void SetName(const std::string& newValue) {
      name = newValue;
    }
  };

  class AwardStatistics : public Packet {
   private:
    std::vector<Statistic> statistics;

   public:
    static inline const uint32_t PACKET_ORDINAL = OrdinalRegistry::PacketRegistry.RegisterOrdinal();

    AwardStatistics() = default;

    explicit AwardStatistics(std::vector<Statistic> statistics) : statistics(std::move(statistics)) {
    }

    static Errorable<AwardStatistics> Instantiate(const PacketHolder& holder) {
      ByteBuffer* buffer = holder.GetCurrentBuffer();
      ProceedErrorable(vectorSize, uint32_t, buffer->ReadVarInt(), InvalidPacketErrorable<AwardStatistics>(PACKET_ORDINAL))

      std::vector<Statistic> statistics;
      for (int i = 0; i < vectorSize; ++i) {
        ProceedErrorable(statistic, Statistic, Statistic::Instantiate(holder), InvalidPacketErrorable<AwardStatistics>(PACKET_ORDINAL))
        statistics.push_back(statistic);
      }

      return SuccessErrorable<AwardStatistics>(AwardStatistics(statistics));
    }

    ~AwardStatistics() override = default;

    void Write(const ProtocolVersion* version, ByteBuffer* buffer) const override {
      buffer->WriteVarInt(statistics.size());
      for (const Statistic& statistic : statistics) {
        if (version >= &MinecraftProtocolVersion::MINECRAFT_1_13) {
          buffer->WriteVarInt(statistic.GetCategoryId());
          buffer->WriteVarInt(statistic.GetStatisticId());
        } else {
          buffer->WriteString(statistic.GetName());
        }
        buffer->WriteVarInt(statistic.GetValue());
      }
    }

    [[nodiscard]] uint32_t GetOrdinal() const override {
      return PACKET_ORDINAL;
    }

    [[nodiscard]] const std::vector<Statistic>& GetStatistics() const {
      return statistics;
    }
  };

  Errorable<Statistic> Statistic::Instantiate(const PacketHolder& holder) {
    ByteBuffer* buffer = holder.GetCurrentBuffer();
    const ProtocolVersion* version = holder.GetVersion();
    std::string name;
    uint32_t categoryId;
    uint32_t statisticId;
    uint32_t value;

    if (version >= &MinecraftProtocolVersion::MINECRAFT_1_13) {
      SetFromErrorable(categoryId, uint32_t, buffer->ReadVarInt(), InvalidPacketErrorable<Statistic>(AwardStatistics::PACKET_ORDINAL))
      SetFromErrorable(statisticId, uint32_t, buffer->ReadVarInt(), InvalidPacketErrorable<Statistic>(AwardStatistics::PACKET_ORDINAL))
    } else {
      SetFromErrorable(name, std::string, buffer->ReadString(), InvalidPacketErrorable<Statistic>(AwardStatistics::PACKET_ORDINAL))
    }
    SetFromErrorable(value, uint32_t, buffer->ReadVarInt(), InvalidPacketErrorable<Statistic>(AwardStatistics::PACKET_ORDINAL))

    return SuccessErrorable<Statistic>({name, categoryId, statisticId, value});
  }
}
