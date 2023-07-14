#pragma once

#include "ShipNet/network/Connection.hpp"
#include "ShipNet/network/SocketAddress.hpp"
#include "../../../network/pipe/MinecraftPipe.hpp"
#include "../../../protocol/data/client/LoginClient.hpp"
#include "../../../protocol/packet/play/Disconnect.hpp"
#include <utility>

namespace Ship {
  class Client {
   private:
    bool active = true;
    Connection* connection;
    MinecraftFramedBytePacketPipe* minecraftPipe;
    SocketAddress address;

   public:
    Client(Connection* connection, MinecraftFramedBytePacketPipe* minecraftPipe, SocketAddress address)
      : connection(connection), minecraftPipe(minecraftPipe), address(std::move(address)) {
      connection->SetOnClose([&](){
        active = false;
      });
    }

    explicit Client(const LoginClient& client) : connection(client.GetConnection()), minecraftPipe(client.GetMinecraftPipe()), address(client.GetAddress()) {}

    [[nodiscard]] Connection* GetConnection() const {
      return connection;
    }

    [[nodiscard]] MinecraftFramedBytePacketPipe* GetMinecraftPipe() const {
      return minecraftPipe;
    }

    [[nodiscard]] const SocketAddress& GetAddress() const {
      return address;
    }

    [[nodiscard]] bool IsActive() const {
      return active;
    }

    void DisconnectWithReason(std::string reason) { // TODO: component
      connection->WriteAndFlush(Disconnect(std::move(reason)));
    }
  };
}
