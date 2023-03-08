#pragma once

#include "../../../utils/ordinal/OrdinalRegistry.hpp"
#include "../Packet.hpp"
#include <string>

namespace Ship {

  class AcknowledgePlayerDigging : public Packet {
   private:
    int locationX;
    int locationY;
    int locationZ;
    uint32_t block;
    uint32_t status;
    bool successful;

   public:
    static inline const uint32_t PACKET_ORDINAL = OrdinalRegistry::PacketRegistry.RegisterOrdinal();

    AcknowledgePlayerDigging(int locationX, int locationY, int locationZ, uint32_t block, uint32_t status, bool successful)
      : locationX(locationX), locationY(locationY), locationZ(locationZ), block(block), status(status), successful(successful) {
    }

    AcknowledgePlayerDigging(const ProtocolVersion* version, ByteBuffer* buffer) {
      buffer->ReadPosition(locationX, locationY, locationZ);
      block = buffer->ReadVarInt();
      status = buffer->ReadVarInt();
      successful = buffer->ReadBoolean();
    }

    ~AcknowledgePlayerDigging() override = default;

    void Write(const ProtocolVersion* version, ByteBuffer* buffer) const override {
      buffer->WritePosition(locationX, locationY, locationZ);
      buffer->WriteVarInt(block);
      buffer->WriteVarInt(status);
      buffer->WriteBoolean(successful);
    }

    uint32_t GetOrdinal() const override {
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

    [[nodiscard]] uint32_t GetBlock() const {
      return block;
    }

    [[nodiscard]] uint32_t GetStatus() const {
      return status;
    }

    [[nodiscard]] bool IsSuccessful() const {
      return successful;
    }
  };
}
