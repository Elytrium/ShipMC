#pragma once

#include "ShipNet/network/SocketAddress.hpp"
#include "ShipNet/utils/ordinal/OrdinalRegistry.hpp"
#include "../../MinecraftProtocol.hpp"
#include <string>
#include <utility>

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

    Handshake() = default;

    Handshake(uint32_t protocolVersionId, std::string hostname, uint16_t port, HandshakeNextStatus nextStatus)
      : protocolVersionID(protocolVersionId), hostname(std::move(hostname)), port(port), nextStatus(nextStatus) {
    }

    static Errorable<Handshake> Instantiate(const PacketHolder& holder) {
      ByteBuffer* buffer = holder.GetCurrentBuffer();
      ProceedErrorable(protocolVersionID, uint32_t, buffer->ReadVarInt(), InvalidPacketErrorable<Handshake>(PACKET_ORDINAL))
      ProceedErrorable(hostname, std::string, buffer->ReadString(MAXIMUM_HOSTNAME_SIZE), InvalidPacketErrorable<Handshake>(PACKET_ORDINAL))
      ProceedErrorable(port, uint16_t, buffer->ReadShort(), InvalidPacketErrorable<Handshake>(PACKET_ORDINAL))
      ProceedErrorable(nextStatus, uint32_t, buffer->ReadVarInt(), InvalidPacketErrorable<Handshake>(PACKET_ORDINAL))
      return SuccessErrorable<Handshake>({protocolVersionID, hostname, port, (HandshakeNextStatus) nextStatus});
    }

    ~Handshake() override = default;

    Errorable<bool> Write(const ProtocolVersion* version, ByteBuffer* buffer) const override {
      buffer->WriteVarInt(protocolVersionID);
      buffer->WriteString(hostname);
      buffer->WriteShort(port);
      buffer->WriteVarInt((uint32_t) nextStatus);
      return SuccessErrorable<bool>(true);
    }

    [[nodiscard]] uint32_t GetOrdinal() const override {
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
