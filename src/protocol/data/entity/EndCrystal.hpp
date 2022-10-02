#pragma once

#include "Entity.hpp"

namespace Ship {

  class EndCrystalMetadata : public EntityMetadata {
   private:
    bool hasBeamTarget = false;
    int beamTargetX = 0;
    int beamTargetY = 0;
    int beamTargetZ = 0;
    bool showBottom = true;

   public:
    EndCrystalMetadata() = default;
    ~EndCrystalMetadata() override = default;

    static uint8_t MaximumEntries(const ProtocolVersion* version) {
      return EntityMetadata::MaximumEntries(version) + 2;
    }

    void Read(Metadata* metadata, const ProtocolVersion* version) override {
      EntityMetadata::Read(metadata, version);
      uint8_t currentIndex = EntityMetadata::MaximumEntries(version);

      if (!metadata->GetOptPosition(currentIndex, hasBeamTarget, beamTargetX, beamTargetY, beamTargetZ)) {
        hasBeamTarget = false;
        beamTargetX = beamTargetY = beamTargetZ = 0;
      }

      showBottom = metadata->GetBoolean(currentIndex + 1).value_or(true);
    }

    void Write(Metadata* metadata, const ProtocolVersion* version) override {
      EntityMetadata::Write(metadata, version);

      uint8_t currentIndex = EntityMetadata::MaximumEntries(version);

      if (hasBeamTarget) {
        metadata->Set(currentIndex, new OptPositionMetadataEntry(beamTargetX, beamTargetY, beamTargetZ));
      }

      if (!showBottom) {
        metadata->Set(currentIndex + 1, new BooleanMetadataEntry(showBottom));
      }
    }

    [[nodiscard]] bool IsHasBeamTarget() const {
      return hasBeamTarget;
    }

    void SetHasBeamTarget(bool value) {
      hasBeamTarget = value;
    }

    [[nodiscard]] int GetBeamTargetX() const {
      return beamTargetX;
    }

    void SetBeamTargetX(int value) {
      beamTargetX = value;
    }

    [[nodiscard]] int GetBeamTargetY() const {
      return beamTargetY;
    }

    void SetBeamTargetY(int value) {
      beamTargetY = value;
    }

    [[nodiscard]] int GetBeamTargetZ() const {
      return beamTargetZ;
    }

    void SetBeamTargetZ(int value) {
      beamTargetZ = value;
    }

    [[nodiscard]] bool IsShowBottom() const {
      return showBottom;
    }

    void SetShowBottom(bool value) {
      showBottom = value;
    }
  };
}