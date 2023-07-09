#pragma once
#include <utility>

#include "../client/Client.hpp"
#include "../../../protocol/data/client/LoginClient.hpp"
#include "../../../protocol/packet/status/StatusPing.hpp"
#include "../../../protocol/packet/status/StatusRequest.hpp"

namespace Ship {
  class StatusPacketHandler : public PacketHandler {
   private:
    LoginClient client;

   public:
    explicit StatusPacketHandler(LoginClient client) : client(std::move(client)) {
    }

    static void Init();
    static inline const uint32_t HANDLER_ORDINAL = OrdinalRegistry::PacketHandlerRegistry.RegisterOrdinal();

    inline bool OnStatusRequest(Connection* connection, const StatusRequest& statusRequest);
    inline bool OnStatusPing(Connection* connection, const StatusPing& statusRequest);

    uint32_t GetOrdinal() const override {
      return HANDLER_ORDINAL;
    }
  };

  class ConnectPacketHandler : public PacketHandler {
   private:
    Client client;

   public:
    explicit ConnectPacketHandler(LoginClient client) : client(Client(std::move(client))) {
    }

    explicit ConnectPacketHandler(Client client) : client(std::move(client)) {
    }

    static void Init();
    static inline const uint32_t HANDLER_ORDINAL = OrdinalRegistry::PacketHandlerRegistry.RegisterOrdinal();

    uint32_t GetOrdinal() const override {
      return HANDLER_ORDINAL;
    }
  };

  class ProxyPacketHandler {
   public:
    static void Init() {
      StatusPacketHandler::Init();
      ConnectPacketHandler::Init();
    }
  };
}
