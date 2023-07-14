#include "Particle.hpp"
#include "../../ProtocolUtils.hpp"
#include <utility>

namespace Ship {

  VibrationParticle::VibrationParticle(
    std::string sourceType, Position blockPosition, uint32_t entityId, float entityEyeHeight, uint32_t ticks)
    : sourceType(std::move(sourceType)), blockPosition(blockPosition), entityId(entityId), entityEyeHeight(entityEyeHeight),
      ticks(ticks) {
  }

  VibrationParticle::VibrationParticle(Position blockPosition, uint32_t ticks)
    : VibrationParticle("minecraft:block", blockPosition, 0, 0, ticks) {
  }

  VibrationParticle::VibrationParticle(uint32_t entityId, float entityEyeHeight, uint32_t ticks)
    : VibrationParticle("minecraft:entity", {}, entityId, entityEyeHeight, ticks) {
  }

  VibrationParticle::VibrationParticle(const std::string& sourceType, uint32_t ticks) : VibrationParticle(sourceType, {}, 0, 0, ticks) {
  }

  Errorable<bool> VibrationParticle::Write(const ProtocolVersion* version, ByteBuffer* buffer) const {
    buffer->WriteString(sourceType);
    if (sourceType == "minecraft:block") {
      ProtocolUtils::WritePosition(version, buffer, blockPosition);
    } else if (sourceType == "minecraft:entity") {
      buffer->WriteVarInt(entityId);
      buffer->WriteFloat(entityEyeHeight);
    }
    buffer->WriteVarInt(ticks);
    return SuccessErrorable<bool>(true);
  }

  Errorable<VibrationParticle> VibrationParticle::Instantiate(const ProtocolVersion* version, ByteBuffer* buffer) {
    ProceedErrorable(sourceType, std::string, buffer->ReadString(), InvalidVibrationParticleErrorable(buffer->GetReadableBytes()))
    if (sourceType == "minecraft:block") {
      ProceedErrorable(position, Position, ProtocolUtils::ReadPosition(version, buffer), InvalidVibrationParticleErrorable(buffer->GetReadableBytes()))
      ProceedErrorable(ticks, uint32_t, buffer->ReadVarInt(), InvalidVibrationParticleErrorable(buffer->GetReadableBytes()))
      return SuccessErrorable<VibrationParticle>(VibrationParticle({position, ticks}));
    } else if (sourceType == "minecraft:entity") {
      ProceedErrorable(entityId, uint32_t, buffer->ReadVarInt(), InvalidVibrationParticleErrorable(buffer->GetReadableBytes()));
      ProceedErrorable(entityEyeHeight, float, buffer->ReadFloat(), InvalidVibrationParticleErrorable(buffer->GetReadableBytes()));
      ProceedErrorable(ticks, uint32_t, buffer->ReadVarInt(), InvalidVibrationParticleErrorable(buffer->GetReadableBytes()));
      return SuccessErrorable<VibrationParticle>(VibrationParticle({entityId, entityEyeHeight, ticks}));
    } else {
      return InvalidVibrationParticleErrorable(buffer->GetReadableBytes());
    }
  }

  std::string VibrationParticle::GetIdentifier() const {
    return "minecraft:vibration";
  }

  uint32_t VibrationParticle::GetOrdinal() const {
    return ORDINAL;
  }

  const std::string& VibrationParticle::GetSourceType() const {
    return sourceType;
  }

  void VibrationParticle::SetSourceType(const std::string& newValue) {
    sourceType = newValue;
  }

  Position VibrationParticle::GetBlockPosition() const {
    return blockPosition;
  }

  void VibrationParticle::SetBlockPosition(Ship::Position newValue) {
    blockPosition = newValue;
  }

  uint32_t VibrationParticle::GetEntityId() const {
    return entityId;
  }

  void VibrationParticle::SetEntityId(uint32_t newValue) {
    entityId = newValue;
  }

  float VibrationParticle::GetEntityEyeHeight() const {
    return entityEyeHeight;
  }

  void VibrationParticle::SetEntityEyeHeight(float newValue) {
    entityEyeHeight = newValue;
  }

  uint32_t VibrationParticle::GetTicks() const {
    return ticks;
  }

  void VibrationParticle::SetTicks(uint32_t newValue) {
    ticks = newValue;
  }
}