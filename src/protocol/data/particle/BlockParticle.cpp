#include "Particle.hpp"

namespace Ship {

  BlockParticle::BlockParticle(uint32_t blockState) : blockState(blockState) {
  }

  Errorable<bool> BlockParticle::Write(const ProtocolVersion* version, ByteBuffer* buffer) const {
    buffer->WriteVarInt(blockState);
    return SuccessErrorable<bool>(true);
  }

  BlockParticle::BlockParticle(const ProtocolVersion* version, ByteBuffer* buffer) {
    blockState = buffer->ReadVarInt();
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