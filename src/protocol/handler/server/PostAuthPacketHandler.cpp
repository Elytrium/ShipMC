#include "ShipNet/network/Connection.hpp"
#include "../../data/client/LoginClient.hpp"
#include "../../data/profile/GameProfile.hpp"
#include "ServerPacketHandler.hpp"

namespace Ship {
  void PostAuthPacketHandler::Init() {
  }

  GameProfile *PostAuthPacketHandler::GetProfile() const {
    return profile;
  }

  const std::function<PacketHandler *(const LoginClient &)> &PostAuthPacketHandler::GetPlayHandler() const {
    return playHandler;
  }
}