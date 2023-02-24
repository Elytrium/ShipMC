#pragma once

#include "../../../network/SocketAddress.hpp"
#include "../../../network/pipe/minecraft/MinecraftPipe.hpp"
#include <utility>

namespace Ship {
  class Client {
   private:
    MinecraftFramedBytePacketPipe* minecraftPipe;
    SocketAddress address;
   public:
    Client(MinecraftFramedBytePacketPipe* minecraftPipe, SocketAddress address) : minecraftPipe(minecraftPipe), address(std::move(address)) {}

    MinecraftFramedBytePacketPipe* GetMinecraftPipe() const {
      return minecraftPipe;
    }

    const SocketAddress& GetAddress() const {
      return address;
    }
  };
} // Ship
