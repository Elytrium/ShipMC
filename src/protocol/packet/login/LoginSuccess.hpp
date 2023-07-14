#pragma once

#include "../../ProtocolUtils.hpp"
#include "ShipNet/utils/ordinal/OrdinalRegistry.hpp"
#include "../../data/profile/GameProfile.hpp"
#include <string>
#include <utility>

namespace Ship {

  class LoginSuccess : public Packet {
   private:
    static const uint32_t MAXIMUM_USERNAME_SIZE = 16;

    UUID uuid;
    std::string username;
    std::vector<GameProfileProperty> properties;

   public:
    static inline const uint32_t PACKET_ORDINAL = OrdinalRegistry::PacketRegistry.RegisterOrdinal();

    LoginSuccess() = default;

    LoginSuccess(const UUID& uuid, std::string username)
      : uuid(uuid), username(std::move(username)) {
    }

    LoginSuccess(const UUID& uuid, std::string username, std::vector<GameProfileProperty> properties)
      : uuid(uuid), username(std::move(username)), properties(std::move(properties)) {
    }

    static Errorable<LoginSuccess> Instantiate(const PacketHolder& holder) {
      ByteBuffer* buffer = holder.GetCurrentBuffer();
      const ProtocolVersion* version = holder.GetVersion();
      UUID uuid;
      if (version >= &MinecraftProtocolVersion::MINECRAFT_1_19) {
        SetFromErrorable(uuid, UUID, buffer->ReadUUID(), InvalidPacketErrorable<LoginSuccess>(PACKET_ORDINAL))
      } else if (version >= &MinecraftProtocolVersion::MINECRAFT_1_16_2) {
        SetFromErrorable(uuid, UUID, buffer->ReadUUIDIntArray(), InvalidPacketErrorable<LoginSuccess>(PACKET_ORDINAL))
      } else {
        ProceedErrorable(uuidString, std::string, buffer->ReadString(36), InvalidPacketErrorable<LoginSuccess>(PACKET_ORDINAL))
        SetFromErrorable(uuid, UUID, UUID::Instantiate(uuidString), InvalidPacketErrorable<LoginSuccess>(PACKET_ORDINAL))
      }

      ProceedErrorable(username, std::string, buffer->ReadString(MAXIMUM_USERNAME_SIZE), InvalidPacketErrorable<LoginSuccess>(PACKET_ORDINAL))
      if (version >= &MinecraftProtocolVersion::MINECRAFT_1_19) {
        ProceedErrorable(properties, std::vector<GameProfileProperty>,
          ProtocolUtils::ReadProperties(buffer), InvalidPacketErrorable<LoginSuccess>(PACKET_ORDINAL))
        return SuccessErrorable<LoginSuccess>(LoginSuccess(uuid, username, properties));
      } else {
        return SuccessErrorable<LoginSuccess>(LoginSuccess(uuid, username));
      }
    }

    ~LoginSuccess() override = default;

    Errorable<bool> Write(const ProtocolVersion* version, ByteBuffer* buffer) const override {
      if (version >= &MinecraftProtocolVersion::MINECRAFT_1_19) {
        buffer->WriteUUID(uuid);
      } else if (version >= &MinecraftProtocolVersion::MINECRAFT_1_16_2) {
        buffer->WriteUUIDIntArray(uuid);
      } else {
        buffer->WriteString(uuid.ToString());
      }

      buffer->WriteString(username);
      if (version >= &MinecraftProtocolVersion::MINECRAFT_1_19) {
        ProtocolUtils::WriteProperties(buffer, properties);
      }
      return SuccessErrorable<bool>(true);
    }

    [[nodiscard]] uint32_t GetOrdinal() const override {
      return PACKET_ORDINAL;
    }

    [[nodiscard]] const UUID& GetUuid() const {
      return uuid;
    }

    [[nodiscard]] const std::string& GetUsername() const {
      return username;
    }

    [[nodiscard]] const std::vector<GameProfileProperty>& GetProperties() const {
      return properties;
    }
  };
}
