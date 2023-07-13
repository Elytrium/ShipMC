#include "Metadata.hpp"

namespace Ship {

  ByteMetadataEntry::ByteMetadataEntry(uint8_t value) : value(value) {
  }

  Errorable<bool> ByteMetadataEntry::Write(const ProtocolVersion* version, ByteBuffer* buffer) const {
    buffer->WriteByte(value);
    return SuccessErrorable<bool>(true);
  }

  Errorable<ByteMetadataEntry> ByteMetadataEntry::Instantiate(const ProtocolVersion* version, ByteBuffer* buffer) {
    ProceedErrorable(value, uint8_t, buffer->ReadByte(), InvalidByteMetadataEntryErrorable(buffer->GetReadableBytes()))
    return SuccessErrorable<ByteMetadataEntry>(ByteMetadataEntry(value));
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