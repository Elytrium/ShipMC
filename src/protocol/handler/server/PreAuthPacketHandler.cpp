#include "../../../../lib/ShipNet/src/network/Connection.hpp"
#include "../../../utils/ShipUtils.hpp"
#include "../../packet/login/EncryptionRequest.hpp"
#include "ServerPacketHandler.hpp"

namespace Ship {
  void PreAuthPacketHandler::Init() {
    SetPacketCallback(PreAuthPacketHandler, LoginStart, OnLoginStart);
    SetPacketCallback(PreAuthPacketHandler, EncryptionResponse, OnEncryptionResponse);
    SetPacketCallback(PreAuthPacketHandler, LoginPluginResponse, OnLoginPluginResponse);
  }

  inline Errorable<bool> PreAuthPacketHandler::OnLoginStart(Connection* connection, const LoginStart& loginStart) {
    AssertState(LoginState::LOGIN_PACKET_EXPECTED);
    currentState = LoginState::LOGIN_PACKET_RECEIVED;
    if (loginStart.HasSigData()) {
      if (loginStart.GetExpiry() > ShipUtils::GetCurrentMillis()) {
        client.DisconnectWithReason("multiplayer.disconnect.invalid_public_key_signature"); // TODO: translatable
        return SuccessErrorable<bool>(true);
      }

      bool isKeyValid = true; // TODO: check if key is valid

      if (!isKeyValid) {
        client.DisconnectWithReason("multiplayer.disconnect.invalid_public_key"); // TODO: translatable
        return SuccessErrorable<bool>(true);
      }
    } else if (client.GetMinecraftPipe()->GetProtocolVersion() >= &MinecraftProtocolVersion::MINECRAFT_1_19
               && client.GetMinecraftPipe()->GetProtocolVersion() < &MinecraftProtocolVersion::MINECRAFT_1_19_3 /*&& forceKeyAuthentication*/) {
      client.DisconnectWithReason("multiplayer.disconnect.missing_public_key"); // TODO: translatable
      return SuccessErrorable<bool>(true);
    }

    client.SetPlayerKey();
    // TODO: event
    [&]() {
      if (!client.IsActive()) {
        // The client was disconnected
        return;
      }

      // TODO: plugin messages queue
      [&]() {
        if (!client.IsActive()) {
          // The client was disconnected
          return;
        }

        client.GetConnection()->GetEventLoop()->Execute([&]() {
          if (/*!event.IsForceOfflineMode() && (isOnlineMode || event.IsOnlineModeAllowed())*/ false) {
            EncryptionRequest request = EncryptionRequest("", {}, {}); // TODO: public key / rnd verify token
            verifyToken = request.GetVerifyToken()->ReadInt(); // TODO: check buffer size
            client.GetConnection()->Write(request);
            currentState = LoginState::ENCRYPTION_REQUEST_SENT;
          } else {
            client.GetConnection()->ReplaceMainPacketHandler(new PostAuthPacketHandler(
              client, GameProfile::ForOfflinePlayer(loginStart.GetUsername()), std::function<PacketHandler*(const LoginClient&)>()));
          }
        });
      }();
    }();

    return SuccessErrorable<bool>(true);
  }

  inline Errorable<bool> PreAuthPacketHandler::OnEncryptionResponse(Connection* connection, const EncryptionResponse& serverLogin) {
    AssertState(LoginState::ENCRYPTION_REQUEST_SENT);
    currentState = LoginState::ENCRYPTION_RESPONSE_RECEIVED;

    // TODO: verify and replace main packet handler

    return SuccessErrorable<bool>(true);
  }

  inline Errorable<bool> PreAuthPacketHandler::OnLoginPluginResponse(Connection* connection, const LoginPluginResponse& serverLogin) {
    // TODO: handle plugin messages in loginClient
    return SuccessErrorable<bool>(true);
  }

  void PreAuthPacketHandler::AssertState(LoginState expected) {
    if (currentState != expected) {
      delete client.GetConnection();
      // TODO: add debug
    }
  }
}