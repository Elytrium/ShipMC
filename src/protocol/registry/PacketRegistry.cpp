#include "PacketRegistry.hpp"

namespace Ship {

  DirectionRegistry::DirectionRegistry(VersionRegistry* version_registry) : versionRegistry(version_registry) {
  }

  VersionRegistry* DirectionRegistry::NewVersionRegistry() {
    return new VersionRegistry[ProtocolVersion::MAXIMUM_VERSION.GetPacketIDOrdinal() + 1];
  }

  void DirectionRegistry::RegisterPacketConstructor(uint32_t ordinal, const std::function<Packet*()>& constructor) {
    ResizeVectorAndSet(ordinalToPacketMap, ordinal, constructor);
  }

  Packet* DirectionRegistry::GetPacketByID(const ProtocolVersion* version, uint32_t id) const {
    uint32_t packetOrdinal;
    if (version == &ProtocolVersion::UNKNOWN) {
      packetOrdinal = 0;
    } else {
      packetOrdinal = version->GetPacketIDOrdinal();
    }

    uint32_t ordinal = versionRegistry[packetOrdinal].GetOrdinalByID(id);
    if (ordinal >= ordinalToPacketMap.size()) {
      return nullptr;
    }

    std::function<Packet*()> constructor = ordinalToPacketMap[ordinal];
    if (constructor) {
      return constructor();
    } else {
      return nullptr;
    }
  }

  uint32_t DirectionRegistry::GetIDByPacket(const ProtocolVersion* version, Packet* packet) const {
    return versionRegistry[version->GetPacketIDOrdinal()].GetIDByOrdinal(packet->GetOrdinal());
  }

  PacketRegistry::PacketRegistry(const DirectionRegistry* clientbound_registry, const DirectionRegistry* serverbound_registry)
    : clientboundRegistry(clientbound_registry), serverboundRegistry(serverbound_registry) {
  }

  const DirectionRegistry* PacketRegistry::GetRegistry(PacketDirection direction) const {
    switch (direction) {
      case CLIENTBOUND:
        return clientboundRegistry;
      case SERVERBOUND:
        return serverboundRegistry;
      default:
        return nullptr;
    }
  }

  const DirectionRegistry* PacketRegistry::GetClientboundRegistry() const {
    return clientboundRegistry;
  }

  const DirectionRegistry* PacketRegistry::GetServerboundRegistry() const {
    return serverboundRegistry;
  }
}
