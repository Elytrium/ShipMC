#pragma once

#include "../../../utils/ordinal/OrdinalRegistry.hpp"
#include "../Packet.hpp"
#include <string>

namespace Ship {

  class CloseInventory : public Packet {
   private:
    uint8_t windowId;

   public:
    static inline const uint32_t PACKET_ORDINAL = OrdinalRegistry::PacketRegistry.RegisterOrdinal();

    explicit CloseInventory(uint8_t windowId) : windowId(windowId) {
    }

    ~CloseInventory() override = default;

    explicit CloseInventory(const PacketHolder& holder) {
      ByteBuffer* buffer = holder.GetCurrentBuffer();
      windowId = buffer->ReadByte();
    }

    void Write(const ProtocolVersion* version, ByteBuffer* buffer) const override {
      buffer->WriteByte(windowId);
    }

    uint32_t GetOrdinal() const override {
      return PACKET_ORDINAL;
    }

    [[nodiscard]] uint8_t GetWindowId() const {
      return windowId;
    }
  };
}
