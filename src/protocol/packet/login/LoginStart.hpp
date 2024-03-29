#pragma once

#include "ShipNet/protocol/packet/Packet.hpp"
#include "ShipNet/utils/exception/Errorable.hpp"
#include "ShipNet/utils/ordinal/OrdinalRegistry.hpp"
#include "../../MinecraftProtocol.hpp"
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
    uint64_t expiry{};
    uint32_t publicKeyLength{};
    uint8_t* publicKey{};
    uint32_t signatureLength{};
    uint8_t* signature{};

   public:
    static inline const uint32_t PACKET_ORDINAL = OrdinalRegistry::PacketRegistry.RegisterOrdinal();

    LoginStart() = default;

    LoginStart(std::string username, bool hasSigData, uint64_t expiry, uint32_t publicKeyLength, uint8_t* publicKey, uint32_t signatureLength,
      uint8_t* signature)
      : username(std::move(username)), hasSigData(hasSigData), expiry(expiry), publicKeyLength(publicKeyLength), publicKey(publicKey),
        signatureLength(signatureLength), signature(signature) {
    }

    static Errorable<LoginStart> Instantiate(const PacketHolder& holder);

    ~LoginStart() override {
      if (hasSigData) {
        delete[] publicKey;
        delete[] signature;
      }
    };

    Errorable<bool> Write(const ProtocolVersion* version, ByteBuffer* buffer) const override {
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
      return SuccessErrorable<bool>(true);
    }

    [[nodiscard]] uint32_t GetOrdinal() const override {
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

  CreateInvalidArgumentErrorable(InvalidLoginPublicKeyErrorable, LoginStart, "Invalid public key length");
  CreateInvalidArgumentErrorable(InvalidLoginSignatureErrorable, LoginStart, "Invalid signature length");
}
