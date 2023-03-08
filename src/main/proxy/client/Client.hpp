#pragma once

#include "../../../network/Connection.hpp"
#include "../../../network/SocketAddress.hpp"
#include "../../../network/pipe/minecraft/MinecraftPipe.hpp"
#include "../../../protocol/packets/login/LoginDisconnect.hpp"
#include "../../../protocol/packets/play/Disconnect.hpp"
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

    Connection* GetConnection() const {
      return connection;
    }

    MinecraftFramedBytePacketPipe* GetMinecraftPipe() const {
      return minecraftPipe;
    }

    const SocketAddress& GetAddress() const {
      return address;
    }

    bool IsActive() const {
      return active;
    }

    void DisconnectWithReason(std::string reason) { // TODO: component
      connection->WriteAndFlush(Disconnect(std::move(reason)));
    }
  };

  class LoginClient {
   private:
    bool active = true;
    Connection* connection;
    MinecraftFramedBytePacketPipe* minecraftPipe;
    SocketAddress address;
    std::nullptr_t playerKey; // TODO: player key

   public:
    LoginClient(Connection* connection, MinecraftFramedBytePacketPipe* minecraftPipe, SocketAddress address)
      : connection(connection), minecraftPipe(minecraftPipe), address(std::move(address)) {
      connection->SetOnClose([&](){
        active = false;
      });
    }

    Connection* GetConnection() const {
      return connection;
    }

    MinecraftFramedBytePacketPipe* GetMinecraftPipe() const {
      return minecraftPipe;
    }

    const SocketAddress& GetAddress() const {
      return address;
    }

    bool IsActive() const {
      return active;
    }

    void SetPlayerKey() {
      playerKey = nullptr;
    }

    void DisconnectWithReason(std::string reason) { // TODO: component
      connection->WriteAndFlush(LoginDisconnect(std::move(reason)));
    }
  };
} // Ship
