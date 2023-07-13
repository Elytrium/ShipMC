#include "Metadata.hpp"

namespace Ship {

  BlockIDMetadataEntry::BlockIDMetadataEntry(uint32_t value) : value(value) {
  }

  Errorable<BlockIDMetadataEntry> BlockIDMetadataEntry::Instantiate(const ProtocolVersion* version, ByteBuffer* buffer) {
    ProceedErrorable(value, uint32_t, buffer->ReadVarInt(), InvalidBlockIDMetadataEntryErrorableErrorable(buffer->GetReadableBytes()))
    return SuccessErrorable<BlockIDMetadataEntry>(BlockIDMetadataEntry(value));
  }

  Errorable<bool> BlockIDMetadataEntry::Write(const ProtocolVersion* version, ByteBuffer* buffer) const {
    buffer->WriteVarInt(value);
    return SuccessErrorable<bool>(true);
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