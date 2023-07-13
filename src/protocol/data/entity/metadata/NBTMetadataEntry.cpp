#include "../../../ProtocolUtils.hpp"
#include "Metadata.hpp"

namespace Ship {

  NBTMetadataEntry::NBTMetadataEntry(NBT* value) : value(value) {
  }

  Errorable<NBTMetadataEntry> NBTMetadataEntry::Instantiate(const ProtocolVersion* version, ByteBuffer* buffer) {
    ProceedErrorable(value, NBT*, ProtocolUtils::ReadNBT(buffer), InvalidNBTMetadataEntryErrorable(buffer->GetReadableBytes()))
    return SuccessErrorable<NBTMetadataEntry>(NBTMetadataEntry(value));
  }

  NBTMetadataEntry::~NBTMetadataEntry() {
    delete value;
  }

  Errorable<bool> NBTMetadataEntry::Write(const ProtocolVersion* version, ByteBuffer* buffer) const {
    if (value) {
      ProtocolUtils::WriteNBT(buffer, value);
    } else {
      buffer->WriteByte(0);
    }
    return SuccessErrorable<bool>(true);
  }

  MetadataEntryType NBTMetadataEntry::GetType() const {
    return MetadataEntryType::NBT;
  }

  uint32_t NBTMetadataEntry::GetOrdinal() const {
    return ORDINAL;
  }

  NBT* NBTMetadataEntry::GetValue() const {
    return value;
  }

  void NBTMetadataEntry::SetValue(NBT* newValue) {
    delete value;
    value = newValue;
  }
}