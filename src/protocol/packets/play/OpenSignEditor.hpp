#pragma once

#include "../../../utils/ordinal/OrdinalRegistry.hpp"
#include "../Packet.hpp"
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

    void Read(const ProtocolVersion* version, ByteBuffer* buffer) override {
      buffer->ReadPosition(locationX, locationY, locationZ);
    }

    void Write(const ProtocolVersion* version, ByteBuffer* buffer) override {
      buffer->WritePosition(locationX, locationY, locationZ);
    }

    uint32_t Size(const ProtocolVersion* version) override {
      return ByteBuffer::POSITION_SIZE;
    }

    uint32_t GetOrdinal() override {
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
