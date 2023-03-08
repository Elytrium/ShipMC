#pragma once

#include "../../../utils/ordinal/OrdinalRegistry.hpp"
#include "../../ProtocolUtils.hpp"
#include "../../data/nbt/NBT.hpp"
#include "../../data/player/Player.hpp"
#include "../../data/world/World.hpp"
#include "../Packet.hpp"
#include <set>
#include <string>
#include <utility>

namespace Ship {

  class JoinGame : public Packet {
   private:
    uint32_t entityId;
    Gamemode gamemode;
    uint64_t partialHashedSeed;
    Difficulty difficulty;
    bool isHardcore;
    uint32_t maxPlayers;
    uint32_t viewDistance;
    bool reducedDebugInfo;
    bool showRespawnScreen;
    std::set<std::string> levelNames;
    std::map<std::string, Dimension*> dimensionRegistry;
    std::string registryIdentifier;
    std::string levelName;
    bool isFlat;
    bool isDebugType;
    Dimension* dimension;
    Gamemode previousGamemode;
    CompoundTag* biomeRegistry;
    uint32_t simulationDistance;
    bool hasLastDeathPosition;
    std::pair<std::string, uint64_t> lastDeathPosition;
    CompoundTag* chatTypeRegistry;
    CompoundTag* registryContainer;

   public:
    static inline const uint32_t PACKET_ORDINAL = OrdinalRegistry::PacketRegistry.RegisterOrdinal();

    JoinGame(uint32_t entityId, Gamemode gamemode, uint64_t partialHashedSeed, Difficulty difficulty, bool isHardcore, uint32_t maxPlayers,
      uint32_t viewDistance, bool reducedDebugInfo, bool showRespawnScreen, std::set<std::string> levelNames,
      std::map<std::string, Dimension*> dimensionRegistry, std::string registryIdentifier, std::string levelName, bool isFlat, bool isDebugType,
      Dimension* dimension, Gamemode previousGamemode, CompoundTag* biomeRegistry, uint32_t simulationDistance, bool hasLastDeathPosition,
      std::pair<std::string, uint64_t> lastDeathPosition, CompoundTag* chatTypeRegistry, CompoundTag* registryContainer)
      : entityId(entityId), gamemode(gamemode), partialHashedSeed(partialHashedSeed), difficulty(difficulty), isHardcore(isHardcore),
        maxPlayers(maxPlayers), viewDistance(viewDistance), reducedDebugInfo(reducedDebugInfo), showRespawnScreen(showRespawnScreen),
        levelNames(std::move(levelNames)), dimensionRegistry(std::move(dimensionRegistry)), registryIdentifier(std::move(registryIdentifier)),
        levelName(std::move(levelName)), isFlat(isFlat), isDebugType(isDebugType), dimension(dimension), previousGamemode(previousGamemode),
        biomeRegistry(biomeRegistry), simulationDistance(simulationDistance), hasLastDeathPosition(hasLastDeathPosition),
        lastDeathPosition(std::move(lastDeathPosition)), chatTypeRegistry(chatTypeRegistry), registryContainer(registryContainer) {
    }

    ~JoinGame() override {
      delete registryContainer;
    }

    explicit JoinGame(const PacketHolder& holder) {
      ByteBuffer* buffer = holder.GetCurrentBuffer();
      const ProtocolVersion* version = holder.GetVersion();
      entityId = buffer->ReadInt();
      if (version >= &ProtocolVersion::MINECRAFT_1_16_2) {
        isHardcore = buffer->ReadBoolean();
        gamemode = (Gamemode) buffer->ReadByte();
      } else {
        uint8_t gamemodeByte = buffer->ReadByte();
        isHardcore = gamemodeByte & 0x08;
        gamemode = (Gamemode) (gamemodeByte & ~0x08);
      }

      if (version >= &ProtocolVersion::MINECRAFT_1_16_2) {
        previousGamemode = (Gamemode) buffer->ReadByte();
        uint32_t arraySize = buffer->ReadVarInt();
        for (int i = 0; i < arraySize; ++i) {
          levelNames.insert(buffer->ReadString());
        }

        registryContainer = (CompoundTag*) ProtocolUtils::ReadNBT(buffer);
        ListTag* dimensionRegistryContainer;
        dimensionRegistryContainer = (ListTag*) ((CompoundTag*) registryContainer->GetNBT("minecraft:dimension_type").value())->GetNBT("value").value();
        biomeRegistry = (CompoundTag*) registryContainer->GetNBT("minecraft:worldgen/biome").value();
        if (version >= &ProtocolVersion::MINECRAFT_1_19) {
          chatTypeRegistry = (CompoundTag*) registryContainer->GetNBT("minecraft:chat_type").value();
        }

        for (const auto& item : dimensionRegistryContainer->GetList()) {
          Dimension* dimensionInRegistry = Dimension::FromNBT((CompoundTag*) item);
          dimensionRegistry.emplace(dimensionInRegistry->GetKey(), dimensionInRegistry);
        }

        delete dimensionRegistryContainer;

        if (version >= &ProtocolVersion::MINECRAFT_1_16_2 && version < &ProtocolVersion::MINECRAFT_1_19) {
          auto* currentDimDataTag = (CompoundTag*) (ProtocolUtils::ReadNBT(buffer));
          dimension = Dimension::FromNBT(currentDimDataTag);
          delete currentDimDataTag;
          registryIdentifier = buffer->ReadString();
          levelName = "world";
        } else {
          registryIdentifier = buffer->ReadString();
          levelName = buffer->ReadString();
        }

        partialHashedSeed = buffer->ReadLong();
        if (version >= &ProtocolVersion::MINECRAFT_1_16_2) {
          maxPlayers = buffer->ReadVarInt();
        } else {
          maxPlayers = buffer->ReadByte();
        }

        viewDistance = buffer->ReadVarInt();
        if (version >= &ProtocolVersion::MINECRAFT_1_16_2) {
          simulationDistance = buffer->ReadVarInt();
        } else {
          simulationDistance = viewDistance;
        }

        reducedDebugInfo = buffer->ReadBoolean();
        showRespawnScreen = buffer->ReadBoolean();
        isDebugType = buffer->ReadBoolean();
        isFlat = buffer->ReadBoolean();
        if (version >= &ProtocolVersion::MINECRAFT_1_19 && buffer->ReadBoolean()) {
          hasLastDeathPosition = true;
          lastDeathPosition = {buffer->ReadString(), buffer->ReadLong()};
        } else {
          hasLastDeathPosition = false;
        }

        difficulty = Difficulty::PEACEFUL;
      } else {
        previousGamemode = gamemode == Gamemode::SPECTATOR ? Gamemode::SURVIVAL : Gamemode::SPECTATOR;
        uint32_t dimensionIndex = buffer->ReadInt();
        dimension = Dimension::FromLegacyID(dimensionIndex);
        registryIdentifier = dimension->GetKey();

        if (version <= &ProtocolVersion::MINECRAFT_1_13_2) {
          difficulty = (Difficulty) buffer->ReadByte();
        } else {
          difficulty = Difficulty::PEACEFUL;
        }

        if (version >= &ProtocolVersion::MINECRAFT_1_15) {
          partialHashedSeed = buffer->ReadLong();
        } else {
          partialHashedSeed = 0;
        }

        levelName = "world";
        levelNames.insert(levelName);

        maxPlayers = buffer->ReadByte();
        isFlat = buffer->ReadString(16) == "flat";
        isDebugType = false;

        if (version >= &ProtocolVersion::MINECRAFT_1_14) {
          viewDistance = buffer->ReadVarInt();
        } else {
          viewDistance = 10;
        }

        simulationDistance = viewDistance;
        reducedDebugInfo = buffer->ReadBoolean();
        if (version >= &ProtocolVersion::MINECRAFT_1_15) {
          showRespawnScreen = buffer->ReadBoolean();
        } else {
          showRespawnScreen = true;
        }

        hasLastDeathPosition = false;
      }
    }

    void Write(const ProtocolVersion* version, ByteBuffer* buffer) const override {
      buffer->WriteInt(entityId);
      if (version >= &ProtocolVersion::MINECRAFT_1_16_2) {
        buffer->WriteBoolean(isHardcore);
        buffer->WriteByte(gamemode);
      } else {
        buffer->WriteByte((isHardcore && version >= &ProtocolVersion::MINECRAFT_1_13 ? 0x08 | gamemode : gamemode));
      }

      if (version >= &ProtocolVersion::MINECRAFT_1_16_2) {
        buffer->WriteByte(previousGamemode);
        buffer->WriteVarInt(levelNames.size());
        for (const auto& iLevelName : levelNames) {
          buffer->WriteString(iLevelName);
        }

        if (registryContainer != nullptr) {
          ProtocolUtils::WriteNBT(buffer, registryContainer);
        } else {
          auto* tag = new CompoundTag("");
          auto* dimensionRegistryContainer = new ListTag("value");
          for (const auto& item : dimensionRegistry) {
            dimensionRegistryContainer->GetList().emplace_back(item.second->Serialize());
          }

          auto* dimensionRegistryEntry = new CompoundTag("minecraft:dimension_type");
          dimensionRegistryEntry->AddNBT(new StringTag("type", "minecraft:dimension_type"));
          dimensionRegistryEntry->AddNBT(dimensionRegistryContainer);
          tag->AddNBT(dimensionRegistryEntry);
          tag->AddNBT(biomeRegistry);
          if (version >= &ProtocolVersion::MINECRAFT_1_19) {
            tag->AddNBT(chatTypeRegistry);
          }

          ProtocolUtils::WriteNBT(buffer, tag);
          delete tag;
        }

        if (version >= &ProtocolVersion::MINECRAFT_1_16_2 && version < &ProtocolVersion::MINECRAFT_1_19) {
          NBT* currentDimDataTag = dimension->Serialize();
          ProtocolUtils::WriteNBT(buffer, currentDimDataTag);
          delete currentDimDataTag;

          buffer->WriteString(registryIdentifier);
        } else {
          buffer->WriteString(registryIdentifier);
          buffer->WriteString(levelName);
        }

        buffer->WriteLong(partialHashedSeed);
        if (version >= &ProtocolVersion::MINECRAFT_1_16_2) {
          buffer->WriteVarInt(maxPlayers);
        } else {
          buffer->WriteByte(maxPlayers);
        }

        buffer->WriteVarInt(viewDistance);
        if (version >= &ProtocolVersion::MINECRAFT_1_16_2) {
          buffer->WriteVarInt(simulationDistance);
        }

        buffer->WriteBoolean(reducedDebugInfo);
        buffer->WriteBoolean(showRespawnScreen);
        buffer->WriteBoolean(isDebugType);
        buffer->WriteBoolean(isFlat);
        if (version >= &ProtocolVersion::MINECRAFT_1_19) {
          buffer->WriteBoolean(hasLastDeathPosition);
          if (hasLastDeathPosition) {
            buffer->WriteString(lastDeathPosition.first);
            buffer->WriteLong(lastDeathPosition.second);
          }
        }
      } else {
        buffer->WriteInt(dimension->GetLegacyId());

        if (version <= &ProtocolVersion::MINECRAFT_1_13_2) {
          buffer->WriteByte(difficulty);
        }

        if (version >= &ProtocolVersion::MINECRAFT_1_15) {
          buffer->WriteLong(partialHashedSeed);
        }

        buffer->WriteByte(maxPlayers);
        buffer->WriteString(isFlat ? "flat" : "default");

        if (version >= &ProtocolVersion::MINECRAFT_1_14) {
          buffer->WriteVarInt(viewDistance);
        }

        buffer->WriteBoolean(reducedDebugInfo);
        if (version >= &ProtocolVersion::MINECRAFT_1_15) {
          buffer->WriteBoolean(showRespawnScreen);
        }
      }
    }

    uint32_t GetOrdinal() const override {
      return PACKET_ORDINAL;
    }

    [[nodiscard]] uint32_t GetEntityId() const {
      return entityId;
    }

    [[nodiscard]] Gamemode GetGamemode() const {
      return gamemode;
    }

    [[nodiscard]] uint64_t GetPartialHashedSeed() const {
      return partialHashedSeed;
    }

    [[nodiscard]] Difficulty GetDifficulty() const {
      return difficulty;
    }

    [[nodiscard]] bool IsHardcore() const {
      return isHardcore;
    }

    [[nodiscard]] uint32_t GetMaxPlayers() const {
      return maxPlayers;
    }

    [[nodiscard]] uint32_t GetViewDistance() const {
      return viewDistance;
    }

    [[nodiscard]] bool IsReducedDebugInfo() const {
      return reducedDebugInfo;
    }

    [[nodiscard]] bool IsShowRespawnScreen() const {
      return showRespawnScreen;
    }

    [[nodiscard]] const std::set<std::string>& GetLevelNames() const {
      return levelNames;
    }

    [[nodiscard]] const std::map<std::string, Dimension*>& GetDimensionRegistry() const {
      return dimensionRegistry;
    }

    [[nodiscard]] const std::string& GetRegistryIdentifier() const {
      return registryIdentifier;
    }

    [[nodiscard]] const std::string& GetLevelName() const {
      return levelName;
    }

    [[nodiscard]] bool IsFlat() const {
      return isFlat;
    }

    [[nodiscard]] bool IsDebugType() const {
      return isDebugType;
    }

    [[nodiscard]] Dimension* GetDimension() const {
      return dimension;
    }

    [[nodiscard]] Gamemode GetPreviousGamemode() const {
      return previousGamemode;
    }

    [[nodiscard]] CompoundTag* GetBiomeRegistry() const {
      return biomeRegistry;
    }

    [[nodiscard]] uint32_t GetSimulationDistance() const {
      return simulationDistance;
    }

    [[nodiscard]] bool IsHasLastDeathPosition() const {
      return hasLastDeathPosition;
    }

    [[nodiscard]] const std::pair<std::string, uint64_t>& GetLastDeathPosition() const {
      return lastDeathPosition;
    }

    [[nodiscard]] CompoundTag* GetChatTypeRegistry() const {
      return chatTypeRegistry;
    }

    [[nodiscard]] CompoundTag* GetRegistryContainer() const {
      return registryContainer;
    }
  };
}
