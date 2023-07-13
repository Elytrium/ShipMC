#include "Metadata.hpp"

namespace Ship {

  LongMetadataEntry::LongMetadataEntry(uint64_t value) : value(value) {
  }

  Errorable<bool> LongMetadataEntry::Write(const ProtocolVersion* version, ByteBuffer* buffer) const {
    buffer->WriteLong(value);
    return SuccessErrorable<bool>(true);
  }

  Errorable<LongMetadataEntry> LongMetadataEntry::Instantiate(const ProtocolVersion* version, ByteBuffer* buffer) {
    ProceedErrorable(value, uint64_t, buffer->ReadLong(), InvalidLongMetadataEntryErrorable(buffer->GetReadableBytes()))
    return SuccessErrorable<LongMetadataEntry>(LongMetadataEntry(value));
  }

  MetadataEntryType LongMetadataEntry::GetType() const {
    return MetadataEntryType::LONG;
  }

  uint32_t LongMetadataEntry::GetOrdinal() const {
    return ORDINAL;
  }

  uint64_t LongMetadataEntry::GetValue() const {
    return value;
  }

  void LongMetadataEntry::SetValue(uint64_t newValue) {
    value = newValue;
  }
}