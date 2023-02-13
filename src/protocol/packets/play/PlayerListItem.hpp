#pragma once

#include "../../../utils/ordinal/OrdinalRegistry.hpp"
#include "../Packet.hpp"
#include <string>
#include <utility>

namespace Ship {

  class PlayerListAction {
   public:
    virtual ~PlayerListAction() = default;

    virtual void Write(const ProtocolVersion* version, ByteBuffer* buffer) = 0;
    virtual void Read(const ProtocolVersion* version, ByteBuffer* buffer) = 0;
    [[nodiscard]] virtual uint32_t Size(const ProtocolVersion* version) const = 0;
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

    void Write(const ProtocolVersion* version, ByteBuffer* buffer) override {
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

    void Read(const ProtocolVersion* version, ByteBuffer* buffer) override {
      gameProfile = GameProfile(buffer->ReadUUID(), buffer->ReadString(), buffer->ReadProperties());
      gamemode = (Gamemode) buffer->ReadVarInt();
      ping = buffer->ReadVarInt();
      if (buffer->ReadBoolean()) {
        displayName = buffer->ReadString();
      } else {
        displayName.reset();
      }
      if (version >= &ProtocolVersion::MINECRAFT_1_19) {

      }
    }

    [[nodiscard]] uint32_t Size(const ProtocolVersion* version) const override {
      uint32_t size = ByteBuffer::StringBytes(gameProfile.GetName()) + ByteBuffer::UUID_SIZE + ByteBuffer::PropertiesBytes(gameProfile.GetProperties())
                    + ByteBuffer::VarIntBytes(gamemode) + ByteBuffer::VarIntBytes(ping) + ByteBuffer::BOOLEAN_SIZE;
      if (displayName) {
        size += ByteBuffer::StringBytes(*displayName);
      }
      if (version >= &ProtocolVersion::MINECRAFT_1_19) {
        size += ByteBuffer::BOOLEAN_SIZE;
        if (hasSigData) {
          size += ByteBuffer::LONG_SIZE;
          if (publicKey) {
            size += ByteBuffer::VarIntBytes(publicKey->GetReadableBytes()) + publicKey->GetReadableBytes();
          } else {
            size += ByteBuffer::BYTE_SIZE;
          }
          if (signature) {
            size += ByteBuffer::VarIntBytes(signature->GetReadableBytes()) + signature->GetReadableBytes();
          } else {
            size += ByteBuffer::BYTE_SIZE;
          }
        }
      }
      return size;
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

    void Write(const ProtocolVersion* version, ByteBuffer* buffer) override {
      buffer->WriteUUID(uuid);
      buffer->WriteVarInt(gamemode);
    }

    void Read(const ProtocolVersion* version, ByteBuffer* buffer) override {
      uuid = buffer->ReadUUID();
      gamemode = (Gamemode) buffer->ReadVarInt();
    }

    [[nodiscard]] uint32_t Size(const ProtocolVersion* version) const override {
      return ByteBuffer::UUID_SIZE + ByteBuffer::VarIntBytes(gamemode);
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

    void Write(const ProtocolVersion* version, ByteBuffer* buffer) override {
      buffer->WriteUUID(uuid);
      buffer->WriteVarInt(ping);
    }

    void Read(const ProtocolVersion* version, ByteBuffer* buffer) override {
      uuid = buffer->ReadUUID();
      ping = buffer->ReadVarInt();
    }

    [[nodiscard]] uint32_t Size(const ProtocolVersion* version) const override {
      return ByteBuffer::UUID_SIZE + ByteBuffer::VarIntBytes(ping);
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

    void Write(const ProtocolVersion* version, ByteBuffer* buffer) override {
      buffer->WriteUUID(uuid);
      buffer->WriteBoolean(displayName.has_value());
      if (displayName) {
        buffer->WriteString(*displayName);
      }
    }

    void Read(const ProtocolVersion* version, ByteBuffer* buffer) override {
      uuid = buffer->ReadUUID();
      if (buffer->ReadBoolean()) {
        displayName = buffer->ReadString();
      } else {
        displayName.reset();
      }
    }

    [[nodiscard]] uint32_t Size(const ProtocolVersion* version) const override {
      return ByteBuffer::UUID_SIZE + ByteBuffer::BOOLEAN_SIZE + (displayName ? ByteBuffer::StringBytes(*displayName) : 0);
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

    void Write(const ProtocolVersion* version, ByteBuffer* buffer) override {
      buffer->WriteUUID(uuid);
    }

    void Read(const ProtocolVersion* version, ByteBuffer* buffer) override {
      uuid = buffer->ReadUUID();
    }

    [[nodiscard]] uint32_t Size(const ProtocolVersion* version) const override {
      return ByteBuffer::UUID_SIZE;
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

    ~PlayerListItem() override {
      for (PlayerListAction* player : players) {
        delete player;
      }
    }

    void Read(const ProtocolVersion* version, ByteBuffer* buffer) override {
      for (PlayerListAction* player : players) {
        delete player;
      }

      uint32_t actionId = buffer->ReadVarInt();
      players.resize(buffer->ReadVarInt());
      for (PlayerListAction*& player : players) {
        switch (actionId) {
          case 0:
            player = new PlayerListAddPlayer(GameProfile({}, {}, {}), {}, 0, {}, false, 0, nullptr, nullptr);
            break;

          case 1:
            player = new PlayerListUpdateGamemode({}, {});
            break;

          case 2:
            player = new PlayerListUpdateLatency({}, 0);
            break;

          case 3:
            player = new PlayerListUpdateDisplayName({}, {});
            break;

          case 4:
            player = new PlayerListRemovePlayer({});
            break;

          default:
            throw Exception("Unexpected value");
        }
        player->Read(version, buffer);
      }
    }

    void Write(const ProtocolVersion* version, ByteBuffer* buffer) override {
    }

    uint32_t Size(const ProtocolVersion* version) override {
      uint32_t size = ByteBuffer::VarIntBytes(action) + ByteBuffer::VarIntBytes(players.size());
      for (PlayerListAction* player : players) {
        size += player->Size(version);
      }

      return size;
    }

    uint32_t GetOrdinal() override {
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
