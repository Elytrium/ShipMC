#include "../Protocol.hpp"
#include "../packets/Packet.hpp"
#include "PacketHandler.hpp"

namespace Ship {
  bool PacketHandler::Handle(const ProtocolVersion* version, Packet* packet) {
    uint32_t ordinal = packet->GetOrdinal();
    if (ordinal >= callbacks.size()) {
      return false;
    }

    std::function<bool(const ProtocolVersion*, Packet*)> callback = callbacks[ordinal];
    if (callback) {
      return callback(version, packet);
    } else {
      return false;
    }
  }

  void PacketHandler::SetCallback(uint32_t ordinal, const std::function<bool(const ProtocolVersion*, Packet*)>& callback) {
    if (ordinal > callbacks.size()) {
      callbacks.reserve(ordinal);
    }

    callbacks.at(ordinal) = callback;
  }

  bool PacketHandler::HasCallback(uint32_t ordinal) {
    return ordinal < callbacks.size() && callbacks[ordinal];
  }
}