#include "Metadata.hpp"

namespace Ship {

  BooleanMetadataEntry::BooleanMetadataEntry(bool value) : value(value) {
  }

  void BooleanMetadataEntry::Write(const ProtocolVersion* version, ByteBuffer* buffer) {
    buffer->WriteBoolean(value);
  }

  void BooleanMetadataEntry::Read(const ProtocolVersion* version, ByteBuffer* buffer) {
    value = buffer->ReadBoolean();
  }

  uint32_t BooleanMetadataEntry::Size(const ProtocolVersion* version) const {
    return ByteBuffer::BOOLEAN_SIZE;
  }

  MetadataEntryType BooleanMetadataEntry::GetType() const {
    return MetadataEntryType::BOOLEAN;
  }

  uint32_t BooleanMetadataEntry::GetOrdinal() const {
    return ORDINAL;
  }

  bool BooleanMetadataEntry::GetValue() const {
    return value;
  }

  void BooleanMetadataEntry::SetValue(bool newValue) {
    value = newValue;
  }
}