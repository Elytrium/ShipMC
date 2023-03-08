#pragma once

#include "../../../utils/ordinal/OrdinalRegistry.hpp"
#include "../../ProtocolUtils.hpp"
#include "../../data/entity/metadata/Metadata.hpp"
#include "../Packet.hpp"
#include <string>

namespace Ship {

  class SpawnPlayer : public Packet {
   private:
    uint32_t entityId;
    UUID playerUuid;
    double x;
    double y;
    double z;
    float yaw;
    float pitch;
    Metadata* metadata;

   public:
    static inline const uint32_t PACKET_ORDINAL = OrdinalRegistry::PacketRegistry.RegisterOrdinal();

    SpawnPlayer(uint32_t entityId, const UUID& playerUuid, double x, double y, double z, float yaw, float pitch, Metadata* metadata)
      : entityId(entityId), playerUuid(playerUuid), x(x), y(y), z(z), yaw(yaw), pitch(pitch), metadata(metadata) {
    }

    ~SpawnPlayer() override {
      delete metadata;
    }

    SpawnPlayer(const ProtocolVersion* version, ByteBuffer* buffer) {
      entityId = buffer->ReadVarInt();
      playerUuid = buffer->ReadUUID();
      x = buffer->ReadDouble();
      y = buffer->ReadDouble();
      z = buffer->ReadDouble();
      yaw = buffer->ReadAngle();
      pitch = buffer->ReadAngle();
      if (version <= &ProtocolVersion::MINECRAFT_1_14_4) {
        delete metadata;
        metadata = ProtocolUtils::ReadMetadata(version, buffer);
      }
    }

    void Write(const ProtocolVersion* version, ByteBuffer* buffer) const override {
      buffer->WriteVarInt(entityId);
      buffer->WriteUUID(playerUuid);
      buffer->WriteDouble(x);
      buffer->WriteDouble(y);
      buffer->WriteDouble(z);
      buffer->WriteAngle(yaw);
      buffer->WriteAngle(pitch);
      if (version <= &ProtocolVersion::MINECRAFT_1_14_4) {
        ProtocolUtils::WriteMetadata(version, buffer, metadata);
      }
    }

    uint32_t GetOrdinal() const override {
      return PACKET_ORDINAL;
    }

    [[nodiscard]] uint32_t GetEntityId() const {
      return entityId;
    }

    [[nodiscard]] const UUID& GetPlayerUuid() const {
      return playerUuid;
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

    [[nodiscard]] float GetYaw() const {
      return yaw;
    }

    [[nodiscard]] float GetPitch() const {
      return pitch;
    }

    [[nodiscard]] Metadata* GetMetadata() const {
      return metadata;
    }
  };
}
