#include "Metadata.hpp"

namespace Ship {

  VarIntMetadataEntry::VarIntMetadataEntry(uint32_t value) : value(value) {
  }

  Errorable<bool> VarIntMetadataEntry::Write(const ProtocolVersion* version, ByteBuffer* buffer) const {
    buffer->WriteVarInt(value);
    return SuccessErrorable<bool>(true);
  }

  Errorable<VarIntMetadataEntry> VarIntMetadataEntry::Instantiate(const ProtocolVersion* version, ByteBuffer* buffer) {
    ProceedErrorable(value, uint32_t, buffer->ReadVarInt(), ss)
    return SuccessErrorable<VarIntMetadataEntry>(VarIntMetadataEntry(value));
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