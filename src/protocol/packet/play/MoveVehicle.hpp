#pragma once


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

    explicit MoveVehicle(const PacketHolder& holder) {
      ByteBuffer* buffer = holder.GetCurrentBuffer();
      x = buffer->ReadDouble();
      y = buffer->ReadDouble();
      z = buffer->ReadDouble();
      yaw = buffer->ReadFloat();
      pitch = buffer->ReadFloat();
    }

    void Write(const ProtocolVersion* version, ByteBuffer* buffer) const override {
      buffer->WriteDouble(x);
      buffer->WriteDouble(y);
      buffer->WriteDouble(z);
      buffer->WriteFloat(yaw);
      buffer->WriteFloat(pitch);
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
