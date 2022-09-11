#pragma once

#include "PacketRegistry.hpp"

namespace Ship {
  class BuiltInPacketRegistry {
   public:
    static const PacketRegistry HANDSHAKE;
    static const PacketRegistry STATUS;
    static const PacketRegistry LOGIN;
    static const PacketRegistry PLAY;
  };
}
