#pragma once
#include "ShipNet/network/Connection.hpp"
#include "ShipNet/protocol/handler/PacketHandler.hpp"
#include "ShipNet/utils/ordinal/OrdinalRegistry.hpp"
#include "../../../main/proxy/client/Client.hpp"
#include "../../data/client/LoginClient.hpp"
#include "../../packet/handshake/Handshake.hpp"
#include "../../packet/login/EncryptionResponse.hpp"
#include "../../packet/login/LoginPluginResponse.hpp"
#include "../../packet/login/LoginStart.hpp"
#include "../../packet/status/StatusPing.hpp"
#include "../../packet/status/StatusRequest.hpp"
#include <utility>

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

    inline Errorable<bool> OnHandshake(Connection* connection, const Handshake& handshake);

    [[nodiscard]] uint32_t GetOrdinal() const override {
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

    inline Errorable<bool> OnLoginStart(Connection* connection, const LoginStart& serverLogin);
    inline Errorable<bool> OnEncryptionResponse(Connection* connection, const EncryptionResponse& serverLogin);
    inline Errorable<bool> OnLoginPluginResponse(Connection* connection, const LoginPluginResponse& serverLogin);
    inline void AssertState(LoginState expected);

    [[nodiscard]] uint32_t GetOrdinal() const override {
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

    [[nodiscard]] uint32_t GetOrdinal() const override {
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
}
