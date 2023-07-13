#include "Metadata.hpp"

namespace Ship {

  FloatMetadataEntry::FloatMetadataEntry(float value) : value(value) {
  }

  Errorable<bool> FloatMetadataEntry::Write(const ProtocolVersion* version, ByteBuffer* buffer) const {
    buffer->WriteFloat(value);
    return SuccessErrorable<bool>(true);
  }

  Errorable<FloatMetadataEntry> FloatMetadataEntry::Instantiate(const ProtocolVersion* version, ByteBuffer* buffer) {
    ProceedErrorable(value, float, buffer->ReadFloat(), InvalidFloatMetadataEntryErrorable(buffer->GetReadableBytes()))
    return SuccessErrorable<FloatMetadataEntry>(FloatMetadataEntry(value));
  }

  MetadataEntryType FloatMetadataEntry::GetType() const {
    return MetadataEntryType::FLOAT;
  }

  uint32_t FloatMetadataEntry::GetOrdinal() const {
    return ORDINAL;
  }

  float FloatMetadataEntry::GetValue() const {
    return value;
  }

  void FloatMetadataEntry::SetValue(float newValue) {
    value = newValue;
  }
}