#pragma once


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
    uint64_t expiry;
    uint32_t publicKeyLength;
    uint8_t* publicKey;
    uint32_t signatureLength;
    uint8_t* signature;

   public:
    static inline const uint32_t PACKET_ORDINAL = OrdinalRegistry::PacketRegistry.RegisterOrdinal();

    LoginStart(std::string username, bool hasSigData, uint64_t expiry, uint32_t publicKeyLength, uint8_t* publicKey, uint32_t signatureLength,
      uint8_t* signature)
      : username(std::move(username)), hasSigData(hasSigData), expiry(expiry), publicKeyLength(publicKeyLength), publicKey(publicKey),
        signatureLength(signatureLength), signature(signature) {
    }

    explicit LoginStart(const PacketHolder& holder) {
      ByteBuffer* buffer = holder.GetCurrentBuffer();
      const ProtocolVersion* version = holder.GetVersion();
      username = buffer->ReadString(MAXIMUM_USERNAME_SIZE);
      if (version >= &MinecraftProtocolVersion::MINECRAFT_1_19) {
        hasSigData = buffer->ReadBoolean();
        if (hasSigData) {
          expiry = buffer->ReadLong();

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

    ~LoginStart() override {
      if (hasSigData) {
        delete[] publicKey;
        delete[] signature;
      }
    };

    void Write(const ProtocolVersion* version, ByteBuffer* buffer) const override {
      buffer->WriteString(username);
      if (version >= &MinecraftProtocolVersion::MINECRAFT_1_19) {
        buffer->WriteBoolean(hasSigData);
        if (hasSigData) {
          buffer->WriteLong(expiry);
          buffer->WriteVarInt(publicKeyLength);
          buffer->WriteBytes(publicKey, publicKeyLength);
          buffer->WriteVarInt(signatureLength);
          buffer->WriteBytes(signature, signatureLength);
        }
      }
    }

    uint32_t GetOrdinal() const override {
      return PACKET_ORDINAL;
    }

    [[nodiscard]] const std::string& GetUsername() const {
      return username;
    }

    [[nodiscard]] bool HasSigData() const {
      return hasSigData;
    }

    [[nodiscard]] uint64_t GetExpiry() const {
      return expiry;
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
