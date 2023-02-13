#include "Particle.hpp"

namespace Ship {

  BlockMarkerParticle::BlockMarkerParticle(uint32_t blockState) : blockState(blockState) {
  }

  void BlockMarkerParticle::Write(const ProtocolVersion* version, ByteBuffer* buffer) {
    buffer->WriteVarInt(blockState);
  }

  void BlockMarkerParticle::Read(const ProtocolVersion* version, ByteBuffer* buffer) {
    blockState = buffer->ReadVarInt();
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