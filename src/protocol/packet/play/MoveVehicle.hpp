#pragma once

#include "../../../../lib/ShipNet/src/utils/ordinal/OrdinalRegistry.hpp"
#include <string>

namespace Ship {

  class MoveVehicle : public Packet {
   private:
    double x;
    double y;
    double z;
    float yaw;
    float pitch;

   public:
    static inline const uint32_t PACKET_ORDINAL = OrdinalRegistry::PacketRegistry.RegisterOrdinal();

    MoveVehicle(double x, double y, double z, float yaw, float pitch) : x(x), y(y), z(z), yaw(yaw), pitch(pitch) {
    }

    ~MoveVehicle() override = default;

    static Errorable<MoveVehicle> Instantiate(const PacketHolder& holder) {
      ByteBuffer* buffer = holder.GetCurrentBuffer();
      ProceedErrorable(x, double, buffer->ReadDouble(), InvalidPacketErrorable<>(PACKET_ORDINAL))
      ProceedErrorable(y, double, buffer->ReadDouble(), InvalidPacketErrorable<>(PACKET_ORDINAL))
      ProceedErrorable(z, double, buffer->ReadDouble(), InvalidPacketErrorable<>(PACKET_ORDINAL))
      ProceedErrorable(yaw, float, buffer->ReadFloat(), InvalidPacketErrorable<>(PACKET_ORDINAL))
      ProceedErrorable(pitch, float, buffer->ReadFloat(), InvalidPacketErrorable<>(PACKET_ORDINAL))
    }

    Errorable<bool> Write(const ProtocolVersion* version, ByteBuffer* buffer) const override {
      buffer->WriteDouble(x);
      buffer->WriteDouble(y);
      buffer->WriteDouble(z);
      buffer->WriteFloat(yaw);
      buffer->WriteFloat(pitch);
      return SuccessErrorable<bool>(true);
    }

    uint32_t GetOrdinal() const override {
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

    [[nodiscard]] float GetYaw() const {
      return yaw;
    }

    [[nodiscard]] float GetPitch() const {
      return pitch;
    }
  };
}
