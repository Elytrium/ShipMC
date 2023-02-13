#include "Metadata.hpp"
#include <utility>

namespace Ship {

  OptChatMetadataEntry::OptChatMetadataEntry() = default;

  OptChatMetadataEntry::OptChatMetadataEntry(std::optional<std::string> optValue) : optValue(std::move(optValue)) {
  }

  void OptChatMetadataEntry::Write(const ProtocolVersion* version, ByteBuffer* buffer) {
    buffer->WriteBoolean(optValue.has_value());
    if (optValue) {
      buffer->WriteString(optValue.value());
    }
  }

  void OptChatMetadataEntry::Read(const ProtocolVersion* version, ByteBuffer* buffer) {
    if (buffer->ReadBoolean()) {
      optValue = buffer->ReadString();
    } else {
      optValue.reset();
    }
  }

  MetadataEntryType OptChatMetadataEntry::GetType() const {
    return MetadataEntryType::OPT_CHAT;
  }

  uint32_t OptChatMetadataEntry::GetOrdinal() const {
    return ORDINAL;
  }

  std::optional<std::string> OptChatMetadataEntry::GetValue() const {
    return optValue;
  }

  void OptChatMetadataEntry::SetValue(const std::optional<std::string>& newValue) {
    optValue = newValue;
  }
}