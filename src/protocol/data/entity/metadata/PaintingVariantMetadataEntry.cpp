#include "Metadata.hpp"

namespace Ship {

  PaintingVariantMetadataEntry::PaintingVariantMetadataEntry(const PaintingVariant& value) : value(value) {
  }

  void PaintingVariantMetadataEntry::Write(const ProtocolVersion* version, ByteBuffer* buffer) {
    buffer->WriteVarInt(PAINTING_VARIANT_REGISTRY.GetID(version, value));
  }

  void PaintingVariantMetadataEntry::Read(const ProtocolVersion* version, ByteBuffer* buffer) {
    value = PAINTING_VARIANT_REGISTRY.GetValue(version, buffer->ReadVarInt());
  }

  uint32_t PaintingVariantMetadataEntry::Size(const ProtocolVersion* version) const {
    return ByteBuffer::VarIntBytes(PAINTING_VARIANT_REGISTRY.GetID(version, value));
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