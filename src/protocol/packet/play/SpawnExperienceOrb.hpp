#pragma once

#include "../../../../lib/ShipNet/src/utils/ordinal/OrdinalRegistry.hpp"
#include <string>

namespace Ship {

  class SpawnExperienceOrb : public Packet {
   private:
    uint32_t entityId;
    double x;
    double y;
    double z;
    uint16_t count;

   public:
    static inline const uint32_t PACKET_ORDINAL = OrdinalRegistry::PacketRegistry.RegisterOrdinal();

    SpawnExperienceOrb(uint32_t entityId, double x, double y, double z, uint16_t count) : entityId(entityId), x(x), y(y), z(z), count(count) {
    }

    ~SpawnExperienceOrb() override = default;

    static Errorable<SpawnExperienceOrb> Instantiate(const PacketHolder& holder) {
      ByteBuffer* buffer = holder.GetCurrentBuffer();
      ProceedErrorable(entityId, uint32_t, buffer->ReadVarInt(), InvalidPacketErrorable<>(PACKET_ORDINAL))
      ProceedErrorable(x, double, buffer->ReadDouble(), InvalidPacketErrorable<>(PACKET_ORDINAL))
      ProceedErrorable(y, double, buffer->ReadDouble(), InvalidPacketErrorable<>(PACKET_ORDINAL))
      ProceedErrorable(z, double, buffer->ReadDouble(), InvalidPacketErrorable<>(PACKET_ORDINAL))
      ProceedErrorable(count, uint16_t, buffer->ReadShort(), InvalidPacketErrorable<>(PACKET_ORDINAL))
    }

    void Write(const ProtocolVersion* version, ByteBuffer* buffer) const override {
      buffer->WriteVarInt(entityId);
      buffer->WriteDouble(x);
      buffer->WriteDouble(y);
      buffer->WriteDouble(z);
      buffer->WriteShort(count);
    }

    [[nodiscard]] uint32_t GetOrdinal() const override {
      return PACKET_ORDINAL;
    }

    [[nodiscard]] uint32_t GetEntityId() const {
      return entityId;
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

    [[nodiscard]] uint16_t GetCount() const {
      return count;
    }
  };
}
