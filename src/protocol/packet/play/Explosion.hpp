#pragma once

#include "../../../../lib/ShipNet/src/utils/ordinal/OrdinalRegistry.hpp"
#include <array>
#include <string>
#include <utility>

namespace Ship {

  class Explosion : public Packet {
   private:
    double x{};
    double y{};
    double z{};
    float strength{};
    std::vector<std::array<uint8_t, 3>> records;
    float playerMotionX{};
    float playerMotionY{};
    float playerMotionZ{};

   public:
    static inline const uint32_t PACKET_ORDINAL = OrdinalRegistry::PacketRegistry.RegisterOrdinal();

    Explosion() = default;
    Explosion(double x, double y, double z, float strength, std::vector<std::array<uint8_t, 3>> records, float playerMotionX, float playerMotionY,
      float playerMotionZ)
      : x(x), y(y), z(z), strength(strength), records(std::move(records)), playerMotionX(playerMotionX), playerMotionY(playerMotionY),
        playerMotionZ(playerMotionZ) {
    }

    ~Explosion() override = default;

    static Errorable<Explosion> Instantiate(const PacketHolder& holder) {
      ByteBuffer* buffer = holder.GetCurrentBuffer();
      const ProtocolVersion* version = holder.GetVersion();
      double x, y, z;
      if (version == &MinecraftProtocolVersion::MINECRAFT_1_19) {
        SetFromErrorable(x, float, buffer->ReadFloat(), InvalidPacketErrorable<Explosion>(PACKET_ORDINAL))
        SetFromErrorable(y, float, buffer->ReadFloat(), InvalidPacketErrorable<Explosion>(PACKET_ORDINAL))
        SetFromErrorable(z, float, buffer->ReadFloat(), InvalidPacketErrorable<Explosion>(PACKET_ORDINAL))
      } else {
        SetFromErrorable(x, double, buffer->ReadDouble(), InvalidPacketErrorable<Explosion>(PACKET_ORDINAL))
        SetFromErrorable(y, double, buffer->ReadDouble(), InvalidPacketErrorable<Explosion>(PACKET_ORDINAL))
        SetFromErrorable(z, double, buffer->ReadDouble(), InvalidPacketErrorable<Explosion>(PACKET_ORDINAL))
      }
      ProceedErrorable(strength, float, buffer->ReadFloat(), InvalidPacketErrorable<Explosion>(PACKET_ORDINAL))
      uint32_t recordsSize;
      if (version >= &MinecraftProtocolVersion::MINECRAFT_1_17) {
        SetFromErrorable(recordsSize, uint32_t , buffer->ReadVarInt(), InvalidPacketErrorable<Explosion>(PACKET_ORDINAL))
      } else {
        SetFromErrorable(recordsSize, uint32_t , buffer->ReadInt(), InvalidPacketErrorable<Explosion>(PACKET_ORDINAL))
      }

      std::vector<std::array<uint8_t, 3>> records(recordsSize);
      for (std::array<uint8_t, 3>& record : records) {
        for (uint8_t& byte : record) {
          SetFromErrorable(byte, uint8_t, buffer->ReadByte(), InvalidPacketErrorable<Explosion>(PACKET_ORDINAL))
        }
      }

      ProceedErrorable(playerMotionX, float, buffer->ReadFloat(), InvalidPacketErrorable<Explosion>(PACKET_ORDINAL))
      ProceedErrorable(playerMotionY, float, buffer->ReadFloat(), InvalidPacketErrorable<Explosion>(PACKET_ORDINAL))
      ProceedErrorable(playerMotionZ, float, buffer->ReadFloat(), InvalidPacketErrorable<Explosion>(PACKET_ORDINAL))
      return SuccessErrorable<Explosion>(Explosion(x, y, z, strength, records, playerMotionX, playerMotionY, playerMotionZ));
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
