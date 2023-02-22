#include "PacketRegistry.hpp"

namespace Ship {
  DirectionRegistry::DirectionRegistry()
    : ConstructorRegistry<Packet>({
      ProtocolVersion::MINECRAFT_1_12_2,
      ProtocolVersion::MINECRAFT_1_13,
      ProtocolVersion::MINECRAFT_1_14,
      ProtocolVersion::MINECRAFT_1_15,
      ProtocolVersion::MINECRAFT_1_16_2,
      ProtocolVersion::MINECRAFT_1_16_2,
      ProtocolVersion::MINECRAFT_1_17,
      ProtocolVersion::MINECRAFT_1_18,
      ProtocolVersion::MINECRAFT_1_18_2,
      ProtocolVersion::MINECRAFT_1_19,
      ProtocolVersion::MINECRAFT_1_19_1,
      ProtocolVersion::MINECRAFT_1_19_3,
    }) {
  }

  void DirectionRegistry::RegisterPacketConstructor(uint32_t ordinal, const std::function<Packet*()>& constructor) {
    ResizeVectorAndSet(ordinalToPacketMap, ordinal, constructor);
  }

  Packet* DirectionRegistry::GetPacketByID(const ProtocolVersion* version, uint32_t id) const {
    return (Packet*) GetObjectByID(version, id);
  }

  uint32_t DirectionRegistry::GetIDByPacket(const ProtocolVersion* version, Packet* packet) const {
    return GetIDByOrdinal(version, packet->GetOrdinal());
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
