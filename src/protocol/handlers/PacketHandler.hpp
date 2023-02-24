#pragma once

#include "../Protocol.hpp"
#include "../packets/Packet.hpp"
#include "../registry/PacketRegistry.hpp"
#include <functional>

#define SetPacketCallback(handlerClass, packetClass, callback)                                                                                         \
  SetPointerCallback(handlerClass::HANDLER_ORDINAL, packetClass::PACKET_ORDINAL, [](PacketHandler* handlerPtr, void* connectionPtr, Packet* dataPtr) { \
    packetClass* pktPtr = (packetClass*) dataPtr;                                                                                                      \
    Connection* connection = (Connection*) connectionPtr;                                                                                              \
    handlerClass* handler = (handlerClass*) handlerPtr;                                                                                                \
    return handler->callback(connection, pktPtr);                                                                                                      \
  })

namespace Ship {
  class PacketHandler {
   private:
    static std::vector<std::vector<std::function<bool(PacketHandler*, void*, Packet*)>>> callbacks;

   public:
    virtual ~PacketHandler() = default;

    bool Handle(PacketHandler* handler_ptr, void* connection, Packet* packet);
    bool HasCallback(uint32_t ordinal);

    virtual uint32_t GetOrdinal() = 0;

    static void SetPointerCallback(uint32_t handler_ordinal, uint32_t packet_ordinal, std::function<bool(PacketHandler*, void*, Packet*)> callback);
  };
} // namespace Ship
