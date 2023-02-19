#include "PacketRegistry.hpp"

namespace Ship {
  void DirectionRegistry::RegisterPacketConstructor(uint32_t ordinal, const std::function<Packet*()>& constructor) {
    ResizeVectorAndSet(ordinalToPacketMap, ordinal, constructor);
  }

  Packet* DirectionRegistry::GetPacketByID(const ProtocolVersion* version, uint32_t id) {
    return (Packet*) GetObjectByID(version, id);
  }

  uint32_t DirectionRegistry::GetIDByPacket(const ProtocolVersion* version, Packet* packet) {
    return GetIDByOrdinal(version, packet->GetOrdinal());
  }

  uint32_t DirectionRegistry::VersionToOrdinal(const ProtocolVersion* version) {
    return version->GetPacketIDOrdinal();
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
