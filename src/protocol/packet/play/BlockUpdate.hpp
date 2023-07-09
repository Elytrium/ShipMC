#pragma once


#include <string>

namespace Ship {

  class BlockUpdate : public Packet {
   private:
    int locationX;
    int locationY;
    int locationZ;
    uint32_t blockId;

   public:
    static inline const uint32_t PACKET_ORDINAL = OrdinalRegistry::PacketRegistry.RegisterOrdinal();

    BlockUpdate(int locationX, int locationY, int locationZ, uint32_t blockId)
      : locationX(locationX), locationY(locationY), locationZ(locationZ), blockId(blockId) {
    }

    explicit BlockUpdate(const PacketHolder& holder) {
      ByteBuffer* buffer = holder.GetCurrentBuffer();
      buffer->ReadPosition(locationX, locationX, locationZ);
      buffer->WriteVarInt(blockId);
    }

    ~BlockUpdate() override = default;

    void Write(const ProtocolVersion* version, ByteBuffer* buffer) const override {
      buffer->WritePosition(locationX, locationY, locationZ);
      buffer->WriteVarInt(blockId);
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

    [[nodiscard]] uint32_t GetBlockId() const {
      return blockId;
    }
  };
}
