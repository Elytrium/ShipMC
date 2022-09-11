#include "PacketRegistry.hpp"
#include "../../utils/exceptions/InvalidArgumentException.hpp"
#include "../packets/Packet.hpp"
#include <utility>

namespace Ship {

  template<typename T>
  inline void ResizeVectorAndSet(std::vector<T>& vector, uint32_t at, T value) {
    if (at >= vector.size()) {
      vector.resize(at + 8);
    }

    vector.at(at) = value;
  }

  DirectionRegistry::DirectionRegistry(VersionRegistry* version_registry) : versionRegistry(version_registry) {
  }

  VersionRegistry* DirectionRegistry::NewVersionRegistry() {
    return new VersionRegistry[ProtocolVersion::MAXIMUM_VERSION.GetPacketIDOrdinal() + 1];
  }

  Packet* DirectionRegistry::GetPacketByID(const ProtocolVersion* version, uint32_t id) const {
    uint32_t ordinal = versionRegistry[version->GetPacketIDOrdinal()].GetOrdinalByID(id);
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

  uint32_t VersionRegistry::GetOrdinalByID(uint32_t id) const {
    if (id >= idToOrdinalMap.size()) {
      return UINT32_MAX;
    }

    return idToOrdinalMap[id];
  }

  uint32_t VersionRegistry::GetIDByOrdinal(uint32_t ordinal) const {
    if (ordinal >= ordinalToIDMap.size()) {
      throw InvalidArgumentException("Invalid (unregistered) packet: ordinal ", ordinal);
    }

    return ordinalToIDMap[ordinal];
  }

  void VersionRegistry::RegisterPacket(uint32_t ordinal, uint32_t id) {
    ResizeVectorAndSet(ordinalToIDMap, ordinal, id);
    ResizeVectorAndSet(idToOrdinalMap, id, ordinal);
  }

  PacketRegistry::PacketRegistry(const DirectionRegistry&  clientbound_registry, const DirectionRegistry& serverbound_registry)
    : clientboundRegistry(clientbound_registry), serverboundRegistry(serverbound_registry) {
  }

  const DirectionRegistry* PacketRegistry::GetRegistry(PacketDirection direction) const {
    switch (direction) {
      case CLIENTBOUND:
        return &clientboundRegistry;
      case SERVERBOUND:
        return &serverboundRegistry;
      default:
        return nullptr;
    }
  }

  const DirectionRegistry* PacketRegistry::GetClientboundRegistry() const {
    return &clientboundRegistry;
  }

  const DirectionRegistry* PacketRegistry::GetServerboundRegistry() const {
    return &serverboundRegistry;
  }
}
