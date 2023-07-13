#include "Metadata.hpp"

namespace Ship {

  ChatMetadataEntry::ChatMetadataEntry(std::string value) : value(std::move(value)) {
  }

  Errorable<bool> ChatMetadataEntry::Write(const ProtocolVersion* version, ByteBuffer* buffer) const {
    buffer->WriteString(value);
    return SuccessErrorable<bool>(true);
  }

  Errorable<ChatMetadataEntry> ChatMetadataEntry::Instantiate(const ProtocolVersion* version, ByteBuffer* buffer) {
    ProceedErrorable(value, std::string, buffer->ReadString(), InvalidChatMetadataEntryErrorable(buffer->GetReadableBytes()))
    return SuccessErrorable<ChatMetadataEntry>(ChatMetadataEntry(value));
  }

  MetadataEntryType ChatMetadataEntry::GetType() const {
    return MetadataEntryType::CHAT;
  }

  uint32_t ChatMetadataEntry::GetOrdinal() const {
    return ORDINAL;
  }

  std::string ChatMetadataEntry::GetValue() const {
    return value;
  }

  void ChatMetadataEntry::SetValue(std::string newValue) {
    value = std::move(newValue);
  }
}