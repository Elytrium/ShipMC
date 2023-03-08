#pragma once

#include "../Protocol.hpp"
#include "../packets/Packet.hpp"
#include "../registry/PacketRegistry.hpp"
#include <functional>

#define SetPacketCallback(handlerClass, packetClass, callback)                                                                                   \
  SetPointerCallback(                                                                                                                            \
    handlerClass::HANDLER_ORDINAL, packetClass::PACKET_ORDINAL, [](PacketHandler* handlerPtr, void* connectionPtr, const PacketHolder& holder) { \
      ByteBuffer* buffer = holder.GetCurrentBuffer();                                                                                            \
      uint32_t oldReadableBytes = buffer->GetReadableBytes();                                                                                    \
      packetClass pkt = packetClass(holder.GetVersion(), buffer);                                                                                \
                                                                                                                                                 \
      if (oldReadableBytes - buffer->GetReadableBytes() != holder.GetExpectedSize()) {                                                           \
        throw InvalidArgumentException("Invalid packet size, expected: ", holder.GetExpectedSize());                                             \
      }                                                                                                                                          \
                                                                                                                                                 \
      Connection* connection = (Connection*) connectionPtr;                                                                                      \
      handlerClass* handler = (handlerClass*) handlerPtr;                                                                                        \
      return handler->callback(connection, pkt);                                                                                                 \
    })

namespace Ship {
  class PacketHandler {
   private:
    static std::vector<std::vector<std::function<bool(PacketHandler*, void*, const PacketHolder&)>>> callbacks;

   public:
    virtual ~PacketHandler() = default;

    bool Handle(PacketHandler* handler_ptr, void* connection, const PacketHolder& packet);
    bool HasCallback(uint32_t ordinal);

    virtual uint32_t GetOrdinal() const = 0;

    static void SetPointerCallback(
      uint32_t handler_ordinal, uint32_t packet_ordinal, std::function<bool(PacketHandler*, void*, const PacketHolder&)> callback);
  };
} // namespace Ship
