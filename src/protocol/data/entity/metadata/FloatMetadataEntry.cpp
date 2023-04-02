#include "Metadata.hpp"

namespace Ship {

  FloatMetadataEntry::FloatMetadataEntry(float value) : value(value) {
  }

  void FloatMetadataEntry::Write(const ProtocolVersion* version, ByteBuffer* buffer) const {
    buffer->WriteFloat(value);
  }

  FloatMetadataEntry::FloatMetadataEntry(const ProtocolVersion* version, ByteBuffer* buffer) {
    ProceedErrorable(value, float, buffer->ReadFloat(), InvalidPacketErrorable<>(PACKET_ORDINAL))
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