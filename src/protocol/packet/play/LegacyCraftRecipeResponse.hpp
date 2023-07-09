#pragma once

#include "../../../../lib/ShipNet/src/utils/ordinal/OrdinalRegistry.hpp"
#include <string>
#include <utility>

namespace Ship {

  class LegacyCraftRecipeResponse : public Packet {
   private:
    uint8_t windowId;
    uint32_t recipe;

   public:
    static inline const uint32_t PACKET_ORDINAL = OrdinalRegistry::PacketRegistry.RegisterOrdinal();

    LegacyCraftRecipeResponse(uint8_t windowId, uint32_t recipe) : windowId(windowId), recipe(recipe) {
    }

    ~LegacyCraftRecipeResponse() override = default;

    static Errorable<LegacyCraftRecipeResponse> Instantiate(const PacketHolder& holder) {
      ByteBuffer* buffer = holder.GetCurrentBuffer();
      ProceedErrorable(windowId, uint8_t, buffer->ReadByte(), InvalidPacketErrorable<>(PACKET_ORDINAL))
      ProceedErrorable(recipe, uint32_t, buffer->ReadVarInt(), InvalidPacketErrorable<>(PACKET_ORDINAL))
    }

    void Write(const ProtocolVersion* version, ByteBuffer* buffer) const override {
      buffer->WriteByte(windowId);
      buffer->WriteVarInt(recipe);
    }

    [[nodiscard]] uint32_t GetOrdinal() const override {
      return PACKET_ORDINAL;
    }

    [[nodiscard]] uint8_t GetWindowId() const {
      return windowId;
    }

    [[nodiscard]] uint32_t GetRecipe() const {
      return recipe;
    }
  };
}
