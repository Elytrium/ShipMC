#include "ProtocolUtils.hpp"

namespace Ship {
  void ProtocolUtils::WriteNBT(ByteBuffer* buffer, NBT* nbt) {
    buffer->WriteByte(nbt->GetType());
    buffer->WriteString(nbt->GetName());
    nbt->Write(buffer);
  }

  void ProtocolUtils::WriteParticle(const ProtocolVersion* version, ByteBuffer* buffer, AbstractParticle* particle) {
    buffer->WriteVarInt(PARTICLE_REGISTRY.GetIDByOrdinal(version, particle->GetOrdinal()));
    particle->Write(version, buffer);
  }

  NBT* ProtocolUtils::ReadNBT(ByteBuffer* buffer) {
    auto type = (TagType) buffer->ReadByte();

    if (type == TagType::END) {
      return new EndTag("");
    }

    NBT* nbt = NBT::Create(type, buffer->ReadString());
    nbt->Read(buffer);
    return nbt;
  }

  AbstractParticle* ProtocolUtils::ReadParticle(const ProtocolVersion* version, ByteBuffer* buffer) {
    AbstractParticle* particle = PARTICLE_REGISTRY.GetObjectByID(version, buffer->ReadVarInt());
    particle->Read(version, buffer);
    return particle;
  }

  uint32_t ProtocolUtils::NBTSize(NBT* nbt) {
    return ByteBuffer::BYTE_SIZE + ByteBuffer::StringBytes(nbt->GetName()) + nbt->GetSize();
  }

  uint32_t ProtocolUtils::ParticleSize(const ProtocolVersion* version, AbstractParticle* particle) {
    return ByteBuffer::VarIntBytes(PARTICLE_REGISTRY.GetIDByOrdinal(version, particle->GetOrdinal())) + particle->Size(version);
  }
} // Ship