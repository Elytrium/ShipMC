#pragma once

#include "ShipNet/utils/ordinal/OrdinalRegistry.hpp"
#include <string>

namespace Ship {

  class BlockDestroyStage : public Packet {
   private:
    uint32_t entityId{};
    Position location{};
    uint8_t destroyStage{};

   public:
    static inline const uint32_t PACKET_ORDINAL = OrdinalRegistry::PacketRegistry.RegisterOrdinal();

    BlockDestroyStage() = default;

    BlockDestroyStage(uint32_t entityId, Position location, uint8_t destroyStage)
      : entityId(entityId), location(location), destroyStage(destroyStage) {
    }

    static Errorable<BlockDestroyStage> Instantiate(const PacketHolder& holder) {
      ByteBuffer* buffer = holder.GetCurrentBuffer();
      ProceedErrorable(entityId, uint32_t, buffer->ReadVarInt(), InvalidPacketErrorable<BlockDestroyStage>(PACKET_ORDINAL))
      ProceedErrorable(location, Position, ProtocolUtils::ReadPosition(holder.GetVersion(), buffer), InvalidPacketErrorable<BlockDestroyStage>(PACKET_ORDINAL))
      ProceedErrorable(destroyStage, uint8_t, buffer->ReadByte(), InvalidPacketErrorable<BlockDestroyStage>(PACKET_ORDINAL))

      return SuccessErrorable<BlockDestroyStage>({entityId, location, destroyStage});
    }

    ~BlockDestroyStage() override = default;

    Errorable<bool> Write(const ProtocolVersion* version, ByteBuffer* buffer) const override {
      buffer->WriteVarInt(entityId);
      ProtocolUtils::WritePosition(version, buffer, location);
      buffer->WriteByte(destroyStage);
      return SuccessErrorable<bool>(true);
    }

    [[nodiscard]] uint32_t GetOrdinal() const override {
      return PACKET_ORDINAL;
    }

    [[nodiscard]] uint32_t GetEntityId() const {
      return entityId;
    }

    [[nodiscard]] Position GetLocation() const {
      return location;
    }

    [[nodiscard]] uint8_t GetDestroyStage() const {
      return destroyStage;
    }
  };
}
