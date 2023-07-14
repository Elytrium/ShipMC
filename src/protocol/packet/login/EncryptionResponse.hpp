#pragma once

#include "ShipNet/utils/ordinal/OrdinalRegistry.hpp"
#include <optional>
#include <string>

namespace Ship {

  class EncryptionResponse : public Packet {
   private:
    ByteBuffer* sharedSecret{};
    ByteBuffer* verifyToken{};
    std::optional<uint64_t> salt;

   public:
    static inline const uint32_t PACKET_ORDINAL = OrdinalRegistry::PacketRegistry.RegisterOrdinal();

    EncryptionResponse() = default;

    EncryptionResponse(ByteBuffer* sharedSecret, ByteBuffer* verifyToken, const std::optional<uint64_t>& salt)
      : sharedSecret(sharedSecret), verifyToken(verifyToken), salt(salt) {
    }

    static Errorable<EncryptionResponse> Instantiate(const PacketHolder& holder) {
      ByteBuffer* buffer = holder.GetCurrentBuffer();
      const ProtocolVersion* version = holder.GetVersion();
      ProceedErrorable(sharedSecret, ByteBuffer*, buffer->ReadByteArray(128), InvalidPacketErrorable<EncryptionResponse>(PACKET_ORDINAL))

      bool hasSalt;
      uint64_t salt;
      if (version >= &MinecraftProtocolVersion::MINECRAFT_1_19 && version < &MinecraftProtocolVersion::MINECRAFT_1_19_3) {
        SetFromErrorable(hasSalt, bool, buffer->ReadBoolean(), InvalidPacketErrorable<EncryptionResponse>(PACKET_ORDINAL))
        if (hasSalt) {
          SetFromErrorable(salt, uint64_t, buffer->ReadLong(), InvalidPacketErrorable<EncryptionResponse>(PACKET_ORDINAL))
        }
      }

      ProceedErrorable(verifyToken, ByteBuffer*, buffer->ReadByteArray(version >= &MinecraftProtocolVersion::MINECRAFT_1_19 ? 256 : 128),
        InvalidPacketErrorable<EncryptionResponse>(PACKET_ORDINAL))

      return SuccessErrorable<EncryptionResponse>({sharedSecret, verifyToken, hasSalt ? std::optional(salt) : std::nullopt});
    }

    ~EncryptionResponse() override = default;

    Errorable<bool> Write(const ProtocolVersion* version, ByteBuffer* buffer) const override {
      buffer->WriteByteArray(sharedSecret);
      if (version >= &MinecraftProtocolVersion::MINECRAFT_1_19 && version < &MinecraftProtocolVersion::MINECRAFT_1_19_3) {
        if (salt.has_value()) {
          buffer->WriteBoolean(false);
          buffer->WriteLong(salt.value());
        } else {
          buffer->WriteBoolean(true);
        }
      }

      buffer->WriteByteArray(verifyToken);
      return SuccessErrorable<bool>(true);
    }

    [[nodiscard]] uint32_t GetOrdinal() const override {
      return PACKET_ORDINAL;
    }
  };
}
