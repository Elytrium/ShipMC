#pragma once

#include "../../../../lib/ShipNet/src/utils/ordinal/OrdinalRegistry.hpp"
#include <string>

namespace Ship {

  class BlockUpdate : public Packet {
   private:
    Position location {};
    uint32_t blockId {};

   public:
    static inline const uint32_t PACKET_ORDINAL = OrdinalRegistry::PacketRegistry.RegisterOrdinal();

    BlockUpdate() = default;

    BlockUpdate(Position location, uint32_t blockId) : location(location), blockId(blockId) {
    }

    static Errorable<BlockUpdate> Instantiate(const PacketHolder& holder) {
      ByteBuffer* buffer = holder.GetCurrentBuffer();
      ProceedErrorable(location, Position, buffer->ReadPosition(), InvalidPacketErrorable<BlockUpdate>(PACKET_ORDINAL))
      ProceedErrorable(blockId, uint32_t, buffer->ReadVarInt(), InvalidPacketErrorable<BlockUpdate>(PACKET_ORDINAL))
      return SuccessErrorable<BlockUpdate>({location, blockId});
    }

    ~BlockUpdate() override = default;

    void Write(const ProtocolVersion* version, ByteBuffer* buffer) const override {
      buffer->WritePosition(location);
      buffer->WriteVarInt(blockId);
    }

    [[nodiscard]] uint32_t GetOrdinal() const override {
      return PACKET_ORDINAL;
    }

    [[nodiscard]] Position GetLocation() const {
      return location;
    }

    [[nodiscard]] uint32_t GetBlockId() const {
      return blockId;
    }
  };
}
