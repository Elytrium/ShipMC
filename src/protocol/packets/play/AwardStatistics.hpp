#pragma once

#include "../../../utils/ordinal/OrdinalRegistry.hpp"
#include "../Packet.hpp"
#include <string>
#include <utility>

namespace Ship {

  class Statistic {
   private:
    std::string name;
    uint32_t categoryId;
    uint32_t statisticId;
    uint32_t value;

   public:
    Statistic(std::string name) : name(std::move(name)) {
    }

    Statistic(uint32_t categoryId, uint32_t statisticId, uint32_t value) : categoryId(categoryId), statisticId(statisticId), value(value) {
    }

    Statistic() : Statistic(0, 0, 0) {
    }

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

    explicit AwardStatistics(std::vector<Statistic> statistics) : statistics(std::move(statistics)) {
    }

    ~AwardStatistics() override = default;

    void Read(const ProtocolVersion* version, ByteBuffer* buffer) override {
      statistics.resize(buffer->ReadVarInt());
      for (Statistic& statistic : statistics) {
        if (version >= &ProtocolVersion::MINECRAFT_1_13) {
          statistic.SetCategoryId(buffer->ReadVarInt());
          statistic.SetStatisticId(buffer->ReadVarInt());
        } else {
          statistic.SetName(buffer->ReadString());
        }
        statistic.SetValue(buffer->ReadVarInt());
      }
    }

    void Write(const ProtocolVersion* version, ByteBuffer* buffer) override {
      buffer->WriteVarInt(statistics.size());
      for (const Statistic& statistic : statistics) {
        if (version >= &ProtocolVersion::MINECRAFT_1_13) {
          buffer->WriteVarInt(statistic.GetCategoryId());
          buffer->WriteVarInt(statistic.GetStatisticId());
        } else {
          buffer->WriteString(statistic.GetName());
        }
        buffer->WriteVarInt(statistic.GetValue());
      }
    }

    uint32_t GetOrdinal() override {
      return PACKET_ORDINAL;
    }

    [[nodiscard]] const std::vector<Statistic>& GetStatistics() const {
      return statistics;
    }
  };
}
