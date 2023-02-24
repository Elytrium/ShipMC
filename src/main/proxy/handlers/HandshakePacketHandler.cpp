#include "../../../network/Connection.hpp"
#include "../../../network/pipe/minecraft/MinecraftPipe.hpp"
#include "../../../protocol/registry/BuiltInPacketRegistry.hpp"
#include "ProxyPacketHandler.hpp"

namespace Ship {
  void HandshakePacketHandler::Init() {
    SetPacketCallback(HandshakePacketHandler, Handshake, OnHandshake);
  }

  inline bool HandshakePacketHandler::OnHandshake(Connection* connection, Handshake* handshake) {
    switch (handshake->GetNextStatus()) {
      case HandshakeNextStatus::STATUS:
        ((MinecraftFramedBytePacketPipe*) connection->GetBytePacketPipe())->SetRegistry(&BuiltInPacketRegistry::STATUS);
        connection->ReplaceMainPacketHandler(new StatusPacketHandler());
        return true;
      case HandshakeNextStatus::LOGIN:
        return true;
    }

    return false;
  }
} // Ship