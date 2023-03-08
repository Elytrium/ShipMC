#pragma once

#include "../../../utils/ordinal/OrdinalRegistry.hpp"
#include "../Packet.hpp"
#include <string>
#include <utility>

namespace Ship {

  class CraftRecipeResponse : public Packet {
   private:
    uint8_t windowId;
    std::string recipe;

   public:
    static inline const uint32_t PACKET_ORDINAL = OrdinalRegistry::PacketRegistry.RegisterOrdinal();

    CraftRecipeResponse(uint8_t windowId, std::string recipe) : windowId(windowId), recipe(std::move(recipe)) {
    }

    ~CraftRecipeResponse() override = default;

    CraftRecipeResponse(const ProtocolVersion* version, ByteBuffer* buffer) {
      windowId = buffer->ReadByte();
      recipe = buffer->ReadString();
    }

    void Write(const ProtocolVersion* version, ByteBuffer* buffer) const override {
      buffer->WriteByte(windowId);
      buffer->WriteString(recipe);
    }

    uint32_t GetOrdinal() const override {
      return PACKET_ORDINAL;
    }

    [[nodiscard]] uint8_t GetWindowId() const {
      return windowId;
    }

    [[nodiscard]] const std::string& GetRecipe() const {
      return recipe;
    }
  };
}
