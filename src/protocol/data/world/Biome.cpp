#include "World.hpp"
#include <utility>
namespace Ship {
  BiomeParticleOptions::BiomeParticleOptions(std::string type) : type(std::move(type)) {
  }

  CompoundTag* BiomeParticleOptions::Encode() {
    auto* tag = new CompoundTag("options");
    tag->AddNBT(new StringTag("type", type));
    return tag;
  }

  BiomeParticleOptions BiomeParticleOptions::Decode(CompoundTag* nbt) {
    return BiomeParticleOptions(nbt->GetString("type").value());
  }

  BiomeParticle::BiomeParticle(float probability, BiomeParticleOptions options) : probability(probability), options(std::move(options)) {
  }

  CompoundTag* BiomeParticle::Encode() {
    auto* tag = new CompoundTag("particle");
    tag->AddNBT(new FloatTag("probability", probability));
    tag->AddNBT(options.Encode());
    return tag;
  }

  BiomeParticle BiomeParticle::Decode(CompoundTag* nbt) {
    return {nbt->GetFloat("probability").value(), BiomeParticleOptions::Decode((CompoundTag*) nbt->GetNBT("options").value())};
  }

  BiomeAdditionsSound::BiomeAdditionsSound(std::string sound, double tickChance) : sound(std::move(sound)), tickChance(tickChance) {
  }

  CompoundTag* BiomeAdditionsSound::Encode() {
    auto* tag = new CompoundTag("additions_sound");
    tag->AddNBT(new DoubleTag("tick_chance", tickChance));
    tag->AddNBT(new StringTag("sound", sound));
    return tag;
  }

  BiomeAdditionsSound BiomeAdditionsSound::Decode(CompoundTag* nbt) {
    return {nbt->GetString("sound").value(), nbt->GetDouble("tick_chance").value()};
  }

  BiomeMusic::BiomeMusic(bool replaceCurrentMusic, const std::string& sound, uint32_t maxDelay, uint32_t minDelay)
    : replaceCurrentMusic(replaceCurrentMusic), sound(sound), maxDelay(maxDelay), minDelay(minDelay) {
  }

  CompoundTag* BiomeMusic::Encode() {
    auto* tag = new CompoundTag("music");
    tag->AddNBT(new ByteTag("replace_current_music", replaceCurrentMusic));
    tag->AddNBT(new StringTag("sound", sound));
    tag->AddNBT(new IntTag("max_delay", maxDelay));
    tag->AddNBT(new IntTag("min_delay", minDelay));
    return tag;
  }

  BiomeMusic BiomeMusic::Decode(CompoundTag* nbt) {
    return {(bool) nbt->GetByte("replace_current_music").value(), nbt->GetString("sound").value(), nbt->GetInt("max_delay").value(),
      nbt->GetInt("min_delay").value()};
  }

  BiomeMoodSound::BiomeMoodSound(uint32_t tickDelay, double offset, uint32_t blockSearchExtent, std::string sound)
    : tickDelay(tickDelay), offset(offset), blockSearchExtent(blockSearchExtent), sound(std::move(sound)) {
  }

  CompoundTag* BiomeMoodSound::Encode() {
    auto* tag = new CompoundTag("mood_sound");
    tag->AddNBT(new IntTag("tick_delay", tickDelay));
    tag->AddNBT(new DoubleTag("offset", offset));
    tag->AddNBT(new IntTag("block_search_extent", blockSearchExtent));
    tag->AddNBT(new StringTag("sound", sound));
    return tag;
  }

  BiomeMoodSound BiomeMoodSound::Decode(CompoundTag* nbt) {
    return {(bool) nbt->GetInt("tick_delay").value(), nbt->GetDouble("offset").value(), nbt->GetInt("block_search_extent").value(),
      nbt->GetString("sound").value()};
  }

  BiomeEffects::BiomeEffects(uint32_t skyColor, uint32_t waterFogColor, uint32_t fogColor, uint32_t waterColor, std::optional<uint32_t> foliageColor,
    std::optional<std::string> grassColorModifier, std::optional<BiomeMusic> music, std::optional<std::string> ambientSound,
    std::optional<BiomeAdditionsSound> additionsSound, std::optional<BiomeMoodSound> moodSound, std::optional<BiomeParticle> particle)
    : skyColor(skyColor), waterFogColor(waterFogColor), fogColor(fogColor), waterColor(waterColor), foliageColor(foliageColor),
      grassColorModifier(std::move(grassColorModifier)), music(std::move(music)), ambientSound(std::move(ambientSound)),
      additionsSound(std::move(additionsSound)), moodSound(std::move(moodSound)), particle(std::move(particle)) {
  }

  CompoundTag* BiomeEffects::Encode() {
    auto* tag = new CompoundTag("effects");
    tag->AddNBT(new IntTag("sky_color", skyColor));
    tag->AddNBT(new IntTag("water_fog_color", waterFogColor));
    tag->AddNBT(new IntTag("fog_color", fogColor));
    tag->AddNBT(new IntTag("water_color", waterColor));

    if (foliageColor) {
      tag->AddNBT(new IntTag("foliage_color", foliageColor.value()));
    }

    if (grassColorModifier) {
      tag->AddNBT(new StringTag("grass_color_modifier", grassColorModifier.value()));
    }

    if (music) {
      tag->AddNBT(music->Encode());
    }

    if (ambientSound) {
      tag->AddNBT(new StringTag("ambient_sound", ambientSound.value()));
    }

    if (additionsSound) {
      tag->AddNBT(additionsSound->Encode());
    }

    if (moodSound) {
      tag->AddNBT(moodSound->Encode());
    }

    if (particle) {
      tag->AddNBT(particle->Encode());
    }
    return tag;
  }

  BiomeEffects BiomeEffects::Decode(CompoundTag* nbt) {
    return {
      nbt->GetInt("sky_color").value(),
      nbt->GetInt("water_fog_color").value(),
      nbt->GetInt("fog_color").value(),
      nbt->GetInt("water_color").value(),
      nbt->GetInt("foliage_color"),
      nbt->GetString("grass_color_modifier"),
      nbt->HasKey("music") ? std::optional(BiomeMusic::Decode((CompoundTag*) nbt->GetNBT("music").value())) : std::nullopt,
      nbt->GetString("ambient_sound"),
      nbt->HasKey("additions_sound") ? std::optional(BiomeAdditionsSound::Decode((CompoundTag*) nbt->GetNBT("additions_sound").value())) : std::nullopt,
      nbt->HasKey("mood_sound") ? std::optional(BiomeMoodSound::Decode((CompoundTag*) nbt->GetNBT("mood_sound").value())) : std::nullopt,
      nbt->HasKey("particle") ? std::optional(BiomeParticle::Decode((CompoundTag*) nbt->GetNBT("particle").value())) : std::nullopt
    };
  }

  BiomeElement::BiomeElement(
    std::string precipitation, float depth, float temperature, float scale, float downfall, std::string category, BiomeEffects effects)
    : precipitation(std::move(precipitation)), depth(depth), temperature(temperature), scale(scale), downfall(downfall), category(std::move(category)),
      effects(std::move(effects)) {
  }

  CompoundTag* BiomeElement::Encode() {
    auto* tag = new CompoundTag("element");
    tag->AddNBT(new StringTag("precipitation", precipitation));
    tag->AddNBT(new FloatTag("depth", depth));
    tag->AddNBT(new FloatTag("temperature", temperature));
    tag->AddNBT(new FloatTag("scale", scale));
    tag->AddNBT(new FloatTag("downfall", downfall));
    tag->AddNBT(new StringTag("category", category));
    tag->AddNBT(effects.Encode());
    return tag;
  }

  BiomeElement BiomeElement::Decode(CompoundTag* nbt) {
    return {
      nbt->GetString("precipitation").value(),
      nbt->GetFloat("depth").value(),
      nbt->GetFloat("temperature").value(),
      nbt->GetFloat("scale").value(),
      nbt->GetFloat("downfall").value(),
      nbt->GetString("category").value(),
      BiomeEffects::Decode((CompoundTag*) nbt->GetNBT("effects").value())
    };
  }

  Biome::Biome(std::string name, uint32_t id, BiomeElement element) : name(std::move(name)), id(id), element(std::move(element)) {
  }

  CompoundTag* Biome::Encode() {
    auto* tag = new CompoundTag("");
    tag->AddNBT(new StringTag("name", name));
    tag->AddNBT(new IntTag("id", id));
    tag->AddNBT(element.Encode());
    return tag;
  }

  Biome Biome::Decode(CompoundTag* nbt) {
    return {
      nbt->GetString("name").value(),
      nbt->GetInt("id").value(),
      BiomeElement::Decode((CompoundTag*) nbt->GetNBT("element").value())
    };
  }
}