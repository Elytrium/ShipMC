#pragma once

#include "../../../utils/ordinal/OrdinalRegistry.hpp"
#include "../Packet.hpp"
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

    void Read(const ProtocolVersion* version, ByteBuffer* buffer) override {
      difficulty = (Difficulty) buffer->ReadByte();
      if (version >= &ProtocolVersion::MINECRAFT_1_14) {
        locked = buffer->ReadBoolean();
      }
    }

    void Write(const ProtocolVersion* version, ByteBuffer* buffer) override {
      buffer->WriteByte(difficulty);
      if (version >= &ProtocolVersion::MINECRAFT_1_14) {
        buffer->WriteBoolean(locked);
      }
    }

    uint32_t Size(const ProtocolVersion* version) override {
      if (version >= &ProtocolVersion::MINECRAFT_1_14) {
        return ByteBuffer::BYTE_SIZE + ByteBuffer::BOOLEAN_SIZE;
      }
      return ByteBuffer::BYTE_SIZE;
    }

    uint32_t GetOrdinal() override {
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
