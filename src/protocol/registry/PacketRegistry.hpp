#pragma once

#include "../packets/Packet.hpp"
#include "VersionRegistry.hpp"
#include <functional>
#include <vector>

namespace Ship {

  class DirectionRegistry {
   private:
    std::vector<std::function<Packet*()>> ordinalToPacketMap;
    const VersionRegistry* versionRegistry = NewVersionRegistry();

   public:
    static VersionRegistry* NewVersionRegistry();

    ~DirectionRegistry() {
      delete[] versionRegistry;
    }

    explicit DirectionRegistry(VersionRegistry* version_registry);

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
    const DirectionRegistry clientboundRegistry;
    const DirectionRegistry serverboundRegistry;

   public:
    PacketRegistry(const DirectionRegistry& clientbound_registry, const DirectionRegistry& serverbound_registry);

    [[nodiscard]] const DirectionRegistry* GetRegistry(PacketDirection direction) const;

    [[nodiscard]] const DirectionRegistry* GetClientboundRegistry() const;
    [[nodiscard]] const DirectionRegistry* GetServerboundRegistry() const;
  };
}