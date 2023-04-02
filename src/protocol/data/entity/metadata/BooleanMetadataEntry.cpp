#include "Metadata.hpp"

namespace Ship {

  BooleanMetadataEntry::BooleanMetadataEntry(bool value) : value(value) {
  }

  BooleanMetadataEntry::BooleanMetadataEntry(const ProtocolVersion* version, ByteBuffer* buffer) {
    ProceedErrorable(value, bool, buffer->ReadBoolean(), InvalidPacketErrorable<>(PACKET_ORDINAL))
  }

  void BooleanMetadataEntry::Write(const ProtocolVersion* version, ByteBuffer* buffer) const {
    buffer->WriteBoolean(value);
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