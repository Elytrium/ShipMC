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

      buffer->WriteByte(index);
      buffer->WriteVarInt(METADATA_ENTRY_REGISTRY.GetIDByOrdinal(version, entry->GetOrdinal()));
      entry->Write(version, buffer);
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

  MetadataEntry* Metadata::Get(uint8_t index) {
    return entries[index];
  }

  void Metadata::Set(uint8_t index, MetadataEntry* value) {
    auto it = entries.find(index);
    if (it != entries.end()) {
      delete it->second;
    }

    entries[index] = value;
  }

  DataTypeRegistry<MetadataEntry> GetMetadataRegistry() {
    VersionRegistry* versionRegistry = DataTypeRegistry<MetadataEntry>::NewVersionRegistry();

    // TODO: Other versions

    for (uint32_t i = ProtocolVersion::MINECRAFT_1_19.GetOrdinal(); i <= ProtocolVersion::MINECRAFT_1_19_1.GetOrdinal(); ++i) {
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
      versionRegistry[i].Register(CatVariantMetadataEntry::ORDINAL, 19);
      versionRegistry[i].Register(FrogVariantMetadataEntry::ORDINAL, 20);
      versionRegistry[i].Register(GlobalPosMetadataEntry::ORDINAL, 21);
      versionRegistry[i].Register(PaintingVariantMetadataEntry::ORDINAL, 22);
    }

    DataTypeRegistry<MetadataEntry> dataRegistry(nullptr);

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

  const DataTypeRegistry<MetadataEntry> METADATA_ENTRY_REGISTRY = GetMetadataRegistry();

  const EnumRegistry<CatVariant> CAT_VARIANT_REGISTRY = GetCatVariantRegistry();
  const EnumRegistry<FrogVariant> FROG_VARIANT_REGISTRY = GetFrogVariantRegistry();
  const EnumRegistry<PaintingVariant> PAINTING_VARIANT_REGISTRY = GetPaintingVariantRegistry();
}