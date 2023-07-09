#pragma once

#include "../../../../lib/ShipNet/src/utils/ordinal/OrdinalRegistry.hpp"
#include <string>

namespace Ship {

  class Particle : public Packet {
   private:
    AbstractParticle* particle;
    bool longDistance;
    double x;
    double y;
    double z;
    float offsetX;
    float offsetY;
    float offsetZ;
    float maxSpeed;
    uint32_t particleCount;

   public:
    static inline const uint32_t PACKET_ORDINAL = OrdinalRegistry::PacketRegistry.RegisterOrdinal();

    Particle(AbstractParticle* particle, bool longDistance, double x, double y, double z, float offsetX, float offsetY, float offsetZ, float maxSpeed,
      uint32_t particleCount)
      : particle(particle), longDistance(longDistance), x(x), y(y), z(z), offsetX(offsetX), offsetY(offsetY), offsetZ(offsetZ), maxSpeed(maxSpeed),
        particleCount(particleCount) {
    }

    ~Particle() override {
      delete particle;
    }

    static Errorable<Particle> Instantiate(const PacketHolder& holder) {
      ByteBuffer* buffer = holder.GetCurrentBuffer();
      const ProtocolVersion* version = holder.GetVersion();
      uint32_t particleId;
      if (version >= &MinecraftProtocolVersion::MINECRAFT_1_19) {
        ProceedErrorable(particleId, uint32_t, buffer->ReadVarInt(), InvalidPacketErrorable<>(PACKET_ORDINAL))
      } else {
        particleId = buffer->ReadInt();
      }
      delete particle;
      ProceedErrorable(longDistance, bool, buffer->ReadBoolean(), InvalidPacketErrorable<>(PACKET_ORDINAL))
      if (version >= &MinecraftProtocolVersion::MINECRAFT_1_15) {
        ProceedErrorable(x, double, buffer->ReadDouble(), InvalidPacketErrorable<>(PACKET_ORDINAL))
        ProceedErrorable(y, double, buffer->ReadDouble(), InvalidPacketErrorable<>(PACKET_ORDINAL))
        ProceedErrorable(z, double, buffer->ReadDouble(), InvalidPacketErrorable<>(PACKET_ORDINAL))
      } else {
        ProceedErrorable(x, float, buffer->ReadFloat(), InvalidPacketErrorable<>(PACKET_ORDINAL))
        ProceedErrorable(y, float, buffer->ReadFloat(), InvalidPacketErrorable<>(PACKET_ORDINAL))
        ProceedErrorable(z, float, buffer->ReadFloat(), InvalidPacketErrorable<>(PACKET_ORDINAL))
      }
      ProceedErrorable(offsetX, float, buffer->ReadFloat(), InvalidPacketErrorable<>(PACKET_ORDINAL))
      ProceedErrorable(offsetY, float, buffer->ReadFloat(), InvalidPacketErrorable<>(PACKET_ORDINAL))
      ProceedErrorable(offsetZ, float, buffer->ReadFloat(), InvalidPacketErrorable<>(PACKET_ORDINAL))
      ProceedErrorable(maxSpeed, float, buffer->ReadFloat(), InvalidPacketErrorable<>(PACKET_ORDINAL))
      particleCount = buffer->ReadInt();
      particle = PARTICLE_REGISTRY.GetObjectByID(version, particleId, buffer);
    }

    void Write(const ProtocolVersion* version, ByteBuffer* buffer) const override {
      uint32_t particleId = PARTICLE_REGISTRY.GetIDByOrdinal(version, particle->GetOrdinal());
      if (version >= &MinecraftProtocolVersion::MINECRAFT_1_19) {
        buffer->WriteVarInt(particleId);
      } else {
        buffer->WriteInt(particleId);
      }
      buffer->WriteBoolean(longDistance);
      if (version >= &MinecraftProtocolVersion::MINECRAFT_1_15) {
        buffer->WriteDouble(x);
        buffer->WriteDouble(y);
        buffer->WriteDouble(z);
      } else {
        buffer->WriteFloat((float) x);
        buffer->WriteFloat((float) y);
        buffer->WriteFloat((float) z);
      }
      buffer->WriteFloat(offsetX);
      buffer->WriteFloat(offsetY);
      buffer->WriteFloat(offsetZ);
      buffer->WriteFloat(maxSpeed);
      buffer->WriteInt(particleCount);
      particle->Write(version, buffer);
    }

    [[nodiscard]] uint32_t GetOrdinal() const override {
      return PACKET_ORDINAL;
    }

    [[nodiscard]] AbstractParticle* GetParticle() const {
      return particle;
    }

    [[nodiscard]] bool IsLongDistance() const {
      return longDistance;
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

    [[nodiscard]] float GetOffsetX() const {
      return offsetX;
    }

    [[nodiscard]] float GetOffsetY() const {
      return offsetY;
    }

    [[nodiscard]] float GetOffsetZ() const {
      return offsetZ;
    }

    [[nodiscard]] float GetMaxSpeed() const {
      return maxSpeed;
    }

    [[nodiscard]] uint32_t GetParticleCount() const {
      return particleCount;
    }
  };
}
