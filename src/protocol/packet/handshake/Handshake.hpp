#pragma once

#include "../../../../lib/ShipNet/src/network/SocketAddress.hpp"
#include "../../MinecraftProtocol.hpp"
#include <string>

namespace Ship {

  enum class HandshakeNextStatus : uint32_t {
    STATUS = 1,
    LOGIN = 2
  };

  class Handshake : public Packet {
   private:
    static const uint32_t MAXIMUM_HOSTNAME_SIZE = 261;

    uint32_t protocolVersionID;
    std::string hostname;
    uint16_t port;
    HandshakeNextStatus nextStatus;

   public:
    static inline const uint32_t PACKET_ORDINAL = OrdinalRegistry::PacketRegistry.RegisterOrdinal();

    explicit Handshake(const PacketHolder& holder) {
      ByteBuffer* buffer = holder.GetCurrentBuffer();
      protocolVersionID = buffer->ReadVarInt();

      hostname = buffer->ReadString(MAXIMUM_HOSTNAME_SIZE);
      port = buffer->ReadShort();
      nextStatus = (HandshakeNextStatus) buffer->ReadVarInt();
    }

    ~Handshake() override = default;

    void Write(const ProtocolVersion* version, ByteBuffer* buffer) const override {
      buffer->WriteVarInt(protocolVersionID);
      buffer->WriteString(hostname);
      buffer->WriteShort(port);
      buffer->WriteVarInt((uint32_t) nextStatus);
    }

    uint32_t GetOrdinal() const override {
      return PACKET_ORDINAL;
    }

    [[nodiscard]] uint32_t GetProtocolVersionID() const {
      return protocolVersionID;
    }

    [[nodiscard]] const ProtocolVersion* GetProtocolVersion() const {
      return MinecraftProtocolVersion::VERSIONS.FromProtocolID(protocolVersionID);
    }

    [[nodiscard]] SocketAddress GetSocketAddress() const {
      return {hostname, port};
    }

    [[nodiscard]] const std::string& GetHostname() const {
      return hostname;
    }

    [[nodiscard]] uint16_t GetPort() const {
      return port;
    }

    [[nodiscard]] HandshakeNextStatus GetNextStatus() const {
      return nextStatus;
    }
  };
}
