#include "Proxy.hpp"
#include "../../Ship.hpp"
#include "../../network/listener/Listener.hpp"
#include "../../network/pipe/minecraft/MinecraftPipe.hpp"
#include "../../protocol/handlers/server/ServerPacketHandler.hpp"
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
          &BuiltInPacketRegistry::HANDSHAKE, &ProtocolVersion::UNKNOWN, MAX_PACKET_SIZE, SERVERBOUND, CLIENTBOUND, LONG_PACKET_BUFFER_CAPACITY);
        auto* connection = new Connection(pipe,
          new ServerHandshakePacketHandler(
            [](LoginClient client) {
              return new StatusPacketHandler(client);
            },
            [](LoginClient client) {
              return new ConnectPacketHandler(client);
            }),
          LONG_PACKET_BUFFER_CAPACITY, LONG_PACKET_BUFFER_CAPACITY, writer, eventLoop);

        return connection;
      },
      64, NO_TIMEOUT, 1024);

    if (!eventLoop.IsSuccess()) {
      // TODO: Log error
      return;
    }

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
