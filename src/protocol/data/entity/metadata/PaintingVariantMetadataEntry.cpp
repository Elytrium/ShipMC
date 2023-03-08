#include "Metadata.hpp"

namespace Ship {

  PaintingVariantMetadataEntry::PaintingVariantMetadataEntry(const PaintingVariant& value) : value(value) {
  }

  void PaintingVariantMetadataEntry::Write(const ProtocolVersion* version, ByteBuffer* buffer) const {
    buffer->WriteVarInt(PAINTING_VARIANT_REGISTRY.GetID(version, value));
  }

  PaintingVariantMetadataEntry::PaintingVariantMetadataEntry(const ProtocolVersion* version, ByteBuffer* buffer) {
    value = PAINTING_VARIANT_REGISTRY.GetValue(version, buffer->ReadVarInt());
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