#include "World.hpp"
#include <string>

namespace Ship {
  Dimension::Dimension(std::string key, uint32_t legacyId, uint32_t modernId, uint32_t sections, bool isNatural, float ambientLight, bool isShrunk,
    bool isUltrawarm, bool hasCeiling, bool hasLegacySkyLight, bool hasModernSkyLight, bool isPiglinSafe, bool doBedsWork, bool doRespawnAnchorsWork,
    bool hasRaids, int32_t logicalHeight, std::string burningBehaviourIdentifier, const std::optional<uint64_t> &fixedTime,
    const std::optional<bool> &createDragonFight, const std::optional<double> &coordinateScale, std::optional<std::string> effects, int32_t minY,
    int32_t height, uint32_t monsterSpawnBlockLightLimit, uint32_t monsterSpawnLightLevel, Biome *defaultBiome)
    : key(std::move(key)), legacyID(legacyId), modernID(modernId), sections(sections), isNatural(isNatural), ambientLight(ambientLight),
      isShrunk(isShrunk), isUltrawarm(isUltrawarm), hasCeiling(hasCeiling), hasLegacySkyLight(hasLegacySkyLight), hasModernSkyLight(hasModernSkyLight),
      isPiglinSafe(isPiglinSafe), doBedsWork(doBedsWork), doRespawnAnchorsWork(doRespawnAnchorsWork), hasRaids(hasRaids), logicalHeight(logicalHeight),
      burningBehaviourIdentifier(std::move(burningBehaviourIdentifier)), fixedTime(fixedTime), createDragonFight(createDragonFight),
      coordinateScale(coordinateScale), effects(std::move(effects)), minY(minY), height(height), monsterSpawnBlockLightLimit(monsterSpawnBlockLightLimit),
      monsterSpawnLightLevel(monsterSpawnLightLevel), defaultBiome(defaultBiome) {
  }

  Dimension Dimension::FromNBT(CompoundTag *nbt) {
    std::string key = nbt->GetString("name").value();
    uint32_t modernId = nbt->GetInt("id").value();
    uint32_t legacyId = 1; // TODO:
    uint32_t sections = 24; // TODO:
    auto *tag = (CompoundTag *) nbt->GetNBT("element").value();

    bool isNatural = tag->GetBool("natural").value();
    float ambientLight = tag->GetBool("ambient_light").value();
    bool isShrunk = tag->GetBool("shrunk").value();
    bool isUltrawarm = tag->GetBool("ultrawarm").value();
    bool hasCeiling = tag->GetBool("has_ceiling").value();
    bool hasModernSkyLight = tag->GetBool("has_skylight").value();
    bool hasLegacySkyLight = true; // TODO:
    bool isPiglinSafe = tag->GetBool("piglin_safe").value();
    bool doBedsWork = tag->GetBool("bed_works").value();
    bool doRespawnAnchorsWork = tag->GetBool("respawn_anchor_works").value();
    bool hasRaids = tag->GetBool("has_raids").value();
    int32_t logicalHeight = (int32_t) tag->GetInt("logical_height").value();
    std::string burningBehaviourIdentifier = tag->GetString("infiniburn").value();

    std::optional<uint64_t> fixedTime = tag->GetLong("fixed_time");
    std::optional<bool> hasEnderdragonFight = tag->GetBool("has_enderdragon_fight");
    std::optional<double> coordinateScale = tag->GetBool("coordinate_scale");
    std::optional<std::string> effects = tag->GetString("effects");

    int32_t minY = (int32_t) tag->GetInt("min_y").value_or(0);
    int32_t height = (int32_t) tag->GetInt("height").value_or(256);
    uint32_t monsterSpawnBlockLightLimit = tag->GetInt("monster_spawn_block_light_limit").value_or(7);
    uint32_t monsterSpawnLightLevel = tag->GetInt("monster_spawn_light_level").value_or(7);

    Biome *defaultBiome = nullptr;

    return {key, legacyId, modernId, sections, isNatural, ambientLight, isShrunk, isUltrawarm, hasCeiling, hasLegacySkyLight, hasModernSkyLight,
      isPiglinSafe, doBedsWork, doRespawnAnchorsWork, hasRaids, logicalHeight, burningBehaviourIdentifier, fixedTime, hasEnderdragonFight, coordinateScale,
      effects, minY, height, monsterSpawnBlockLightLimit, monsterSpawnLightLevel, defaultBiome};
  }

  CompoundTag *Dimension::Serialize() const {
    auto *tag = new CompoundTag("element");
    tag->AddNBT(new ByteTag("natural", isNatural));
    tag->AddNBT(new FloatTag("ambient_light", ambientLight));
    tag->AddNBT(new ByteTag("shrunk", isShrunk));
    tag->AddNBT(new ByteTag("ultrawarm", isUltrawarm));
    tag->AddNBT(new ByteTag("has_ceiling", hasCeiling));
    tag->AddNBT(new ByteTag("has_skylight", hasModernSkyLight));
    tag->AddNBT(new ByteTag("natural", isNatural));
    tag->AddNBT(new ByteTag("piglin_safe", isPiglinSafe));
    tag->AddNBT(new ByteTag("bed_works", doBedsWork));
    tag->AddNBT(new ByteTag("respawn_anchor_works", doRespawnAnchorsWork));
    tag->AddNBT(new ByteTag("has_raids", hasRaids));
    tag->AddNBT(new IntTag("logical_height", logicalHeight));
    tag->AddNBT(new StringTag("infiniburn", burningBehaviourIdentifier));

    if (fixedTime) {
      tag->AddNBT(new LongTag("fixed_time", fixedTime.value()));
    }

    if (createDragonFight) {
      tag->AddNBT(new ByteTag("has_enderdragon_fight", createDragonFight.value()));
    }

    if (coordinateScale) {
      tag->AddNBT(new DoubleTag("coordinate_scale", coordinateScale.value()));
    }

    if (effects) {
      tag->AddNBT(new StringTag("effects", effects.value()));
    }

    tag->AddNBT(new IntTag("min_y", minY));
    tag->AddNBT(new IntTag("height", height));
    tag->AddNBT(new IntTag("monster_spawn_block_light_limit", monsterSpawnBlockLightLimit));
    tag->AddNBT(new IntTag("monster_spawn_light_level", monsterSpawnLightLevel));

    return tag;
  }
  const std::string &Dimension::GetKey() const {
    return key;
  }
  uint32_t Dimension::GetLegacyId() const {
    return legacyID;
  }
  uint32_t Dimension::GetModernId() const {
    return modernID;
  }
  uint32_t Dimension::GetSections() const {
    return sections;
  }
  bool Dimension::HasLegacySkyLight() const {
    return hasLegacySkyLight;
  }
  bool Dimension::HasModernSkyLight() const {
    return hasModernSkyLight;
  }
  Biome *Dimension::GetDefaultBiome() const {
    return defaultBiome;
  }

  Dimension Dimension::FromLegacyID(uint32_t id) {
  }
}