#pragma once

#include "Animal.hpp"

namespace Ship {

  class TurtleMetadata : public AnimalMetadata {
   private:
    int homeX = 0;
    int homeY = 0;
    int homeZ = 0;
    bool hasEgg = false;
    bool layingEgg = false;
    int travelX = 0;
    int travelY = 0;
    int travelZ = 0;
    bool goingHome = false;
    bool traveling = false;

   public:
    TurtleMetadata() = default;
    ~TurtleMetadata() override = default;

    [[nodiscard]] static uint8_t MaximumEntries(const ProtocolVersion* version) {
      return AnimalMetadata::MaximumEntries(version) + 6;
    }

    void Read(Metadata* metadata, const ProtocolVersion* version) override {
      AnimalMetadata::Read(metadata, version);
      uint8_t currentIndex = AnimalMetadata::MaximumEntries(version);

      if (!metadata->GetPosition(currentIndex, homeX, homeY, homeZ)) {
        homeX = homeY = homeZ = 0;
      }

      hasEgg = metadata->GetBoolean(currentIndex + 1).value_or(false);
      layingEgg = metadata->GetBoolean(currentIndex + 2).value_or(false);

      if (!metadata->GetPosition(currentIndex + 3, travelX, travelY, travelZ)) {
        travelX = travelY = travelZ = 0;
      }

      goingHome = metadata->GetBoolean(currentIndex + 4).value_or(false);
      traveling = metadata->GetBoolean(currentIndex + 5).value_or(false);
    }

    void Write(Metadata* metadata, const ProtocolVersion* version) override {
      AnimalMetadata::Write(metadata, version);
      uint8_t currentIndex = AnimalMetadata::MaximumEntries(version);

      if (homeX || homeY || homeZ) {
        metadata->Set(currentIndex, new PositionMetadataEntry(homeX, homeY, homeZ));
      }

      if (hasEgg) {
        metadata->Set(currentIndex + 1, new BooleanMetadataEntry(hasEgg));
      }

      if (layingEgg) {
        metadata->Set(currentIndex + 2, new BooleanMetadataEntry(layingEgg));
      }

      if (travelX || travelY || travelZ) {
        metadata->Set(currentIndex + 3, new PositionMetadataEntry(travelX, travelY, travelZ));
      }

      if (goingHome) {
        metadata->Set(currentIndex + 4, new BooleanMetadataEntry(goingHome));
      }

      if (traveling) {
        metadata->Set(currentIndex + 5, new BooleanMetadataEntry(traveling));
      }
    }

    [[nodiscard]] int GetHomeX() const {
      return homeX;
    }

    void SetHomeX(int value) {
      homeX = value;
    }

    [[nodiscard]] int GetHomeY() const {
      return homeY;
    }

    void SetHomeY(int value) {
      homeY = value;
    }

    [[nodiscard]] int GetHomeZ() const {
      return homeZ;
    }

    void SetHomeZ(int value) {
      homeZ = value;
    }

    [[nodiscard]] bool IsHasEgg() const {
      return hasEgg;
    }

    void SetHasEgg(bool value) {
      hasEgg = value;
    }

    [[nodiscard]] bool IsLayingEgg() const {
      return layingEgg;
    }

    void SetLayingEgg(bool value) {
      layingEgg = value;
    }

    [[nodiscard]] int GetTravelX() const {
      return travelX;
    }

    void SetTravelX(int value) {
      travelX = value;
    }

    [[nodiscard]] int GetTravelY() const {
      return travelY;
    }

    void SetTravelY(int value) {
      travelY = value;
    }

    [[nodiscard]] int GetTravelZ() const {
      return travelZ;
    }

    void SetTravelZ(int value) {
      travelZ = value;
    }

    [[nodiscard]] bool IsGoingHome() const {
      return goingHome;
    }

    void SetGoingHome(bool value) {
      goingHome = value;
    }

    [[nodiscard]] bool IsTraveling() const {
      return traveling;
    }

    void SetTraveling(bool value) {
      traveling = value;
    }
  };
}