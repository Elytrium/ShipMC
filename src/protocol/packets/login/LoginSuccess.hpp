#pragma once

#include "../../../utils/ordinal/OrdinalRegistry.hpp"
#include "../../data/profile/GameProfile.hpp"
#include "../Packet.hpp"
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

    ~LoginSuccess() override = default;

    void Read(const ProtocolVersion* version, ByteBuffer* buffer) override {
      if (version >= &ProtocolVersion::MINECRAFT_1_19) {
        uuid = buffer->ReadUUID();
      } else if (version >= &ProtocolVersion::MINECRAFT_1_16_2) {
        uuid = buffer->ReadUUIDIntArray();
      } else {
        uuid = UUID(buffer->ReadString(36));
      }

      username = buffer->ReadString(MAXIMUM_USERNAME_SIZE);
      if (version >= &ProtocolVersion::MINECRAFT_1_19) {
        properties = buffer->ReadProperties();
      }
    }

    void Write(const ProtocolVersion* version, ByteBuffer* buffer) override {
      if (version >= &ProtocolVersion::MINECRAFT_1_19) {
        buffer->WriteUUID(uuid);
      } else if (version >= &ProtocolVersion::MINECRAFT_1_16_2) {
        buffer->WriteUUIDIntArray(uuid);
      } else {
        buffer->WriteString(uuid.ToString());
      }

      buffer->WriteString(username);
      if (version >= &ProtocolVersion::MINECRAFT_1_19) {
        buffer->WriteProperties(properties);
      }
    }

    uint32_t GetOrdinal() override {
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
