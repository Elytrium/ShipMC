#pragma once


#include <optional>
#include <string>

namespace Ship {

  class EncryptionResponse : public Packet {
   private:
    ByteBuffer* sharedSecret;
    ByteBuffer* verifyToken;
    std::optional<uint64_t> salt;

   public:
    static inline const uint32_t PACKET_ORDINAL = OrdinalRegistry::PacketRegistry.RegisterOrdinal();

    explicit EncryptionResponse(const PacketHolder& holder) {
      ByteBuffer* buffer = holder.GetCurrentBuffer();
      const ProtocolVersion* version = holder.GetVersion();
      sharedSecret = buffer->ReadByteArray(128);
      if (version >= &MinecraftProtocolVersion::MINECRAFT_1_19 && version < &MinecraftProtocolVersion::MINECRAFT_1_19_3 && !buffer->ReadBoolean()) {
        salt = buffer->ReadLong();
      }

      verifyToken = buffer->ReadByteArray(version >= &MinecraftProtocolVersion::MINECRAFT_1_19 ? 256 : 128);
    }

    ~EncryptionResponse() override = default;

    void Write(const ProtocolVersion* version, ByteBuffer* buffer) const override {
      buffer->WriteByteArray(sharedSecret);
      if (version >= &MinecraftProtocolVersion::MINECRAFT_1_19
          && version < &MinecraftProtocolVersion::MINECRAFT_1_19_3) {
        if (salt.has_value()) {
          buffer->WriteBoolean(false);
          buffer->WriteLong(salt.value());
        } else {
          buffer->WriteBoolean(true);
        }
      }

      buffer->WriteByteArray(verifyToken);
    }

    uint32_t GetOrdinal() const override {
      return PACKET_ORDINAL;
    }
  };
}
