#include "Particle.hpp"

namespace Ship {

  BlockParticle::BlockParticle(uint32_t blockState) : blockState(blockState) {
  }

  void BlockParticle::Write(const ProtocolVersion* version, ByteBuffer* buffer) const {
    buffer->WriteVarInt(blockState);
  }

  BlockParticle::BlockParticle(const ProtocolVersion* version, ByteBuffer* buffer) {
    ProceedErrorable(blockState, uint32_t, buffer->ReadVarInt(), InvalidPacketErrorable<>(PACKET_ORDINAL))
  }

  std::string BlockParticle::GetIdentifier() const {
    return "minecraft:block";
  }

  uint32_t BlockParticle::GetOrdinal() const {
    return ORDINAL;
  }

  uint32_t BlockParticle::GetBlockState() const {
    return blockState;
  }

  void BlockParticle::SetBlockState(uint32_t newValue) {
    blockState = newValue;
  }
}