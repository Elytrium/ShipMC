#pragma once

#include "../../../../lib/ShipNet/src/utils/ordinal/OrdinalRegistry.hpp"
#include <string>

namespace Ship {

  class ServerChangeDifficulty : public Packet {
   private:
    Difficulty difficulty;
    bool locked;

   public:
    static inline const uint32_t PACKET_ORDINAL = OrdinalRegistry::PacketRegistry.RegisterOrdinal();

    ServerChangeDifficulty(Difficulty difficulty, bool locked) : difficulty(difficulty), locked(locked) {
    }

    ~ServerChangeDifficulty() override = default;

    static Errorable<ServerChangeDifficulty> Instantiate(const PacketHolder& holder) {
      ByteBuffer* buffer = holder.GetCurrentBuffer();
      const ProtocolVersion* version = holder.GetVersion();
      difficulty = (Difficulty) buffer->ReadByte();
      if (version >= &MinecraftProtocolVersion::MINECRAFT_1_14) {
        ProceedErrorable(locked, bool, buffer->ReadBoolean(), InvalidPacketErrorable<>(PACKET_ORDINAL))
      }
    }

    Errorable<bool> Write(const ProtocolVersion* version, ByteBuffer* buffer) const override {
      buffer->WriteByte(difficulty);
      if (version >= &MinecraftProtocolVersion::MINECRAFT_1_14) {
        buffer->WriteBoolean(locked);
      }
      return SuccessErrorable<bool>(true);
    }

    [[nodiscard]] uint32_t GetOrdinal() const override {
      return PACKET_ORDINAL;
    }

    [[nodiscard]] Difficulty GetDifficulty() const {
      return difficulty;
    }

    [[nodiscard]] bool IsLocked() const {
      return locked;
    }
  };
}
