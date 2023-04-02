#pragma once

#include "../../../utils/ordinal/OrdinalRegistry.hpp"
#include "../Packet.hpp"
#include <string>

namespace Ship {

  class InitializeWorldBorder : public Packet {
   private:
    double x;
    double z;
    double oldDiameter;
    double newDiameter;
    uint64_t speed;
    uint32_t portalTeleportBoundary;
    uint32_t warningBlocks;
    uint32_t warningTime;

   public:
    static inline const uint32_t PACKET_ORDINAL = OrdinalRegistry::PacketRegistry.RegisterOrdinal();

    InitializeWorldBorder(double x, double z, double oldDiameter, double newDiameter, uint64_t speed, uint32_t portalTeleportBoundary,
      uint32_t warningBlocks, uint32_t warningTime)
      : x(x), z(z), oldDiameter(oldDiameter), newDiameter(newDiameter), speed(speed), portalTeleportBoundary(portalTeleportBoundary),
        warningBlocks(warningBlocks), warningTime(warningTime) {
    }

    ~InitializeWorldBorder() override = default;

    static Errorable<InitializeWorldBorder> Instantiate(const PacketHolder& holder) {
      ByteBuffer* buffer = holder.GetCurrentBuffer();
      ProceedErrorable(x, double, buffer->ReadDouble(), InvalidPacketErrorable<>(PACKET_ORDINAL))
      ProceedErrorable(z, double, buffer->ReadDouble(), InvalidPacketErrorable<>(PACKET_ORDINAL))
      ProceedErrorable(oldDiameter, double, buffer->ReadDouble(), InvalidPacketErrorable<>(PACKET_ORDINAL))
      ProceedErrorable(newDiameter, double, buffer->ReadDouble(), InvalidPacketErrorable<>(PACKET_ORDINAL))
      speed = buffer->ReadVarLong();
      ProceedErrorable(portalTeleportBoundary, uint32_t, buffer->ReadVarInt(), InvalidPacketErrorable<>(PACKET_ORDINAL))
      ProceedErrorable(warningBlocks, uint32_t, buffer->ReadVarInt(), InvalidPacketErrorable<>(PACKET_ORDINAL))
      ProceedErrorable(warningTime, uint32_t, buffer->ReadVarInt(), InvalidPacketErrorable<>(PACKET_ORDINAL))
    }

    void Write(const ProtocolVersion* version, ByteBuffer* buffer) const override {
      buffer->WriteDouble(x);
      buffer->WriteDouble(z);
      buffer->WriteDouble(oldDiameter);
      buffer->WriteDouble(newDiameter);
      buffer->WriteVarLong(speed);
      buffer->WriteVarInt(portalTeleportBoundary);
      buffer->WriteVarInt(warningBlocks);
      buffer->WriteVarInt(warningTime);
    }

    uint32_t GetOrdinal() const override {
      return PACKET_ORDINAL;
    }

    [[nodiscard]] double GetX() const {
      return x;
    }

    [[nodiscard]] double GetZ() const {
      return z;
    }

    [[nodiscard]] double GetOldDiameter() const {
      return oldDiameter;
    }

    [[nodiscard]] double GetNewDiameter() const {
      return newDiameter;
    }

    [[nodiscard]] uint64_t GetSpeed() const {
      return speed;
    }

    [[nodiscard]] uint32_t GetPortalTeleportBoundary() const {
      return portalTeleportBoundary;
    }

    [[nodiscard]] uint32_t GetWarningBlocks() const {
      return warningBlocks;
    }

    [[nodiscard]] uint32_t GetWarningTime() const {
      return warningTime;
    }
  };
}
