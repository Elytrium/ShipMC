#pragma once

#include "Entity.hpp"

namespace Ship {

  class AreaEffectCloudMetadata : public EntityMetadata {
   private:
    float radius = 0.5f;
    uint32_t color = 0;
    bool ignoreRadius = false;
    AbstractParticle* particle = new EffectParticle; // TODO: 1.12.2 particles

   public:
    AreaEffectCloudMetadata() = default;
    ~AreaEffectCloudMetadata() override {
      delete particle;
    }

    [[nodiscard]] static uint8_t MaximumEntries(const ProtocolVersion* version) {
      if (version >= &MinecraftProtocolVersion::MINECRAFT_1_13) {
        return EntityMetadata::MaximumEntries(version) + 4;
      }
      return EntityMetadata::MaximumEntries(version) + 6;
    }

    void Read(Metadata* metadata, const ProtocolVersion* version) override {
      EntityMetadata::Read(metadata, version);
      uint8_t currentIndex = EntityMetadata::MaximumEntries(version);
      delete particle;

      radius = metadata->GetFloat(currentIndex).value_or(0.5f);
      color = metadata->GetVarInt(currentIndex + 1).value_or(0);
      ignoreRadius = metadata->GetBoolean(currentIndex + 2).value_or(false);
      particle = metadata->GetParticle(currentIndex + 3).value_or(nullptr);
    }

    void Write(Metadata* metadata, const ProtocolVersion* version) override {
      EntityMetadata::Write(metadata, version);
      uint8_t currentIndex = EntityMetadata::MaximumEntries(version);

      if (radius != 0.5) {
        metadata->Set(currentIndex, new FloatMetadataEntry(radius));
      }

      if (color) {
        metadata->Set(currentIndex + 1, new VarIntMetadataEntry(color));
      }

      if (ignoreRadius) {
        metadata->Set(currentIndex + 2, new BooleanMetadataEntry(ignoreRadius));
      }

      if (particle) {
        metadata->Set(currentIndex + 3, new ParticleMetadataEntry(particle));
      }
    }

    [[nodiscard]] float GetRadius() const {
      return radius;
    }

    void SetRadius(float value) {
      radius = value;
    }

    [[nodiscard]] uint32_t GetColor() const {
      return color;
    }

    void SetColor(uint32_t value) {
      color = value;
    }

    [[nodiscard]] bool IsIgnoreRadius() const {
      return ignoreRadius;
    }

    void SetIgnoreRadius(bool value) {
      ignoreRadius = value;
    }

    [[nodiscard]] AbstractParticle* GetParticle() const {
      return particle;
    }

    void SetParticle(AbstractParticle* value) {
      particle = value;
    }
  };
}