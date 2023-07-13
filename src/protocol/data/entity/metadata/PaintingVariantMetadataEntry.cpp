#include "Metadata.hpp"

namespace Ship {

  PaintingVariantMetadataEntry::PaintingVariantMetadataEntry(const PaintingVariant& value) : value(value) {
  }

  Errorable<bool> PaintingVariantMetadataEntry::Write(const ProtocolVersion* version, ByteBuffer* buffer) const {
    ProceedErrorable(id, uint32_t, PAINTING_VARIANT_REGISTRY.GetID(version, value), InvalidSerializableWriteErrorable(buffer->GetReadableBytes()))
    buffer->WriteVarInt(id);
    return SuccessErrorable<bool>(true);
  }

  Errorable<PaintingVariantMetadataEntry> PaintingVariantMetadataEntry::Instantiate(const ProtocolVersion* version, ByteBuffer* buffer) {
    ProceedErrorable(id, uint32_t, buffer->ReadVarInt(), InvalidPaintingVariantMetadataEntryErrorable(buffer->GetReadableBytes()))
    ProceedErrorable(value, PaintingVariant, PAINTING_VARIANT_REGISTRY.GetValue(version, id), InvalidPaintingVariantMetadataEntryErrorable(buffer->GetReadableBytes()))
    return SuccessErrorable<PaintingVariantMetadataEntry>(PaintingVariantMetadataEntry(value));
  }

  MetadataEntryType PaintingVariantMetadataEntry::GetType() const {
    return MetadataEntryType::FROG_VARIANT;
  }

  uint32_t PaintingVariantMetadataEntry::GetOrdinal() const {
    return ORDINAL;
  }

  PaintingVariant PaintingVariantMetadataEntry::GetValue() const {
    return value;
  }

  void PaintingVariantMetadataEntry::SetValue(const PaintingVariant& newValue) {
    value = newValue;
  }
}