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

    static Errorable<UnloadChunk> Instantiate(const PacketHolder& holder) {
      ByteBuffer* buffer = holder.GetCurrentBuffer();
      chunkX = buffer->ReadInt();
      chunkZ = buffer->ReadInt();
    }

    void Write(const ProtocolVersion* version, ByteBuffer* buffer) const override {
      buffer->WriteInt(chunkX);
      buffer->WriteInt(chunkZ);
    }

    uint32_t GetOrdinal() const override {
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
