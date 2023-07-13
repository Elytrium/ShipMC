#pragma once

#include "../../../../lib/ShipNet/src/utils/ordinal/OrdinalRegistry.hpp"
#include <string>

namespace Ship {

  class AcknowledgePlayerDigging : public Packet {
   private:
    Position location{};
    uint32_t block{};
    uint32_t status{};
    bool successful{};

   public:
    static inline const uint32_t PACKET_ORDINAL = OrdinalRegistry::PacketRegistry.RegisterOrdinal();

    AcknowledgePlayerDigging() = default;

    AcknowledgePlayerDigging(Position location, uint32_t block, uint32_t status, bool successful)
      : location(location), block(block), status(status), successful(successful) {
    }

    static Errorable<AcknowledgePlayerDigging> Instantiate(const PacketHolder& holder) {
      ByteBuffer* buffer = holder.GetCurrentBuffer();
      ProceedErrorable(location, Position, buffer->ReadPosition(), InvalidPacketErrorable<AcknowledgePlayerDigging>(PACKET_ORDINAL))
      ProceedErrorable(block, uint32_t, buffer->ReadVarInt(), InvalidPacketErrorable<AcknowledgePlayerDigging>(PACKET_ORDINAL))
      ProceedErrorable(status, uint32_t, buffer->ReadVarInt(), InvalidPacketErrorable<AcknowledgePlayerDigging>(PACKET_ORDINAL))
      ProceedErrorable(successful, bool, buffer->ReadBoolean(), InvalidPacketErrorable<AcknowledgePlayerDigging>(PACKET_ORDINAL))
      return SuccessErrorable<AcknowledgePlayerDigging>({location, block, status, successful});
    }

    ~AcknowledgePlayerDigging() override = default;

    Errorable<bool> Write(const ProtocolVersion* version, ByteBuffer* buffer) const override {
      buffer->WritePosition(location);
      buffer->WriteVarInt(block);
      buffer->WriteVarInt(status);
      buffer->WriteBoolean(successful);
      return SuccessErrorable<bool>(true);
    }

    [[nodiscard]] uint32_t GetOrdinal() const override {
      return PACKET_ORDINAL;
    }

    [[nodiscard]] Position GetLocation() const {
      return location;
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
