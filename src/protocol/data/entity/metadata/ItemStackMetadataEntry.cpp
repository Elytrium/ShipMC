#include "Metadata.hpp"

namespace Ship {

  ItemStackMetadataEntry::ItemStackMetadataEntry(const ItemStack& value) : value(value) {
  }

  Errorable<bool> ItemStackMetadataEntry::Write(const ProtocolVersion* version, ByteBuffer* buffer) const {
    value.Write(version, buffer);
    return SuccessErrorable<bool>(true);
  }

  Errorable<ItemStackMetadataEntry> ItemStackMetadataEntry::Instantiate(const ProtocolVersion* version, ByteBuffer* buffer) {
    ProceedErrorable(value, ItemStack, ItemStack::Instantiate(version, buffer), InvalidItemStackMetadataEntryErrorable(buffer->GetReadableBytes()))
    return SuccessErrorable<ItemStackMetadataEntry>(ItemStackMetadataEntry(value));
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