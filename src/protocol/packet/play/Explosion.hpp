#pragma once

#include "../../../../lib/ShipNet/src/utils/ordinal/OrdinalRegistry.hpp"
#include <array>
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

    static Errorable<Explosion> Instantiate(const PacketHolder& holder) {
      ByteBuffer* buffer = holder.GetCurrentBuffer();
      const ProtocolVersion* version = holder.GetVersion();
      if (version == &MinecraftProtocolVersion::MINECRAFT_1_19) {
        ProceedErrorable(x, float, buffer->ReadFloat(), InvalidPacketErrorable<>(PACKET_ORDINAL))
        ProceedErrorable(y, float, buffer->ReadFloat(), InvalidPacketErrorable<>(PACKET_ORDINAL))
        ProceedErrorable(z, float, buffer->ReadFloat(), InvalidPacketErrorable<>(PACKET_ORDINAL))
      } else {
        ProceedErrorable(x, double, buffer->ReadDouble(), InvalidPacketErrorable<>(PACKET_ORDINAL))
        ProceedErrorable(y, double, buffer->ReadDouble(), InvalidPacketErrorable<>(PACKET_ORDINAL))
        ProceedErrorable(z, double, buffer->ReadDouble(), InvalidPacketErrorable<>(PACKET_ORDINAL))
      }
      ProceedErrorable(strength, float, buffer->ReadFloat(), InvalidPacketErrorable<>(PACKET_ORDINAL))
      if (version >= &MinecraftProtocolVersion::MINECRAFT_1_17) {
        records.resize(buffer->ReadVarInt());
      } else {
        records.resize(buffer->ReadInt());
      }
      for (std::array<uint8_t, 3>& record : records) {
        for (uint8_t& byte : record) {
          ProceedErrorable(byte, uint8_t, buffer->ReadByte(), InvalidPacketErrorable<>(PACKET_ORDINAL))
        }
      }
      ProceedErrorable(playerMotionX, float, buffer->ReadFloat(), InvalidPacketErrorable<>(PACKET_ORDINAL))
      ProceedErrorable(playerMotionY, float, buffer->ReadFloat(), InvalidPacketErrorable<>(PACKET_ORDINAL))
      ProceedErrorable(playerMotionZ, float, buffer->ReadFloat(), InvalidPacketErrorable<>(PACKET_ORDINAL))
    }

    Errorable<bool> Write(const ProtocolVersion* version, ByteBuffer* buffer) const override {
      if (version == &MinecraftProtocolVersion::MINECRAFT_1_19) {
        buffer->WriteFloat((float) x);
        buffer->WriteFloat((float) y);
        buffer->WriteFloat((float) z);
      } else {
        buffer->WriteDouble(x);
        buffer->WriteDouble(y);
        buffer->WriteDouble(z);
      }
      buffer->WriteFloat(strength);
      if (version >= &MinecraftProtocolVersion::MINECRAFT_1_17) {
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
      return SuccessErrorable<bool>(true);
    }

    [[nodiscard]] uint32_t GetOrdinal() const override {
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
