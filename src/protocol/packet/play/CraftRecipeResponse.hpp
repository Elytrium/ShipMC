#pragma once

#include "../../../../lib/ShipNet/src/utils/ordinal/OrdinalRegistry.hpp"
#include <string>
#include <utility>

namespace Ship {

  class CraftRecipeResponse : public Packet {
   private:
    uint8_t windowId{};
    std::string recipe;

   public:
    static inline const uint32_t PACKET_ORDINAL = OrdinalRegistry::PacketRegistry.RegisterOrdinal();

    CraftRecipeResponse() = default;
    CraftRecipeResponse(uint8_t windowId, std::string recipe) : windowId(windowId), recipe(std::move(recipe)) {
    }

    ~CraftRecipeResponse() override = default;

    static Errorable<CraftRecipeResponse> Instantiate(const PacketHolder& holder) {
      ByteBuffer* buffer = holder.GetCurrentBuffer();
      ProceedErrorable(windowId, uint8_t, buffer->ReadByte(), InvalidPacketErrorable<CraftRecipeResponse>(PACKET_ORDINAL))
      ProceedErrorable(recipe, std::string, buffer->ReadString(), InvalidPacketErrorable<CraftRecipeResponse>(PACKET_ORDINAL))
      return SuccessErrorable<CraftRecipeResponse>(CraftRecipeResponse(windowId, recipe));
    }

    Errorable<bool> Write(const ProtocolVersion* version, ByteBuffer* buffer) const override {
      buffer->WriteByte(windowId);
      buffer->WriteString(recipe);
      return SuccessErrorable<bool>(true);
    }

    [[nodiscard]] uint32_t GetOrdinal() const override {
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
