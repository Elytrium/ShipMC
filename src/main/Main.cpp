#include "Main.hpp"
#include "../network/listener/Listener.hpp"
#include "../network/pipe/minecraft/MinecraftPipe.hpp"
#include "../protocol/registry/BuiltInPacketRegistry.hpp"
#include <thread>

namespace Ship {

  Main::Main() {
    ProtocolVersion::Init();

    auto* eventLoop = new SystemEventLoop(
      [](ReadWriteCloser* writer) {
        auto pipe = new MinecraftFramedBytePacketPipe(&BuiltInPacketRegistry::HANDSHAKE, &ProtocolVersion::UNKNOWN, 65536, SERVERBOUND, CLIENTBOUND, 1024);
        Connection* connection = new Connection(pipe, 1024, 1024, writer);

        return connection;
      },
      64, NO_TIMEOUT, 1024);

    std::thread t(&SystemEventLoop::StartLoop, eventLoop);
    Listener* listener = new SystemListener(eventLoop, 64, NO_TIMEOUT);

    listener->StartListening("0.0.0.0", 25577);
  }
}
