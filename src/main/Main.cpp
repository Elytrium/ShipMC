#include "Main.hpp"
#include "../network/listener/Listener.hpp"
#include "../network/pipe/minecraft/MinecraftPipe.hpp"
#include "../protocol/registry/BuiltInPacketRegistry.hpp"
#include <thread>

namespace Ship {

  Main::Main() {
    ProtocolVersion::Init();

    auto* epollEventLoop = new EpollEventLoop(
      [](ReadWriteCloser* writer) {
        return new Connection(
          new MinecraftFramedBytePacketPipe(&BuiltInPacketRegistry::HANDSHAKE, &ProtocolVersion::UNKNOWN, 65536,
            SERVERBOUND, CLIENTBOUND, 1024), 1024, 1024, writer);
      },
      64, -1, 1024);

    std::thread t(&EpollEventLoop::StartLoop, epollEventLoop);
    Listener* listener = new EpollListener(epollEventLoop, 64, -1);

    listener->StartListening("0.0.0.0", 25577);
  }
}
