#include "../../../network/Connection.hpp"
#include "../../../network/pipe/minecraft/MinecraftPipe.hpp"
#include "../../registry/BuiltInPacketRegistry.hpp"
#include "ServerPacketHandler.hpp"

namespace Ship {
  void ServerHandshakePacketHandler::Init() {
    SetPacketCallback(ServerHandshakePacketHandler, Handshake, OnHandshake);
  }

  inline bool ServerHandshakePacketHandler::OnHandshake(Connection* connection, const Handshake& handshake) {
    auto minecraftPipe = (MinecraftFramedBytePacketPipe*) connection->GetBytePacketPipe();
    minecraftPipe->SetProtocolVersion(handshake.GetProtocolVersion());

    LoginClient client(connection, minecraftPipe, handshake.GetSocketAddress());
    switch (handshake.GetNextStatus()) {
      case HandshakeNextStatus::STATUS:
        minecraftPipe->SetRegistry(&BuiltInPacketRegistry::STATUS);
        connection->ReplaceMainPacketHandler(statusHandler(client));
        return true;
      case HandshakeNextStatus::LOGIN:
        minecraftPipe->SetRegistry(&BuiltInPacketRegistry::LOGIN);
        connection->ReplaceMainPacketHandler(new PreAuthPacketHandler(client, std::function<PacketHandler *(const LoginClient &)>()));
        return true;
    }

    return false;
  }

  ServerHandshakePacketHandler::ServerHandshakePacketHandler(
    const std::function<PacketHandler *(const LoginClient &)> &statusHandler, const std::function<PacketHandler *(const LoginClient &)> &playHandler)
    : statusHandler(statusHandler), playHandler(playHandler) {
  }
} // Ship