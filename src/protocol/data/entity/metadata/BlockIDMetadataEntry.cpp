#include "Metadata.hpp"

namespace Ship {

  BlockIDMetadataEntry::BlockIDMetadataEntry() : value(0) {
  }

  BlockIDMetadataEntry::BlockIDMetadataEntry(uint32_t value) : value(value) {
  }

  void BlockIDMetadataEntry::Write(const ProtocolVersion* version, ByteBuffer* buffer) {
    buffer->WriteVarInt(value);
  }

  void BlockIDMetadataEntry::Read(const ProtocolVersion* version, ByteBuffer* buffer) {
    value = buffer->ReadVarInt();
  }

  MetadataEntryType BlockIDMetadataEntry::GetType() const {
    return MetadataEntryType::BLOCK_ID;
  }

  uint32_t BlockIDMetadataEntry::GetOrdinal() const {
    return ORDINAL;
  }

  uint32_t BlockIDMetadataEntry::GetValue() const {
    return value;
  }

  void BlockIDMetadataEntry::SetValue(uint32_t newValue) {
    value = newValue;
  }
}