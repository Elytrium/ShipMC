#pragma once

#include "data/entity/metadata/Metadata.hpp"
#include "data/nbt/NBT.hpp"
#include "data/particle/Particle.hpp"
#include "data/profile/GameProfile.hpp"

namespace Ship {

  class ProtocolUtils {
   public:
    static void WriteNBT(ByteBuffer* buffer, NBT* nbt);
    static void WriteParticle(const ProtocolVersion* version, ByteBuffer* buffer, AbstractParticle* particle);
    static void WriteMetadata(const ProtocolVersion* version, ByteBuffer* buffer, Metadata* metadata);

    static NBT* ReadNBT(ByteBuffer* buffer);
    static AbstractParticle* ReadParticle(const ProtocolVersion* version, ByteBuffer* buffer);
    static Metadata* ReadMetadata(const ProtocolVersion* version, ByteBuffer* buffer);

    static uint32_t NBTSize(NBT* nbt);
    static uint32_t ParticleSize(const ProtocolVersion* version, AbstractParticle* particle);
    static uint32_t MetadataSize(const ProtocolVersion* version, Metadata* metadata);
  };

} // Ship
