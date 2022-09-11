#pragma once

#include "data/nbt/NBT.hpp"
#include "data/profile/GameProfile.hpp"

namespace Ship {

  class ProtocolUtils {
   public:
    static void WriteNBT(ByteBuffer* buffer, NBT* nbt);

    static NBT* ReadNBT(ByteBuffer* buffer);
  };

} // Ship
