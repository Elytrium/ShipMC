#pragma once
#include <utility>

#include "../../../main/proxy/client/Client.hpp"
#include "../../../network/Connection.hpp"
#include "../../data/client/LoginClient.hpp"
#include "../../packets/handshake/Handshake.hpp"
#include "../../packets/login/EncryptionResponse.hpp"
#include "../../packets/login/LoginPluginResponse.hpp"
#include "../../packets/login/LoginStart.hpp"
#include "../../packets/status/StatusPing.hpp"
#include "../../packets/status/StatusRequest.hpp"
#include "../PacketHandler.hpp"

namespace Ship {
  enum class LoginState {
    LOGIN_PACKET_EXPECTED,
    LOGIN_PACKET_RECEIVED,
    ENCRYPTION_REQUEST_SENT,
    ENCRYPTION_RESPONSE_RECEIVED
  };

  class ServerHandshakePacketHandler : public PacketHandler {
   private:
    std::function<PacketHandler*(const LoginClient&)> statusHandler;
    std::function<PacketHandler*(const LoginClient&)> playHandler;
   public:
    ServerHandshakePacketHandler(
      const std::function<PacketHandler*(const LoginClient&)>& statusHandler, const std::function<PacketHandler*(const LoginClient&)>& playHandler);

    static void Init();
    static inline const uint32_t HANDLER_ORDINAL = OrdinalRegistry::PacketHandlerRegistry.RegisterOrdinal();

    inline bool OnHandshake(Connection* connection, const Handshake& handshake);

    uint32_t GetOrdinal() const override {
      return HANDLER_ORDINAL;
    }
  };

  class PreAuthPacketHandler : public PacketHandler {
   private:
    LoginClient client;
    LoginState currentState = LoginState::LOGIN_PACKET_EXPECTED;
    uint32_t verifyToken;
    std::function<PacketHandler*(const LoginClient&)> playHandler;

   public:
    PreAuthPacketHandler(LoginClient client, std::function<PacketHandler*(const LoginClient&)> playHandler)
      : client(std::move(client)), playHandler(std::move(playHandler)) {
    }

    static void Init();
    static inline const uint32_t HANDLER_ORDINAL = OrdinalRegistry::PacketHandlerRegistry.RegisterOrdinal();

    inline bool OnLoginStart(Connection* connection, const LoginStart& serverLogin);
    inline bool OnEncryptionResponse(Connection* connection, const EncryptionResponse& serverLogin);
    inline bool OnLoginPluginResponse(Connection* connection, const LoginPluginResponse& serverLogin);
    inline void AssertState(LoginState expected);

    uint32_t GetOrdinal() const override {
      return HANDLER_ORDINAL;
    }
  };

  class PostAuthPacketHandler : public PacketHandler {
   private:
    LoginClient client;
    GameProfile* profile;
    std::function<PacketHandler*(const LoginClient&)> playHandler;

   public:
    PostAuthPacketHandler(LoginClient client, GameProfile* profile, std::function<PacketHandler*(const LoginClient&)> playHandler)
      : client(std::move(client)), profile(profile), playHandler(std::move(playHandler)) {
    }

    static void Init();
    static inline const uint32_t HANDLER_ORDINAL = OrdinalRegistry::PacketHandlerRegistry.RegisterOrdinal();

    uint32_t GetOrdinal() const override {
      return HANDLER_ORDINAL;
    }

    const std::function<PacketHandler*(const LoginClient&)>& GetPlayHandler() const;

    GameProfile* GetProfile() const;
  };

  class ServerPacketHandler {
   public:
    static void Init() {
      ServerHandshakePacketHandler::Init();
      PreAuthPacketHandler::Init();
      PostAuthPacketHandler::Init();
    }
  };
} // Ship
