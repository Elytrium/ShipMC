#include "Metadata.hpp"

namespace Ship {

  DirectionMetadataEntry::DirectionMetadataEntry(const Direction& value) : value(value) {
  }

  Errorable<DirectionMetadataEntry> DirectionMetadataEntry::Instantiate(const ProtocolVersion* version, ByteBuffer* buffer) {
    ProceedErrorable(value, uint32_t, buffer->ReadVarInt(), InvalidDirectionMetadataEntryErrorable(buffer->GetReadableBytes()))
    return SuccessErrorable<DirectionMetadataEntry>(DirectionMetadataEntry((Direction) value));
  }

  Errorable<bool> DirectionMetadataEntry::Write(const ProtocolVersion* version, ByteBuffer* buffer) const {
    buffer->WriteVarInt((uint32_t) value);
    return SuccessErrorable<bool>(true);
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