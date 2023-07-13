#include "Metadata.hpp"

namespace Ship {

  FrogVariantMetadataEntry::FrogVariantMetadataEntry(const FrogVariant& value) : value(value) {
  }

  Errorable<bool> FrogVariantMetadataEntry::Write(const ProtocolVersion* version, ByteBuffer* buffer) const {
    ProceedErrorable(id, uint32_t, FROG_VARIANT_REGISTRY.GetID(version, value), InvalidSerializableWriteErrorable(buffer->GetReadableBytes()))
    buffer->WriteVarInt(id);
    return SuccessErrorable<bool>(true);
  }

  Errorable<FrogVariantMetadataEntry> FrogVariantMetadataEntry::Instantiate(const ProtocolVersion* version, ByteBuffer* buffer) {
    ProceedErrorable(id, uint32_t, buffer->ReadVarInt(), InvalidFrogVariantMetadataEntryErrorable(buffer->GetReadableBytes()))
    ProceedErrorable(value, FrogVariant, FROG_VARIANT_REGISTRY.GetValue(version, id), InvalidFrogVariantMetadataEntryErrorable(buffer->GetReadableBytes()))
    return SuccessErrorable<FrogVariantMetadataEntry>(FrogVariantMetadataEntry(value));
  }

  MetadataEntryType FrogVariantMetadataEntry::GetType() const {
    return MetadataEntryType::FROG_VARIANT;
  }

  uint32_t FrogVariantMetadataEntry::GetOrdinal() const {
    return ORDINAL;
  }

  FrogVariant FrogVariantMetadataEntry::GetValue() const {
    return value;
  }

  void FrogVariantMetadataEntry::SetValue(const FrogVariant& newValue) {
    value = newValue;
  }
}