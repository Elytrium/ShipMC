#include "Particle.hpp"

namespace Ship {

  FallingDustParticle::FallingDustParticle(uint32_t blockState) : blockState(blockState) {
  }

  void FallingDustParticle::Write(const ProtocolVersion* version, ByteBuffer* buffer) {
    buffer->WriteVarInt(blockState);
  }

  void FallingDustParticle::Read(const ProtocolVersion* version, ByteBuffer* buffer) {
    blockState = buffer->ReadVarInt();
  }

  uint32_t FallingDustParticle::Size(const ProtocolVersion* version) const {
    return ByteBuffer::VarIntBytes(blockState);
  }

  std::string FallingDustParticle::GetIdentifier() const {
    return "minecraft:falling_dust";
  }

  uint32_t FallingDustParticle::GetOrdinal() const {
    return ORDINAL;
  }

  uint32_t FallingDustParticle::GetBlockState() const {
    return blockState;
  }

  void FallingDustParticle::SetBlockState(uint32_t newValue) {
    blockState = newValue;
  }
}