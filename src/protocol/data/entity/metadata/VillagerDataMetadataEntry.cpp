#include "Metadata.hpp"

namespace Ship {

  VillagerDataMetadataEntry::VillagerDataMetadataEntry(const VillagerType& type, const VillagerProfession& profession, uint32_t level)
    : type(type), profession(profession), level(level) {
  }

  void VillagerDataMetadataEntry::Write(const ProtocolVersion* version, ByteBuffer* buffer) {
    buffer->WriteVarInt(VILLAGER_TYPE_REGISTRY.GetID(version, type));
    buffer->WriteVarInt(VILLAGER_PROFESSION_REGISTRY.GetID(version, profession));
    buffer->WriteVarInt(level);
  }

  void VillagerDataMetadataEntry::Read(const ProtocolVersion* version, ByteBuffer* buffer) {
    type = VILLAGER_TYPE_REGISTRY.GetValue(version, buffer->ReadVarInt());
    profession = VILLAGER_PROFESSION_REGISTRY.GetValue(version, buffer->ReadVarInt());
    level = buffer->ReadVarInt();
  }

  uint32_t VillagerDataMetadataEntry::Size(const ProtocolVersion* version) const {
    return ByteBuffer::VarIntBytes(VILLAGER_TYPE_REGISTRY.GetID(version, type))
         + ByteBuffer::VarIntBytes(VILLAGER_PROFESSION_REGISTRY.GetID(version, profession)) + ByteBuffer::VarIntBytes(level);
  }

  MetadataEntryType VillagerDataMetadataEntry::GetType() const {
    return MetadataEntryType::VILLAGER_DATA;
  }

  uint32_t VillagerDataMetadataEntry::GetOrdinal() const {
    return ORDINAL;
  }

  VillagerType VillagerDataMetadataEntry::GetVillagerType() const {
    return type;
  }

  void VillagerDataMetadataEntry::SetVillagerType(VillagerType newValue) {
    type = newValue;
  }

  VillagerProfession VillagerDataMetadataEntry::GetProfession() const {
    return profession;
  }

  void VillagerDataMetadataEntry::SetProfession(VillagerProfession newValue) {
    profession = newValue;
  }

  uint32_t VillagerDataMetadataEntry::GetLevel() const {
    return level;
  }

  void VillagerDataMetadataEntry::SetLevel(uint32_t newValue) {
    level = newValue;
  }
}