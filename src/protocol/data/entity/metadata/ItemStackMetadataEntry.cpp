#include "Metadata.hpp"

namespace Ship {

  ItemStackMetadataEntry::ItemStackMetadataEntry(const ItemStack& value) : value(value) {
  }

  void ItemStackMetadataEntry::Write(const ProtocolVersion* version, ByteBuffer* buffer) {
    value.Write(buffer);
  }

  void ItemStackMetadataEntry::Read(const ProtocolVersion* version, ByteBuffer* buffer) {
    value.Read(buffer);
  }

  uint32_t ItemStackMetadataEntry::Size(const ProtocolVersion* version) const {
    return value.Size();
  }

  MetadataEntryType ItemStackMetadataEntry::GetType() const {
    return MetadataEntryType::ITEM_STACK;
  }

  uint32_t ItemStackMetadataEntry::GetOrdinal() const {
    return ORDINAL;
  }

  ItemStack ItemStackMetadataEntry::GetValue() const {
    return value;
  }

  void ItemStackMetadataEntry::SetValue(const ItemStack& newValue) {
    value = newValue;
  }
}