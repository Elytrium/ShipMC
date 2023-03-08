#include "../../../network/Connection.hpp"
#include "../../../network/pipe/minecraft/MinecraftPipe.hpp"
#include "../../../protocol/registry/BuiltInPacketRegistry.hpp"
#include "ProxyPacketHandler.hpp"

namespace Ship {
  void HandshakePacketHandler::Init() {
    SetPacketCallback(HandshakePacketHandler, Handshake, OnHandshake);
  }

  inline bool HandshakePacketHandler::OnHandshake(Connection* connection, const Handshake& handshake) {
    auto minecraftPipe = (MinecraftFramedBytePacketPipe*) connection->GetBytePacketPipe();
    minecraftPipe->SetProtocolVersion(handshake.GetProtocolVersion());

    LoginClient client(connection, minecraftPipe, handshake.GetSocketAddress());
    switch (handshake.GetNextStatus()) {
      case HandshakeNextStatus::STATUS:
        minecraftPipe->SetRegistry(&BuiltInPacketRegistry::STATUS);
        connection->ReplaceMainPacketHandler(new StatusPacketHandler(client));
        return true;
      case HandshakeNextStatus::LOGIN:
        minecraftPipe->SetRegistry(&BuiltInPacketRegistry::LOGIN);
        connection->ReplaceMainPacketHandler(new PreAuthPacketHandler(client));
        return true;
    }

    return false;
  }
} // Ship