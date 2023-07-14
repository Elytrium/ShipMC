#pragma once

#include "ShipNet/utils/ordinal/OrdinalRegistry.hpp"
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
      ProceedErrorable(location, Position, ProtocolUtils::ReadPosition(holder.GetVersion(), buffer), InvalidPacketErrorable<BlockUpdate>(PACKET_ORDINAL))
      ProceedErrorable(blockId, uint32_t, buffer->ReadVarInt(), InvalidPacketErrorable<BlockUpdate>(PACKET_ORDINAL))
      return SuccessErrorable<BlockUpdate>({location, blockId});
    }

    ~BlockUpdate() override = default;

    Errorable<bool> Write(const ProtocolVersion* version, ByteBuffer* buffer) const override {
      ProtocolUtils::WritePosition(version, buffer, location);
      buffer->WriteVarInt(blockId);
      return SuccessErrorable<bool>(true);
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
