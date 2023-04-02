#pragma once

#include "../../../network/Connection.hpp"
#include "../../../network/SocketAddress.hpp"
#include "../../../network/pipe/minecraft/MinecraftPipe.hpp"
#include "../../packets/login/LoginDisconnect.hpp"

namespace Ship {
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

      void SetPlayerKey() {
        playerKey = nullptr;
      }

      void DisconnectWithReason(std::string reason) { // TODO: component
        connection->WriteAndFlush(LoginDisconnect(std::move(reason)));
      }
    };
} // Ship
