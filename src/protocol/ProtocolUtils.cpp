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

  void ProtocolUtils::WriteMetadata(const ProtocolVersion* version, ByteBuffer* buffer, Metadata* metadata) {
    if (metadata) {
      metadata->Write(version, buffer);
    } else {
      buffer->WriteByte(0xFF);
    }
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
    return PARTICLE_REGISTRY.GetObjectByID(version, buffer->ReadVarInt(), buffer);
  }

  Metadata* ProtocolUtils::ReadMetadata(const ProtocolVersion* version, ByteBuffer* buffer) {
    return new Metadata(version, buffer);
  }

  uint32_t ProtocolUtils::NBTSize(NBT* nbt) {
    if (nbt) {
      return ByteBuffer::BYTE_SIZE + ByteBuffer::StringBytes(nbt->GetName()) + nbt->GetSize();
    } else {
      return ByteBuffer::BYTE_SIZE;
    }
  }

  uint32_t ProtocolUtils::ParticleSize(const ProtocolVersion* version, AbstractParticle* particle) {
    return ByteBuffer::VarIntBytes(PARTICLE_REGISTRY.GetIDByOrdinal(version, particle->GetOrdinal())) + particle->Size(version);
  }

  uint32_t ProtocolUtils::MetadataSize(const ProtocolVersion* version, Metadata* metadata) {
    if (metadata) {
      return metadata->Size(version);
    } else {
      return 1;
    }
  }

  std::vector<GameProfileProperty> ProtocolUtils::ReadProperties(ByteBuffer* buffer) {
    std::vector<GameProfileProperty> properties;
    for (uint32_t i = 0; i < buffer->ReadVarInt(); ++i) {
      std::string name = buffer->ReadString();
      std::string value = buffer->ReadString();
      if (buffer->ReadBoolean()) {
        properties.emplace_back(name, value, buffer->ReadString());
      } else {
        properties.emplace_back(name, value, "");
      }
    }

    return properties;
  }

  void ProtocolUtils::WriteProperties(ByteBuffer* buffer, const std::vector<GameProfileProperty>& properties) {
    buffer->WriteVarInt(properties.size());
    for (const GameProfileProperty& property : properties) {
      buffer->WriteString(property.GetName());
      buffer->WriteString(property.GetValue());
      if (property.GetSignature().empty()) {
        buffer->WriteBoolean(false);
      } else {
        buffer->WriteBoolean(true);
        buffer->WriteString(property.GetSignature());
      }
    }
  }
}
