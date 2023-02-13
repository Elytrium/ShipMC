#include "Metadata.hpp"

namespace Ship {

  ChatMetadataEntry::ChatMetadataEntry(std::string value) : value(std::move(value)) {
  }

  void ChatMetadataEntry::Write(const ProtocolVersion* version, ByteBuffer* buffer) {
    buffer->WriteString(value);
  }

  void ChatMetadataEntry::Read(const ProtocolVersion* version, ByteBuffer* buffer) {
    value = buffer->ReadString();
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