#include "Particle.hpp"
#include <utility>

namespace Ship {

  VibrationParticle::VibrationParticle(
    std::string sourceType, int blockX, int blockY, int blockZ, uint32_t entityId, float entityEyeHeight, uint32_t ticks)
    : sourceType(std::move(sourceType)), blockX(blockX), blockY(blockY), blockZ(blockZ), entityId(entityId), entityEyeHeight(entityEyeHeight),
      ticks(ticks) {
  }

  VibrationParticle::VibrationParticle(int blockX, int blockY, int blockZ, uint32_t ticks)
    : VibrationParticle("minecraft:block", blockX, blockY, blockZ, 0, 0, ticks) {
  }

  VibrationParticle::VibrationParticle(uint32_t entityId, float entityEyeHeight, uint32_t ticks)
    : VibrationParticle("minecraft:entity", 0, 0, 0, entityId, entityEyeHeight, ticks) {
  }

  VibrationParticle::VibrationParticle(std::string sourceType, uint32_t ticks) : VibrationParticle(std::move(sourceType), 0, 0, 0, 0, 0, ticks) {
  }

  void VibrationParticle::Write(const ProtocolVersion* version, ByteBuffer* buffer) {
    buffer->WriteString(sourceType);
    if (sourceType == "minecraft:block") {
      buffer->WritePosition(blockX, blockY, blockZ);
    } else if (sourceType == "minecraft:entity") {
      buffer->WriteVarInt(entityId);
      buffer->WriteFloat(entityEyeHeight);
    }
    buffer->WriteVarInt(ticks);
  }

  void VibrationParticle::Read(const ProtocolVersion* version, ByteBuffer* buffer) {
    sourceType = buffer->ReadString();
    if (sourceType == "minecraft:block") {
      buffer->ReadPosition(blockX, blockY, blockZ);
    } else if (sourceType == "minecraft:entity") {
      entityId = buffer->ReadVarInt();
      entityEyeHeight = buffer->ReadFloat();
    }
    ticks = buffer->ReadVarInt();
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

  int VibrationParticle::GetBlockX() const {
    return blockX;
  }

  void VibrationParticle::SetBlockX(int newValue) {
    blockX = newValue;
  }

  int VibrationParticle::GetBlockY() const {
    return blockY;
  }

  void VibrationParticle::SetBlockY(int newValue) {
    blockY = newValue;
  }

  int VibrationParticle::GetBlockZ() const {
    return blockZ;
  }

  void VibrationParticle::SetBlockZ(int newValue) {
    blockZ = newValue;
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