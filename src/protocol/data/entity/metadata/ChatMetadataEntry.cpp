#include "Metadata.hpp"

namespace Ship {

  ChatMetadataEntry::ChatMetadataEntry(std::string value) : value(std::move(value)) {
  }

  void ChatMetadataEntry::Write(const ProtocolVersion* version, ByteBuffer* buffer) const {
    buffer->WriteString(value);
  }

  ChatMetadataEntry::ChatMetadataEntry(const ProtocolVersion* version, ByteBuffer* buffer) {
    ProceedErrorable(value, std::string, buffer->ReadString(), InvalidPacketErrorable<>(PACKET_ORDINAL))
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