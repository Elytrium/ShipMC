#pragma once

#include "../../../../lib/ShipNet/src/utils/ordinal/OrdinalRegistry.hpp"
#include "../../ProtocolUtils.hpp"
#include "../../data/entity/metadata/Metadata.hpp"
#include <string>

namespace Ship {

  class SpawnPlayer : public Packet {
   private:
    uint32_t entityId{};
    UUID playerUuid{};
    double x{};
    double y{};
    double z{};
    float yaw{};
    float pitch{};
    Metadata* metadata{};

   public:
    static inline const uint32_t PACKET_ORDINAL = OrdinalRegistry::PacketRegistry.RegisterOrdinal();

    SpawnPlayer() = default;
    SpawnPlayer(uint32_t entityId, const UUID& playerUuid, double x, double y, double z, float yaw, float pitch, Metadata* metadata)
      : entityId(entityId), playerUuid(playerUuid), x(x), y(y), z(z), yaw(yaw), pitch(pitch), metadata(metadata) {
    }

    ~SpawnPlayer() override {
      delete metadata;
    }

    static Errorable<SpawnPlayer> Instantiate(const PacketHolder& holder) {
      ByteBuffer* buffer = holder.GetCurrentBuffer();
      const ProtocolVersion* version = holder.GetVersion();
      ProceedErrorable(entityId, uint32_t, buffer->ReadVarInt(), InvalidPacketErrorable<SpawnPlayer>(PACKET_ORDINAL))
      ProceedErrorable(playerUuid, UUID, buffer->ReadUUID(), InvalidPacketErrorable<SpawnPlayer>(PACKET_ORDINAL))
      ProceedErrorable(x, double, buffer->ReadDouble(), InvalidPacketErrorable<SpawnPlayer>(PACKET_ORDINAL))
      ProceedErrorable(y, double, buffer->ReadDouble(), InvalidPacketErrorable<SpawnPlayer>(PACKET_ORDINAL))
      ProceedErrorable(z, double, buffer->ReadDouble(), InvalidPacketErrorable<SpawnPlayer>(PACKET_ORDINAL))
      ProceedErrorable(yaw, float, buffer->ReadAngle(), InvalidPacketErrorable<SpawnPlayer>(PACKET_ORDINAL))
      ProceedErrorable(pitch, float, buffer->ReadAngle(), InvalidPacketErrorable<SpawnPlayer>(PACKET_ORDINAL))
      Metadata* metadata{};
      if (version <= &MinecraftProtocolVersion::MINECRAFT_1_14_4) {
        SetFromErrorable(metadata, Metadata*, ProtocolUtils::ReadMetadata(version, buffer), InvalidPacketErrorable<SpawnPlayer>(PACKET_ORDINAL));
      }

      return SuccessErrorable<SpawnPlayer>(SpawnPlayer(entityId, playerUuid, x, y, z, yaw, pitch, metadata));
    }

    Errorable<bool> Write(const ProtocolVersion* version, ByteBuffer* buffer) const override {
      buffer->WriteVarInt(entityId);
      buffer->WriteUUID(playerUuid);
      buffer->WriteDouble(x);
      buffer->WriteDouble(y);
      buffer->WriteDouble(z);
      buffer->WriteAngle(yaw);
      buffer->WriteAngle(pitch);
      if (version <= &MinecraftProtocolVersion::MINECRAFT_1_14_4) {
        ProtocolUtils::WriteMetadata(version, buffer, metadata);
      }
      return SuccessErrorable<bool>(true);
    }

    [[nodiscard]] uint32_t GetOrdinal() const override {
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
