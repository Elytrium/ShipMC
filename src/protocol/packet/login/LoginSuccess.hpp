#pragma once

#include "../../../../lib/ShipNet/src/utils/ordinal/OrdinalRegistry.hpp"
#include "../../ProtocolUtils.hpp"
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

    explicit LoginSuccess(const PacketHolder& holder) {
      ByteBuffer* buffer = holder.GetCurrentBuffer();
      const ProtocolVersion* version = holder.GetVersion();
      if (version >= &MinecraftProtocolVersion::MINECRAFT_1_19) {
        uuid = buffer->ReadUUID();
      } else if (version >= &MinecraftProtocolVersion::MINECRAFT_1_16_2) {
        uuid = buffer->ReadUUIDIntArray();
      } else {
        uuid = UUID(buffer->ReadString(36));
      }

      username = buffer->ReadString(MAXIMUM_USERNAME_SIZE);
      if (version >= &MinecraftProtocolVersion::MINECRAFT_1_19) {
        properties = ProtocolUtils::ReadProperties(buffer);
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
        ProtocolUtils::WriteProperties(buffer, properties);
      }
    }

    uint32_t GetOrdinal() const override {
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
