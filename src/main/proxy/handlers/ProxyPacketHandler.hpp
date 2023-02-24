#pragma once
#include "../../../network/Connection.hpp"
#include "../../../protocol/handlers/PacketHandler.hpp"
#include "../../../protocol/packets/handshake/Handshake.hpp"
#include "../../../protocol/packets/status/StatusPing.hpp"
#include "../../../protocol/packets/status/StatusRequest.hpp"
#include "../client/Client.hpp"

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
   private:
    Client client;

   public:
    explicit StatusPacketHandler(Client client) : client(std::move(client)) {
    }

    static void Init();
    static inline const uint32_t HANDLER_ORDINAL = OrdinalRegistry::PacketHandlerRegistry.RegisterOrdinal();

    static inline bool OnStatusRequest(Connection* connection, StatusRequest* statusRequest);
    static inline bool OnStatusPing(Connection* connection, StatusPing* statusRequest);

    uint32_t GetOrdinal() override {
      return HANDLER_ORDINAL;
    }
  };

  class PreAuthPacketHandler : public PacketHandler {
   private:
    Client client;

   public:
    explicit PreAuthPacketHandler(Client client) : client(std::move(client)) {
    }

    static void Init();
    static inline const uint32_t HANDLER_ORDINAL = OrdinalRegistry::PacketHandlerRegistry.RegisterOrdinal();

    uint32_t GetOrdinal() override {
      return HANDLER_ORDINAL;
    }
  };

  class PostAuthPacketHandler : public PacketHandler {
   private:
    Client client;

   public:
    explicit PostAuthPacketHandler(Client client) : client(std::move(client)) {
    }

    static void Init();
    static inline const uint32_t HANDLER_ORDINAL = OrdinalRegistry::PacketHandlerRegistry.RegisterOrdinal();

    uint32_t GetOrdinal() override {
      return HANDLER_ORDINAL;
    }
  };

  class ConnectPacketHandler : public PacketHandler {
   private:
    Client client;

   public:
    explicit ConnectPacketHandler(Client client) : client(std::move(client)) {
    }

    static void Init();
    static inline const uint32_t HANDLER_ORDINAL = OrdinalRegistry::PacketHandlerRegistry.RegisterOrdinal();

    uint32_t GetOrdinal() override {
      return HANDLER_ORDINAL;
    }
  };

  class ProxyPacketHandler {
   public:
    static void Init() {
      HandshakePacketHandler::Init();
      StatusPacketHandler::Init();
      PreAuthPacketHandler::Init();
      PostAuthPacketHandler::Init();
      ConnectPacketHandler::Init();
    }
  };
} // Ship
