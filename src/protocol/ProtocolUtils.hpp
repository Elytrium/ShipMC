#pragma once

#include "data/nbt/NBT.hpp"
#include "data/particle/Particle.hpp"
#include "data/profile/GameProfile.hpp"

namespace Ship {

  class ProtocolUtils {
   public:
    static void WriteNBT(ByteBuffer* buffer, NBT* nbt);
    static void WriteParticle(const ProtocolVersion* version, ByteBuffer* buffer, AbstractParticle* particle);

    static NBT* ReadNBT(ByteBuffer* buffer);
    static AbstractParticle* ReadParticle(const ProtocolVersion* version, ByteBuffer* buffer);
  };

} // Ship
