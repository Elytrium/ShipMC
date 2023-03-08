#pragma once

#include "../../../utils/ordinal/OrdinalRegistry.hpp"
#include "../Packet.hpp"
#include <string>
#include <utility>

namespace Ship {

  class PlayerListAction : public Serializable {
   public:
    ~PlayerListAction() override = default;
  };

  class PlayerListAddPlayer : public PlayerListAction {
   private:
    GameProfile gameProfile;
    Gamemode gamemode;
    uint32_t ping;
    std::optional<std::string> displayName;
    bool hasSigData;
    uint64_t timestamp;
    ByteBuffer* publicKey;
    ByteBuffer* signature;

   public:
    PlayerListAddPlayer(GameProfile gameProfile, Gamemode gamemode, uint32_t ping, std::optional<std::string> displayName, bool hasSigData,
      uint64_t timestamp, ByteBuffer* publicKey, ByteBuffer* signature)
      : gameProfile(std::move(gameProfile)), gamemode(gamemode), ping(ping), displayName(std::move(displayName)), hasSigData(hasSigData),
        timestamp(timestamp), publicKey(publicKey), signature(signature) {
    }

    ~PlayerListAddPlayer() override {
      delete publicKey;
      delete signature;
    }

    void Write(const ProtocolVersion* version, ByteBuffer* buffer) const override {
      buffer->WriteUUID(gameProfile.GetUuid());
      buffer->WriteString(gameProfile.GetName());
      buffer->WriteProperties(gameProfile.GetProperties());
      buffer->WriteVarInt(gamemode);
      buffer->WriteVarInt(ping);
      buffer->WriteBoolean(displayName.has_value());
      if (displayName) {
        buffer->WriteString(*displayName);
      }
      if (hasSigData && version >= &ProtocolVersion::MINECRAFT_1_19) {
        buffer->WriteLong(timestamp);
        if (publicKey) {
          buffer->WriteVarInt(publicKey->GetReadableBytes());
          buffer->WriteBytes(publicKey, publicKey->GetReadableBytes());
        } else {
          buffer->WriteByte(0);
        }
        if (signature) {
          buffer->WriteVarInt(signature->GetReadableBytes());
          buffer->WriteBytes(signature, signature->GetReadableBytes());
        } else {
          buffer->WriteByte(0);
        }
      }
    }

    PlayerListAddPlayer(const ProtocolVersion* version, ByteBuffer* buffer)
      : gameProfile(GameProfile(buffer->ReadUUID(), buffer->ReadString(), buffer->ReadProperties())), gamemode((Gamemode) buffer->ReadVarInt()),
        ping(buffer->ReadVarInt()) {
      if (buffer->ReadBoolean()) {
        displayName = buffer->ReadString();
      } else {
        displayName.reset();
      }
      if (version >= &ProtocolVersion::MINECRAFT_1_19) {
        // TODO: 1.19+
      }
    }

    [[nodiscard]] const GameProfile& GetGameProfile() const {
      return gameProfile;
    }

    [[nodiscard]] Gamemode GetGamemode() const {
      return gamemode;
    }

    [[nodiscard]] uint32_t GetPing() const {
      return ping;
    }

    [[nodiscard]] const std::optional<std::string>& GetDisplayName() const {
      return displayName;
    }

    [[nodiscard]] bool IsHasSigData() const {
      return hasSigData;
    }

    [[nodiscard]] uint64_t GetTimestamp() const {
      return timestamp;
    }

    [[nodiscard]] ByteBuffer* GetPublicKey() const {
      return publicKey;
    }

    [[nodiscard]] ByteBuffer* GetSignature() const {
      return signature;
    }
  };

  class PlayerListUpdateGamemode : public PlayerListAction {
   private:
    UUID uuid;
    Gamemode gamemode;

   public:
    PlayerListUpdateGamemode(const UUID& uuid, Gamemode gamemode) : uuid(uuid), gamemode(gamemode) {
    }

    PlayerListUpdateGamemode(const ProtocolVersion* version, ByteBuffer* buffer) {
      uuid = buffer->ReadUUID();
      gamemode = (Gamemode) buffer->ReadVarInt();
    }

    void Write(const ProtocolVersion* version, ByteBuffer* buffer) const override {
      buffer->WriteUUID(uuid);
      buffer->WriteVarInt(gamemode);
    }

    [[nodiscard]] const UUID& GetUuid() const {
      return uuid;
    }

    [[nodiscard]] Gamemode GetGamemode() const {
      return gamemode;
    }
  };

  class PlayerListUpdateLatency : public PlayerListAction {
   private:
    UUID uuid;
    uint32_t ping;

   public:
    PlayerListUpdateLatency(const UUID& uuid, uint32_t ping) : uuid(uuid), ping(ping) {
    }

    PlayerListUpdateLatency(const ProtocolVersion* version, ByteBuffer* buffer) {
      uuid = buffer->ReadUUID();
      ping = buffer->ReadVarInt();
    }

    void Write(const ProtocolVersion* version, ByteBuffer* buffer) const override {
      buffer->WriteUUID(uuid);
      buffer->WriteVarInt(ping);
    }

    [[nodiscard]] const UUID& GetUuid() const {
      return uuid;
    }

    [[nodiscard]] uint32_t GetPing() const {
      return ping;
    }
  };

  class PlayerListUpdateDisplayName : public PlayerListAction {
   private:
    UUID uuid;
    std::optional<std::string> displayName;

   public:
    PlayerListUpdateDisplayName(const UUID& uuid, std::optional<std::string> displayName) : uuid(uuid), displayName(std::move(displayName)) {
    }

    PlayerListUpdateDisplayName(const ProtocolVersion* version, ByteBuffer* buffer) {
      uuid = buffer->ReadUUID();
      if (buffer->ReadBoolean()) {
        displayName = buffer->ReadString();
      } else {
        displayName.reset();
      }
    }

    void Write(const ProtocolVersion* version, ByteBuffer* buffer) const override {
      buffer->WriteUUID(uuid);
      buffer->WriteBoolean(displayName.has_value());
      if (displayName) {
        buffer->WriteString(*displayName);
      }
    }

    [[nodiscard]] const UUID& GetUuid() const {
      return uuid;
    }

    [[nodiscard]] const std::optional<std::string>& GetDisplayName() const {
      return displayName;
    }
  };

  class PlayerListRemovePlayer : public PlayerListAction {
   private:
    UUID uuid;

   public:
    explicit PlayerListRemovePlayer(const UUID& uuid) : uuid(uuid) {
    }

    PlayerListRemovePlayer(const ProtocolVersion* version, ByteBuffer* buffer) {
      uuid = buffer->ReadUUID();
    }

    void Write(const ProtocolVersion* version, ByteBuffer* buffer) const override {
      buffer->WriteUUID(uuid);
    }

    [[nodiscard]] const UUID& GetUuid() const {
      return uuid;
    }
  };

  class PlayerListItem : public Packet {
   private:
    uint32_t action;
    std::vector<PlayerListAction*> players;

   public:
    static inline const uint32_t PACKET_ORDINAL = OrdinalRegistry::PacketRegistry.RegisterOrdinal();

    PlayerListItem(uint32_t action, std::vector<PlayerListAction*> players) : action(action), players(std::move(players)) {
    }

    ~PlayerListItem() override = default;

    PlayerListItem(const ProtocolVersion* version, ByteBuffer* buffer) {
      action = buffer->ReadVarInt();
      players.resize(buffer->ReadVarInt());
      for (PlayerListAction*& player : players) {
        switch (action) {
          case 0:
            player = new PlayerListAddPlayer(version, buffer);
            break;

          case 1:
            player = new PlayerListUpdateGamemode(version, buffer);
            break;

          case 2:
            player = new PlayerListUpdateLatency(version, buffer);
            break;

          case 3:
            player = new PlayerListUpdateDisplayName(version, buffer);
            break;

          case 4:
            player = new PlayerListRemovePlayer(version, buffer);
            break;

          default:
            throw Exception("Unexpected value");
        }
      }
    }

    void Write(const ProtocolVersion* version, ByteBuffer* buffer) const override {
      // TODO: Write PlayerListItem
    }

    uint32_t GetOrdinal() const override {
      return PACKET_ORDINAL;
    }

    [[nodiscard]] uint32_t GetAction() const {
      return action;
    }

    [[nodiscard]] const std::vector<PlayerListAction*>& GetPlayers() const {
      return players;
    }
  };
}
