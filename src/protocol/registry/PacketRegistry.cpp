#include "PacketRegistry.hpp"
#include "../MinecraftProtocol.hpp"

namespace Ship {
  DirectionRegistry::DirectionRegistry()
    : VersionedRegistry(MinecraftProtocolVersion::VERSIONS, {
      MinecraftProtocolVersion::MINECRAFT_1_12_2,
      MinecraftProtocolVersion::MINECRAFT_1_13,
      MinecraftProtocolVersion::MINECRAFT_1_14,
      MinecraftProtocolVersion::MINECRAFT_1_15,
      MinecraftProtocolVersion::MINECRAFT_1_16_2,
      MinecraftProtocolVersion::MINECRAFT_1_17,
      MinecraftProtocolVersion::MINECRAFT_1_18,
      MinecraftProtocolVersion::MINECRAFT_1_18_2,
      MinecraftProtocolVersion::MINECRAFT_1_19,
      MinecraftProtocolVersion::MINECRAFT_1_19_1,
      MinecraftProtocolVersion::MINECRAFT_1_19_3,
    }) {
  }

  uint32_t DirectionRegistry::GetIDByPacket(const ProtocolVersion* version, const Packet& packet) const {
    return GetIDByOrdinal(version, packet.GetOrdinal());
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
