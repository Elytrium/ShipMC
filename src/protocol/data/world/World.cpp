#include "World.hpp"

namespace Ship {
  World::~World() {
    for (const auto& item : chunks) {
      delete item.second;
    }
  }

  inline uint64_t getChunkIndex(int posX, int posZ) {
    return (uint64_t) posX << 32 | (posZ & 0xFFFFFFFFL);
  }

  bool World::HasChunk(int32_t posX, int32_t posZ) {
    return chunks.count(getChunkIndex(posX, posZ));
  }

  Chunk* World::GetChunk(int32_t posX, int32_t posZ) {
    uint64_t index = getChunkIndex(posX, posZ);
    if (chunks.count(index)) {
      return chunks.at(index);
    } else {
      auto* chunk = new Chunk(posX, posZ, defaultBiome, dimension);
      chunks.emplace(index, chunk);
      return chunk;
    }
  }

  std::map<uint64_t, Chunk*>& World::GetChunks() {
    return chunks;
  }

  void World::SetSkyLight(int32_t posX, int32_t posY, int32_t posZ, uint32_t data) {
    chunks.at(getChunkIndex(posX >> 4, posZ >> 4))->SetSkyLight(posX & 15, posY, posZ & 15, data);
  }

  void World::SetBlockLight(int32_t posX, int32_t posY, int32_t posZ, uint32_t data) {
    chunks.at(getChunkIndex(posX >> 4, posZ >> 4))->SetBlockLight(posX & 15, posY, posZ & 15, data);
  }

  void World::SetBlock(int32_t posX, int32_t posY, int32_t posZ, Block block) {
    chunks.at(getChunkIndex(posX >> 4, posZ >> 4))->SetBlock(posX & 15, posY, posZ & 15, block);
  }

  void World::SetBiome(int32_t posX, int32_t posY, int32_t posZ, Biome* biome) {
    chunks.at(getChunkIndex(posX >> 4, posZ >> 4))->SetBiome(posX & 15, posY, posZ & 15, biome);
  }

  uint32_t World::GetSkyLight(int32_t posX, int32_t posY, int32_t posZ) {
    return chunks.at(getChunkIndex(posX >> 4, posZ >> 4))->GetSkyLight(posX & 15, posY, posZ & 15);
  }

  uint32_t World::GetBlockLight(int32_t posX, int32_t posY, int32_t posZ) {
    return chunks.at(getChunkIndex(posX >> 4, posZ >> 4))->GetBlockLight(posX & 15, posY, posZ & 15);
  }

  Block World::GetBlock(int32_t posX, int32_t posY, int32_t posZ) {
    return chunks.at(getChunkIndex(posX >> 4, posZ >> 4))->GetBlock(posX & 15, posY, posZ & 15);
  }

  Biome* World::GetBiome(int32_t posX, int32_t posY, int32_t posZ) {
    return chunks.at(getChunkIndex(posX >> 4, posZ >> 4))->GetBiome(posX & 15, posY, posZ & 15);
  }
}