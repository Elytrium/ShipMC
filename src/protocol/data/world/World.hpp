#pragma once

#include "../../packets/prepared/PreparedPacket.hpp"
#include "../nbt/NBT.hpp"
#include "../player/Player.hpp"
#include <functional>
#include <map>
#include <optional>
#include <set>
#include <string>
#include <utility>
namespace Ship {
  class BiomeParticleOptions {
   private:
    std::string type;

   public:
    explicit BiomeParticleOptions(std::string type);

    static BiomeParticleOptions Decode(CompoundTag* nbt);

    CompoundTag* Encode();
  };

  class BiomeParticle {
   private:
    float probability;
    BiomeParticleOptions options;

   public:
    BiomeParticle(float probability, BiomeParticleOptions options);

    static BiomeParticle Decode(CompoundTag* nbt);

    CompoundTag* Encode();
  };

  class BiomeAdditionsSound {
   private:
    std::string sound;
    double tickChance;

   public:
    BiomeAdditionsSound(std::string sound, double tickChance);

    static BiomeAdditionsSound Decode(CompoundTag* nbt);

    CompoundTag* Encode();
  };

  class BiomeMusic {
   private:
    bool replaceCurrentMusic;
    std::string sound;
    uint32_t maxDelay;
    uint32_t minDelay;

   public:
    BiomeMusic(bool replaceCurrentMusic, const std::string& sound, uint32_t maxDelay, uint32_t minDelay);

    static BiomeMusic Decode(CompoundTag* nbt);

    CompoundTag* Encode();
  };

  class BiomeMoodSound {
   private:
    uint32_t tickDelay;
    double offset;
    uint32_t blockSearchExtent;
    std::string sound;

   public:
    BiomeMoodSound(uint32_t tickDelay, double offset, uint32_t blockSearchExtent, std::string sound);

    static BiomeMoodSound Decode(CompoundTag* nbt);

    CompoundTag* Encode();
  };

  class BiomeEffects {
   private:
    uint32_t skyColor;
    uint32_t waterFogColor;
    uint32_t fogColor;
    uint32_t waterColor;

    std::optional<uint32_t> foliageColor;
    std::optional<std::string> grassColorModifier;
    std::optional<BiomeMusic> music;
    std::optional<std::string> ambientSound;
    std::optional<BiomeAdditionsSound> additionsSound;
    std::optional<BiomeMoodSound> moodSound;
    std::optional<BiomeParticle> particle;

   public:
    BiomeEffects(uint32_t skyColor, uint32_t waterFogColor, uint32_t fogColor, uint32_t waterColor, std::optional<uint32_t> foliageColor,
      std::optional<std::string> grassColorModifier, std::optional<BiomeMusic> music, std::optional<std::string> ambientSound,
      std::optional<BiomeAdditionsSound> additionsSound, std::optional<BiomeMoodSound> moodSound, std::optional<BiomeParticle> particle);

    static BiomeEffects Decode(CompoundTag* nbt);

    CompoundTag* Encode();
  };

  class BiomeElement {
   private:
    std::string precipitation;
    float depth;
    float temperature;
    float scale;
    float downfall;
    std::string category;
    BiomeEffects effects;

   public:
    BiomeElement(std::string precipitation, float depth, float temperature, float scale, float downfall, std::string category, BiomeEffects effects);

    static BiomeElement Decode(CompoundTag* nbt);

    CompoundTag* Encode();
  };

  class Biome {
   private:
    std::string name;
    uint32_t id;
    BiomeElement element;

   public:
    Biome(std::string name, uint32_t id, BiomeElement element);

    static Biome Decode(CompoundTag* nbt);

    CompoundTag* Encode();
  };

  class Dimension {
   private:
    std::string key;
    uint32_t legacyID;
    uint32_t modernID;
    uint32_t sections;

    bool isNatural;
    float ambientLight;
    bool isShrunk;
    bool isUltrawarm;
    bool hasCeiling;
    bool hasLegacySkyLight;
    bool hasModernSkyLight;
    bool isPiglinSafe;
    bool doBedsWork;
    bool doRespawnAnchorsWork;
    bool hasRaids;
    int32_t logicalHeight;
    std::string burningBehaviourIdentifier;

    std::optional<uint64_t> fixedTime;
    std::optional<bool> createDragonFight;
    std::optional<double> coordinateScale;
    std::optional<std::string> effects;

    int32_t minY;
    int32_t height;
    uint32_t monsterSpawnBlockLightLimit;
    uint32_t monsterSpawnLightLevel;

    Biome* defaultBiome;

   public:
    Dimension(std::string key, uint32_t legacyId, uint32_t modernId, uint32_t sections, bool isNatural, float ambientLight, bool isShrunk,
      bool isUltrawarm, bool hasCeiling, bool hasLegacySkyLight, bool hasModernSkyLight, bool isPiglinSafe, bool doBedsWork, bool doRespawnAnchorsWork,
      bool hasRaids, int32_t logicalHeight, std::string burningBehaviourIdentifier, const std::optional<uint64_t>& fixedTime,
      const std::optional<bool>& createDragonFight, const std::optional<double>& coordinateScale, std::optional<std::string> effects, int32_t minY,
      int32_t height, uint32_t monsterSpawnBlockLightLimit, uint32_t monsterSpawnLightLevel, Biome* defaultBiome);

    static Dimension* FromLegacyID(uint32_t id);

    static Dimension* FromNBT(CompoundTag* nbt);

    [[nodiscard]] CompoundTag* Serialize() const;

    [[nodiscard]] const std::string& GetKey() const;

    [[nodiscard]] uint32_t GetLegacyId() const;

    [[nodiscard]] uint32_t GetModernId() const;

    [[nodiscard]] uint32_t GetSections() const;

    [[nodiscard]] bool HasLegacySkyLight() const;

    [[nodiscard]] bool HasModernSkyLight() const;

    [[nodiscard]] Biome* GetDefaultBiome() const;
  };

  class Block {
   private:
    uint16_t id;
    bool motionBlocking;

   public:
    Block() : id(0), motionBlocking(false) {
    }

    Block(uint16_t id, bool motionBlocking) : id(id), motionBlocking(motionBlocking) {
    }

    [[nodiscard]] uint16_t GetId() const {
      return id;
    }

    [[nodiscard]] bool IsMotionBlocking() const {
      return motionBlocking;
    }
  };

  class ChunkSection {
   private:
    uint32_t blockCount = 0;
    Block* blocks = new Block[MAX_BLOCKS_PER_SECTION];
    Biome** biomes = new Biome*[MAX_BIOMES_PER_SECTION];
    uint8_t* skyLight = new uint8_t[MAX_BIOMES_PER_SECTION / 2];
    uint8_t* blockLight = new uint8_t[MAX_BIOMES_PER_SECTION / 2];

   public:
    static const uint32_t MAX_BLOCKS_PER_SECTION = 16 * 16 * 16;
    static const uint32_t MAX_BIOMES_PER_SECTION = 4 * 4 * 4;

    ~ChunkSection();

    [[nodiscard]] uint32_t GetBlockCount() const;

    Block* GetBlocks();
    Biome** GetBiomes();

    void SetSkyLight(int32_t posX, int32_t posY, int32_t posZ, uint32_t data);
    void SetBlockLight(int32_t posX, int32_t posY, int32_t posZ, uint32_t data);
    void SetBlock(int32_t posX, int32_t posY, int32_t posZ, Block block);
    void SetBiome(int32_t posX, int32_t posY, int32_t posZ, Biome* biome);

    uint32_t GetSkyLight(int32_t posX, int32_t posY, int32_t posZ);
    uint32_t GetBlockLight(int32_t posX, int32_t posY, int32_t posZ);
    Block GetBlock(int32_t posX, int32_t posY, int32_t posZ);
    Biome* GetBiome(int32_t posX, int32_t posY, int32_t posZ);
  };

  class Chunk {
   private:
    uint32_t chunkPosX, chunkPosZ, sectionsAmount;
    ChunkSection* sections;
    Dimension* dimension;

   public:
    Chunk(int32_t posX, int32_t posZ, Biome* defaultBiome, Dimension* dimension);

    ~Chunk();

    ChunkSection& GetSection(uint32_t index);

    void SetSkyLight(int32_t posX, int32_t posY, int32_t posZ, uint32_t data);
    void SetBlockLight(int32_t posX, int32_t posY, int32_t posZ, uint32_t data);
    void SetBlock(int32_t posX, int32_t posY, int32_t posZ, Block block);
    void SetBiome(int32_t posX, int32_t posY, int32_t posZ, Biome* biome);

    uint32_t GetSkyLight(int32_t posX, int32_t posY, int32_t posZ);
    uint32_t GetBlockLight(int32_t posX, int32_t posY, int32_t posZ);
    Block GetBlock(int32_t posX, int32_t posY, int32_t posZ);
    Biome* GetBiome(int32_t posX, int32_t posY, int32_t posZ);

    [[nodiscard]] uint32_t GetChunkPosX() const;
    [[nodiscard]] uint32_t GetChunkPosZ() const;
    [[nodiscard]] uint32_t GetSectionsAmount() const;
    [[nodiscard]] Dimension* GetDimension() const;
  };

  class World {
   private:
    std::map<uint64_t, Chunk*> chunks {};
    Dimension* dimension;
    Biome* defaultBiome;
    std::set<Player> players;
    std::map<uint32_t, PreparedPacket> cachedPackets;

   public:
    World(Dimension* dimension, Biome* defaultBiome) : dimension(dimension), defaultBiome(defaultBiome) {
    }

    ~World();

    void SetSkyLight(int32_t posX, int32_t posY, int32_t posZ, uint32_t data);
    void SetBlockLight(int32_t posX, int32_t posY, int32_t posZ, uint32_t data);
    void SetBlock(int32_t posX, int32_t posY, int32_t posZ, Block block);
    void SetBiome(int32_t posX, int32_t posY, int32_t posZ, Biome* biome);

    uint32_t GetSkyLight(int32_t posX, int32_t posY, int32_t posZ);
    uint32_t GetBlockLight(int32_t posX, int32_t posY, int32_t posZ);
    Block GetBlock(int32_t posX, int32_t posY, int32_t posZ);
    Biome* GetBiome(int32_t posX, int32_t posY, int32_t posZ);

    bool HasChunk(int32_t posX, int32_t posZ);
    Chunk* GetChunk(int32_t posX, int32_t posZ);
    std::map<uint64_t, Chunk*>& GetChunks();
  };
}