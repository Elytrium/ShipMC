#include "../../../network/Connection.hpp"
#include "../../../utils/ShipUtils.hpp"
#include "ProxyPacketHandler.hpp"

namespace Ship {
  void PreAuthPacketHandler::Init() {
    SetPacketCallback(PreAuthPacketHandler, LoginStart, OnLoginStart);
  }

  inline bool PreAuthPacketHandler::OnLoginStart(Connection* connection, const LoginStart& loginStart) {
    AssertState(LoginState::LOGIN_PACKET_EXPECTED);
    currentState = LoginState::LOGIN_PACKET_RECEIVED;
    if (loginStart.HasSigData()) {
      if (loginStart.GetExpiry() > ShipUtils::GetCurrentMillis()) {
        client.DisconnectWithReason(""); // TODO translatable: multiplayer.disconnect.invalid_public_key_signature
      }
    }

    return true;
  }

  void PreAuthPacketHandler::AssertState(LoginState expected) {
    if (currentState != expected) {
      delete client.GetConnection();
      // TODO: add debug
    }
  }
} // Ship