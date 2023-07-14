#pragma once

#include "../../../../lib/ShipNet/src/utils/ordinal/OrdinalRegistry.hpp"
#include <string>

namespace Ship {

  class Cooldown : public Packet {
   private:
    uint32_t itemId;
    uint32_t cooldownTicks;

   public:
    static inline const uint32_t PACKET_ORDINAL = OrdinalRegistry::PacketRegistry.RegisterOrdinal();

    Cooldown() = default;
    Cooldown(uint32_t itemId, uint32_t cooldownTicks) : itemId(itemId), cooldownTicks(cooldownTicks) {
    }

    ~Cooldown() override = default;

    static Errorable<Cooldown> Instantiate(const PacketHolder& holder) {
      ByteBuffer* buffer = holder.GetCurrentBuffer();
      ProceedErrorable(itemId, uint32_t, buffer->ReadVarInt(), InvalidPacketErrorable<Cooldown>(PACKET_ORDINAL))
      ProceedErrorable(cooldownTicks, uint32_t, buffer->ReadVarInt(), InvalidPacketErrorable<Cooldown>(PACKET_ORDINAL))
      return SuccessErrorable<Cooldown>(Cooldown(itemId, cooldownTicks));
    }

    Errorable<bool> Write(const ProtocolVersion* version, ByteBuffer* buffer) const override {
      buffer->WriteVarInt(itemId);
      buffer->WriteVarInt(cooldownTicks);
      return SuccessErrorable<bool>(true);
    }

    [[nodiscard]] uint32_t GetOrdinal() const override {
      return PACKET_ORDINAL;
    }

    [[nodiscard]] uint32_t GetItemId() const {
      return itemId;
    }

    [[nodiscard]] uint32_t GetCooldownTicks() const {
      return cooldownTicks;
    }
  };
}
