#pragma once

#include "data/entity/metadata/Metadata.hpp"
#include "data/nbt/NBT.hpp"
#include "data/particle/Particle.hpp"
#include "data/profile/GameProfile.hpp"

namespace Ship {

  CreateInvalidArgumentErrorable(InvalidGameProdilePropertiesErrorable, std::vector<GameProfileProperty>, "Invalid GameProfile properties read");

  class ProtocolUtils {
   public:
    static void WriteNBT(ByteBuffer* buffer, NBT* nbt);
    static Errorable<bool> WriteParticle(const ProtocolVersion* version, ByteBuffer* buffer, AbstractParticle* particle);
    static void WriteMetadata(const ProtocolVersion* version, ByteBuffer* buffer, Metadata* metadata);
    static void WritePosition(const ProtocolVersion* version, ByteBuffer* buffer, Position position);

    static Errorable<NBT*> ReadNBT(ByteBuffer* buffer);
    static Errorable<AbstractParticle*> ReadParticle(const ProtocolVersion* version, ByteBuffer* buffer);
    static Errorable<Metadata> ReadMetadata(const ProtocolVersion* version, ByteBuffer* buffer);
    static Errorable<Position> ReadPosition(const ProtocolVersion* version, ByteBuffer* buffer);

    static uint32_t NBTSize(NBT* nbt);
    static Errorable<uint32_t> ParticleSize(const ProtocolVersion* version, AbstractParticle* particle);
    static uint32_t MetadataSize(const ProtocolVersion* version, Metadata* metadata);

    static Errorable<std::vector<GameProfileProperty>> ReadProperties(ByteBuffer* buffer);
    static void WriteProperties(ByteBuffer* buffer, const std::vector<GameProfileProperty>& properties);
  };

}
