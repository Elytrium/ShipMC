#include "Metadata.hpp"

namespace Ship {

  ByteMetadataEntry::ByteMetadataEntry(uint8_t value) : value(value) {
  }

  void ByteMetadataEntry::Write(const ProtocolVersion* version, ByteBuffer* buffer) {
    buffer->WriteByte(value);
  }

  void ByteMetadataEntry::Read(const ProtocolVersion* version, ByteBuffer* buffer) {
    value = buffer->ReadByte();
  }

  uint32_t ByteMetadataEntry::Size(const ProtocolVersion* version) const {
    return ByteBuffer::BYTE_SIZE;
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