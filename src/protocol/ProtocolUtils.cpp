#include "ProtocolUtils.hpp"

namespace Ship {
  void ProtocolUtils::WriteNBT(ByteBuffer* buffer, NBT* nbt) {
    buffer->WriteByte(nbt->GetType());
    buffer->WriteString(nbt->GetName());
    nbt->Write(buffer);
  }

  Errorable<bool> ProtocolUtils::WriteParticle(const ProtocolVersion* version, ByteBuffer* buffer, AbstractParticle* particle) {
    ProceedErrorable(id, uint32_t, PARTICLE_REGISTRY.GetIDByOrdinal(version, particle->GetOrdinal()), InvalidSerializableWriteErrorable(buffer->GetReadableBytes()))
    buffer->WriteVarInt(id);
    particle->Write(version, buffer);
    return SuccessErrorable<bool>(true);
  }

  void ProtocolUtils::WriteMetadata(const ProtocolVersion* version, ByteBuffer* buffer, Metadata* metadata) {
    if (metadata) {
      metadata->Write(version, buffer);
    } else {
      buffer->WriteByte(0xFF);
    }
  }

  Errorable<NBT*> ProtocolUtils::ReadNBT(ByteBuffer* buffer) {
    ProceedErrorable(type, uint8_t, buffer->ReadByte(), InvalidNBTErrorable(buffer->GetReadableBytes()))

    if (type == TagType::END) {
      return SuccessErrorable<NBT*>(new EndTag(""));
    }

    ProceedErrorable(name, std::string, buffer->ReadString(), InvalidNBTErrorable(buffer->GetReadableBytes()))
    NBT* nbt = NBT::Create((TagType) type, name);
    nbt->Read(buffer);
    return SuccessErrorable<NBT*>(nbt);
  }

  Errorable<AbstractParticle*> ProtocolUtils::ReadParticle(const ProtocolVersion* version, ByteBuffer* buffer) {
    ProceedErrorable(id, uint32_t, buffer->ReadVarInt(), InvalidParticleErrorable(buffer->GetReadableBytes()))
    return PARTICLE_REGISTRY.GetObjectByID(version, id, buffer);
  }

  Errorable<Metadata> ProtocolUtils::ReadMetadata(const ProtocolVersion* version, ByteBuffer* buffer) {
    return Metadata::Instantiate(version, buffer);
  }

  uint32_t ProtocolUtils::NBTSize(NBT* nbt) {
    if (nbt) {
      return ByteBuffer::BYTE_SIZE + ByteBuffer::StringBytes(nbt->GetName()) + nbt->GetSize();
    } else {
      return ByteBuffer::BYTE_SIZE;
    }
  }

  Errorable<uint32_t> ProtocolUtils::ParticleSize(const ProtocolVersion* version, AbstractParticle* particle) {
    ProceedErrorable(id, uint32_t, PARTICLE_REGISTRY.GetIDByOrdinal(version, particle->GetOrdinal()), InvalidPacketByOrdinal(particle->GetOrdinal()))
    return SuccessErrorable<uint32_t>(ByteBuffer::VarIntBytes(id) + particle->Size(version));
  }

  uint32_t ProtocolUtils::MetadataSize(const ProtocolVersion* version, Metadata* metadata) {
    if (metadata) {
      return metadata->Size(version);
    } else {
      return 1;
    }
  }

  Errorable<std::vector<GameProfileProperty>> ProtocolUtils::ReadProperties(ByteBuffer* buffer) {
    std::vector<GameProfileProperty> properties;
    ProceedErrorable(count, uint32_t, buffer->ReadVarInt(), InvalidGameProdilePropertiesErrorable(buffer->GetReadableBytes()))
    for (uint32_t i = 0; i < count; ++i) {
      ProceedErrorable(name, std::string, buffer->ReadString(), InvalidGameProdilePropertiesErrorable(buffer->GetReadableBytes()))
      ProceedErrorable(value, std::string, buffer->ReadString(), InvalidGameProdilePropertiesErrorable(buffer->GetReadableBytes()))
      ProceedErrorable(hasSignature, bool, buffer->ReadBoolean(), InvalidGameProdilePropertiesErrorable(buffer->GetReadableBytes()))
      if (hasSignature) {
        ProceedErrorable(signature, std::string, buffer->ReadString(), InvalidGameProdilePropertiesErrorable(buffer->GetReadableBytes()))
        properties.emplace_back(name, value, signature);
      } else {
        properties.emplace_back(name, value, "");
      }
    }

    return SuccessErrorable<std::vector<GameProfileProperty>>(properties);
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

  Errorable<Position> ProtocolUtils::ReadPosition(const ProtocolVersion* version, ByteBuffer* buffer) {
    ProceedErrorable(value, uint64_t, buffer->ReadLong(), InvalidPositionErrorable(buffer->GetReadableBytes()))
    int x = (int) (value >> 38);
    int y = (int) (value & 0xFFF);
    int z = (int) (value >> 12) & 0x3FFFFFF;

    if (x >= 1 << 25) {
      x -= 1 << 26;
    }

    if (y >= 1 << 11) {
      y -= 1 << 12;
    }

    if (z >= 1 << 25) {
      z -= 1 << 26;
    }

    return SuccessErrorable<Position>({x, y, z});
  }

  void ProtocolUtils::WritePosition(const ProtocolVersion* version, ByteBuffer* buffer, Position position) {
    buffer->WriteLong(((position.GetX() & 0x3FFFFFFULL) << 38) | ((position.GetZ() & 0x3FFFFFFULL) << 12) | (position.GetY() & 0xFFF));
  }
}
