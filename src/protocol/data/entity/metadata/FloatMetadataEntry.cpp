#include "Metadata.hpp"

namespace Ship {

  FloatMetadataEntry::FloatMetadataEntry(float value) : value(value) {
  }

  void FloatMetadataEntry::Write(const ProtocolVersion* version, ByteBuffer* buffer) {
    buffer->WriteFloat(value);
  }

  void FloatMetadataEntry::Read(const ProtocolVersion* version, ByteBuffer* buffer) {
    value = buffer->ReadFloat();
  }

  uint32_t FloatMetadataEntry::Size(const ProtocolVersion* version) const {
    return ByteBuffer::FLOAT_SIZE;
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