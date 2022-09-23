#include "Particle.hpp"

namespace Ship {

  BlockParticle::BlockParticle(uint32_t blockState) : blockState(blockState) {
  }

  void BlockParticle::Write(const ProtocolVersion* version, ByteBuffer* buffer) {
    buffer->WriteVarInt(blockState);
  }

  void BlockParticle::Read(const ProtocolVersion* version, ByteBuffer* buffer) {
    blockState = buffer->ReadVarInt();
  }

  uint32_t BlockParticle::Size(const ProtocolVersion* version) const {
    return ByteBuffer::VarIntBytes(blockState);
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