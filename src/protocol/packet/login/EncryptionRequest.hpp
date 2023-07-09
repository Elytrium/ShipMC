#pragma once

#include <string>
#include <utility>

namespace Ship {

  class EncryptionRequest : public Packet {
   private:
    std::string serverID;
    ByteBuffer* publicKey;
    ByteBuffer* verifyToken;

   public:
    static inline const uint32_t PACKET_ORDINAL = OrdinalRegistry::PacketRegistry.RegisterOrdinal();

    EncryptionRequest(std::string serverID, ByteBuffer* publicKey, ByteBuffer* verifyToken)
      : serverID(std::move(serverID)), publicKey(publicKey), verifyToken(verifyToken) {
    }

    EncryptionRequest(const ProtocolVersion* version, ByteBuffer* buffer)
      : serverID(buffer->ReadString(20)), publicKey(buffer->ReadByteArray(256)), verifyToken(buffer->ReadByteArray(16)) {
    }

    ~EncryptionRequest() override {
      delete publicKey;
      delete verifyToken;
    }

    void Write(const ProtocolVersion* version, ByteBuffer* buffer) const override {
    }

    const std::string& GetServerId() const {
      return serverID;
    }

    ByteBuffer* GetPublicKey() const {
      return publicKey;
    }

    ByteBuffer* GetVerifyToken() const {
      return verifyToken;
    }

    uint32_t GetOrdinal() const override {
      return PACKET_ORDINAL;
    }
  };
}
