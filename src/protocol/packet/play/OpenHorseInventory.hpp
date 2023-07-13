#pragma once

#include "../../../../lib/ShipNet/src/utils/ordinal/OrdinalRegistry.hpp"
#include <string>

namespace Ship {

  class OpenHorseInventory : public Packet {
   private:
    uint8_t windowId;
    uint32_t slotCount;
    uint32_t entityId;

   public:
    static inline const uint32_t PACKET_ORDINAL = OrdinalRegistry::PacketRegistry.RegisterOrdinal();

    OpenHorseInventory(uint8_t windowId, uint32_t slotCount, uint32_t entityId) : windowId(windowId), slotCount(slotCount), entityId(entityId) {
    }

    ~OpenHorseInventory() override = default;

    static Errorable<OpenHorseInventory> Instantiate(const PacketHolder& holder) {
      ByteBuffer* buffer = holder.GetCurrentBuffer();
      ProceedErrorable(windowId, uint8_t, buffer->ReadByte(), InvalidPacketErrorable<>(PACKET_ORDINAL))
      ProceedErrorable(slotCount, uint32_t, buffer->ReadVarInt(), InvalidPacketErrorable<>(PACKET_ORDINAL))
      entityId = buffer->ReadInt();
    }

    Errorable<bool> Write(const ProtocolVersion* version, ByteBuffer* buffer) const override {
      buffer->WriteByte(windowId);
      buffer->WriteVarInt(slotCount);
      buffer->WriteInt(entityId);
      return SuccessErrorable<bool>(true);
    }

    [[nodiscard]] uint32_t GetOrdinal() const override {
      return PACKET_ORDINAL;
    }

    [[nodiscard]] uint8_t GetWindowId() const {
      return windowId;
    }

    [[nodiscard]] uint32_t GetSlotCount() const {
      return slotCount;
    }

    [[nodiscard]] uint32_t GetEntityId() const {
      return entityId;
    }
  };
}
