#pragma once

#include "../Protocol.hpp"
#include "../packets/Packet.hpp"
#include <functional>
#include <vector>

namespace Ship {

  class VersionRegistry {
   private:
    std::vector<uint32_t> ordinalToIDMap = std::vector<uint32_t>(128);
    std::vector<uint32_t> idToOrdinalMap = std::vector<uint32_t>(128);

   public:
    void RegisterPacket(uint32_t ordinal, uint32_t id);
    [[nodiscard]] uint32_t GetOrdinalByID(uint32_t id) const;
    [[nodiscard]] uint32_t GetIDByOrdinal(uint32_t ordinal) const;
  };

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