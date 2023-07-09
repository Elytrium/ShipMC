#pragma once

#include "../../lib/ShipNet/src/protocol/Protocol.hpp"
#include "data/profile/GameProfile.hpp"
#include <string>
#include <utility>

namespace Ship {
  enum class Direction {
    DOWN = 0,
    UP = 1,
    NORTH = 2,
    SOUTH = 3,
    WEST = 4,
    EAST = 5,
  };

  class MinecraftProtocolVersion {
   public:
    static const ProtocolVersion MINECRAFT_1_12_2;
    static const ProtocolVersion MINECRAFT_1_13;
    static const ProtocolVersion MINECRAFT_1_13_1;
    static const ProtocolVersion MINECRAFT_1_13_2;
    static const ProtocolVersion MINECRAFT_1_14;
    static const ProtocolVersion MINECRAFT_1_14_1;
    static const ProtocolVersion MINECRAFT_1_14_2;
    static const ProtocolVersion MINECRAFT_1_14_3;
    static const ProtocolVersion MINECRAFT_1_14_4;
    static const ProtocolVersion MINECRAFT_1_15;
    static const ProtocolVersion MINECRAFT_1_15_1;
    static const ProtocolVersion MINECRAFT_1_15_2;
    static const ProtocolVersion MINECRAFT_1_16_2;
    static const ProtocolVersion MINECRAFT_1_16_3;
    static const ProtocolVersion MINECRAFT_1_16_4;
    static const ProtocolVersion MINECRAFT_1_17;
    static const ProtocolVersion MINECRAFT_1_17_1;
    static const ProtocolVersion MINECRAFT_1_18;
    static const ProtocolVersion MINECRAFT_1_18_2;
    static const ProtocolVersion MINECRAFT_1_19;
    static const ProtocolVersion MINECRAFT_1_19_1;
    static const ProtocolVersion MINECRAFT_1_19_3;

    static const ProtocolVersions VERSIONS;
  };
}