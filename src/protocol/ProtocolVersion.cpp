#include "Protocol.hpp"
#include <utility>

namespace Ship {

  ProtocolVersion::ProtocolVersion() : ordinal(UINT32_MAX), protocolID(UINT32_MAX), displayVersion("Unknown") {
  }

  const ProtocolVersion ProtocolVersion::UNKNOWN = ProtocolVersion();
  const ProtocolVersion ProtocolVersion::MINECRAFT_1_12_2 = ProtocolVersion(0, 340, "1.12.2");
  const ProtocolVersion ProtocolVersion::MINECRAFT_1_13 = ProtocolVersion(1, 393, "1.13");
  const ProtocolVersion ProtocolVersion::MINECRAFT_1_13_1 = ProtocolVersion(2, 401, "1.13.1");
  const ProtocolVersion ProtocolVersion::MINECRAFT_1_13_2 = ProtocolVersion(3, 404, "1.13.2");
  const ProtocolVersion ProtocolVersion::MINECRAFT_1_14 = ProtocolVersion(4, 477, "1.14");
  const ProtocolVersion ProtocolVersion::MINECRAFT_1_14_1 = ProtocolVersion(5, 480, "1.14.1");
  const ProtocolVersion ProtocolVersion::MINECRAFT_1_14_2 = ProtocolVersion(6, 485, "1.14.2");
  const ProtocolVersion ProtocolVersion::MINECRAFT_1_14_3 = ProtocolVersion(7, 490, "1.14.3");
  const ProtocolVersion ProtocolVersion::MINECRAFT_1_14_4 = ProtocolVersion(8, 498, "1.14.4");
  const ProtocolVersion ProtocolVersion::MINECRAFT_1_15 = ProtocolVersion(9, 573, "1.15");
  const ProtocolVersion ProtocolVersion::MINECRAFT_1_15_1 = ProtocolVersion(10, 575, "1.15.1");
  const ProtocolVersion ProtocolVersion::MINECRAFT_1_15_2 = ProtocolVersion(11, 578, "1.15.2");
  const ProtocolVersion ProtocolVersion::MINECRAFT_1_16_2 = ProtocolVersion(12, 751, "1.16.2");
  const ProtocolVersion ProtocolVersion::MINECRAFT_1_16_3 = ProtocolVersion(13, 753, "1.16.3");
  const ProtocolVersion ProtocolVersion::MINECRAFT_1_16_4 = ProtocolVersion(14, 754, "1.16.4 - 1.16.5");
  const ProtocolVersion ProtocolVersion::MINECRAFT_1_17 = ProtocolVersion(15, 755, "1.17");
  const ProtocolVersion ProtocolVersion::MINECRAFT_1_17_1 = ProtocolVersion(16, 756, "1.17.1");
  const ProtocolVersion ProtocolVersion::MINECRAFT_1_18 = ProtocolVersion(17, 757, "1.18 - 1.18.1");
  const ProtocolVersion ProtocolVersion::MINECRAFT_1_18_2 = ProtocolVersion(18, 758, "1.18.2");
  const ProtocolVersion ProtocolVersion::MINECRAFT_1_19 = ProtocolVersion(19, 759, "1.19");
  const ProtocolVersion ProtocolVersion::MINECRAFT_1_19_1 = ProtocolVersion(20, 760, "1.19.1 - 1.19.2");
  const ProtocolVersion ProtocolVersion::MINECRAFT_1_19_3 = ProtocolVersion(21, 761, "1.19.3");

  const ProtocolVersion ProtocolVersion::MINIMUM_VERSION = ProtocolVersion::MINECRAFT_1_12_2;
  const ProtocolVersion ProtocolVersion::MAXIMUM_VERSION = ProtocolVersion::MINECRAFT_1_19_3;

  const uint32_t MINIMUM_PROTOCOL_VERSION = ProtocolVersion::MINIMUM_VERSION.GetProtocolID();
  const uint32_t MAXIMUM_PROTOCOL_VERSION = ProtocolVersion::MAXIMUM_VERSION.GetProtocolID();
  const uint32_t MINIMUM_ORDINAL = ProtocolVersion::MINIMUM_VERSION.GetOrdinal();
  const uint32_t MAXIMUM_ORDINAL = ProtocolVersion::MAXIMUM_VERSION.GetOrdinal();

  ProtocolVersion ordinalToVersionMap[] = {ProtocolVersion::MINECRAFT_1_12_2, ProtocolVersion::MINECRAFT_1_13, ProtocolVersion::MINECRAFT_1_13_1,
    ProtocolVersion::MINECRAFT_1_13_2, ProtocolVersion::MINECRAFT_1_14, ProtocolVersion::MINECRAFT_1_14_1, ProtocolVersion::MINECRAFT_1_14_2,
    ProtocolVersion::MINECRAFT_1_14_3, ProtocolVersion::MINECRAFT_1_14_4, ProtocolVersion::MINECRAFT_1_15, ProtocolVersion::MINECRAFT_1_15_1,
    ProtocolVersion::MINECRAFT_1_15_2, ProtocolVersion::MINECRAFT_1_16_2, ProtocolVersion::MINECRAFT_1_16_3, ProtocolVersion::MINECRAFT_1_16_4,
    ProtocolVersion::MINECRAFT_1_17, ProtocolVersion::MINECRAFT_1_17_1, ProtocolVersion::MINECRAFT_1_18, ProtocolVersion::MINECRAFT_1_18_2,
    ProtocolVersion::MINECRAFT_1_19, ProtocolVersion::MINECRAFT_1_19_1, ProtocolVersion::MINECRAFT_1_19_3, ProtocolVersion::UNKNOWN};
  ProtocolVersion* idToVersionMap;

  ProtocolVersion::ProtocolVersion(uint32_t ordinal, uint32_t protocol_id, std::string display_version)
    : ordinal(ordinal), protocolID(protocol_id), displayVersion(std::move(display_version)) {
  }

  void ProtocolVersion::Init() {
    idToVersionMap = new ProtocolVersion[MAXIMUM_PROTOCOL_VERSION + 1];
    for (uint32_t i = MINIMUM_ORDINAL; i <= MAXIMUM_ORDINAL; ++i) {
      ProtocolVersion version = ordinalToVersionMap[i];
      idToVersionMap[version.protocolID] = version;
    }
  }

  const ProtocolVersion* ProtocolVersion::FromProtocolID(uint32_t protocol_id) {
    if (protocol_id < MINIMUM_PROTOCOL_VERSION || protocol_id > MAXIMUM_PROTOCOL_VERSION) {
      return &ProtocolVersion::UNKNOWN;
    } else {
      return idToVersionMap + protocol_id;
    }
  }

  const ProtocolVersion* ProtocolVersion::FromOrdinal(uint32_t ordinal) {
    if (ordinal < MINIMUM_ORDINAL || ordinal > MAXIMUM_ORDINAL) {
      return &ProtocolVersion::UNKNOWN;
    } else {
      return ordinalToVersionMap + ordinal;
    }
  }

  uint32_t ProtocolVersion::GetOrdinal() const {
    return ordinal;
  }

  uint32_t ProtocolVersion::GetProtocolID() const {
    return protocolID;
  }

  const std::string& ProtocolVersion::GetDisplayVersion() const {
    return displayVersion;
  }
}
