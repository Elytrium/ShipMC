#pragma once

#include "../../../../lib/ShipNet/src/utils/ordinal/OrdinalRegistry.hpp"
#include <string>

namespace Ship {

  class OpenSignEditor : public Packet {
   private:
    int locationX;
    int locationY;
    int locationZ;

   public:
    static inline const uint32_t PACKET_ORDINAL = OrdinalRegistry::PacketRegistry.RegisterOrdinal();

    OpenSignEditor(int locationX, int locationY, int locationZ) : locationX(locationX), locationY(locationY), locationZ(locationZ) {
    }

    ~OpenSignEditor() override = default;

    static Errorable<OpenSignEditor> Instantiate(const PacketHolder& holder) {
      ByteBuffer* buffer = holder.GetCurrentBuffer();
      buffer->ReadPosition(locationX, locationY, locationZ);
    }

    Errorable<bool> Write(const ProtocolVersion* version, ByteBuffer* buffer) const override {
      buffer->WritePosition(locationX, locationY, locationZ);
      return SuccessErrorable<bool>(true);
    }

    [[nodiscard]] uint32_t GetOrdinal() const override {
      return PACKET_ORDINAL;
    }

    [[nodiscard]] int GetLocationX() const {
      return locationX;
    }

    [[nodiscard]] int GetLocationY() const {
      return locationY;
    }

    [[nodiscard]] int GetLocationZ() const {
      return locationZ;
    }
  };
}
