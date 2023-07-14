#pragma once

#include "../../../../lib/ShipNet/src/utils/ordinal/OrdinalRegistry.hpp"
#include <string>
#include <utility>

namespace Ship {

  class OpenInventory : public Packet {
   private:
    uint32_t windowId{};
    uint32_t windowType{};
    std::string windowTitle;

   public:
    static inline const uint32_t PACKET_ORDINAL = OrdinalRegistry::PacketRegistry.RegisterOrdinal();

    OpenInventory() = default;
    OpenInventory(uint32_t windowId, uint32_t windowType, std::string windowTitle)
      : windowId(windowId), windowType(windowType), windowTitle(std::move(windowTitle)) {
    }

    ~OpenInventory() override = default;

    static Errorable<OpenInventory> Instantiate(const PacketHolder& holder) {
      ByteBuffer* buffer = holder.GetCurrentBuffer();
      ProceedErrorable(windowId, uint32_t, buffer->ReadVarInt(), InvalidPacketErrorable<OpenInventory>(PACKET_ORDINAL))
      ProceedErrorable(windowType, uint32_t, buffer->ReadVarInt(), InvalidPacketErrorable<OpenInventory>(PACKET_ORDINAL))
      ProceedErrorable(windowTitle, std::string, buffer->ReadString(), InvalidPacketErrorable<OpenInventory>(PACKET_ORDINAL))
      return SuccessErrorable<OpenInventory>(OpenInventory(windowId, windowType, windowTitle));
    }

    Errorable<bool> Write(const ProtocolVersion* version, ByteBuffer* buffer) const override {
      buffer->WriteVarInt(windowId);
      buffer->WriteVarInt(windowType);
      buffer->WriteString(windowTitle);
      return SuccessErrorable<bool>(true);
    }

    [[nodiscard]] uint32_t GetOrdinal() const override {
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
