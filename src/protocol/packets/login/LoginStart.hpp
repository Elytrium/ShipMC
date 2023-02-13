#pragma once

#include "../../../utils/ordinal/OrdinalRegistry.hpp"
#include "../Packet.hpp"
#include <string>
#include <utility>

namespace Ship {

  class LoginStart : public Packet {
   private:
    static const uint32_t MAXIMUM_USERNAME_SIZE = 16;
    static const uint32_t MAXIMUM_PUBLIC_KEY_SIZE = 256;
    static const uint32_t MAXIMUM_SIGNATURE_SIZE = 256;

    std::string username;
    bool hasSigData = false;
    uint64_t timestamp;
    uint32_t publicKeyLength;
    uint8_t* publicKey;
    uint32_t signatureLength;
    uint8_t* signature;

   public:
    static inline const uint32_t PACKET_ORDINAL = OrdinalRegistry::PacketRegistry.RegisterOrdinal();

    LoginStart(std::string username, bool hasSigData, uint64_t timestamp, uint32_t publicKeyLength, uint8_t* publicKey, uint32_t signatureLength,
      uint8_t* signature)
      : username(std::move(username)), hasSigData(hasSigData), timestamp(timestamp), publicKeyLength(publicKeyLength), publicKey(publicKey),
        signatureLength(signatureLength), signature(signature) {
    }

    ~LoginStart() override {
      if (hasSigData) {
        delete[] publicKey;
        delete[] signature;
      }
    };

    void Read(const ProtocolVersion* version, ByteBuffer* buffer) override {
      username = buffer->ReadString(MAXIMUM_USERNAME_SIZE);
      if (version >= &ProtocolVersion::MINECRAFT_1_19) {
        hasSigData = buffer->ReadBoolean();
        if (hasSigData) {
          timestamp = buffer->ReadLong();

          publicKeyLength = buffer->ReadVarInt();
          if (publicKeyLength > MAXIMUM_PUBLIC_KEY_SIZE) {
            throw InvalidArgumentException("Invalid public key length: ", publicKeyLength);
          }
          publicKey = buffer->ReadBytes(publicKeyLength);

          signatureLength = buffer->ReadVarInt();
          if (signatureLength > MAXIMUM_SIGNATURE_SIZE) {
            throw InvalidArgumentException("Invalid signature length: ", publicKeyLength);
          }
          signature = buffer->ReadBytes(signatureLength);
        }
      }
    }

    void Write(const ProtocolVersion* version, ByteBuffer* buffer) override {
      buffer->WriteString(username);
      if (version >= &ProtocolVersion::MINECRAFT_1_19) {
        buffer->WriteBoolean(hasSigData);
        if (hasSigData) {
          buffer->WriteLong(timestamp);
          buffer->WriteVarInt(publicKeyLength);
          buffer->WriteBytes(publicKey, publicKeyLength);
          buffer->WriteVarInt(signatureLength);
          buffer->WriteBytes(signature, signatureLength);
        }
      }
    }

    uint32_t GetOrdinal() override {
      return PACKET_ORDINAL;
    }

    [[nodiscard]] const std::string& GetUsername() const {
      return username;
    }

    [[nodiscard]] bool HasSigData() const {
      return hasSigData;
    }

    [[nodiscard]] uint64_t GetTimestamp() const {
      return timestamp;
    }

    [[nodiscard]] uint32_t GetPublicKeyLength() const {
      return publicKeyLength;
    }

    [[nodiscard]] uint8_t* GetPublicKey() const {
      return publicKey;
    }

    [[nodiscard]] uint32_t GetSignatureLength() const {
      return signatureLength;
    }

    [[nodiscard]] uint8_t* GetSignature() const {
      return signature;
    }
  };
}
