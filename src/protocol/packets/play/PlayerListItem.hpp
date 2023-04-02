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

    explicit PlayerListAddPlayer(const PacketHolder& holder)
      : gameProfile(
        GameProfile(holder.GetCurrentBuffer()->ReadUUID(), holder.GetCurrentBuffer()->ReadString(), holder.GetCurrentBuffer()->ReadProperties())),
        gamemode((Gamemode) holder.GetCurrentBuffer()->ReadVarInt()), ping(holder.GetCurrentBuffer()->ReadVarInt()) {
      ByteBuffer* buffer = holder.GetCurrentBuffer();
      const ProtocolVersion* version = holder.GetVersion();
      if (buffer->ReadBoolean()) {
        ProceedErrorable(displayName, std::string, buffer->ReadString(), InvalidPacketErrorable<>(PACKET_ORDINAL))
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

    static Errorable<PlayerListUpdateGamemode> Instantiate(const PacketHolder& holder) {
      ByteBuffer* buffer = holder.GetCurrentBuffer();
      ProceedErrorable(uuid, UUID, buffer->ReadUUID(), InvalidPacketErrorable<>(PACKET_ORDINAL))
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

    static Errorable<PlayerListUpdateLatency> Instantiate(const PacketHolder& holder) {
      ByteBuffer* buffer = holder.GetCurrentBuffer();
      ProceedErrorable(uuid, UUID, buffer->ReadUUID(), InvalidPacketErrorable<>(PACKET_ORDINAL))
      ProceedErrorable(ping, uint32_t, buffer->ReadVarInt(), InvalidPacketErrorable<>(PACKET_ORDINAL))
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

    static Errorable<PlayerListUpdateDisplayName> Instantiate(const PacketHolder& holder) {
      ByteBuffer* buffer = holder.GetCurrentBuffer();
      ProceedErrorable(uuid, UUID, buffer->ReadUUID(), InvalidPacketErrorable<>(PACKET_ORDINAL))
      if (buffer->ReadBoolean()) {
        ProceedErrorable(displayName, std::string, buffer->ReadString(), InvalidPacketErrorable<>(PACKET_ORDINAL))
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

    static Errorable<PlayerListRemovePlayer> Instantiate(const PacketHolder& holder) {
      ByteBuffer* buffer = holder.GetCurrentBuffer();
      ProceedErrorable(uuid, UUID, buffer->ReadUUID(), InvalidPacketErrorable<>(PACKET_ORDINAL))
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

    static Errorable<PlayerListItem> Instantiate(const PacketHolder& holder) {
      ByteBuffer* buffer = holder.GetCurrentBuffer();
      ProceedErrorable(action, uint32_t, buffer->ReadVarInt(), InvalidPacketErrorable<>(PACKET_ORDINAL))
      players.resize(buffer->ReadVarInt());
      for (PlayerListAction*& player : players) {
        switch (action) {
          case 0:
            player = new PlayerListAddPlayer(holder);
            break;

          case 1:
            player = new PlayerListUpdateGamemode(holder);
            break;

          case 2:
            player = new PlayerListUpdateLatency(holder);
            break;

          case 3:
            player = new PlayerListUpdateDisplayName(holder);
            break;

          case 4:
            player = new PlayerListRemovePlayer(holder);
            break;

          default:
            throw Exception("Unexpected value");
        }
      }
    }

    void Write(const ProtocolVersion* version, ByteBuffer* buffer) const override {
      // TODO: Write PlayerListItem
    }

    [[nodiscard]] uint32_t GetOrdinal() const override {
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
