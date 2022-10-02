#pragma once

#include "AbstractVillager.hpp"

namespace Ship {

  class VillagerMetadata : public AbstractVillagerMetadata {
   private:
    VillagerType type = VillagerType::PLAINS;
    VillagerProfession profession = VillagerProfession::NONE;
    uint32_t level = 1;

   public:
    VillagerMetadata() = default;
    ~VillagerMetadata() override = default;

    [[nodiscard]] static uint8_t MaximumEntries(const ProtocolVersion* version) {
      return AbstractVillagerMetadata::MaximumEntries(version) + 1;
    }

    void Read(Metadata* metadata, const ProtocolVersion* version) override {
      AbstractVillagerMetadata::Read(metadata, version);

      if (!metadata->GetVillagerData(AbstractVillagerMetadata::MaximumEntries(version), type, profession, level)) {
        type = VillagerType::PLAINS;
        profession = VillagerProfession::NONE;
        level = 1;
      }
    }

    void Write(Metadata* metadata, const ProtocolVersion* version) override {
      AbstractVillagerMetadata::Write(metadata, version);

      if (type != VillagerType::PLAINS || profession != VillagerProfession::NONE || level != 1) {
        metadata->Set(AbstractVillagerMetadata::MaximumEntries(version), new VillagerDataMetadataEntry(type, profession, level));
      }
    }

    [[nodiscard]] VillagerType GetType() const {
      return type;
    }

    void SetType(VillagerType value) {
      type = value;
    }

    [[nodiscard]] VillagerProfession GetProfession() const {
      return profession;
    }

    void SetProfession(VillagerProfession value) {
      profession = value;
    }

    [[nodiscard]] uint32_t GetLevel() const {
      return level;
    }

    void SetLevel(uint32_t value) {
      level = value;
    }
  };
}