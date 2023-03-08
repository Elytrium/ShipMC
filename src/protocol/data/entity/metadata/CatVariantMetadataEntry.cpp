#include "Metadata.hpp"

namespace Ship {

  CatVariantMetadataEntry::CatVariantMetadataEntry(const CatVariant& value) : value(value) {
  }

  void CatVariantMetadataEntry::Write(const ProtocolVersion* version, ByteBuffer* buffer) const {
    buffer->WriteVarInt(CAT_VARIANT_REGISTRY.GetID(version, value));
  }

  CatVariantMetadataEntry::CatVariantMetadataEntry(const ProtocolVersion* version, ByteBuffer* buffer) {
    value = CAT_VARIANT_REGISTRY.GetValue(version, buffer->ReadVarInt());
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