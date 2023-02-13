#pragma once

#include "../../../utils/ordinal/OrdinalRegistry.hpp"
#include "../Packet.hpp"
#include <string>

namespace Ship {

  class UnloadChunk : public Packet {
   private:
    uint32_t chunkX;
    uint32_t chunkZ;

   public:
    static inline const uint32_t PACKET_ORDINAL = OrdinalRegistry::PacketRegistry.RegisterOrdinal();

    UnloadChunk(uint32_t chunkX, uint32_t chunkZ) : chunkX(chunkX), chunkZ(chunkZ) {
    }

    ~UnloadChunk() override = default;

    void Read(const ProtocolVersion* version, ByteBuffer* buffer) override {
      chunkX = buffer->ReadInt();
      chunkZ = buffer->ReadInt();
    }

    void Write(const ProtocolVersion* version, ByteBuffer* buffer) override {
      buffer->WriteInt(chunkX);
      buffer->WriteInt(chunkZ);
    }

    uint32_t Size(const ProtocolVersion* version) override {
      return ByteBuffer::INT_SIZE + ByteBuffer::INT_SIZE;
    }

    uint32_t GetOrdinal() override {
      return PACKET_ORDINAL;
    }

    [[nodiscard]] uint32_t GetChunkX() const {
      return chunkX;
    }

    [[nodiscard]] uint32_t GetChunkZ() const {
      return chunkZ;
    }
  };
}
