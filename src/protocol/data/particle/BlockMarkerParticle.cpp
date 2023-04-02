#include "Particle.hpp"

namespace Ship {

  BlockMarkerParticle::BlockMarkerParticle(uint32_t blockState) : blockState(blockState) {
  }

  void BlockMarkerParticle::Write(const ProtocolVersion* version, ByteBuffer* buffer) const {
    buffer->WriteVarInt(blockState);
  }

  BlockMarkerParticle::BlockMarkerParticle(const ProtocolVersion* version, ByteBuffer* buffer) {
    ProceedErrorable(blockState, uint32_t, buffer->ReadVarInt(), InvalidPacketErrorable<>(PACKET_ORDINAL))
  }

  std::string BlockMarkerParticle::GetIdentifier() const {
    return "minecraft:block_marker";
  }

  uint32_t BlockMarkerParticle::GetOrdinal() const {
    return ORDINAL;
  }

  uint32_t BlockMarkerParticle::GetBlockState() const {
    return blockState;
  }

  void BlockMarkerParticle::SetBlockState(uint32_t newValue) {
    blockState = newValue;
  }
}