#include "Metadata.hpp"

namespace Ship {

  FrogVariantMetadataEntry::FrogVariantMetadataEntry(const FrogVariant& value) : value(value) {
  }

  void FrogVariantMetadataEntry::Write(const ProtocolVersion* version, ByteBuffer* buffer) {
    buffer->WriteVarInt(FROG_VARIANT_REGISTRY.GetID(version, value));
  }

  void FrogVariantMetadataEntry::Read(const ProtocolVersion* version, ByteBuffer* buffer) {
    value = FROG_VARIANT_REGISTRY.GetValue(version, buffer->ReadVarInt());
  }

  uint32_t FrogVariantMetadataEntry::Size(const ProtocolVersion* version) const {
    return ByteBuffer::VarIntBytes(FROG_VARIANT_REGISTRY.GetID(version, value));
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