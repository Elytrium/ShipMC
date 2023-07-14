#include "Metadata.hpp"

namespace Ship {

  VillagerDataMetadataEntry::VillagerDataMetadataEntry(VillagerData value) : value(value) {
  }

  Errorable<bool> VillagerDataMetadataEntry::Write(const ProtocolVersion* version, ByteBuffer* buffer) const {
    ProceedErrorable(typeID, uint32_t, VILLAGER_TYPE_REGISTRY.GetID(version, value.GetType()), InvalidSerializableWriteErrorable(buffer->GetReadableBytes()))
    buffer->WriteVarInt(typeID);
    ProceedErrorable(professionID, uint32_t, VILLAGER_PROFESSION_REGISTRY.GetID(version, value.GetProfession()), InvalidSerializableWriteErrorable(buffer->GetReadableBytes()))
    buffer->WriteVarInt(professionID);
    buffer->WriteVarInt(value.GetLevel());
    return SuccessErrorable<bool>(true);
  }

  Errorable<VillagerDataMetadataEntry> VillagerDataMetadataEntry::Instantiate(const ProtocolVersion* version, ByteBuffer* buffer) {
    ProceedErrorable(typeID, uint32_t, buffer->ReadVarInt(), InvalidVillagerDataMetadataEntryErrorable(buffer->GetReadableBytes()))
    ProceedErrorable(type, VillagerType, VILLAGER_TYPE_REGISTRY.GetValue(version, typeID), InvalidVillagerDataMetadataEntryErrorable(buffer->GetReadableBytes()))

    ProceedErrorable(professionID, uint32_t, buffer->ReadVarInt(), InvalidVillagerDataMetadataEntryErrorable(buffer->GetReadableBytes()))
    ProceedErrorable(profession, VillagerProfession, VILLAGER_PROFESSION_REGISTRY.GetValue(version, professionID), InvalidVillagerDataMetadataEntryErrorable(buffer->GetReadableBytes()))

    ProceedErrorable(level, uint32_t, buffer->ReadVarInt(), InvalidVillagerDataMetadataEntryErrorable(buffer->GetReadableBytes()))

    return SuccessErrorable<VillagerDataMetadataEntry>(VillagerDataMetadataEntry({type, profession, level}));
  }

  MetadataEntryType VillagerDataMetadataEntry::GetType() const {
    return MetadataEntryType::VILLAGER_DATA;
  }

  uint32_t VillagerDataMetadataEntry::GetOrdinal() const {
    return ORDINAL;
  }

  VillagerData VillagerDataMetadataEntry::GetValue() const {
    return value;
  }

  void VillagerDataMetadataEntry::SetValue(VillagerData newValue) {
    value = newValue;
  }
}