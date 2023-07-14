#pragma once

#include "../../../../lib/ShipNet/src/utils/ordinal/OrdinalRegistry.hpp"
#include <string>
#include <utility>

namespace Ship {

  class PlayerListAction : public Serializable {
   public:
    ~PlayerListAction() override = default;
  };

  template<typename T>
  class InvalidPlayerListActionErrorable : public Errorable<T> {
   public:
    static inline const uint32_t TYPE_ORDINAL = OrdinalRegistry::ErrorableTypeRegistry.RegisterOrdinal();

    explicit InvalidPlayerListActionErrorable(uint32_t action_id) : Errorable<T>(TYPE_ORDINAL, {}, action_id) {
    }

    void Print(std::ostream o) {
      o << "Invalid player list action received, action id: " << this->GetErrorCode();
    }
  };

  class PlayerListAddPlayer : public PlayerListAction {
   private:
    GameProfile gameProfile{{}, {}, {}};
    Gamemode gamemode{};
    uint32_t ping{};
    std::optional<std::string> displayName;
    bool hasSigData{};
    uint64_t timestamp{};
    ByteBuffer* publicKey{};
    ByteBuffer* signature{};

   public:
    static inline const uint32_t ACTION_ID = 0;

    PlayerListAddPlayer() = default;
    PlayerListAddPlayer(GameProfile gameProfile, Gamemode gamemode, uint32_t ping, std::optional<std::string> displayName)
      : gameProfile(std::move(gameProfile)), gamemode(gamemode), ping(ping), displayName(std::move(displayName)) {
    }
    PlayerListAddPlayer(GameProfile gameProfile, Gamemode gamemode, uint32_t ping, std::optional<std::string> displayName, bool hasSigData,
      uint64_t timestamp, ByteBuffer* publicKey, ByteBuffer* signature)
      : gameProfile(std::move(gameProfile)), gamemode(gamemode), ping(ping), displayName(std::move(displayName)), hasSigData(hasSigData),
        timestamp(timestamp), publicKey(publicKey), signature(signature) {
    }

    ~PlayerListAddPlayer() override {
      delete publicKey;
      delete signature;
    }

    Errorable<bool> Write(const ProtocolVersion* version, ByteBuffer* buffer) const override {
      buffer->WriteUUID(gameProfile.GetUuid());
      buffer->WriteString(gameProfile.GetName());
      ProtocolUtils::WriteProperties(buffer, gameProfile.GetProperties());
      buffer->WriteVarInt(gamemode);
      buffer->WriteVarInt(ping);
      buffer->WriteBoolean(displayName.has_value());
      if (displayName) {
        buffer->WriteString(*displayName);
      }
      if (hasSigData && version >= &MinecraftProtocolVersion::MINECRAFT_1_19) {
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
      return SuccessErrorable<bool>(true);
    }

    static Errorable<PlayerListAddPlayer*> Instantiate(const PacketHolder& holder) {
      ByteBuffer* buffer = holder.GetCurrentBuffer();
      const ProtocolVersion* version = holder.GetVersion();

      ProceedErrorable(uuid, UUID, buffer->ReadUUID(), InvalidPlayerListActionErrorable<PlayerListAddPlayer*>(buffer->GetReadableBytes()))
      ProceedErrorable(name, std::string, buffer->ReadString(), InvalidPlayerListActionErrorable<PlayerListAddPlayer*>(buffer->GetReadableBytes()))
      ProceedErrorable(properties, std::vector<GameProfileProperty>, ProtocolUtils::ReadProperties(buffer), InvalidPlayerListActionErrorable<PlayerListAddPlayer*>(buffer->GetReadableBytes()))
      GameProfile profile = GameProfile(uuid, name, properties);
            
      ProceedErrorable(gamemodeInt, uint32_t, buffer->ReadVarInt(), InvalidPlayerListActionErrorable<PlayerListAddPlayer*>(buffer->GetReadableBytes()))
      auto gamemode = (Gamemode) gamemodeInt;
      
      ProceedErrorable(ping, uint32_t, buffer->ReadVarInt(), InvalidPlayerListActionErrorable<PlayerListAddPlayer*>(buffer->GetReadableBytes()))

      ProceedErrorable(hasDisplayName, bool, buffer->ReadBoolean(), InvalidPlayerListActionErrorable<PlayerListAddPlayer*>(buffer->GetReadableBytes()))
      std::optional<std::string> displayName;
      if (hasDisplayName) {
        SetFromErrorable(displayName, std::string, buffer->ReadString(), InvalidPlayerListActionErrorable<PlayerListAddPlayer*>(buffer->GetReadableBytes()))
      }

      if (version >= &MinecraftProtocolVersion::MINECRAFT_1_19) {
        // TODO: 1.19+
      }
      return SuccessErrorable<PlayerListAddPlayer*>(new PlayerListAddPlayer(profile, gamemode, ping, displayName));
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
    Gamemode gamemode{};

   public:
    static inline const uint32_t ACTION_ID = 1;

    PlayerListUpdateGamemode() = default;
    PlayerListUpdateGamemode(const UUID& uuid, Gamemode gamemode) : uuid(uuid), gamemode(gamemode) {
    }

    static Errorable<PlayerListUpdateGamemode*> Instantiate(const PacketHolder& holder) {
      ByteBuffer* buffer = holder.GetCurrentBuffer();
      ProceedErrorable(uuid, UUID, buffer->ReadUUID(), InvalidPlayerListActionErrorable<PlayerListUpdateGamemode*>(buffer->GetReadableBytes()))
      ProceedErrorable(gamemodeInt, uint32_t, buffer->ReadVarInt(), InvalidPlayerListActionErrorable<PlayerListUpdateGamemode*>(buffer->GetReadableBytes()))
      auto gamemode = (Gamemode) gamemodeInt;
      return SuccessErrorable<PlayerListUpdateGamemode*>(new PlayerListUpdateGamemode(uuid, gamemode));
    }

    Errorable<bool> Write(const ProtocolVersion* version, ByteBuffer* buffer) const override {
      buffer->WriteUUID(uuid);
      buffer->WriteVarInt(gamemode);
      return SuccessErrorable<bool>(true);
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
    uint32_t ping{};

   public:
    static inline const uint32_t ACTION_ID = 2;

    PlayerListUpdateLatency() = default;
    PlayerListUpdateLatency(const UUID& uuid, uint32_t ping) : uuid(uuid), ping(ping) {
    }

    static Errorable<PlayerListUpdateLatency*> Instantiate(const PacketHolder& holder) {
      ByteBuffer* buffer = holder.GetCurrentBuffer();
      ProceedErrorable(uuid, UUID, buffer->ReadUUID(), InvalidPlayerListActionErrorable<PlayerListUpdateLatency*>(buffer->GetReadableBytes()))
      ProceedErrorable(ping, uint32_t, buffer->ReadVarInt(), InvalidPlayerListActionErrorable<PlayerListUpdateLatency*>(buffer->GetReadableBytes()))
      return SuccessErrorable<PlayerListUpdateLatency*>(new PlayerListUpdateLatency(uuid, ping));
    }

    Errorable<bool> Write(const ProtocolVersion* version, ByteBuffer* buffer) const override {
      buffer->WriteUUID(uuid);
      buffer->WriteVarInt(ping);
      return SuccessErrorable<bool>(true);
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
    static inline const uint32_t ACTION_ID = 3;

    PlayerListUpdateDisplayName() = default;
    PlayerListUpdateDisplayName(const UUID& uuid, std::optional<std::string> displayName) : uuid(uuid), displayName(std::move(displayName)) {
    }

    static Errorable<PlayerListUpdateDisplayName*> Instantiate(const PacketHolder& holder) {
      ByteBuffer* buffer = holder.GetCurrentBuffer();
      ProceedErrorable(uuid, UUID, buffer->ReadUUID(), InvalidPlayerListActionErrorable<PlayerListUpdateDisplayName*>(buffer->GetReadableBytes()))

      std::optional<std::string> displayName;

      ProceedErrorable(hasDisplayName, bool, buffer->ReadBoolean(), InvalidPlayerListActionErrorable<PlayerListUpdateDisplayName*>(buffer->GetReadableBytes()))
      if (hasDisplayName) {
        SetFromErrorable(displayName, std::string, buffer->ReadString(), InvalidPlayerListActionErrorable<PlayerListUpdateDisplayName*>(buffer->GetReadableBytes()))
      }
      return SuccessErrorable<PlayerListUpdateDisplayName*>(new PlayerListUpdateDisplayName(uuid, displayName));
    }

    Errorable<bool> Write(const ProtocolVersion* version, ByteBuffer* buffer) const override {
      buffer->WriteUUID(uuid);
      buffer->WriteBoolean(displayName.has_value());
      if (displayName) {
        buffer->WriteString(*displayName);
      }
      return SuccessErrorable<bool>(true);
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
    static inline const uint32_t ACTION_ID = 4;

    PlayerListRemovePlayer() = default;
    explicit PlayerListRemovePlayer(const UUID& uuid) : uuid(uuid) {
    }

    static Errorable<PlayerListRemovePlayer*> Instantiate(const PacketHolder& holder) {
      ByteBuffer* buffer = holder.GetCurrentBuffer();
      ProceedErrorable(uuid, UUID, buffer->ReadUUID(), InvalidPlayerListActionErrorable<PlayerListRemovePlayer*>(buffer->GetReadableBytes()))
      return SuccessErrorable<PlayerListRemovePlayer*>(new PlayerListRemovePlayer(uuid));
    }

    Errorable<bool> Write(const ProtocolVersion* version, ByteBuffer* buffer) const override {
      buffer->WriteUUID(uuid);
      return SuccessErrorable<bool>(true);
    }

    [[nodiscard]] const UUID& GetUuid() const {
      return uuid;
    }
  };

  class PlayerListItem : public Packet {
   private:
    uint32_t action{};
    std::vector<PlayerListAction*> players;

   public:
    static inline const uint32_t PACKET_ORDINAL = OrdinalRegistry::PacketRegistry.RegisterOrdinal();

    PlayerListItem() = default;
    PlayerListItem(uint32_t action, std::vector<PlayerListAction*> players) : action(action), players(std::move(players)) {
    }

    ~PlayerListItem() override = default;

    static Errorable<PlayerListItem> Instantiate(const PacketHolder& holder);

    Errorable<bool> Write(const ProtocolVersion* version, ByteBuffer* buffer) const override {
      // TODO: Write PlayerListItem
      return SuccessErrorable<bool>(true);
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
  CreateInvalidArgumentErrorable(UnknownPlayerListActionErrorable, PlayerListItem, "Unknown player list action");

  Errorable<PlayerListItem> PlayerListItem::Instantiate(const PacketHolder& holder) {
    ByteBuffer* buffer = holder.GetCurrentBuffer();
    ProceedErrorable(actionID, uint32_t, buffer->ReadVarInt(), InvalidPacketErrorable<PlayerListItem>(PACKET_ORDINAL))
    ProceedErrorable(recordsSize, uint32_t, buffer->ReadVarInt(), InvalidPacketErrorable<PlayerListItem>(PACKET_ORDINAL))
    std::vector<PlayerListAction*> players(recordsSize);
    for (PlayerListAction*& player : players) {
      switch (actionID) {
        case PlayerListAddPlayer::ACTION_ID: {
          SetFromErrorable(player, PlayerListAddPlayer*, PlayerListAddPlayer::Instantiate(holder), InvalidPacketErrorable<PlayerListItem>(PACKET_ORDINAL))
          break;
        }
        case PlayerListUpdateGamemode::ACTION_ID: {
          SetFromErrorable(player, PlayerListUpdateGamemode*, PlayerListUpdateGamemode::Instantiate(holder), InvalidPacketErrorable<PlayerListItem>(PACKET_ORDINAL))
          break;
        }
        case PlayerListUpdateLatency::ACTION_ID: {
          SetFromErrorable(player, PlayerListUpdateLatency*, PlayerListUpdateLatency::Instantiate(holder), InvalidPacketErrorable<PlayerListItem>(PACKET_ORDINAL))
          break;
        }
        case PlayerListUpdateDisplayName::ACTION_ID: {
          SetFromErrorable(player, PlayerListUpdateDisplayName*, PlayerListUpdateDisplayName::Instantiate(holder), InvalidPacketErrorable<PlayerListItem>(PACKET_ORDINAL))
          break;
        }
        case PlayerListRemovePlayer::ACTION_ID: {
          SetFromErrorable(player, PlayerListRemovePlayer*, PlayerListRemovePlayer::Instantiate(holder), InvalidPacketErrorable<PlayerListItem>(PACKET_ORDINAL))
          break;
        }
        default: {
          return UnknownPlayerListActionErrorable(actionID);
        }
      }
    }

    return SuccessErrorable<PlayerListItem>(PlayerListItem(actionID, players));
  }
}
