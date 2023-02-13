#include "Metadata.hpp"

namespace Ship {

  VarIntMetadataEntry::VarIntMetadataEntry(uint32_t value) : value(value) {
  }

  void VarIntMetadataEntry::Write(const ProtocolVersion* version, ByteBuffer* buffer) {
    buffer->WriteVarInt(value);
  }

  void VarIntMetadataEntry::Read(const ProtocolVersion* version, ByteBuffer* buffer) {
    value = buffer->ReadVarInt();
  }

  MetadataEntryType VarIntMetadataEntry::GetType() const {
    return MetadataEntryType::VARINT;
  }

  uint32_t VarIntMetadataEntry::GetOrdinal() const {
    return ORDINAL;
  }

  uint32_t VarIntMetadataEntry::GetValue() const {
    return value;
  }

  void VarIntMetadataEntry::SetValue(uint32_t newValue) {
    value = newValue;
  }
}