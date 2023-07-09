#include "Proxy.hpp"
#include "../../../lib/ShipNet/src/Ship.hpp"
#include "../../../lib/ShipNet/src/network/listener/Listener.hpp"
#include "../../network/pipe/MinecraftPipe.hpp"
#include "../../protocol/handler/server/ServerPacketHandler.hpp"
#include "../../protocol/registry/BuiltInPacketRegistry.hpp"
#include "handlers/ProxyPacketHandler.hpp"
#include <thread>

namespace Ship {

  Proxy::Proxy() {
    ServerPacketHandler::Init();
    ProxyPacketHandler::Init();

    auto* eventLoop = new SystemEventLoop(
      [](EventLoop* eventLoop, ReadWriteCloser* writer) {
        auto pipe = new MinecraftFramedBytePacketPipe(
          &BuiltInPacketRegistry::HANDSHAKE, &ProtocolVersion::UNKNOWN, MAX_PACKET_SIZE, SERVERBOUND, CLIENTBOUND, 1024);
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

    std::thread t(&SystemEventLoop::StartLoop, eventLoop);
    Listener* listener = new SystemListener(eventLoop, 64, NO_TIMEOUT);

    listener->StartListening(SocketAddress {"0.0.0.0", 25577});
  }
}
