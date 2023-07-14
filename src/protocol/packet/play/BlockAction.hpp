#pragma once

#include "../../../../lib/ShipNet/src/utils/ordinal/OrdinalRegistry.hpp"
#include <string>

namespace Ship {

  class BlockAction : public Packet {
   private:
    Position location {};
    uint8_t actionId {};
    uint8_t actionParameter {};
    uint32_t blockType {};

   public:
    static inline const uint32_t PACKET_ORDINAL = OrdinalRegistry::PacketRegistry.RegisterOrdinal();

    BlockAction() = default;

    BlockAction(Position location, uint8_t actionId, uint8_t actionParameter, uint32_t blockType): location(location), actionId(actionId),
        actionParameter(actionParameter), blockType(blockType) {
    }

    static Errorable<BlockAction> Instantiate(const PacketHolder& holder) {
      ByteBuffer* buffer = holder.GetCurrentBuffer();
      ProceedErrorable(location, Position, ProtocolUtils::ReadPosition(holder.GetVersion(), buffer), InvalidPacketErrorable<BlockAction>(PACKET_ORDINAL))
      ProceedErrorable(actionId, uint8_t, buffer->ReadByte(), InvalidPacketErrorable<BlockAction>(PACKET_ORDINAL))
      ProceedErrorable(actionParameter, uint8_t, buffer->ReadByte(), InvalidPacketErrorable<BlockAction>(PACKET_ORDINAL))
      ProceedErrorable(blockType, uint32_t, buffer->ReadVarInt(), InvalidPacketErrorable<BlockAction>(PACKET_ORDINAL))
      return SuccessErrorable<BlockAction>({location, actionId, actionParameter, blockType});
    }

    ~BlockAction() override = default;

    Errorable<bool> Write(const ProtocolVersion* version, ByteBuffer* buffer) const override {
      ProtocolUtils::WritePosition(version, buffer, location);
      buffer->WriteByte(actionId);
      buffer->WriteByte(actionParameter);
      buffer->WriteVarInt(blockType);
      return SuccessErrorable<bool>(true);
    }

    [[nodiscard]] uint32_t GetOrdinal() const override {
      return PACKET_ORDINAL;
    }

    [[nodiscard]] Position GetLocation() const {
      return location;
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
