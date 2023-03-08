#pragma once

#include "../../../utils/ordinal/OrdinalRegistry.hpp"
#include "../Packet.hpp"
#include <string>

namespace Ship {

  class BlockAction : public Packet {
   private:
    int locationX;
    int locationY;
    int locationZ;
    uint8_t actionId;
    uint8_t actionParameter;
    uint32_t blockType;

   public:
    static inline const uint32_t PACKET_ORDINAL = OrdinalRegistry::PacketRegistry.RegisterOrdinal();

    BlockAction(int locationX, int locationY, int locationZ, uint8_t actionId, uint8_t actionParameter, uint32_t blockType)
      : locationX(locationX), locationY(locationY), locationZ(locationZ), actionId(actionId), actionParameter(actionParameter), blockType(blockType) {
    }

    BlockAction(const ProtocolVersion* version, ByteBuffer* buffer) {
      buffer->ReadPosition(locationX, locationY, locationZ);
      actionId = buffer->ReadByte();
      actionParameter = buffer->ReadByte();
      blockType = buffer->ReadVarInt();
    }

    ~BlockAction() override = default;

    void Write(const ProtocolVersion* version, ByteBuffer* buffer) const override {
      buffer->WritePosition(locationX, locationY, locationZ);
      buffer->WriteByte(actionId);
      buffer->WriteByte(actionParameter);
      buffer->WriteVarInt(blockType);
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

    [[nodiscard]] uint8_t GetActionId() const {
      return actionId;
    }

    [[nodiscard]] uint8_t GetActionParameter() const {
      return actionParameter;
    }

    [[nodiscard]] uint32_t GetBlockType() const {
      return blockType;
    }
  };
}
