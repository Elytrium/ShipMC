#pragma once

#include "../../../utils/exceptions/InvalidArgumentException.hpp"
#include "../../../utils/ordinal/OrdinalRegistry.hpp"
#include "../Packet.hpp"
#include <string>

namespace Ship {

  class Handshake : public Packet {
   private:
    static const uint32_t MAXIMUM_HOSTNAME_SIZE = 261;

    uint32_t protocolVersion;
    std::string serverAddress;
    uint16_t port;
    uint32_t nextStatus;

   public:
    static inline const uint32_t PACKET_ORDINAL = OrdinalRegistry::PacketRegistry.RegisterOrdinal();

    ~Handshake() override = default;

    void Read(const ProtocolVersion* version, ByteBuffer* buffer) override {
      protocolVersion = buffer->ReadVarInt();

      serverAddress = buffer->ReadString(MAXIMUM_HOSTNAME_SIZE);
      port = buffer->ReadShort();
      nextStatus = buffer->ReadVarInt();
    }

    void Write(const ProtocolVersion* version, ByteBuffer* buffer) override {
      buffer->WriteVarInt(protocolVersion);
      buffer->WriteString(serverAddress);
      buffer->WriteShort(port);
      buffer->WriteVarInt(nextStatus);
    }

    uint32_t GetOrdinal() override {
      return PACKET_ORDINAL;
    }

    [[nodiscard]] uint32_t GetProtocolVersion() const {
      return protocolVersion;
    }

    [[nodiscard]] const std::string& GetServerAddress() const {
      return serverAddress;
    }

    [[nodiscard]] uint16_t GetPort() const {
      return port;
    }

    [[nodiscard]] uint32_t GetNextStatus() const {
      return nextStatus;
    }
  };
}
