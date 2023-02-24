#pragma once
#include "../../../network/Connection.hpp"
#include "../../../protocol/handlers/PacketHandler.hpp"
#include "../../../protocol/packets/handshake/Handshake.hpp"
#include "../../../protocol/packets/status/StatusPing.hpp"
#include "../../../protocol/packets/status/StatusRequest.hpp"

namespace Ship {
  class HandshakePacketHandler : public PacketHandler {
   public:
    static void Init();
    static inline const uint32_t HANDLER_ORDINAL = OrdinalRegistry::PacketHandlerRegistry.RegisterOrdinal();

    static inline bool OnHandshake(Connection* connection, Handshake* handshake);

    uint32_t GetOrdinal() override {
      return HANDLER_ORDINAL;
    }
  };

  class StatusPacketHandler : public PacketHandler {
   public:
    static void Init();
    static inline const uint32_t HANDLER_ORDINAL = OrdinalRegistry::PacketHandlerRegistry.RegisterOrdinal();

    static inline bool OnStatusRequest(Connection* connection, StatusRequest* statusRequest);
    static inline bool OnStatusPing(Connection* connection, StatusPing* statusRequest);

    uint32_t GetOrdinal() override {
      return HANDLER_ORDINAL;
    }
  };

  class ProxyPacketHandler {
   public:
    static void Init() {
      HandshakePacketHandler::Init();
      StatusPacketHandler::Init();
    }
  };
} // Ship
