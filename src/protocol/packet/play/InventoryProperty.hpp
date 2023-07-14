#pragma once

#include "../../../../lib/ShipNet/src/utils/ordinal/OrdinalRegistry.hpp"
#include <string>

namespace Ship {

  class InventoryProperty : public Packet {
   private:
    uint8_t windowId{};
    uint16_t property{};
    uint16_t value{};

   public:
    static inline const uint32_t PACKET_ORDINAL = OrdinalRegistry::PacketRegistry.RegisterOrdinal();

    InventoryProperty() = default;
    InventoryProperty(uint8_t windowId, uint16_t aProperty, uint16_t value) : windowId(windowId), property(aProperty), value(value) {
    }

    ~InventoryProperty() override = default;

    static Errorable<InventoryProperty> Instantiate(const PacketHolder& holder) {
      ByteBuffer* buffer = holder.GetCurrentBuffer();
      ProceedErrorable(windowId, uint8_t, buffer->ReadByte(), InvalidPacketErrorable<InventoryProperty>(PACKET_ORDINAL))
      ProceedErrorable(property, uint16_t, buffer->ReadShort(), InvalidPacketErrorable<InventoryProperty>(PACKET_ORDINAL))
      ProceedErrorable(value, uint16_t, buffer->ReadShort(), InvalidPacketErrorable<InventoryProperty>(PACKET_ORDINAL))
      return SuccessErrorable<InventoryProperty>(InventoryProperty(windowId, property, value));
    }

    Errorable<bool> Write(const ProtocolVersion* version, ByteBuffer* buffer) const override {
      buffer->WriteByte(windowId);
      buffer->WriteShort(property);
      buffer->WriteShort(value);
      return SuccessErrorable<bool>(true);
    }

    [[nodiscard]] uint32_t GetOrdinal() const override {
      return PACKET_ORDINAL;
    }

    [[nodiscard]] uint8_t GetWindowId() const {
      return windowId;
    }

    [[nodiscard]] uint16_t GetAProperty() const {
      return property;
    }

    [[nodiscard]] uint16_t GetValue() const {
      return value;
    }
  };
}
