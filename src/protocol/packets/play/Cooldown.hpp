#pragma once

#include "../../../utils/ordinal/OrdinalRegistry.hpp"
#include "../Packet.hpp"
#include <string>

namespace Ship {

  class Cooldown : public Packet {
   private:
    uint32_t itemId;
    uint32_t cooldownTicks;

   public:
    static inline const uint32_t PACKET_ORDINAL = OrdinalRegistry::PacketRegistry.RegisterOrdinal();

    Cooldown(uint32_t itemId, uint32_t cooldownTicks) : itemId(itemId), cooldownTicks(cooldownTicks) {
    }

    ~Cooldown() override = default;

    Cooldown(const ProtocolVersion* version, ByteBuffer* buffer) {
      itemId = buffer->ReadVarInt();
      cooldownTicks = buffer->ReadVarInt();
    }

    void Write(const ProtocolVersion* version, ByteBuffer* buffer) const override {
      buffer->WriteVarInt(itemId);
      buffer->WriteVarInt(cooldownTicks);
    }

    uint32_t GetOrdinal() const override {
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
