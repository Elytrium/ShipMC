#pragma once

#include "../../../utils/ordinal/OrdinalRegistry.hpp"
#include "../Packet.hpp"
#include <string>

namespace Ship {

  class ServerPlayerAbilities : public Packet {
   private:
    union {
      struct {
        uint8_t invulnerable : 1;
        uint8_t flying : 1;
        uint8_t allowFlying : 1;
        uint8_t creativeMode : 1;
      };

      uint8_t value;
    } flags {};
    float flyingSpeed;
    float fovModifier;

   public:
    static inline const uint32_t PACKET_ORDINAL = OrdinalRegistry::PacketRegistry.RegisterOrdinal();

    ServerPlayerAbilities(bool invulnerable, bool flying, bool allowFlying, bool creativeMode, float flyingSpeed, float fovModifier)
      : flags {.invulnerable = invulnerable, .flying = flying, .allowFlying = allowFlying, .creativeMode = creativeMode}, flyingSpeed(flyingSpeed),
        fovModifier(fovModifier) {
    }

    ~ServerPlayerAbilities() override = default;

    explicit ServerPlayerAbilities(const PacketHolder& holder) {
      ByteBuffer* buffer = holder.GetCurrentBuffer();
      flags.value = buffer->ReadByte();
      flyingSpeed = buffer->ReadFloat();
      fovModifier = buffer->ReadFloat();
    }

    void Write(const ProtocolVersion* version, ByteBuffer* buffer) const override {
      buffer->WriteByte(flags.value);
      buffer->WriteFloat(flyingSpeed);
      buffer->WriteFloat(fovModifier);
    }

    uint32_t GetOrdinal() const override {
      return PACKET_ORDINAL;
    }

    [[nodiscard]] bool IsInvulnerable() const {
      return flags.invulnerable;
    }

    [[nodiscard]] bool IsFlying() const {
      return flags.flying;
    }

    [[nodiscard]] bool IsAllowFlying() const {
      return flags.allowFlying;
    }

    [[nodiscard]] bool IsCreativeMode() const {
      return flags.creativeMode;
    }

    [[nodiscard]] float GetFlyingSpeed() const {
      return flyingSpeed;
    }

    [[nodiscard]] float GetFovModifier() const {
      return fovModifier;
    }
  };
}
