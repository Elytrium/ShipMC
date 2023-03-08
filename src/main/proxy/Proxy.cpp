#include "Proxy.hpp"
#include "../../Ship.hpp"
#include "../../network/listener/Listener.hpp"
#include "../../network/pipe/minecraft/MinecraftPipe.hpp"
#include "../../protocol/registry/BuiltInPacketRegistry.hpp"
#include "handlers/ProxyPacketHandler.hpp"
#include <thread>

namespace Ship {

  Proxy::Proxy() {
    ProxyPacketHandler::Init();

    auto* eventLoop = new SystemEventLoop(
      [](EventLoop* eventLoop, ReadWriteCloser* writer) {
        auto pipe = new MinecraftFramedBytePacketPipe(
          &BuiltInPacketRegistry::HANDSHAKE, &ProtocolVersion::UNKNOWN, MAX_PACKET_SIZE, SERVERBOUND, CLIENTBOUND, LONG_PACKET_BUFFER_CAPACITY);
        auto* connection = new Connection(pipe, new HandshakePacketHandler(), LONG_PACKET_BUFFER_CAPACITY, LONG_PACKET_BUFFER_CAPACITY, writer, eventLoop);

        return connection;
      },
      64, NO_TIMEOUT, 1024);

    std::thread t(&SystemEventLoop::StartLoop, eventLoop);
    Listener* listener = new SystemListener(eventLoop, 64, NO_TIMEOUT);

    listener->StartListening(SocketAddress {"0.0.0.0", 25577});
  }
}
