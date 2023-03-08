#pragma once

#include "../../../network/Connection.hpp"
#include "../../../network/SocketAddress.hpp"
#include "../../../network/pipe/minecraft/MinecraftPipe.hpp"
#include "../../../protocol/packets/play/Disconnect.hpp"
#include <utility>

namespace Ship {
  class Client {
   private:
    Connection* connection;
    MinecraftFramedBytePacketPipe* minecraftPipe;
    SocketAddress address;

   public:
    Client(Connection* connection, MinecraftFramedBytePacketPipe* minecraftPipe, SocketAddress address)
      : connection(connection), minecraftPipe(minecraftPipe), address(std::move(address)) {
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

    void DisconnectWithReason(std::string reason) { // TODO: component
      connection->WriteAndFlush(Disconnect(std::move(reason)));
    }
  };
} // Ship
