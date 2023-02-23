#include "Metadata.hpp"
#include "../../../../utils/exceptions/Exception.hpp"

namespace Ship {

  void Metadata::Read(const ProtocolVersion* version, ByteBuffer* buffer) {
    while (true) {
      uint8_t index = buffer->ReadByte();
      if (index == 0xFF) {
        break;
      }

      uint32_t type = buffer->ReadVarInt();
      MetadataEntry* entry = METADATA_ENTRY_REGISTRY.GetObjectByID(version, type);
      entry->Read(version, buffer);
      Set(index, entry);
    }
  }

  void Metadata::Write(const ProtocolVersion* version, ByteBuffer* buffer) {
    for (auto& pair : entries) {
      uint8_t index = pair.first;
      MetadataEntry* entry = pair.second;

      if (entry) {
        buffer->WriteByte(index);
        buffer->WriteVarInt(METADATA_ENTRY_REGISTRY.GetIDByOrdinal(version, entry->GetOrdinal()));
        entry->Write(version, buffer);
      }
    }
    buffer->WriteByte(0xFF);
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

  std::optional<uint8_t> Metadata::GetByte(uint8_t index) const {
    auto* entry = Get<ByteMetadataEntry>(index);
    if (!entry) {
      return std::nullopt;
    }

    if (entry->GetType() != MetadataEntryType::BYTE) {
      throw Exception("The requested type (Byte) doesn't match the actual type");
    }

    return entry->GetValue();
  }

  std::optional<uint32_t> Metadata::GetVarInt(uint8_t index) const {
    auto* entry = Get<VarIntMetadataEntry>(index);
    if (!entry) {
      return std::nullopt;
    }

    if (entry->GetType() != MetadataEntryType::VARINT) {
      throw Exception("The requested type (VarInt) doesn't match the actual type");
    }

    return entry->GetValue();
  }

  std::optional<uint64_t> Metadata::GetLong(uint8_t index) const {
    auto* entry = Get<LongMetadataEntry>(index);
    if (!entry) {
      return std::nullopt;
    }

    if (entry->GetType() != MetadataEntryType::LONG) {
      throw Exception("The requested type (Long) doesn't match the actual type");
    }

    return entry->GetValue();
  }

  std::optional<float> Metadata::GetFloat(uint8_t index) const {
    auto* entry = Get<FloatMetadataEntry>(index);
    if (!entry) {
      return std::nullopt;
    }

    if (entry->GetType() != MetadataEntryType::FLOAT) {
      throw Exception("The requested type (Float) doesn't match the actual type");
    }

    return entry->GetValue();
  }

  std::optional<std::string> Metadata::GetString(uint8_t index) const {
    auto* entry = Get<StringMetadataEntry>(index);
    if (!entry) {
      return std::nullopt;
    }

    if (entry->GetType() != MetadataEntryType::STRING) {
      throw Exception("The requested type (String) doesn't match the actual type");
    }

    return entry->GetValue();
  }

  std::optional<std::string> Metadata::GetChat(uint8_t index) const {
    auto* entry = Get<ChatMetadataEntry>(index);
    if (!entry) {
      return std::nullopt;
    }

    if (entry->GetType() != MetadataEntryType::CHAT) {
      throw Exception("The requested type (Chat) doesn't match the actual type");
    }

    return entry->GetValue();
  }

  std::optional<std::optional<std::string>> Metadata::GetOptChat(uint8_t index) const {
    auto* entry = Get<OptChatMetadataEntry>(index);
    if (!entry) {
      return std::nullopt;
    }

    if (entry->GetType() != MetadataEntryType::OPT_CHAT) {
      throw Exception("The requested type (OptChat) doesn't match the actual type");
    }

    return entry->GetValue();
  }

  std::optional<ItemStack> Metadata::GetItemStack(uint8_t index) const {
    auto* entry = Get<ItemStackMetadataEntry>(index);
    if (!entry) {
      return std::nullopt;
    }

    if (entry->GetType() != MetadataEntryType::ITEM_STACK) {
      throw Exception("The requested type (ItemStack) doesn't match the actual type");
    }

    return entry->GetValue();
  }

  std::optional<bool> Metadata::GetBoolean(uint8_t index) const {
    auto* entry = Get<BooleanMetadataEntry>(index);
    if (!entry) {
      return std::nullopt;
    }

    if (entry->GetType() != MetadataEntryType::BOOLEAN) {
      throw Exception("The requested type (Boolean) doesn't match the actual type");
    }

    return entry->GetValue();
  }

  bool Metadata::GetRotation(uint8_t index, float& x, float& y, float& z) const {
    auto* entry = Get<RotationMetadataEntry>(index);
    if (!entry) {
      return false;
    }

    if (entry->GetType() != MetadataEntryType::ROTATION) {
      throw Exception("The requested type (Rotation) doesn't match the actual type");
    }

    entry->Get(x, y, z);
    return true;
  }

  bool Metadata::GetPosition(uint8_t index, int& x, int& y, int& z) const {
    auto* entry = Get<PositionMetadataEntry>(index);
    if (!entry) {
      return false;
    }

    if (entry->GetType() != MetadataEntryType::POSITION) {
      throw Exception("The requested type (Position) doesn't match the actual type");
    }

    entry->Get(x, y, z);
    return true;
  }

  bool Metadata::GetOptPosition(uint8_t index, bool& present, int& x, int& y, int& z) const {
    auto* entry = Get<OptPositionMetadataEntry>(index);
    if (!entry) {
      return false;
    }

    if (entry->GetType() != MetadataEntryType::OPT_POSITION) {
      throw Exception("The requested type (OptPosition) doesn't match the actual type");
    }

    entry->Get(present, x, y, z);
    return true;
  }

  std::optional<Direction> Metadata::GetDirection(uint8_t index) const {
    auto* entry = Get<DirectionMetadataEntry>(index);
    if (!entry) {
      return std::nullopt;
    }

    if (entry->GetType() != MetadataEntryType::DIRECTION) {
      throw Exception("The requested type (Direction) doesn't match the actual type");
    }

    return entry->GetValue();
  }

  std::optional<std::optional<UUID>> Metadata::GetOptUUID(uint8_t index) const {
    auto* entry = Get<OptUUIDMetadataEntry>(index);
    if (!entry) {
      return std::nullopt;
    }

    if (entry->GetType() != MetadataEntryType::OPT_UUID) {
      throw Exception("The requested type (OptUUID) doesn't match the actual type");
    }

    return entry->GetValue();
  }

  std::optional<uint32_t> Metadata::GetBlockID(uint8_t index) const {
    auto* entry = Get<BlockIDMetadataEntry>(index);
    if (!entry) {
      return std::nullopt;
    }

    if (entry->GetType() != MetadataEntryType::BLOCK_ID) {
      throw Exception("The requested type (BlockID) doesn't match the actual type");
    }

    return entry->GetValue();
  }

  std::optional<NBT*> Metadata::GetNBT(uint8_t index) const {
    auto* entry = Get<NBTMetadataEntry>(index);
    if (!entry) {
      return std::nullopt;
    }

    if (entry->GetType() != MetadataEntryType::NBT) {
      throw Exception("The requested type (NBT) doesn't match the actual type");
    }

    return entry->GetValue();
  }

  std::optional<AbstractParticle*> Metadata::GetParticle(uint8_t index) const {
    auto* entry = Get<ParticleMetadataEntry>(index);
    if (!entry) {
      return std::nullopt;
    }

    if (entry->GetType() != MetadataEntryType::PARTICLE) {
      throw Exception("The requested type (Particle) doesn't match the actual type");
    }

    return entry->GetValue();
  }

  bool Metadata::GetVillagerData(uint8_t index, VillagerType& type, VillagerProfession& profession, uint32_t& level) const {
    auto* entry = Get<VillagerDataMetadataEntry>(index);
    if (!entry) {
      return false;
    }

    if (entry->GetType() != MetadataEntryType::VILLAGER_DATA) {
      throw Exception("The requested type (VillagerData) doesn't match the actual type");
    }

    type = entry->GetVillagerType();
    profession = entry->GetProfession();
    level = entry->GetLevel();
    return true;
  }

  std::optional<std::optional<uint32_t>> Metadata::GetOptVarInt(uint8_t index) const {
    auto* entry = Get<OptVarIntMetadataEntry>(index);
    if (!entry) {
      return std::nullopt;
    }

    if (entry->GetType() != MetadataEntryType::OPT_VARINT) {
      throw Exception("The requested type (OptVarInt) doesn't match the actual type");
    }

    return entry->GetValue();
  }

  std::optional<Pose> Metadata::GetPose(uint8_t index) const {
    auto* entry = Get<PoseMetadataEntry>(index);
    if (!entry) {
      return std::nullopt;
    }

    if (entry->GetType() != MetadataEntryType::POSE) {
      throw Exception("The requested type (Pose) doesn't match the actual type");
    }

    return entry->GetValue();
  }

  std::optional<CatVariant> Metadata::GetCatVariant(uint8_t index) const {
    auto* entry = Get<CatVariantMetadataEntry>(index);
    if (!entry) {
      return std::nullopt;
    }

    if (entry->GetType() != MetadataEntryType::CAT_VARIANT) {
      throw Exception("The requested type (CatVariant) doesn't match the actual type");
    }

    return entry->GetValue();
  }

  std::optional<FrogVariant> Metadata::GetFrogVariant(uint8_t index) const {
    auto* entry = Get<FrogVariantMetadataEntry>(index);
    if (!entry) {
      return std::nullopt;
    }

    if (entry->GetType() != MetadataEntryType::FROG_VARIANT) {
      throw Exception("The requested type (FrogVariant) doesn't match the actual type");
    }

    return entry->GetValue();
  }

  bool Metadata::GetGlobalPos(uint8_t index, std::string& dimension, int& x, int& y, int& z) const {
    auto* entry = Get<GlobalPosMetadataEntry>(index);
    if (!entry) {
      return false;
    }

    if (entry->GetType() != MetadataEntryType::GLOBAL_POS) {
      throw Exception("The requested type (GlobalPos) doesn't match the actual type");
    }

    entry->Get(dimension, x, y, z);
    return true;
  }

  std::optional<PaintingVariant> Metadata::GetPaintingVariant(uint8_t index) const {
    auto* entry = Get<PaintingVariantMetadataEntry>(index);
    if (!entry) {
      return std::nullopt;
    }

    if (entry->GetType() != MetadataEntryType::PAINTING_VARIANT) {
      throw Exception("The requested type (PaintingVariant) doesn't match the actual type");
    }

    return entry->GetValue();
  }

  ConstructorRegistry<MetadataEntry> GetMetadataRegistry() {
    ConstructorRegistry<MetadataEntry> dataRegistry({ProtocolVersion::MINECRAFT_1_12_2, ProtocolVersion::MINECRAFT_1_13, ProtocolVersion::MINECRAFT_1_14,
      ProtocolVersion::MINECRAFT_1_19, ProtocolVersion::MINECRAFT_1_19_1, ProtocolVersion::MINECRAFT_1_19_3});

    dataRegistry.RegisterConstructor(ByteMetadataEntry::ORDINAL, CreateConstructor<ByteMetadataEntry>(0));
    dataRegistry.RegisterConstructor(VarIntMetadataEntry::ORDINAL, CreateConstructor<VarIntMetadataEntry>(0));
    dataRegistry.RegisterConstructor(LongMetadataEntry::ORDINAL, CreateConstructor<LongMetadataEntry>(0));
    dataRegistry.RegisterConstructor(FloatMetadataEntry::ORDINAL, CreateConstructor<FloatMetadataEntry>(0));
    dataRegistry.RegisterConstructor(StringMetadataEntry::ORDINAL, CreateConstructor<StringMetadataEntry>(std::string {}));
    dataRegistry.RegisterConstructor(ChatMetadataEntry::ORDINAL, CreateConstructor<ChatMetadataEntry>(std::string {}));
    dataRegistry.RegisterConstructor(OptChatMetadataEntry::ORDINAL, CreateConstructor<OptChatMetadataEntry>());
    dataRegistry.RegisterConstructor(ItemStackMetadataEntry::ORDINAL, CreateConstructor<ItemStackMetadataEntry>(ItemStack {}));
    dataRegistry.RegisterConstructor(BooleanMetadataEntry::ORDINAL, CreateConstructor<BooleanMetadataEntry>(false));
    dataRegistry.RegisterConstructor(RotationMetadataEntry::ORDINAL, CreateConstructor<RotationMetadataEntry>(0, 0, 0));
    dataRegistry.RegisterConstructor(PositionMetadataEntry::ORDINAL, CreateConstructor<PositionMetadataEntry>(0, 0, 0));
    dataRegistry.RegisterConstructor(OptPositionMetadataEntry::ORDINAL, CreateConstructor<OptPositionMetadataEntry>());
    dataRegistry.RegisterConstructor(DirectionMetadataEntry::ORDINAL, CreateConstructor<DirectionMetadataEntry>(Direction {}));
    dataRegistry.RegisterConstructor(OptUUIDMetadataEntry::ORDINAL, CreateConstructor<OptUUIDMetadataEntry>());
    dataRegistry.RegisterConstructor(BlockIDMetadataEntry::ORDINAL, CreateConstructor<BlockIDMetadataEntry>());
    dataRegistry.RegisterConstructor(NBTMetadataEntry::ORDINAL, CreateConstructor<NBTMetadataEntry>(nullptr));
    dataRegistry.RegisterConstructor(ParticleMetadataEntry::ORDINAL, CreateConstructor<ParticleMetadataEntry>(nullptr));
    dataRegistry.RegisterConstructor(
      VillagerDataMetadataEntry::ORDINAL, CreateConstructor<VillagerDataMetadataEntry>(VillagerType {}, VillagerProfession {}, 0));
    dataRegistry.RegisterConstructor(OptVarIntMetadataEntry::ORDINAL, CreateConstructor<OptVarIntMetadataEntry>());
    dataRegistry.RegisterConstructor(PoseMetadataEntry::ORDINAL, CreateConstructor<PoseMetadataEntry>(Pose {}));
    dataRegistry.RegisterConstructor(CatVariantMetadataEntry::ORDINAL, CreateConstructor<CatVariantMetadataEntry>(CatVariant {}));
    dataRegistry.RegisterConstructor(FrogVariantMetadataEntry::ORDINAL, CreateConstructor<FrogVariantMetadataEntry>(FrogVariant {}));
    dataRegistry.RegisterConstructor(GlobalPosMetadataEntry::ORDINAL, CreateConstructor<GlobalPosMetadataEntry>(std::string {}, 0, 0, 0));
    dataRegistry.RegisterConstructor(PaintingVariantMetadataEntry::ORDINAL, CreateConstructor<PaintingVariantMetadataEntry>(PaintingVariant {}));

    dataRegistry.RegisterVersion(&ProtocolVersion::MINECRAFT_1_12_2,
      new VersionRegistry({ByteMetadataEntry::ORDINAL, VarIntMetadataEntry::ORDINAL, FloatMetadataEntry::ORDINAL, StringMetadataEntry::ORDINAL,
        ChatMetadataEntry::ORDINAL, ItemStackMetadataEntry::ORDINAL, BooleanMetadataEntry::ORDINAL, RotationMetadataEntry::ORDINAL,
        PositionMetadataEntry::ORDINAL, OptPositionMetadataEntry::ORDINAL, DirectionMetadataEntry::ORDINAL, OptUUIDMetadataEntry::ORDINAL,
        BlockIDMetadataEntry::ORDINAL, NBTMetadataEntry::ORDINAL}));

    dataRegistry.RegisterVersion(&ProtocolVersion::MINECRAFT_1_13,
      new VersionRegistry({ByteMetadataEntry::ORDINAL, VarIntMetadataEntry::ORDINAL, FloatMetadataEntry::ORDINAL, StringMetadataEntry::ORDINAL,
        ChatMetadataEntry::ORDINAL, OptChatMetadataEntry::ORDINAL, ItemStackMetadataEntry::ORDINAL, BooleanMetadataEntry::ORDINAL,
        RotationMetadataEntry::ORDINAL, PositionMetadataEntry::ORDINAL, OptPositionMetadataEntry::ORDINAL, DirectionMetadataEntry::ORDINAL,
        OptUUIDMetadataEntry::ORDINAL, BlockIDMetadataEntry::ORDINAL, NBTMetadataEntry::ORDINAL, ParticleMetadataEntry::ORDINAL}));

    dataRegistry.RegisterVersion(&ProtocolVersion::MINECRAFT_1_14,
      new VersionRegistry({ByteMetadataEntry::ORDINAL, VarIntMetadataEntry::ORDINAL, FloatMetadataEntry::ORDINAL, StringMetadataEntry::ORDINAL,
        ChatMetadataEntry::ORDINAL, OptChatMetadataEntry::ORDINAL, ItemStackMetadataEntry::ORDINAL, BooleanMetadataEntry::ORDINAL,
        RotationMetadataEntry::ORDINAL, PositionMetadataEntry::ORDINAL, OptPositionMetadataEntry::ORDINAL, DirectionMetadataEntry::ORDINAL,
        OptUUIDMetadataEntry::ORDINAL, BlockIDMetadataEntry::ORDINAL, NBTMetadataEntry::ORDINAL, ParticleMetadataEntry::ORDINAL,
        VillagerDataMetadataEntry::ORDINAL, OptVarIntMetadataEntry::ORDINAL, PoseMetadataEntry::ORDINAL}));

    dataRegistry.RegisterVersion(&ProtocolVersion::MINECRAFT_1_19,
      new VersionRegistry({ByteMetadataEntry::ORDINAL, VarIntMetadataEntry::ORDINAL, FloatMetadataEntry::ORDINAL, StringMetadataEntry::ORDINAL,
        ChatMetadataEntry::ORDINAL, OptChatMetadataEntry::ORDINAL, ItemStackMetadataEntry::ORDINAL, BooleanMetadataEntry::ORDINAL,
        RotationMetadataEntry::ORDINAL, PositionMetadataEntry::ORDINAL, OptPositionMetadataEntry::ORDINAL, DirectionMetadataEntry::ORDINAL,
        OptUUIDMetadataEntry::ORDINAL, BlockIDMetadataEntry::ORDINAL, NBTMetadataEntry::ORDINAL, ParticleMetadataEntry::ORDINAL,
        VillagerDataMetadataEntry::ORDINAL, OptVarIntMetadataEntry::ORDINAL, PoseMetadataEntry::ORDINAL, CatVariantMetadataEntry::ORDINAL,
        FrogVariantMetadataEntry::ORDINAL, PaintingVariantMetadataEntry::ORDINAL}));

    dataRegistry.RegisterVersion(&ProtocolVersion::MINECRAFT_1_19_1,
      new VersionRegistry({ByteMetadataEntry::ORDINAL, VarIntMetadataEntry::ORDINAL, FloatMetadataEntry::ORDINAL, StringMetadataEntry::ORDINAL,
        ChatMetadataEntry::ORDINAL, OptChatMetadataEntry::ORDINAL, ItemStackMetadataEntry::ORDINAL, BooleanMetadataEntry::ORDINAL,
        RotationMetadataEntry::ORDINAL, PositionMetadataEntry::ORDINAL, OptPositionMetadataEntry::ORDINAL, DirectionMetadataEntry::ORDINAL,
        OptUUIDMetadataEntry::ORDINAL, BlockIDMetadataEntry::ORDINAL, NBTMetadataEntry::ORDINAL, ParticleMetadataEntry::ORDINAL,
        VillagerDataMetadataEntry::ORDINAL, OptVarIntMetadataEntry::ORDINAL, PoseMetadataEntry::ORDINAL, CatVariantMetadataEntry::ORDINAL,
        FrogVariantMetadataEntry::ORDINAL, GlobalPosMetadataEntry::ORDINAL, PaintingVariantMetadataEntry::ORDINAL}));

    dataRegistry.RegisterVersion(&ProtocolVersion::MINECRAFT_1_19_3,
      new VersionRegistry({ByteMetadataEntry::ORDINAL, VarIntMetadataEntry::ORDINAL, LongMetadataEntry::ORDINAL, FloatMetadataEntry::ORDINAL,
        StringMetadataEntry::ORDINAL, ChatMetadataEntry::ORDINAL, OptChatMetadataEntry::ORDINAL, ItemStackMetadataEntry::ORDINAL,
        BooleanMetadataEntry::ORDINAL, RotationMetadataEntry::ORDINAL, PositionMetadataEntry::ORDINAL, OptPositionMetadataEntry::ORDINAL,
        DirectionMetadataEntry::ORDINAL, OptUUIDMetadataEntry::ORDINAL, BlockIDMetadataEntry::ORDINAL, NBTMetadataEntry::ORDINAL,
        ParticleMetadataEntry::ORDINAL, VillagerDataMetadataEntry::ORDINAL, OptVarIntMetadataEntry::ORDINAL, PoseMetadataEntry::ORDINAL,
        CatVariantMetadataEntry::ORDINAL, FrogVariantMetadataEntry::ORDINAL, GlobalPosMetadataEntry::ORDINAL, PaintingVariantMetadataEntry::ORDINAL}));

    return dataRegistry;
  }

  EnumRegistry<CatVariant> GetCatVariantRegistry() {
    EnumRegistry<CatVariant> catRegistry({ProtocolVersion::MINECRAFT_1_19});

    catRegistry.RegisterVersion(&ProtocolVersion::MINECRAFT_1_19,
      new VersionRegistry(
        std::vector<CatVariant>({CatVariant::TABBY, CatVariant::BLACK, CatVariant::RED, CatVariant::SIAMESE, CatVariant::BRITISH_SHORTHAIR,
          CatVariant::CALICO, CatVariant::PERSIAN, CatVariant::RAGDOLL, CatVariant::WHITE, CatVariant::JELLIE, CatVariant::ALL_BLACK})));

    return catRegistry;
  }

  EnumRegistry<FrogVariant> GetFrogVariantRegistry() {
    EnumRegistry<FrogVariant> frogRegistry({ProtocolVersion::MINECRAFT_1_19});

    frogRegistry.RegisterVersion(
      &ProtocolVersion::MINECRAFT_1_19, new VersionRegistry(std::vector<FrogVariant>({FrogVariant::TEMPERATE, FrogVariant::WARM, FrogVariant::COLD})));

    return frogRegistry;
  }

  EnumRegistry<PaintingVariant> GetPaintingVariantRegistry() {
    EnumRegistry<PaintingVariant> paintingRegistry({
      ProtocolVersion::MINECRAFT_1_12_2,
      ProtocolVersion::MINECRAFT_1_19,
    });

    paintingRegistry.RegisterVersion(&ProtocolVersion::MINECRAFT_1_12_2,
      new VersionRegistry(std::vector<PaintingVariant>(
        {PaintingVariant::KEBAB, PaintingVariant::AZTEC, PaintingVariant::ALBAN, PaintingVariant::AZTEC2, PaintingVariant::BOMB, PaintingVariant::PLANT,
          PaintingVariant::WASTELAND, PaintingVariant::POOL, PaintingVariant::COURBET, PaintingVariant::SEA, PaintingVariant::SUNSET,
          PaintingVariant::CREEBET, PaintingVariant::WANDERER, PaintingVariant::GRAHAM, PaintingVariant::MATCH, PaintingVariant::BUST,
          PaintingVariant::STAGE, PaintingVariant::VOID, PaintingVariant::SKULL_AND_ROSES, PaintingVariant::WITHER, PaintingVariant::FIGHTERS,
          PaintingVariant::POINTER, PaintingVariant::PIGSCENE, PaintingVariant::BURNING_SKULL, PaintingVariant::SKELETON, PaintingVariant::DONKEY_KONG})));

    paintingRegistry.RegisterVersion(&ProtocolVersion::MINECRAFT_1_19,
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