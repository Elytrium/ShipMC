#pragma once

#include "../packets/Packet.hpp"
#include "ConstructorRegistry.hpp"
#include "VersionRegistry.hpp"
#include "VersionedRegistry.hpp"
#include <functional>
#include <vector>

namespace Ship {

  class DirectionRegistry : public ConstructorRegistry<Packet> {
   public:
    DirectionRegistry();

    void RegisterPacketConstructor(uint32_t ordinal, const std::function<Packet*()>& constructor);
    Packet* GetPacketByID(const ProtocolVersion* version, uint32_t ordinal) const;
    uint32_t GetIDByPacket(const ProtocolVersion* version, Packet* packet) const;
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