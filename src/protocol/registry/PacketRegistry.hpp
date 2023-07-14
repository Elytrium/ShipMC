#pragma once

#include "ShipNet/protocol/packet/Packet.hpp"
#include "ShipNet/protocol/registry/VersionedRegistry.hpp"
#include <functional>
#include <vector>

namespace Ship {

  class DirectionRegistry : public VersionedRegistry {
   public:
    DirectionRegistry();

    Errorable<uint32_t> GetIDByPacket(const ProtocolVersion* version, const Packet& packet) const;
  };

  enum PacketDirection {
    CLIENTBOUND,
    SERVERBOUND
  };

  class PacketRegistry {
   private:
    const DirectionRegistry* clientboundRegistry;
    const DirectionRegistry* serverboundRegistry;

   public:
    ~PacketRegistry() {
      delete clientboundRegistry;
      delete serverboundRegistry;
    }

    PacketRegistry(const DirectionRegistry* clientbound_registry, const DirectionRegistry* serverbound_registry);

    [[nodiscard]] const DirectionRegistry* GetRegistry(PacketDirection direction) const;

    [[nodiscard]] const DirectionRegistry* GetClientboundRegistry() const;
    [[nodiscard]] const DirectionRegistry* GetServerboundRegistry() const;
  };
}