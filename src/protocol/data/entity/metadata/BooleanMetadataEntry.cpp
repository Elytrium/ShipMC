#include "Metadata.hpp"

namespace Ship {

  BooleanMetadataEntry::BooleanMetadataEntry(bool value) : value(value) {
  }

  Errorable<BooleanMetadataEntry> BooleanMetadataEntry::Instantiate(const ProtocolVersion* version, ByteBuffer* buffer) {
    ProceedErrorable(value, bool, buffer->ReadBoolean(), InvalidBooleanMetadataEntryErrorable(buffer->GetReadableBytes()))
    return SuccessErrorable<BooleanMetadataEntry>(BooleanMetadataEntry(value));
  }

  Errorable<bool> BooleanMetadataEntry::Write(const ProtocolVersion* version, ByteBuffer* buffer) const {
    buffer->WriteBoolean(value);
    return SuccessErrorable<bool>(true);
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