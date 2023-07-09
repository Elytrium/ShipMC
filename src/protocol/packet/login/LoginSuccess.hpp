#pragma once

#include "../../../../lib/ShipNet/src/utils/ordinal/OrdinalRegistry.hpp"
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

    LoginSuccess(const UUID& uuid, std::string username, std::vector<GameProfileProperty> properties)
      : uuid(uuid), username(std::move(username)), properties(std::move(properties)) {
    }

    static Errorable<LoginSuccess> Instantiate(const PacketHolder& holder) {
      ByteBuffer* buffer = holder.GetCurrentBuffer();
      const ProtocolVersion* version = holder.GetVersion();
      if (version >= &MinecraftProtocolVersion::MINECRAFT_1_19) {
        ProceedErrorable(uuid, UUID, buffer->ReadUUID(), InvalidPacketErrorable<>(PACKET_ORDINAL))
      } else if (version >= &MinecraftProtocolVersion::MINECRAFT_1_16_2) {
        uuid = buffer->ReadUUIDIntArray();
      } else {
        uuid = UUID(buffer->ReadString(36));
      }

      ProceedErrorable(username, std::string, buffer->ReadString(MAXIMUM_USERNAME_SIZE), InvalidPacketErrorable<>(PACKET_ORDINAL))
      if (version >= &MinecraftProtocolVersion::MINECRAFT_1_19) {
        properties = buffer->ReadProperties();
      }
    }

    ~LoginSuccess() override = default;

    void Write(const ProtocolVersion* version, ByteBuffer* buffer) const override {
      if (version >= &MinecraftProtocolVersion::MINECRAFT_1_19) {
        buffer->WriteUUID(uuid);
      } else if (version >= &MinecraftProtocolVersion::MINECRAFT_1_16_2) {
        buffer->WriteUUIDIntArray(uuid);
      } else {
        buffer->WriteString(uuid.ToString());
      }

      buffer->WriteString(username);
      if (version >= &MinecraftProtocolVersion::MINECRAFT_1_19) {
        buffer->WriteProperties(properties);
      }
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
