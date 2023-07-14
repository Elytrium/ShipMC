#pragma once

#include "ShipNet/utils/ordinal/OrdinalRegistry.hpp"
#include <string>

namespace Ship {

  class ServerChangeDifficulty : public Packet {
   private:
    Difficulty difficulty{};
    bool locked{};

   public:
    static inline const uint32_t PACKET_ORDINAL = OrdinalRegistry::PacketRegistry.RegisterOrdinal();

    ServerChangeDifficulty() = default;
    ServerChangeDifficulty(Difficulty difficulty, bool locked) : difficulty(difficulty), locked(locked) {
    }

    ~ServerChangeDifficulty() override = default;

    static Errorable<ServerChangeDifficulty> Instantiate(const PacketHolder& holder) {
      ByteBuffer* buffer = holder.GetCurrentBuffer();
      const ProtocolVersion* version = holder.GetVersion();
      ProceedErrorable(difficultyByte, uint8_t, buffer->ReadByte(), InvalidPacketErrorable<ServerChangeDifficulty>(PACKET_ORDINAL))
      auto difficulty = (Difficulty) difficultyByte;
      bool locked = false;
      if (version >= &MinecraftProtocolVersion::MINECRAFT_1_14) {
        SetFromErrorable(locked, bool, buffer->ReadBoolean(), InvalidPacketErrorable<ServerChangeDifficulty>(PACKET_ORDINAL))
      }

      return SuccessErrorable<ServerChangeDifficulty>(ServerChangeDifficulty(difficulty, locked));
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
