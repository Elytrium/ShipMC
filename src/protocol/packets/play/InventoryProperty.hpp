#pragma once

#include "../../../utils/ordinal/OrdinalRegistry.hpp"
#include "../Packet.hpp"
#include <string>

namespace Ship {

  class InventoryProperty : public Packet {
   private:
    uint8_t windowId;
    uint16_t property;
    uint16_t value;

   public:
    static inline const uint32_t PACKET_ORDINAL = OrdinalRegistry::PacketRegistry.RegisterOrdinal();

    InventoryProperty(uint8_t windowId, uint16_t aProperty, uint16_t value) : windowId(windowId), property(aProperty), value(value) {
    }

    ~InventoryProperty() override = default;

    InventoryProperty(const ProtocolVersion* version, ByteBuffer* buffer) {
      windowId = buffer->ReadByte();
      property = buffer->ReadShort();
      value = buffer->ReadShort();
    }

    void Write(const ProtocolVersion* version, ByteBuffer* buffer) const override {
      buffer->WriteByte(windowId);
      buffer->WriteShort(property);
      buffer->WriteShort(value);
    }

    uint32_t GetOrdinal() const override {
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
