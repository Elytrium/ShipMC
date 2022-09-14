#include "World.hpp"

namespace Ship {
  ChunkSection::~ChunkSection() {
    delete[] blocks;
    delete[] biomes;
  }

  void NibbleArraySet(uint8_t* nibbleArray, uint32_t index, uint32_t data) {
    uint32_t arrayIndex = index >> 1;

    if (index & 1) {
      nibbleArray[arrayIndex] = (nibbleArray[arrayIndex] & 15) | ((data & 15) << 4);
    } else {
      nibbleArray[arrayIndex] = (nibbleArray[arrayIndex] & 240) | (data & 15);
    }
  }

  uint32_t NibbleArrayGet(const uint8_t* nibbleArray, uint32_t index) {
    uint32_t arrayIndex = index >> 1;

    if (index & 1) {
      return nibbleArray[arrayIndex] >> 4;
    } else {
      return nibbleArray[arrayIndex] & 15;
    }
  }

  inline uint32_t GetBlockIndex(int32_t posX, int32_t posY, int32_t posZ) {
    return posY << 8 | posZ << 4 | posX;
  }

  inline uint32_t GetBiomeIndex(int32_t posX, int32_t posY, int32_t posZ) {
    return (posY >> 2 & 63) << 4 | (posZ >> 2 & 3) << 2 | (posX >> 2 & 3);
  }

  void ChunkSection::SetSkyLight(int32_t posX, int32_t posY, int32_t posZ, uint32_t data) {
    NibbleArraySet(skyLight, GetBlockIndex(posX, posY, posZ), data);
  }

  void ChunkSection::SetBlockLight(int32_t posX, int32_t posY, int32_t posZ, uint32_t data) {
    NibbleArraySet(blockLight, GetBlockIndex(posX, posY, posZ), data);
  }

  void ChunkSection::SetBlock(int32_t posX, int32_t posY, int32_t posZ, Block block) {
    blocks[GetBlockIndex(posX, posY, posZ)] = block;
  }

  void ChunkSection::SetBiome(int32_t posX, int32_t posY, int32_t posZ, Biome* biome) {
    biomes[GetBiomeIndex(posX, posY, posZ)] = biome;
  }

  uint32_t ChunkSection::GetSkyLight(int32_t posX, int32_t posY, int32_t posZ) {
    return NibbleArrayGet(skyLight, GetBlockIndex(posX, posY, posZ));
  }

  uint32_t ChunkSection::GetBlockLight(int32_t posX, int32_t posY, int32_t posZ) {
    return NibbleArrayGet(blockLight, GetBlockIndex(posX, posY, posZ));
  }

  Block ChunkSection::GetBlock(int32_t posX, int32_t posY, int32_t posZ) {
    return blocks[GetBlockIndex(posX, posY, posZ)];
  }

  Biome* ChunkSection::GetBiome(int32_t posX, int32_t posY, int32_t posZ) {
    return biomes[GetBiomeIndex(posX, posY, posZ)];
  }

  Block* ChunkSection::GetBlocks() {
    return blocks;
  }

  Biome** ChunkSection::GetBiomes() {
    return biomes;
  }

  uint32_t ChunkSection::GetBlockCount() const {
    return blockCount;
  }

  inline uint32_t GetSectionIndex(int32_t posY) {
    // TODO: negative Y
    return posY >> 4;
  }

  Chunk::Chunk(int32_t posX, int32_t posZ, Biome* defaultBiome, Dimension* dimension)
    : chunkPosX(posX), chunkPosZ(posZ), sectionsAmount(dimension->GetSections()), sections(new ChunkSection[sectionsAmount]), dimension(dimension) {
    for (int i = 0; i < sectionsAmount; ++i) {
      Biome** biomes = sections[i].GetBiomes();
      std::fill(biomes, biomes + (ChunkSection::MAX_BIOMES_PER_SECTION * sizeof(Biome)), defaultBiome);
    }
  }

  Chunk::~Chunk() {
    delete[] sections;
  }

  void Chunk::SetSkyLight(int32_t posX, int32_t posY, int32_t posZ, uint32_t data) {
    sections[GetSectionIndex(posY)].SetSkyLight(posX, posY & 15, posZ, data);
  }

  void Chunk::SetBlockLight(int32_t posX, int32_t posY, int32_t posZ, uint32_t data) {
    sections[GetSectionIndex(posY)].SetBlockLight(posX, posY & 15, posZ, data);
  }

  void Chunk::SetBlock(int32_t posX, int32_t posY, int32_t posZ, Block block) {
    sections[GetSectionIndex(posY)].SetBlock(posX, posY & 15, posZ, block);
  }

  void Chunk::SetBiome(int32_t posX, int32_t posY, int32_t posZ, Biome* biome) {
    sections[GetSectionIndex(posY)].SetBiome(posX, posY & 15, posZ, biome);
  }

  uint32_t Chunk::GetSkyLight(int32_t posX, int32_t posY, int32_t posZ) {
    return sections[GetSectionIndex(posY)].GetSkyLight(posX, posY & 15, posZ);
  }

  uint32_t Chunk::GetBlockLight(int32_t posX, int32_t posY, int32_t posZ) {
    return sections[GetSectionIndex(posY)].GetBlockLight(posX, posY & 15, posZ);
  }

  Block Chunk::GetBlock(int32_t posX, int32_t posY, int32_t posZ) {
    return sections[GetSectionIndex(posY)].GetBlock(posX, posY & 15, posZ);
  }

  Biome* Chunk::GetBiome(int32_t posX, int32_t posY, int32_t posZ) {
    return sections[GetSectionIndex(posY)].GetBiome(posX, posY & 15, posZ);
  }

  ChunkSection& Chunk::GetSection(uint32_t index) {
    if (index > sectionsAmount) {
      throw InvalidArgumentException("Invalid section index: ", index);
    }

    return sections[index];
  }
  uint32_t Chunk::GetChunkPosX() const {
    return chunkPosX;
  }
  uint32_t Chunk::GetChunkPosZ() const {
    return chunkPosZ;
  }
  uint32_t Chunk::GetSectionsAmount() const {
    return sectionsAmount;
  }
  Dimension* Chunk::GetDimension() const {
    return dimension;
  }
}