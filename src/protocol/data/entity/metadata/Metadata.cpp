#include "Metadata.hpp"

namespace Ship {

  Metadata::Metadata(std::map<uint8_t, MetadataEntry*> entries) : entries(std::move(entries)) {
  }

  Errorable<Metadata*> Metadata::Instantiate(const Ship::ProtocolVersion* version, Ship::ByteBuffer* buffer) {
    auto* metadata = new Metadata();
    while (true) {
      ProceedErrorable(index, uint8_t, buffer->ReadByte(), InvalidMetadataErrorable(buffer->GetReadableBytes()))
      if (index == 0xFF) {
        break;
      }

      ProceedErrorable(type, uint32_t, buffer->ReadVarInt(), InvalidMetadataErrorable(buffer->GetReadableBytes()))
      ProceedErrorable(entry, MetadataEntry*, METADATA_ENTRY_REGISTRY.GetObjectByID(version, type, buffer), InvalidMetadataErrorable(buffer->GetReadableBytes()))
      metadata->Set(index, entry);
    }

    return SuccessErrorable<Metadata*>(metadata);
  }

  Errorable<bool> Metadata::Write(const ProtocolVersion* version, ByteBuffer* buffer) const {
    for (auto& pair : entries) {
      uint8_t index = pair.first;
      MetadataEntry* entry = pair.second;

      if (entry) {
        buffer->WriteByte(index);
        ProceedErrorable(id, uint32_t, METADATA_ENTRY_REGISTRY.GetIDByOrdinal(version, entry->GetOrdinal()), InvalidSerializableWriteErrorable(buffer->GetReadableBytes()))
        buffer->WriteVarInt(id);
        entry->Write(version, buffer);
      }
    }
    buffer->WriteByte(0xFF);
    return SuccessErrorable<bool>(true);
  }

  uint32_t Metadata::Size(const ProtocolVersion* version) const {
    uint32_t size = 1;
    for (auto& pair : entries) {
      size += pair.second->Size(version);
    }

    return size;
  }

  void Metadata::Set(uint8_t index, MetadataEntry* value) {
    auto it = entries.find(index);
    if (it != entries.end()) {
      delete it->second;
    }

    entries[index] = value;
  }

  Errorable<uint8_t> Metadata::GetByte(uint8_t index) const {
    auto* entry = Get<ByteMetadataEntry>(index);
    if (!entry) {
      return NoSuchByteMetadataEntryErrorable(index);
    }

    if (entry->GetType() != MetadataEntryType::BYTE) {
      return MismatchByteMetadataEntryErrorable((uint64_t) entry->GetType());
    }

    return SuccessErrorable<uint8_t>(entry->GetValue());
  }

  Errorable<uint32_t> Metadata::GetVarInt(uint8_t index) const {
    auto* entry = Get<VarIntMetadataEntry>(index);
    if (!entry) {
      return NoSuchVarIntMetadataEntryErrorable(index);
    }

    if (entry->GetType() != MetadataEntryType::VARINT) {
      return MismatchVarIntMetadataEntryErrorable((uint64_t) entry->GetType());
    }

    return SuccessErrorable<uint32_t>(entry->GetValue());
  }

  Errorable<uint64_t> Metadata::GetLong(uint8_t index) const {
    auto* entry = Get<LongMetadataEntry>(index);
    if (!entry) {
      return NoSuchLongMetadataEntryErrorable(index);
    }

    if (entry->GetType() != MetadataEntryType::LONG) {
      return MismatchLongMetadataEntryErrorable((uint64_t) entry->GetType());
    }

    return SuccessErrorable<uint64_t>(entry->GetValue());
  }

  Errorable<float> Metadata::GetFloat(uint8_t index) const {
    auto* entry = Get<FloatMetadataEntry>(index);
    if (!entry) {
      return NoSuchFloatMetadataEntryErrorable(index);
    }

    if (entry->GetType() != MetadataEntryType::FLOAT) {
      return MismatchFloatMetadataEntryErrorable((uint64_t) entry->GetType());
    }

    return SuccessErrorable<float>(entry->GetValue());
  }

  Errorable<std::string> Metadata::GetString(uint8_t index) const {
    auto* entry = Get<StringMetadataEntry>(index);
    if (!entry) {
      return NoSuchStringMetadataEntryErrorable(index);
    }

    if (entry->GetType() != MetadataEntryType::STRING) {
      return MismatchStringMetadataEntryErrorable((uint64_t) entry->GetType());
    }

    return SuccessErrorable<std::string>(entry->GetValue());
  }

  Errorable<std::string> Metadata::GetChat(uint8_t index) const {
    auto* entry = Get<ChatMetadataEntry>(index);
    if (!entry) {
      return NoSuchChatMetadataEntryErrorable(index);
    }

    if (entry->GetType() != MetadataEntryType::CHAT) {
      return MismatchChatMetadataEntryErrorable((uint64_t) entry->GetType());
    }

    return SuccessErrorable<std::string>(entry->GetValue());
  }

  Errorable<std::optional<std::string>> Metadata::GetOptChat(uint8_t index) const {
    auto* entry = Get<OptChatMetadataEntry>(index);
    if (!entry) {
      return NoSuchOptChatMetadataEntryErrorable(index);
    }

    if (entry->GetType() != MetadataEntryType::OPT_CHAT) {
      return MismatchOptChatMetadataEntryErrorable((uint64_t) entry->GetType());
    }

    return SuccessErrorable<std::optional<std::string>>(entry->GetValue());
  }

  Errorable<ItemStack> Metadata::GetItemStack(uint8_t index) const {
    auto* entry = Get<ItemStackMetadataEntry>(index);
    if (!entry) {
      return NoSuchItemStackMetadataEntryErrorable(index);
    }

    if (entry->GetType() != MetadataEntryType::ITEM_STACK) {
      return MismatchItemStackMetadataEntryErrorable((uint64_t) entry->GetType());
    }

    return SuccessErrorable<ItemStack>(entry->GetValue());
  }

  Errorable<bool> Metadata::GetBoolean(uint8_t index) const {
    auto* entry = Get<BooleanMetadataEntry>(index);
    if (!entry) {
      return NoSuchBooleanMetadataEntryErrorable(index);
    }

    if (entry->GetType() != MetadataEntryType::BOOLEAN) {
      return MismatchBooleanMetadataEntryErrorable((uint64_t) entry->GetType());
    }

    return SuccessErrorable<bool>(entry->GetValue());
  }

  Errorable<Rotation> Metadata::GetRotation(uint8_t index) const {
    auto* entry = Get<RotationMetadataEntry>(index);
    if (!entry) {
      return NoSuchRotationMetadataEntryErrorable(index);
    }

    if (entry->GetType() != MetadataEntryType::ROTATION) {
      return MismatchRotationMetadataEntryErrorable((uint64_t) entry->GetType());
    }

    return SuccessErrorable<Rotation>(entry->GetValue());
  }

  Errorable<Position> Metadata::GetPosition(uint8_t index) const {
    auto* entry = Get<PositionMetadataEntry>(index);
    if (!entry) {
      return NoSuchPositionMetadataEntryErrorable(index);
    }

    if (entry->GetType() != MetadataEntryType::POSITION) {
      return MismatchPositionMetadataEntryErrorable((uint64_t) entry->GetType());
    }

    return SuccessErrorable<Position>(entry->GetValue());
  }

  Errorable<std::optional<Position>> Metadata::GetOptPosition(uint8_t index) const {
    auto* entry = Get<OptPositionMetadataEntry>(index);
    if (!entry) {
      return NoSuchOptPositionMetadataEntryErrorable(index);
    }

    if (entry->GetType() != MetadataEntryType::OPT_POSITION) {
      return MismatchOptPositionMetadataEntryErrorable((uint64_t) entry->GetType());
    }

    return SuccessErrorable<std::optional<Position>>(entry->GetValue());
  }

  Errorable<Direction> Metadata::GetDirection(uint8_t index) const {
    auto* entry = Get<DirectionMetadataEntry>(index);
    if (!entry) {
      return NoSuchDirectionMetadataEntryErrorable(index);
    }

    if (entry->GetType() != MetadataEntryType::DIRECTION) {
      return MismatchDirectionMetadataEntryErrorable((uint64_t) entry->GetType());
    }

    return SuccessErrorable<Direction>(entry->GetValue());
  }

  Errorable<std::optional<UUID>> Metadata::GetOptUUID(uint8_t index) const {
    auto* entry = Get<OptUUIDMetadataEntry>(index);
    if (!entry) {
      return NoSuchOptUUIDMetadataEntryErrorable(index);
    }

    if (entry->GetType() != MetadataEntryType::OPT_UUID) {
      return MismatchOptUUIDMetadataEntryErrorable((uint64_t) entry->GetType());
    }

    return SuccessErrorable<std::optional<UUID>>(entry->GetValue());
  }

  Errorable<uint32_t> Metadata::GetBlockID(uint8_t index) const {
    auto* entry = Get<BlockIDMetadataEntry>(index);
    if (!entry) {
      return NoSuchBlockIDMetadataEntryErrorable(index);
    }

    if (entry->GetType() != MetadataEntryType::BLOCK_ID) {
      return MismatchBlockIDMetadataEntryErrorable((uint64_t) entry->GetType());
    }

    return SuccessErrorable<uint32_t>(entry->GetValue());
  }

  Errorable<NBT*> Metadata::GetNBT(uint8_t index) const {
    auto* entry = Get<NBTMetadataEntry>(index);
    if (!entry) {
      return NoSuchNBTMetadataEntryErrorable(index);
    }

    if (entry->GetType() != MetadataEntryType::NBT) {
      return MismatchNBTMetadataEntryErrorable((uint64_t) entry->GetType());
    }

    return SuccessErrorable<NBT*>(entry->GetValue());
  }

  Errorable<AbstractParticle*> Metadata::GetParticle(uint8_t index) const {
    auto* entry = Get<ParticleMetadataEntry>(index);
    if (!entry) {
      return NoSuchParticleMetadataEntryErrorable(index);
    }

    if (entry->GetType() != MetadataEntryType::PARTICLE) {
      return MismatchParticleMetadataEntryErrorable((uint64_t) entry->GetType());
    }

    return SuccessErrorable<AbstractParticle*>(entry->GetValue());
  }

  Errorable<VillagerData> Metadata::GetVillagerData(uint8_t index) const {
    auto* entry = Get<VillagerDataMetadataEntry>(index);
    if (!entry) {
      return NoSuchVillagerDataMetadataEntryErrorable(index);
    }

    if (entry->GetType() != MetadataEntryType::VILLAGER_DATA) {
      return MismatchVillagerDataMetadataEntryErrorable((uint64_t) entry->GetType());
    }

    return SuccessErrorable<VillagerData>(entry->GetValue());
  }

  Errorable<std::optional<uint32_t>> Metadata::GetOptVarInt(uint8_t index) const {
    auto* entry = Get<OptVarIntMetadataEntry>(index);
    if (!entry) {
      return NoSuchOptVarIntMetadataEntryErrorable(index);
    }

    if (entry->GetType() != MetadataEntryType::OPT_VARINT) {
      return MismatchOptVarIntMetadataEntryErrorable((uint64_t) entry->GetType());
    }

    return SuccessErrorable<std::optional<uint32_t>>(entry->GetValue());
  }

  Errorable<Pose> Metadata::GetPose(uint8_t index) const {
    auto* entry = Get<PoseMetadataEntry>(index);
    if (!entry) {
      return NoSuchPoseMetadataEntryErrorable(index);
    }

    if (entry->GetType() != MetadataEntryType::POSE) {
      return MismatchPoseMetadataEntryErrorable((uint64_t) entry->GetType());
    }

    return SuccessErrorable<Pose>(entry->GetValue());
  }

  Errorable<CatVariant> Metadata::GetCatVariant(uint8_t index) const {
    auto* entry = Get<CatVariantMetadataEntry>(index);
    if (!entry) {
      return NoSuchCatVariantMetadataEntryErrorable(index);
    }

    if (entry->GetType() != MetadataEntryType::CAT_VARIANT) {
      return MismatchCatVariantMetadataEntryErrorable((uint64_t) entry->GetType());
    }

    return SuccessErrorable<CatVariant>(entry->GetValue());
  }

  Errorable<FrogVariant> Metadata::GetFrogVariant(uint8_t index) const {
    auto* entry = Get<FrogVariantMetadataEntry>(index);
    if (!entry) {
      return NoSuchFrogVariantMetadataEntryErrorable(index);
    }

    if (entry->GetType() != MetadataEntryType::FROG_VARIANT) {
      return MismatchFrogVariantMetadataEntryErrorable((uint64_t) entry->GetType());
    }

    return SuccessErrorable<FrogVariant>(entry->GetValue());
  }

  Errorable<GlobalPos> Metadata::GetGlobalPos(uint8_t index) const {
    auto* entry = Get<GlobalPosMetadataEntry>(index);
    if (!entry) {
      return NoSuchGlobalPosMetadataEntryErrorable(index);
    }

    if (entry->GetType() != MetadataEntryType::GLOBAL_POS) {
      return MismatchGlobalPosMetadataEntryErrorable((uint64_t) entry->GetType());
    }

    return SuccessErrorable<GlobalPos>(entry->GetValue());
  }

  Errorable<PaintingVariant> Metadata::GetPaintingVariant(uint8_t index) const {
    auto* entry = Get<PaintingVariantMetadataEntry>(index);
    if (!entry) {
      return NoSuchPaintingVariantMetadataEntryErrorable(index);
    }

    if (entry->GetType() != MetadataEntryType::PAINTING_VARIANT) {
      return MismatchPaintingVariantMetadataEntryErrorable((uint64_t) entry->GetType());
    }

    return SuccessErrorable<PaintingVariant>(entry->GetValue());
  }

  ConstructorRegistry<MetadataEntry> GetMetadataRegistry() {
    ConstructorRegistry<MetadataEntry> dataRegistry(MinecraftProtocolVersion::VERSIONS, {MinecraftProtocolVersion::MINECRAFT_1_12_2, MinecraftProtocolVersion::MINECRAFT_1_13, MinecraftProtocolVersion::MINECRAFT_1_14,
      MinecraftProtocolVersion::MINECRAFT_1_19, MinecraftProtocolVersion::MINECRAFT_1_19_1, MinecraftProtocolVersion::MINECRAFT_1_19_3});

    dataRegistry.RegisterConstructor(ByteMetadataEntry::ORDINAL, WrapConstructor<MetadataEntry, ByteMetadataEntry>());
    dataRegistry.RegisterConstructor(VarIntMetadataEntry::ORDINAL, WrapConstructor<MetadataEntry, VarIntMetadataEntry>());
    dataRegistry.RegisterConstructor(LongMetadataEntry::ORDINAL, WrapConstructor<MetadataEntry, LongMetadataEntry>());
    dataRegistry.RegisterConstructor(FloatMetadataEntry::ORDINAL, WrapConstructor<MetadataEntry, FloatMetadataEntry>());
    dataRegistry.RegisterConstructor(StringMetadataEntry::ORDINAL, WrapConstructor<MetadataEntry, StringMetadataEntry>());
    dataRegistry.RegisterConstructor(ChatMetadataEntry::ORDINAL, WrapConstructor<MetadataEntry, ChatMetadataEntry>());
    dataRegistry.RegisterConstructor(OptChatMetadataEntry::ORDINAL, WrapConstructor<MetadataEntry, OptChatMetadataEntry>());
    dataRegistry.RegisterConstructor(ItemStackMetadataEntry::ORDINAL, WrapConstructor<MetadataEntry, ItemStackMetadataEntry>());
    dataRegistry.RegisterConstructor(BooleanMetadataEntry::ORDINAL, WrapConstructor<MetadataEntry, BooleanMetadataEntry>());
    dataRegistry.RegisterConstructor(RotationMetadataEntry::ORDINAL, WrapConstructor<MetadataEntry, RotationMetadataEntry>());
    dataRegistry.RegisterConstructor(PositionMetadataEntry::ORDINAL, WrapConstructor<MetadataEntry, PositionMetadataEntry>());
    dataRegistry.RegisterConstructor(OptPositionMetadataEntry::ORDINAL, WrapConstructor<MetadataEntry, OptPositionMetadataEntry>());
    dataRegistry.RegisterConstructor(DirectionMetadataEntry::ORDINAL, WrapConstructor<MetadataEntry, DirectionMetadataEntry>());
    dataRegistry.RegisterConstructor(OptUUIDMetadataEntry::ORDINAL, WrapConstructor<MetadataEntry, OptUUIDMetadataEntry>());
    dataRegistry.RegisterConstructor(BlockIDMetadataEntry::ORDINAL, WrapConstructor<MetadataEntry, BlockIDMetadataEntry>());
    dataRegistry.RegisterConstructor(NBTMetadataEntry::ORDINAL, WrapConstructor<MetadataEntry, NBTMetadataEntry>());
    dataRegistry.RegisterConstructor(ParticleMetadataEntry::ORDINAL, WrapConstructor<MetadataEntry, ParticleMetadataEntry>());
    dataRegistry.RegisterConstructor(
      VillagerDataMetadataEntry::ORDINAL, WrapConstructor<MetadataEntry, VillagerDataMetadataEntry>());
    dataRegistry.RegisterConstructor(OptVarIntMetadataEntry::ORDINAL, WrapConstructor<MetadataEntry, OptVarIntMetadataEntry>());
    dataRegistry.RegisterConstructor(PoseMetadataEntry::ORDINAL, WrapConstructor<MetadataEntry, PoseMetadataEntry>());
    dataRegistry.RegisterConstructor(CatVariantMetadataEntry::ORDINAL, WrapConstructor<MetadataEntry, CatVariantMetadataEntry>());
    dataRegistry.RegisterConstructor(FrogVariantMetadataEntry::ORDINAL, WrapConstructor<MetadataEntry, FrogVariantMetadataEntry>());
    dataRegistry.RegisterConstructor(GlobalPosMetadataEntry::ORDINAL, WrapConstructor<MetadataEntry, GlobalPosMetadataEntry>());
    dataRegistry.RegisterConstructor(PaintingVariantMetadataEntry::ORDINAL, WrapConstructor<MetadataEntry, PaintingVariantMetadataEntry>());

    dataRegistry.RegisterVersion(&MinecraftProtocolVersion::MINECRAFT_1_12_2,
      new VersionRegistry({ByteMetadataEntry::ORDINAL, VarIntMetadataEntry::ORDINAL, FloatMetadataEntry::ORDINAL, StringMetadataEntry::ORDINAL,
        ChatMetadataEntry::ORDINAL, ItemStackMetadataEntry::ORDINAL, BooleanMetadataEntry::ORDINAL, RotationMetadataEntry::ORDINAL,
        PositionMetadataEntry::ORDINAL, OptPositionMetadataEntry::ORDINAL, DirectionMetadataEntry::ORDINAL, OptUUIDMetadataEntry::ORDINAL,
        BlockIDMetadataEntry::ORDINAL, NBTMetadataEntry::ORDINAL}));

    dataRegistry.RegisterVersion(&MinecraftProtocolVersion::MINECRAFT_1_13,
      new VersionRegistry({ByteMetadataEntry::ORDINAL, VarIntMetadataEntry::ORDINAL, FloatMetadataEntry::ORDINAL, StringMetadataEntry::ORDINAL,
        ChatMetadataEntry::ORDINAL, OptChatMetadataEntry::ORDINAL, ItemStackMetadataEntry::ORDINAL, BooleanMetadataEntry::ORDINAL,
        RotationMetadataEntry::ORDINAL, PositionMetadataEntry::ORDINAL, OptPositionMetadataEntry::ORDINAL, DirectionMetadataEntry::ORDINAL,
        OptUUIDMetadataEntry::ORDINAL, BlockIDMetadataEntry::ORDINAL, NBTMetadataEntry::ORDINAL, ParticleMetadataEntry::ORDINAL}));

    dataRegistry.RegisterVersion(&MinecraftProtocolVersion::MINECRAFT_1_14,
      new VersionRegistry({ByteMetadataEntry::ORDINAL, VarIntMetadataEntry::ORDINAL, FloatMetadataEntry::ORDINAL, StringMetadataEntry::ORDINAL,
        ChatMetadataEntry::ORDINAL, OptChatMetadataEntry::ORDINAL, ItemStackMetadataEntry::ORDINAL, BooleanMetadataEntry::ORDINAL,
        RotationMetadataEntry::ORDINAL, PositionMetadataEntry::ORDINAL, OptPositionMetadataEntry::ORDINAL, DirectionMetadataEntry::ORDINAL,
        OptUUIDMetadataEntry::ORDINAL, BlockIDMetadataEntry::ORDINAL, NBTMetadataEntry::ORDINAL, ParticleMetadataEntry::ORDINAL,
        VillagerDataMetadataEntry::ORDINAL, OptVarIntMetadataEntry::ORDINAL, PoseMetadataEntry::ORDINAL}));

    dataRegistry.RegisterVersion(&MinecraftProtocolVersion::MINECRAFT_1_19,
      new VersionRegistry({ByteMetadataEntry::ORDINAL, VarIntMetadataEntry::ORDINAL, FloatMetadataEntry::ORDINAL, StringMetadataEntry::ORDINAL,
        ChatMetadataEntry::ORDINAL, OptChatMetadataEntry::ORDINAL, ItemStackMetadataEntry::ORDINAL, BooleanMetadataEntry::ORDINAL,
        RotationMetadataEntry::ORDINAL, PositionMetadataEntry::ORDINAL, OptPositionMetadataEntry::ORDINAL, DirectionMetadataEntry::ORDINAL,
        OptUUIDMetadataEntry::ORDINAL, BlockIDMetadataEntry::ORDINAL, NBTMetadataEntry::ORDINAL, ParticleMetadataEntry::ORDINAL,
        VillagerDataMetadataEntry::ORDINAL, OptVarIntMetadataEntry::ORDINAL, PoseMetadataEntry::ORDINAL, CatVariantMetadataEntry::ORDINAL,
        FrogVariantMetadataEntry::ORDINAL, PaintingVariantMetadataEntry::ORDINAL}));

    dataRegistry.RegisterVersion(&MinecraftProtocolVersion::MINECRAFT_1_19_1,
      new VersionRegistry({ByteMetadataEntry::ORDINAL, VarIntMetadataEntry::ORDINAL, FloatMetadataEntry::ORDINAL, StringMetadataEntry::ORDINAL,
        ChatMetadataEntry::ORDINAL, OptChatMetadataEntry::ORDINAL, ItemStackMetadataEntry::ORDINAL, BooleanMetadataEntry::ORDINAL,
        RotationMetadataEntry::ORDINAL, PositionMetadataEntry::ORDINAL, OptPositionMetadataEntry::ORDINAL, DirectionMetadataEntry::ORDINAL,
        OptUUIDMetadataEntry::ORDINAL, BlockIDMetadataEntry::ORDINAL, NBTMetadataEntry::ORDINAL, ParticleMetadataEntry::ORDINAL,
        VillagerDataMetadataEntry::ORDINAL, OptVarIntMetadataEntry::ORDINAL, PoseMetadataEntry::ORDINAL, CatVariantMetadataEntry::ORDINAL,
        FrogVariantMetadataEntry::ORDINAL, GlobalPosMetadataEntry::ORDINAL, PaintingVariantMetadataEntry::ORDINAL}));

    dataRegistry.RegisterVersion(&MinecraftProtocolVersion::MINECRAFT_1_19_3,
      new VersionRegistry({ByteMetadataEntry::ORDINAL, VarIntMetadataEntry::ORDINAL, LongMetadataEntry::ORDINAL, FloatMetadataEntry::ORDINAL,
        StringMetadataEntry::ORDINAL, ChatMetadataEntry::ORDINAL, OptChatMetadataEntry::ORDINAL, ItemStackMetadataEntry::ORDINAL,
        BooleanMetadataEntry::ORDINAL, RotationMetadataEntry::ORDINAL, PositionMetadataEntry::ORDINAL, OptPositionMetadataEntry::ORDINAL,
        DirectionMetadataEntry::ORDINAL, OptUUIDMetadataEntry::ORDINAL, BlockIDMetadataEntry::ORDINAL, NBTMetadataEntry::ORDINAL,
        ParticleMetadataEntry::ORDINAL, VillagerDataMetadataEntry::ORDINAL, OptVarIntMetadataEntry::ORDINAL, PoseMetadataEntry::ORDINAL,
        CatVariantMetadataEntry::ORDINAL, FrogVariantMetadataEntry::ORDINAL, GlobalPosMetadataEntry::ORDINAL, PaintingVariantMetadataEntry::ORDINAL}));

    return dataRegistry;
  }

  EnumRegistry<CatVariant> GetCatVariantRegistry() {
    EnumRegistry<CatVariant> catRegistry(MinecraftProtocolVersion::VERSIONS, {MinecraftProtocolVersion::MINECRAFT_1_19});

    catRegistry.RegisterVersion(&MinecraftProtocolVersion::MINECRAFT_1_19,
      new VersionRegistry(
        std::vector<CatVariant>({CatVariant::TABBY, CatVariant::BLACK, CatVariant::RED, CatVariant::SIAMESE, CatVariant::BRITISH_SHORTHAIR,
          CatVariant::CALICO, CatVariant::PERSIAN, CatVariant::RAGDOLL, CatVariant::WHITE, CatVariant::JELLIE, CatVariant::ALL_BLACK})));

    return catRegistry;
  }

  EnumRegistry<FrogVariant> GetFrogVariantRegistry() {
    EnumRegistry<FrogVariant> frogRegistry(MinecraftProtocolVersion::VERSIONS, {MinecraftProtocolVersion::MINECRAFT_1_19});

    frogRegistry.RegisterVersion(
      &MinecraftProtocolVersion::MINECRAFT_1_19, new VersionRegistry(std::vector<FrogVariant>({FrogVariant::TEMPERATE, FrogVariant::WARM, FrogVariant::COLD})));

    return frogRegistry;
  }

  EnumRegistry<PaintingVariant> GetPaintingVariantRegistry() {
    EnumRegistry<PaintingVariant> paintingRegistry(MinecraftProtocolVersion::VERSIONS, {
      MinecraftProtocolVersion::MINECRAFT_1_12_2,
      MinecraftProtocolVersion::MINECRAFT_1_19,
    });

    paintingRegistry.RegisterVersion(&MinecraftProtocolVersion::MINECRAFT_1_12_2,
      new VersionRegistry(std::vector<PaintingVariant>(
        {PaintingVariant::KEBAB, PaintingVariant::AZTEC, PaintingVariant::ALBAN, PaintingVariant::AZTEC2, PaintingVariant::BOMB, PaintingVariant::PLANT,
          PaintingVariant::WASTELAND, PaintingVariant::POOL, PaintingVariant::COURBET, PaintingVariant::SEA, PaintingVariant::SUNSET,
          PaintingVariant::CREEBET, PaintingVariant::WANDERER, PaintingVariant::GRAHAM, PaintingVariant::MATCH, PaintingVariant::BUST,
          PaintingVariant::STAGE, PaintingVariant::VOID, PaintingVariant::SKULL_AND_ROSES, PaintingVariant::WITHER, PaintingVariant::FIGHTERS,
          PaintingVariant::POINTER, PaintingVariant::PIGSCENE, PaintingVariant::BURNING_SKULL, PaintingVariant::SKELETON, PaintingVariant::DONKEY_KONG})));

    paintingRegistry.RegisterVersion(&MinecraftProtocolVersion::MINECRAFT_1_19,
      new VersionRegistry(std::vector<PaintingVariant>({PaintingVariant::KEBAB, PaintingVariant::AZTEC, PaintingVariant::ALBAN, PaintingVariant::AZTEC2,
        PaintingVariant::BOMB, PaintingVariant::PLANT, PaintingVariant::WASTELAND, PaintingVariant::POOL, PaintingVariant::COURBET, PaintingVariant::SEA,
        PaintingVariant::SUNSET, PaintingVariant::CREEBET, PaintingVariant::WANDERER, PaintingVariant::GRAHAM, PaintingVariant::MATCH,
        PaintingVariant::BUST, PaintingVariant::STAGE, PaintingVariant::VOID, PaintingVariant::SKULL_AND_ROSES, PaintingVariant::WITHER,
        PaintingVariant::FIGHTERS, PaintingVariant::POINTER, PaintingVariant::PIGSCENE, PaintingVariant::BURNING_SKULL, PaintingVariant::SKELETON,
        PaintingVariant::EARTH, PaintingVariant::WIND, PaintingVariant::WATER, PaintingVariant::FIRE, PaintingVariant::DONKEY_KONG})));

    return paintingRegistry;
  }

  const ConstructorRegistry<MetadataEntry> METADATA_ENTRY_REGISTRY = GetMetadataRegistry();

  const EnumRegistry<CatVariant> CAT_VARIANT_REGISTRY = GetCatVariantRegistry();
  const EnumRegistry<FrogVariant> FROG_VARIANT_REGISTRY = GetFrogVariantRegistry();
  const EnumRegistry<PaintingVariant> PAINTING_VARIANT_REGISTRY = GetPaintingVariantRegistry();
}