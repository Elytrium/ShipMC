#include "Metadata.hpp"

namespace Ship {

  DirectionMetadataEntry::DirectionMetadataEntry(const Direction& value) : value(value) {
  }

  void DirectionMetadataEntry::Write(const ProtocolVersion* version, ByteBuffer* buffer) {
    buffer->WriteVarInt((uint32_t) value);
  }

  void DirectionMetadataEntry::Read(const ProtocolVersion* version, ByteBuffer* buffer) {
    value = (Direction) buffer->ReadVarInt();
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