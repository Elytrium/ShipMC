#pragma once

#include "../../../../lib/ShipNet/src/utils/ordinal/OrdinalRegistry.hpp"
#include <string>

namespace Ship {

  class SpawnEntity : public Packet {
   private:
    uint32_t entityId{};
    UUID entityUuid{};
    uint32_t type{};
    double x{};
    double y{};
    double z{};
    float pitch{};
    float yaw{};
    float headYaw{};
    uint32_t data{};
    float velocityX{};
    float velocityY{};
    float velocityZ{};

   public:
    static inline const uint32_t PACKET_ORDINAL = OrdinalRegistry::PacketRegistry.RegisterOrdinal();

    SpawnEntity() = default;
    SpawnEntity(uint32_t entityId, const UUID& entityUuid, uint32_t type, double x, double y, double z, float pitch, float yaw, float headYaw,
      uint32_t data, float velocityX, float velocityY, float velocityZ)
      : entityId(entityId), entityUuid(entityUuid), type(type), x(x), y(y), z(z), pitch(pitch), yaw(yaw), headYaw(headYaw), data(data),
        velocityX(velocityX), velocityY(velocityY), velocityZ(velocityZ) {
    }

    ~SpawnEntity() override = default;

    static Errorable<SpawnEntity> Instantiate(const PacketHolder& holder) {
      ByteBuffer* buffer = holder.GetCurrentBuffer();
      const ProtocolVersion* version = holder.GetVersion();
      ProceedErrorable(entityId, uint32_t, buffer->ReadVarInt(), InvalidPacketErrorable<SpawnEntity>(PACKET_ORDINAL))
      ProceedErrorable(entityUuid, UUID, buffer->ReadUUID(), InvalidPacketErrorable<SpawnEntity>(PACKET_ORDINAL))
      uint32_t type;
      if (version >= &MinecraftProtocolVersion::MINECRAFT_1_14) {
        SetFromErrorable(type, uint32_t, buffer->ReadVarInt(), InvalidPacketErrorable<SpawnEntity>(PACKET_ORDINAL))
      } else {
        SetFromErrorable(type, uint8_t, buffer->ReadByte(), InvalidPacketErrorable<SpawnEntity>(PACKET_ORDINAL))
      }
      ProceedErrorable(x, double, buffer->ReadDouble(), InvalidPacketErrorable<SpawnEntity>(PACKET_ORDINAL))
      ProceedErrorable(y, double, buffer->ReadDouble(), InvalidPacketErrorable<SpawnEntity>(PACKET_ORDINAL))
      ProceedErrorable(z, double, buffer->ReadDouble(), InvalidPacketErrorable<SpawnEntity>(PACKET_ORDINAL))
      ProceedErrorable(pitch, float, buffer->ReadAngle(), InvalidPacketErrorable<SpawnEntity>(PACKET_ORDINAL))
      ProceedErrorable(yaw, float, buffer->ReadAngle(), InvalidPacketErrorable<SpawnEntity>(PACKET_ORDINAL))
      float headYaw;
      uint32_t data;
      if (version >= &MinecraftProtocolVersion::MINECRAFT_1_19) {
        SetFromErrorable(headYaw, float, buffer->ReadAngle(), InvalidPacketErrorable<SpawnEntity>(PACKET_ORDINAL))
        SetFromErrorable(data, uint32_t, buffer->ReadVarInt(), InvalidPacketErrorable<SpawnEntity>(PACKET_ORDINAL))
      } else {
        SetFromErrorable(data, uint32_t, buffer->ReadInt(), InvalidPacketErrorable<SpawnEntity>(PACKET_ORDINAL))
      }
      ProceedErrorable(velocityXShort, uint16_t, buffer->ReadShort(), InvalidPacketErrorable<SpawnEntity>(PACKET_ORDINAL))
      ProceedErrorable(velocityYShort, uint16_t, buffer->ReadShort(), InvalidPacketErrorable<SpawnEntity>(PACKET_ORDINAL))
      ProceedErrorable(velocityZShort, uint16_t, buffer->ReadShort(), InvalidPacketErrorable<SpawnEntity>(PACKET_ORDINAL))
      auto velocityX = (float) velocityXShort / 8000.0F;
      auto velocityY = (float) velocityYShort / 8000.0F;
      auto velocityZ = (float) velocityZShort / 8000.0F;
      return SuccessErrorable<SpawnEntity>(SpawnEntity(entityId, entityUuid, type, x, y, z, pitch, yaw, headYaw, data, velocityX, velocityY, velocityZ));
    }

    Errorable<bool> Write(const ProtocolVersion* version, ByteBuffer* buffer) const override {
      buffer->WriteVarInt(entityId);
      buffer->WriteUUID(entityUuid);
      if (version >= &MinecraftProtocolVersion::MINECRAFT_1_14) {
        buffer->WriteVarInt(type);
      } else {
        buffer->WriteByte(type);
      }
      buffer->WriteDouble(x);
      buffer->WriteDouble(y);
      buffer->WriteDouble(z);
      buffer->WriteAngle(pitch);
      buffer->WriteAngle(yaw);
      if (version >= &MinecraftProtocolVersion::MINECRAFT_1_19) {
        buffer->WriteAngle(headYaw);
        buffer->WriteVarInt(data);
      } else {
        buffer->WriteInt(data);
      }
      buffer->WriteShort((uint16_t) (velocityX * 8000.0F));
      buffer->WriteShort((uint16_t) (velocityY * 8000.0F));
      buffer->WriteShort((uint16_t) (velocityZ * 8000.0F));
      return SuccessErrorable<bool>(true);
    }

    [[nodiscard]] uint32_t GetOrdinal() const override {
      return PACKET_ORDINAL;
    }

    [[nodiscard]] uint32_t GetEntityId() const {
      return entityId;
    }

    [[nodiscard]] const UUID& GetEntityUuid() const {
      return entityUuid;
    }

    [[nodiscard]] uint32_t getType() const {
      return type;
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

    [[nodiscard]] float GetPitch() const {
      return pitch;
    }

    [[nodiscard]] float GetYaw() const {
      return yaw;
    }

    [[nodiscard]] float GetHeadYaw() const {
      return headYaw;
    }

    [[nodiscard]] uint32_t GetData() const {
      return data;
    }

    [[nodiscard]] float GetVelocityX() const {
      return velocityX;
    }

    [[nodiscard]] float GetVelocityY() const {
      return velocityY;
    }

    [[nodiscard]] float GetVelocityZ() const {
      return velocityZ;
    }
  };
}
