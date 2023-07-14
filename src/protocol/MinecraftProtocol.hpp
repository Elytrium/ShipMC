#pragma once

#include "ShipNet/protocol/Protocol.hpp"
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

  class Position {
   private:
    int x, y, z;

   public:
    Position() : x(0), y(0), z(0) {
    }

    Position(int x, int y, int z) : x(x), y(y), z(z) {
    }

    [[nodiscard]] int GetX() const {
      return x;
    }
    [[nodiscard]] int GetY() const {
      return y;
    }
    [[nodiscard]] int GetZ() const {
      return z;
    }

    void SetX(int _x) {
      this->x = _x;
    }

    void SetY(int _y) {
      this->y = _y;
    }

    void SetZ(int _z) {
      this->z = _z;
    }
  };
  CreateInvalidArgumentErrorable(InvalidPositionErrorable, Position, "Invalid Position value read");

  class Rotation {
   private:
    float x, y, z;

   public:
    Rotation() : x(0), y(0), z(0) {
    }

    Rotation(float x, float y, float z) : x(x), y(y), z(z) {
    }

    [[nodiscard]] float GetX() const {
      return x;
    }
    [[nodiscard]] float GetY() const {
      return y;
    }
    [[nodiscard]] float GetZ() const {
      return z;
    }

    void SetX(float _x) {
      this->x = _x;
    }

    void SetY(float _y) {
      this->y = _y;
    }

    void SetZ(float _z) {
      this->z = _z;
    }
  };
  CreateInvalidArgumentErrorable(InvalidRotationErrorable, Rotation, "Invalid Rotation value read");

  class GlobalPos {
   private:
    std::string dimension;
    Position position{};
   public:
    GlobalPos() = default;

    GlobalPos(std::string dimension, const Position& position);

    [[nodiscard]] const std::string& GetDimension() const;
    void SetDimension(const std::string& dimension);
    const Position& GetPosition() const;
    void SetPosition(const Position& position);
  };
  CreateInvalidArgumentErrorable(InvalidGlobalPosErrorable, GlobalPos, "Invalid GlobalPos value read");

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