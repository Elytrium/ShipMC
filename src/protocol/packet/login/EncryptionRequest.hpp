#pragma once

#include "../../../../lib/ShipNet/src/utils/ordinal/OrdinalRegistry.hpp"
#include <string>
#include <utility>

namespace Ship {

  class EncryptionRequest : public Packet {
   private:
    std::string serverID;
    ByteBuffer* publicKey{};
    ByteBuffer* verifyToken{};

   public:
    static inline const uint32_t PACKET_ORDINAL = OrdinalRegistry::PacketRegistry.RegisterOrdinal();

    EncryptionRequest() = default;

    EncryptionRequest(std::string serverID, ByteBuffer* publicKey, ByteBuffer* verifyToken)
      : serverID(std::move(serverID)), publicKey(publicKey), verifyToken(verifyToken) {
    }

    static Errorable<EncryptionRequest> Instantiate(const ProtocolVersion* version, ByteBuffer* buffer) {
      ProceedErrorable(serverID, std::string, buffer->ReadString(20), InvalidPacketErrorable<EncryptionRequest>(PACKET_ORDINAL))
      ProceedErrorable(publicKey, ByteBuffer*, buffer->ReadByteArray(256), InvalidPacketErrorable<EncryptionRequest>(PACKET_ORDINAL))
      ProceedErrorable(verifyToken, ByteBuffer*, buffer->ReadByteArray(16), InvalidPacketErrorable<EncryptionRequest>(PACKET_ORDINAL))
      return SuccessErrorable<EncryptionRequest>(EncryptionRequest(serverID, publicKey, verifyToken));
    }

    ~EncryptionRequest() override {
      delete publicKey;
      delete verifyToken;
    }

    Errorable<bool> Write(const ProtocolVersion* version, ByteBuffer* buffer) const override {
      return SuccessErrorable<bool>(true);
    }

    [[nodiscard]] const std::string& GetServerId() const {
      return serverID;
    }

    ByteBuffer* GetPublicKey() const {
      return publicKey;
    }

    ByteBuffer* GetVerifyToken() const {
      return verifyToken;
    }

    [[nodiscard]] uint32_t GetOrdinal() const override {
      return PACKET_ORDINAL;
    }
  };
}
