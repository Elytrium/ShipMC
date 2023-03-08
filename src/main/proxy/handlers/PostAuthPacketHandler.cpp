#include "../../../network/Connection.hpp"
#include "ProxyPacketHandler.hpp"

namespace Ship {
  void PostAuthPacketHandler::Init() {
    
  }

  GameProfile* PostAuthPacketHandler::GetProfile() const {
    return profile;
  }
} // Ship