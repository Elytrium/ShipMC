#include "Particle.hpp"

namespace Ship {

  FallingDustParticle::FallingDustParticle(uint32_t blockState) : blockState(blockState) {
  }

  Errorable<bool> FallingDustParticle::Write(const ProtocolVersion* version, ByteBuffer* buffer) const {
    buffer->WriteVarInt(blockState);
    return SuccessErrorable<bool>(true);
  }

  Errorable<FallingDustParticle> FallingDustParticle::Instantiate(const ProtocolVersion* version, ByteBuffer* buffer) {
    ProceedErrorable(blockState, uint32_t, buffer->ReadVarInt(), InvalidFallingDustParticleErrorable(buffer->GetReadableBytes()))
    return SuccessErrorable<FallingDustParticle>(FallingDustParticle(blockState));
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