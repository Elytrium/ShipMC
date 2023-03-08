#pragma once

#include "../../../utils/ordinal/OrdinalRegistry.hpp"
#include "../Packet.hpp"
#include <string>
#include <utility>

namespace Ship {

  class OpenInventory : public Packet {
   private:
    uint32_t windowId;
    uint32_t windowType;
    std::string windowTitle;

   public:
    static inline const uint32_t PACKET_ORDINAL = OrdinalRegistry::PacketRegistry.RegisterOrdinal();

    OpenInventory(uint32_t windowId, uint32_t windowType, std::string windowTitle)
      : windowId(windowId), windowType(windowType), windowTitle(std::move(windowTitle)) {
    }

    ~OpenInventory() override = default;

    OpenInventory(const ProtocolVersion* version, ByteBuffer* buffer) {
      windowId = buffer->ReadVarInt();
      windowType = buffer->ReadVarInt();
      windowTitle = buffer->ReadString();
    }

    void Write(const ProtocolVersion* version, ByteBuffer* buffer) const override {
      buffer->WriteVarInt(windowId);
      buffer->WriteVarInt(windowType);
      buffer->WriteString(windowTitle);
    }

    uint32_t GetOrdinal() const override {
      return PACKET_ORDINAL;
    }

    [[nodiscard]] uint32_t GetWindowId() const {
      return windowId;
    }

    [[nodiscard]] uint32_t GetWindowType() const {
      return windowType;
    }

    [[nodiscard]] const std::string& GetWindowTitle() const {
      return windowTitle;
    }
  };
}
