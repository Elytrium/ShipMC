#pragma once

#include "../../../utils/ordinal/OrdinalRegistry.hpp"
#include "../Packet.hpp"
#include <string>
#include <utility>

namespace Ship {

  class Explosion : public Packet {
   private:
    double x;
    double y;
    double z;
    float strength;
    std::vector<std::array<uint8_t, 3>> records;
    float playerMotionX;
    float playerMotionY;
    float playerMotionZ;

   public:
    static inline const uint32_t PACKET_ORDINAL = OrdinalRegistry::PacketRegistry.RegisterOrdinal();

    Explosion(double x, double y, double z, float strength, std::vector<std::array<uint8_t, 3>> records, float playerMotionX, float playerMotionY,
      float playerMotionZ)
      : x(x), y(y), z(z), strength(strength), records(std::move(records)), playerMotionX(playerMotionX), playerMotionY(playerMotionY),
        playerMotionZ(playerMotionZ) {
    }

    ~Explosion() override = default;

    void Read(const ProtocolVersion* version, ByteBuffer* buffer) override {
      if (version == &ProtocolVersion::MINECRAFT_1_19) {
        x = buffer->ReadFloat();
        y = buffer->ReadFloat();
        z = buffer->ReadFloat();
      } else {
        x = buffer->ReadDouble();
        y = buffer->ReadDouble();
        z = buffer->ReadDouble();
      }
      strength = buffer->ReadFloat();
      if (version >= &ProtocolVersion::MINECRAFT_1_17) {
        records.resize(buffer->ReadVarInt());
      } else {
        records.resize(buffer->ReadInt());
      }
      for (std::array<uint8_t, 3>& record : records) {
        for (uint8_t& byte : record) {
          byte = buffer->ReadByte();
        }
      }
      playerMotionX = buffer->ReadFloat();
      playerMotionY = buffer->ReadFloat();
      playerMotionZ = buffer->ReadFloat();
    }

    void Write(const ProtocolVersion* version, ByteBuffer* buffer) override {
      if (version == &ProtocolVersion::MINECRAFT_1_19) {
        buffer->WriteFloat((float) x);
        buffer->WriteFloat((float) y);
        buffer->WriteFloat((float) z);
      } else {
        buffer->WriteDouble(x);
        buffer->WriteDouble(y);
        buffer->WriteDouble(z);
      }
      buffer->WriteFloat(strength);
      if (version >= &ProtocolVersion::MINECRAFT_1_17) {
        buffer->WriteVarInt(records.size());
      } else {
        buffer->WriteInt(records.size());
      }
      for (const std::array<uint8_t, 3>& record : records) {
        for (uint8_t byte : record) {
          buffer->WriteByte(byte);
        }
      }
      buffer->WriteFloat(playerMotionX);
      buffer->WriteFloat(playerMotionY);
      buffer->WriteFloat(playerMotionZ);
    }

    uint32_t GetOrdinal() override {
      return PACKET_ORDINAL;
    }

    [[nodiscard]] double GetX() const {
      return x;
    }

    [[nodiscard]] double GetY() const {
      return y;
    }

    [[nodiscard]] double GetZ() const {
      return z;
    }

    [[nodiscard]] float GetStrength() const {
      return strength;
    }

    [[nodiscard]] const std::vector<std::array<uint8_t, 3>>& GetRecords() const {
      return records;
    }

    [[nodiscard]] float GetPlayerMotionX() const {
      return playerMotionX;
    }

    [[nodiscard]] float GetPlayerMotionY() const {
      return playerMotionY;
    }

    [[nodiscard]] float GetPlayerMotionZ() const {
      return playerMotionZ;
    }
  };
}
