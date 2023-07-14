#include "LoginStart.hpp"

namespace Ship {
  Errorable<LoginStart> LoginStart::Instantiate(const PacketHolder& holder) {
    ByteBuffer* buffer = holder.GetCurrentBuffer();
    const ProtocolVersion* version = holder.GetVersion();
    ProceedErrorable(username, std::string, buffer->ReadString(MAXIMUM_USERNAME_SIZE), InvalidPacketErrorable<LoginStart>(PACKET_ORDINAL))

    bool hasSigData = false;
    uint64_t expiry{};
    uint32_t publicKeyLength{};
    uint8_t* publicKey{};
    uint32_t signatureLength{};
    uint8_t* signature{};
    if (version >= &MinecraftProtocolVersion::MINECRAFT_1_19) {
      SetFromErrorable(hasSigData, bool, buffer->ReadBoolean(), InvalidPacketErrorable<LoginStart>(PACKET_ORDINAL))
      if (hasSigData) {
        SetFromErrorable(expiry, uint64_t, buffer->ReadLong(), InvalidPacketErrorable<LoginStart>(PACKET_ORDINAL))

        SetFromErrorable(publicKeyLength, uint32_t, buffer->ReadVarInt(), InvalidPacketErrorable<LoginStart>(PACKET_ORDINAL))
        if (publicKeyLength > MAXIMUM_PUBLIC_KEY_SIZE) {
          return InvalidLoginPublicKeyErrorable(publicKeyLength);
        }
        SetFromErrorable(publicKey, uint8_t*, buffer->ReadBytes(publicKeyLength), InvalidPacketErrorable<LoginStart>(PACKET_ORDINAL))

        SetFromErrorable(signatureLength, uint32_t, buffer->ReadVarInt(), InvalidPacketErrorable<LoginStart>(PACKET_ORDINAL))
        if (signatureLength > MAXIMUM_SIGNATURE_SIZE) {
          return InvalidLoginSignatureErrorable(publicKeyLength);
        }
        SetFromErrorable(signature, uint8_t*, buffer->ReadBytes(signatureLength), InvalidPacketErrorable<LoginStart>(PACKET_ORDINAL))
      }
    }

    return SuccessErrorable<LoginStart>({username, hasSigData, expiry, publicKeyLength, publicKey, signatureLength, signature});
  }
}