#pragma once

#include "../../../utils/ordinal/OrdinalRegistry.hpp"
#include "../Packet.hpp"
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

    void Read(const ProtocolVersion* version, ByteBuffer* buffer) override {
      uint32_t particleId;
      if (version >= &ProtocolVersion::MINECRAFT_1_19) {
        particleId = buffer->ReadVarInt();
      } else {
        particleId = buffer->ReadInt();
      }
      delete particle;
      particle = PARTICLE_REGISTRY.GetObjectByID(version, particleId);
      longDistance = buffer->ReadBoolean();
      if (version >= &ProtocolVersion::MINECRAFT_1_15) {
        x = buffer->ReadDouble();
        y = buffer->ReadDouble();
        z = buffer->ReadDouble();
      } else {
        x = buffer->ReadFloat();
        y = buffer->ReadFloat();
        z = buffer->ReadFloat();
      }
      offsetX = buffer->ReadFloat();
      offsetY = buffer->ReadFloat();
      offsetZ = buffer->ReadFloat();
      maxSpeed = buffer->ReadFloat();
      particleCount = buffer->ReadInt();
      particle->Read(version, buffer);
    }

    void Write(const ProtocolVersion* version, ByteBuffer* buffer) override {
      uint32_t particleId = PARTICLE_REGISTRY.GetIDByOrdinal(version, particle->GetOrdinal());
      if (version >= &ProtocolVersion::MINECRAFT_1_19) {
        buffer->WriteVarInt(particleId);
      } else {
        buffer->WriteInt(particleId);
      }
      buffer->WriteBoolean(longDistance);
      if (version >= &ProtocolVersion::MINECRAFT_1_15) {
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

    uint32_t GetOrdinal() override {
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
