#include "Metadata.hpp"

namespace Ship {

  DirectionMetadataEntry::DirectionMetadataEntry(const Direction& value) : value(value) {
  }

  DirectionMetadataEntry::DirectionMetadataEntry(const ProtocolVersion* version, ByteBuffer* buffer) {
    value = (Direction) buffer->ReadVarInt();
  }

  void DirectionMetadataEntry::Write(const ProtocolVersion* version, ByteBuffer* buffer) const {
    buffer->WriteVarInt((uint32_t) value);
  }

  MetadataEntryType DirectionMetadataEntry::GetType() const {
    return MetadataEntryType::DIRECTION;
  }

  uint32_t DirectionMetadataEntry::GetOrdinal() const {
    return ORDINAL;
  }

  Direction DirectionMetadataEntry::GetValue() const {
    return value;
  }

  void DirectionMetadataEntry::SetValue(const Direction& newValue) {
    value = newValue;
  }
}