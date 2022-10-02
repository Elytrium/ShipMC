#pragma once

#include "Entity.hpp"

namespace Ship {

  class FallingBlockMetadata : public EntityMetadata {
   private:
    int spawnX = 0;
    int spawnY = 0;
    int spawnZ = 0;

   public:
    FallingBlockMetadata() = default;
    ~FallingBlockMetadata() override = default;

    [[nodiscard]] static uint8_t MaximumEntries(const ProtocolVersion* version) {
      return EntityMetadata::MaximumEntries(version) + 1;
    }

    void Read(Metadata* metadata, const ProtocolVersion* version) override {
      EntityMetadata::Read(metadata, version);

      if (!metadata->GetPosition(EntityMetadata::MaximumEntries(version), spawnX, spawnY, spawnZ)) {
        spawnX = spawnY = spawnZ = 0;
      }
    }

    void Write(Metadata* metadata, const ProtocolVersion* version) override {
      EntityMetadata::Write(metadata, version);

      if (spawnX || spawnY || spawnZ) {
        metadata->Set(EntityMetadata::MaximumEntries(version), new PositionMetadataEntry(spawnX, spawnY, spawnZ));
      }
    }

    [[nodiscard]] int GetSpawnX() const {
      return spawnX;
    }

    void SetSpawnX(int value) {
      spawnX = value;
    }

    [[nodiscard]] int GetSpawnY() const {
      return spawnY;
    }

    void SetSpawnY(int value) {
      spawnY = value;
    }

    [[nodiscard]] int GetSpawnZ() const {
      return spawnZ;
    }

    void SetSpawnZ(int value) {
      spawnZ = value;
    }
  };
}