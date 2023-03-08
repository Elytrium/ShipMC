#include "Metadata.hpp"

namespace Ship {

  ByteMetadataEntry::ByteMetadataEntry(uint8_t value) : value(value) {
  }

  void ByteMetadataEntry::Write(const ProtocolVersion* version, ByteBuffer* buffer) const {
    buffer->WriteByte(value);
  }

  ByteMetadataEntry::ByteMetadataEntry(const ProtocolVersion* version, ByteBuffer* buffer) {
    value = buffer->ReadByte();
  }

  MetadataEntryType ByteMetadataEntry::GetType() const {
    return MetadataEntryType::BYTE;
  }

  uint32_t ByteMetadataEntry::GetOrdinal() const {
    return ORDINAL;
  }

  uint8_t ByteMetadataEntry::GetValue() const {
    return value;
  }

  void ByteMetadataEntry::SetValue(uint8_t newValue) {
    value = newValue;
  }
}