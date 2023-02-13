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

    void Read(const ProtocolVersion* version, ByteBuffer* buffer) override {
      x = buffer->ReadDouble();
      z = buffer->ReadDouble();
      oldDiameter = buffer->ReadDouble();
      newDiameter = buffer->ReadDouble();
      speed = buffer->ReadVarLong();
      portalTeleportBoundary = buffer->ReadVarInt();
      warningBlocks = buffer->ReadVarInt();
      warningTime = buffer->ReadVarInt();
    }

    void Write(const ProtocolVersion* version, ByteBuffer* buffer) override {
      buffer->WriteDouble(x);
      buffer->WriteDouble(z);
      buffer->WriteDouble(oldDiameter);
      buffer->WriteDouble(newDiameter);
      buffer->WriteVarLong(speed);
      buffer->WriteVarInt(portalTeleportBoundary);
      buffer->WriteVarInt(warningBlocks);
      buffer->WriteVarInt(warningTime);
    }

    uint32_t GetOrdinal() override {
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
