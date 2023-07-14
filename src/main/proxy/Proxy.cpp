#include "Proxy.hpp"
#include "ShipNet/Ship.hpp"
#include "ShipNet/network/listener/Listener.hpp"
#include "../../network/pipe/MinecraftPipe.hpp"
#include "../../protocol/handler/server/ServerPacketHandler.hpp"
#include "../../protocol/registry/BuiltInPacketRegistry.hpp"
#include "handlers/ProxyPacketHandler.hpp"
#include <thread>

namespace Ship {

  Proxy::Proxy() {
    ServerPacketHandler::Init();
    ProxyPacketHandler::Init();

    Errorable<SystemEventLoop*> eventLoop = SystemEventLoop::NewEventLoop(
      [](EventLoop* eventLoop, ReadWriteCloser* writer) {
        auto pipe = new MinecraftFramedBytePacketPipe(
          &BuiltInPacketRegistry::HANDSHAKE, &ProtocolVersion::UNKNOWN, MAX_PACKET_SIZE, SERVERBOUND, CLIENTBOUND);
        auto* connection = new Connection(pipe,
          new ServerHandshakePacketHandler(
            [](LoginClient client) {
              return new StatusPacketHandler(client);
            },
            [](LoginClient client) {
              return new ConnectPacketHandler(client);
            }),
          1024, 1024, writer, eventLoop);

        return connection;
      },
      64, NO_TIMEOUT, 1024);

    std::thread t(&SystemEventLoop::StartLoop, eventLoop.GetValue());
    Listener* listener = new SystemListener(eventLoop.GetValue(), 64, NO_TIMEOUT);

    Errorable<int> bindRequest = listener->Bind(SocketAddress {"0.0.0.0", 25577});
    if (!bindRequest.IsSuccess()) {
      // TODO: log error
      return;
    }

    listener->StartListening();
  }
}
