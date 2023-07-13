#include "Metadata.hpp"

namespace Ship {

  CatVariantMetadataEntry::CatVariantMetadataEntry(const CatVariant& value) : value(value) {
  }

  Errorable<bool> CatVariantMetadataEntry::Write(const ProtocolVersion* version, ByteBuffer* buffer) const {
    ProceedErrorable(id, uint32_t, CAT_VARIANT_REGISTRY.GetID(version, value), InvalidSerializableWriteErrorable(buffer->GetReadableBytes()))
    buffer->WriteVarInt(id);
    return SuccessErrorable<bool>(true);
  }

  Errorable<CatVariantMetadataEntry> CatVariantMetadataEntry::Instantiate(const ProtocolVersion* version, ByteBuffer* buffer) {
    ProceedErrorable(id, uint32_t, buffer->ReadVarInt(), InvalidCatVariantMetadataEntryErrorable(buffer->GetReadableBytes()))
    ProceedErrorable(value, CatVariant, CAT_VARIANT_REGISTRY.GetValue(version, id), InvalidCatVariantMetadataEntryErrorable(buffer->GetReadableBytes()))
    return SuccessErrorable<CatVariantMetadataEntry>(CatVariantMetadataEntry(value));
  }

  MetadataEntryType CatVariantMetadataEntry::GetType() const {
    return MetadataEntryType::CAT_VARIANT;
  }

  uint32_t CatVariantMetadataEntry::GetOrdinal() const {
    return ORDINAL;
  }

  CatVariant CatVariantMetadataEntry::GetValue() const {
    return value;
  }

  void CatVariantMetadataEntry::SetValue(const CatVariant& newValue) {
    value = newValue;
  }
}