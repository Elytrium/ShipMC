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
    VersionRegistry* versionRegistry = ConstructorRegistry<MetadataEntry>::NewVersionRegistry();

    VersionRegistry* registry1_12_2 = versionRegistry + ProtocolVersion::MINECRAFT_1_12_2.GetPacketIDOrdinal();
    registry1_12_2->Register(ByteMetadataEntry::ORDINAL, 0);
    registry1_12_2->Register(VarIntMetadataEntry::ORDINAL, 1);
    registry1_12_2->Register(FloatMetadataEntry::ORDINAL, 2);
    registry1_12_2->Register(StringMetadataEntry::ORDINAL, 3);
    registry1_12_2->Register(ChatMetadataEntry::ORDINAL, 4);
    registry1_12_2->Register(ItemStackMetadataEntry::ORDINAL, 5);
    registry1_12_2->Register(BooleanMetadataEntry::ORDINAL, 6);
    registry1_12_2->Register(RotationMetadataEntry::ORDINAL, 7);
    registry1_12_2->Register(PositionMetadataEntry::ORDINAL, 8);
    registry1_12_2->Register(OptPositionMetadataEntry::ORDINAL, 9);
    registry1_12_2->Register(DirectionMetadataEntry::ORDINAL, 10);
    registry1_12_2->Register(OptUUIDMetadataEntry::ORDINAL, 11);
    registry1_12_2->Register(BlockIDMetadataEntry::ORDINAL, 12);
    registry1_12_2->Register(NBTMetadataEntry::ORDINAL, 13);

    for (uint32_t i = ProtocolVersion::MINECRAFT_1_13.GetOrdinal(); i <= ProtocolVersion::MINECRAFT_1_13_2.GetOrdinal(); ++i) {
      versionRegistry[i].Register(ByteMetadataEntry::ORDINAL, 0);
      versionRegistry[i].Register(VarIntMetadataEntry::ORDINAL, 1);
      versionRegistry[i].Register(FloatMetadataEntry::ORDINAL, 2);
      versionRegistry[i].Register(StringMetadataEntry::ORDINAL, 3);
      versionRegistry[i].Register(ChatMetadataEntry::ORDINAL, 4);
      versionRegistry[i].Register(OptChatMetadataEntry::ORDINAL, 5);
      versionRegistry[i].Register(ItemStackMetadataEntry::ORDINAL, 6);
      versionRegistry[i].Register(BooleanMetadataEntry::ORDINAL, 7);
      versionRegistry[i].Register(RotationMetadataEntry::ORDINAL, 8);
      versionRegistry[i].Register(PositionMetadataEntry::ORDINAL, 9);
      versionRegistry[i].Register(OptPositionMetadataEntry::ORDINAL, 10);
      versionRegistry[i].Register(DirectionMetadataEntry::ORDINAL, 11);
      versionRegistry[i].Register(OptUUIDMetadataEntry::ORDINAL, 12);
      versionRegistry[i].Register(BlockIDMetadataEntry::ORDINAL, 13);
      versionRegistry[i].Register(NBTMetadataEntry::ORDINAL, 14);
      versionRegistry[i].Register(ParticleMetadataEntry::ORDINAL, 15);
    }

    for (uint32_t i = ProtocolVersion::MINECRAFT_1_14.GetOrdinal(); i <= ProtocolVersion::MINECRAFT_1_17_1.GetOrdinal(); ++i) {
      versionRegistry[i].Register(ByteMetadataEntry::ORDINAL, 0);
      versionRegistry[i].Register(VarIntMetadataEntry::ORDINAL, 1);
      versionRegistry[i].Register(FloatMetadataEntry::ORDINAL, 2);
      versionRegistry[i].Register(StringMetadataEntry::ORDINAL, 3);
      versionRegistry[i].Register(ChatMetadataEntry::ORDINAL, 4);
      versionRegistry[i].Register(OptChatMetadataEntry::ORDINAL, 5);
      versionRegistry[i].Register(ItemStackMetadataEntry::ORDINAL, 6);
      versionRegistry[i].Register(BooleanMetadataEntry::ORDINAL, 7);
      versionRegistry[i].Register(RotationMetadataEntry::ORDINAL, 8);
      versionRegistry[i].Register(PositionMetadataEntry::ORDINAL, 9);
      versionRegistry[i].Register(OptPositionMetadataEntry::ORDINAL, 10);
      versionRegistry[i].Register(DirectionMetadataEntry::ORDINAL, 11);
      versionRegistry[i].Register(OptUUIDMetadataEntry::ORDINAL, 12);
      versionRegistry[i].Register(BlockIDMetadataEntry::ORDINAL, 13);
      versionRegistry[i].Register(NBTMetadataEntry::ORDINAL, 14);
      versionRegistry[i].Register(ParticleMetadataEntry::ORDINAL, 15);
      versionRegistry[i].Register(VillagerDataMetadataEntry::ORDINAL, 16);
      versionRegistry[i].Register(OptVarIntMetadataEntry::ORDINAL, 17);
      versionRegistry[i].Register(PoseMetadataEntry::ORDINAL, 18);
    }

    VersionRegistry* registry1_19 = versionRegistry + ProtocolVersion::MINECRAFT_1_19.GetPacketIDOrdinal();
    registry1_19->Register(ByteMetadataEntry::ORDINAL, 0);
    registry1_19->Register(VarIntMetadataEntry::ORDINAL, 1);
    registry1_19->Register(FloatMetadataEntry::ORDINAL, 2);
    registry1_19->Register(StringMetadataEntry::ORDINAL, 3);
    registry1_19->Register(ChatMetadataEntry::ORDINAL, 4);
    registry1_19->Register(OptChatMetadataEntry::ORDINAL, 5);
    registry1_19->Register(ItemStackMetadataEntry::ORDINAL, 6);
    registry1_19->Register(BooleanMetadataEntry::ORDINAL, 7);
    registry1_19->Register(RotationMetadataEntry::ORDINAL, 8);
    registry1_19->Register(PositionMetadataEntry::ORDINAL, 9);
    registry1_19->Register(OptPositionMetadataEntry::ORDINAL, 10);
    registry1_19->Register(DirectionMetadataEntry::ORDINAL, 11);
    registry1_19->Register(OptUUIDMetadataEntry::ORDINAL, 12);
    registry1_19->Register(BlockIDMetadataEntry::ORDINAL, 13);
    registry1_19->Register(NBTMetadataEntry::ORDINAL, 14);
    registry1_19->Register(ParticleMetadataEntry::ORDINAL, 15);
    registry1_19->Register(VillagerDataMetadataEntry::ORDINAL, 16);
    registry1_19->Register(OptVarIntMetadataEntry::ORDINAL, 17);
    registry1_19->Register(PoseMetadataEntry::ORDINAL, 18);
    registry1_19->Register(CatVariantMetadataEntry::ORDINAL, 19);
    registry1_19->Register(FrogVariantMetadataEntry::ORDINAL, 20);
    registry1_19->Register(PaintingVariantMetadataEntry::ORDINAL, 21);

    VersionRegistry* registry1_19_1 = versionRegistry + ProtocolVersion::MINECRAFT_1_19_1.GetPacketIDOrdinal();
    registry1_19_1->Register(ByteMetadataEntry::ORDINAL, 0);
    registry1_19_1->Register(VarIntMetadataEntry::ORDINAL, 1);
    registry1_19_1->Register(FloatMetadataEntry::ORDINAL, 2);
    registry1_19_1->Register(StringMetadataEntry::ORDINAL, 3);
    registry1_19_1->Register(ChatMetadataEntry::ORDINAL, 4);
    registry1_19_1->Register(OptChatMetadataEntry::ORDINAL, 5);
    registry1_19_1->Register(ItemStackMetadataEntry::ORDINAL, 6);
    registry1_19_1->Register(BooleanMetadataEntry::ORDINAL, 7);
    registry1_19_1->Register(RotationMetadataEntry::ORDINAL, 8);
    registry1_19_1->Register(PositionMetadataEntry::ORDINAL, 9);
    registry1_19_1->Register(OptPositionMetadataEntry::ORDINAL, 10);
    registry1_19_1->Register(DirectionMetadataEntry::ORDINAL, 11);
    registry1_19_1->Register(OptUUIDMetadataEntry::ORDINAL, 12);
    registry1_19_1->Register(BlockIDMetadataEntry::ORDINAL, 13);
    registry1_19_1->Register(NBTMetadataEntry::ORDINAL, 14);
    registry1_19_1->Register(ParticleMetadataEntry::ORDINAL, 15);
    registry1_19_1->Register(VillagerDataMetadataEntry::ORDINAL, 16);
    registry1_19_1->Register(OptVarIntMetadataEntry::ORDINAL, 17);
    registry1_19_1->Register(PoseMetadataEntry::ORDINAL, 18);
    registry1_19_1->Register(CatVariantMetadataEntry::ORDINAL, 19);
    registry1_19_1->Register(FrogVariantMetadataEntry::ORDINAL, 20);
    registry1_19_1->Register(GlobalPosMetadataEntry::ORDINAL, 21);
    registry1_19_1->Register(PaintingVariantMetadataEntry::ORDINAL, 22);

    ConstructorRegistry<MetadataEntry> dataRegistry(nullptr);

    dataRegistry.RegisterConstructor(ByteMetadataEntry::ORDINAL, CreateConstructor<ByteMetadataEntry>(0));
    dataRegistry.RegisterConstructor(VarIntMetadataEntry::ORDINAL, CreateConstructor<VarIntMetadataEntry>(0));
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

    return dataRegistry;
  }

  EnumRegistry<CatVariant> GetCatVariantRegistry() {
    VersionRegistry* versionRegistry = EnumRegistry<CatVariant>::NewVersionRegistry();

    // TODO: Other versions

    for (uint32_t i = ProtocolVersion::MINECRAFT_1_19.GetOrdinal(); i <= ProtocolVersion::MINECRAFT_1_19_1.GetOrdinal(); ++i) {
      versionRegistry[i].Register((uint32_t) CatVariant::TABBY, 0);
      versionRegistry[i].Register((uint32_t) CatVariant::BLACK, 1);
      versionRegistry[i].Register((uint32_t) CatVariant::RED, 2);
      versionRegistry[i].Register((uint32_t) CatVariant::SIAMESE, 3);
      versionRegistry[i].Register((uint32_t) CatVariant::BRITISH_SHORTHAIR, 4);
      versionRegistry[i].Register((uint32_t) CatVariant::CALICO, 5);
      versionRegistry[i].Register((uint32_t) CatVariant::PERSIAN, 6);
      versionRegistry[i].Register((uint32_t) CatVariant::RAGDOLL, 7);
      versionRegistry[i].Register((uint32_t) CatVariant::WHITE, 8);
      versionRegistry[i].Register((uint32_t) CatVariant::JELLIE, 9);
      versionRegistry[i].Register((uint32_t) CatVariant::ALL_BLACK, 10);
    }

    return EnumRegistry<CatVariant>(versionRegistry);
  }

  EnumRegistry<FrogVariant> GetFrogVariantRegistry() {
    VersionRegistry* versionRegistry = EnumRegistry<FrogVariant>::NewVersionRegistry();

    // TODO: Other versions

    for (uint32_t i = ProtocolVersion::MINECRAFT_1_19.GetOrdinal(); i <= ProtocolVersion::MINECRAFT_1_19_1.GetOrdinal(); ++i) {
      versionRegistry[i].Register((uint32_t) FrogVariant::TEMPERATE, 0);
      versionRegistry[i].Register((uint32_t) FrogVariant::WARM, 1);
      versionRegistry[i].Register((uint32_t) FrogVariant::COLD, 2);
    }

    return EnumRegistry<FrogVariant>(versionRegistry);
  }

  EnumRegistry<PaintingVariant> GetPaintingVariantRegistry() {
    VersionRegistry* versionRegistry = EnumRegistry<PaintingVariant>::NewVersionRegistry();

    // TODO: Other versions

    for (uint32_t i = ProtocolVersion::MINECRAFT_1_19.GetOrdinal(); i <= ProtocolVersion::MINECRAFT_1_19_1.GetOrdinal(); ++i) {
      versionRegistry[i].Register((uint32_t) PaintingVariant::KEBAB, 0);
      versionRegistry[i].Register((uint32_t) PaintingVariant::AZTEC, 1);
      versionRegistry[i].Register((uint32_t) PaintingVariant::ALBAN, 2);
      versionRegistry[i].Register((uint32_t) PaintingVariant::AZTEC2, 3);
      versionRegistry[i].Register((uint32_t) PaintingVariant::BOMB, 4);
      versionRegistry[i].Register((uint32_t) PaintingVariant::PLANT, 5);
      versionRegistry[i].Register((uint32_t) PaintingVariant::WASTELAND, 6);
      versionRegistry[i].Register((uint32_t) PaintingVariant::POOL, 7);
      versionRegistry[i].Register((uint32_t) PaintingVariant::COURBET, 8);
      versionRegistry[i].Register((uint32_t) PaintingVariant::SEA, 9);
      versionRegistry[i].Register((uint32_t) PaintingVariant::SUNSET, 10);
      versionRegistry[i].Register((uint32_t) PaintingVariant::CREEBET, 11);
      versionRegistry[i].Register((uint32_t) PaintingVariant::WANDERER, 12);
      versionRegistry[i].Register((uint32_t) PaintingVariant::GRAHAM, 13);
      versionRegistry[i].Register((uint32_t) PaintingVariant::MATCH, 14);
      versionRegistry[i].Register((uint32_t) PaintingVariant::BUST, 15);
      versionRegistry[i].Register((uint32_t) PaintingVariant::STAGE, 16);
      versionRegistry[i].Register((uint32_t) PaintingVariant::VOID, 17);
      versionRegistry[i].Register((uint32_t) PaintingVariant::SKULL_AND_ROSES, 18);
      versionRegistry[i].Register((uint32_t) PaintingVariant::WITHER, 19);
      versionRegistry[i].Register((uint32_t) PaintingVariant::FIGHTERS, 20);
      versionRegistry[i].Register((uint32_t) PaintingVariant::POINTER, 21);
      versionRegistry[i].Register((uint32_t) PaintingVariant::PIGSCENE, 22);
      versionRegistry[i].Register((uint32_t) PaintingVariant::BURNING_SKULL, 23);
      versionRegistry[i].Register((uint32_t) PaintingVariant::SKELETON, 24);
      versionRegistry[i].Register((uint32_t) PaintingVariant::EARTH, 25);
      versionRegistry[i].Register((uint32_t) PaintingVariant::WIND, 26);
      versionRegistry[i].Register((uint32_t) PaintingVariant::WATER, 27);
      versionRegistry[i].Register((uint32_t) PaintingVariant::FIRE, 28);
      versionRegistry[i].Register((uint32_t) PaintingVariant::DONKEY_KONG, 29);
    }

    return EnumRegistry<PaintingVariant>(versionRegistry);
  }

  const ConstructorRegistry<MetadataEntry> METADATA_ENTRY_REGISTRY = GetMetadataRegistry();

  const EnumRegistry<CatVariant> CAT_VARIANT_REGISTRY = GetCatVariantRegistry();
  const EnumRegistry<FrogVariant> FROG_VARIANT_REGISTRY = GetFrogVariantRegistry();
  const EnumRegistry<PaintingVariant> PAINTING_VARIANT_REGISTRY = GetPaintingVariantRegistry();
}