#pragma once

#include "../Protocol.hpp"
#include "../packets/Packet.hpp"
#include <functional>

namespace Ship {
  class PacketHandler {
   private:
    std::vector<std::function<bool(const ProtocolVersion*, Packet*)>> callbacks;

   public:
    virtual ~PacketHandler() = default;

    bool Handle(const ProtocolVersion* version, Packet* packet);
    void SetCallback(uint32_t ordinal, const std::function<bool(const ProtocolVersion*, Packet*)>& callback);
    bool HasCallback(uint32_t ordinal);

    virtual uint32_t GetOrdinal() = 0;
  };
} // namespace Ship
