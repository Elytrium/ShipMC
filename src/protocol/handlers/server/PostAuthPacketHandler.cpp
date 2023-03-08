#include "../../../network/Connection.hpp"
#include "ServerPacketHandler.hpp"

namespace Ship {
  void PostAuthPacketHandler::Init() {
    
  }

  GameProfile* PostAuthPacketHandler::GetProfile() const {
    return profile;
  }

  const std::function<PacketHandler *(const LoginClient &)> &PostAuthPacketHandler::GetPlayHandler() const {
    return playHandler;
  }
} // Ship