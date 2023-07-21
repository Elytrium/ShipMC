#include "MinecraftProtocol.hpp"

#include <utility>

namespace Ship {
  inline const ProtocolVersion MinecraftProtocolVersion::MINECRAFT_1_12_2 = ProtocolVersion(0, 340, "1.12.2");
  inline const ProtocolVersion MinecraftProtocolVersion::MINECRAFT_1_13 = ProtocolVersion(1, 393, "1.13");
  inline const ProtocolVersion MinecraftProtocolVersion::MINECRAFT_1_13_1 = ProtocolVersion(2, 401, "1.13.1");
  inline const ProtocolVersion MinecraftProtocolVersion::MINECRAFT_1_13_2 = ProtocolVersion(3, 404, "1.13.2");
  inline const ProtocolVersion MinecraftProtocolVersion::MINECRAFT_1_14 = ProtocolVersion(4, 477, "1.14");
  inline const ProtocolVersion MinecraftProtocolVersion::MINECRAFT_1_14_1 = ProtocolVersion(5, 480, "1.14.1");
  inline const ProtocolVersion MinecraftProtocolVersion::MINECRAFT_1_14_2 = ProtocolVersion(6, 485, "1.14.2");
  inline const ProtocolVersion MinecraftProtocolVersion::MINECRAFT_1_14_3 = ProtocolVersion(7, 490, "1.14.3");
  inline const ProtocolVersion MinecraftProtocolVersion::MINECRAFT_1_14_4 = ProtocolVersion(8, 498, "1.14.4");
  inline const ProtocolVersion MinecraftProtocolVersion::MINECRAFT_1_15 = ProtocolVersion(9, 573, "1.15");
  inline const ProtocolVersion MinecraftProtocolVersion::MINECRAFT_1_15_1 = ProtocolVersion(10, 575, "1.15.1");
  inline const ProtocolVersion MinecraftProtocolVersion::MINECRAFT_1_15_2 = ProtocolVersion(11, 578, "1.15.2");
  inline const ProtocolVersion MinecraftProtocolVersion::MINECRAFT_1_16_2 = ProtocolVersion(12, 751, "1.16.2");
  inline const ProtocolVersion MinecraftProtocolVersion::MINECRAFT_1_16_3 = ProtocolVersion(13, 753, "1.16.3");
  inline const ProtocolVersion MinecraftProtocolVersion::MINECRAFT_1_16_4 = ProtocolVersion(14, 754, "1.16.4 - 1.16.5");
  inline const ProtocolVersion MinecraftProtocolVersion::MINECRAFT_1_17 = ProtocolVersion(15, 755, "1.17");
  inline const ProtocolVersion MinecraftProtocolVersion::MINECRAFT_1_17_1 = ProtocolVersion(16, 756, "1.17.1");
  inline const ProtocolVersion MinecraftProtocolVersion::MINECRAFT_1_18 = ProtocolVersion(17, 757, "1.18 - 1.18.1");
  inline const ProtocolVersion MinecraftProtocolVersion::MINECRAFT_1_18_2 = ProtocolVersion(18, 758, "1.18.2");
  inline const ProtocolVersion MinecraftProtocolVersion::MINECRAFT_1_19 = ProtocolVersion(19, 759, "1.19");
  inline const ProtocolVersion MinecraftProtocolVersion::MINECRAFT_1_19_1 = ProtocolVersion(20, 760, "1.19.1 - 1.19.2");
  inline const ProtocolVersion MinecraftProtocolVersion::MINECRAFT_1_19_3 = ProtocolVersion(21, 761, "1.19.3");
  inline const ProtocolVersion MinecraftProtocolVersion::MINECRAFT_1_19_4 = ProtocolVersion(22, 762, "1.19.4");
  inline const ProtocolVersion MinecraftProtocolVersion::MINECRAFT_1_20 = ProtocolVersion(23, 763, "1.20 - 1.20.1");

  inline const ProtocolVersions MinecraftProtocolVersion::VERSIONS = ProtocolVersions({MinecraftProtocolVersion::MINECRAFT_1_12_2,
    MinecraftProtocolVersion::MINECRAFT_1_13, MinecraftProtocolVersion::MINECRAFT_1_13_1, MinecraftProtocolVersion::MINECRAFT_1_13_2,
    MinecraftProtocolVersion::MINECRAFT_1_14, MinecraftProtocolVersion::MINECRAFT_1_14_1, MinecraftProtocolVersion::MINECRAFT_1_14_2,
    MinecraftProtocolVersion::MINECRAFT_1_14_3, MinecraftProtocolVersion::MINECRAFT_1_14_4, MinecraftProtocolVersion::MINECRAFT_1_15,
    MinecraftProtocolVersion::MINECRAFT_1_15_1, MinecraftProtocolVersion::MINECRAFT_1_15_2, MinecraftProtocolVersion::MINECRAFT_1_16_2,
    MinecraftProtocolVersion::MINECRAFT_1_16_3, MinecraftProtocolVersion::MINECRAFT_1_16_4, MinecraftProtocolVersion::MINECRAFT_1_17,
    MinecraftProtocolVersion::MINECRAFT_1_17_1, MinecraftProtocolVersion::MINECRAFT_1_18, MinecraftProtocolVersion::MINECRAFT_1_18_2,
    MinecraftProtocolVersion::MINECRAFT_1_19, MinecraftProtocolVersion::MINECRAFT_1_19_1, MinecraftProtocolVersion::MINECRAFT_1_19_3,
    MinecraftProtocolVersion::MINECRAFT_1_19_4, MinecraftProtocolVersion::MINECRAFT_1_20});

  GlobalPos::GlobalPos(std::string  dimension, const Position& position) : dimension(std::move(dimension)), position(position) {
  }
  const std::string& GlobalPos::GetDimension() const {
    return dimension;
  }
  void GlobalPos::SetDimension(const std::string& newDimension) {
    GlobalPos::dimension = newDimension;
  }
  const Position& GlobalPos::GetPosition() const {
    return position;
  }
  void GlobalPos::SetPosition(const Position& newPosition) {
    GlobalPos::position = newPosition;
  }
}