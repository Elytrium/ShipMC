#include "Metadata.hpp"
#include <utility>

namespace Ship {

  OptChatMetadataEntry::OptChatMetadataEntry() = default;

  OptChatMetadataEntry::OptChatMetadataEntry(std::optional<std::string> optValue) : optValue(std::move(optValue)) {
  }

  Errorable<bool> OptChatMetadataEntry::Write(const ProtocolVersion* version, ByteBuffer* buffer) const {
    buffer->WriteBoolean(optValue.has_value());
    if (optValue) {
      buffer->WriteString(optValue.value());
    }
    return SuccessErrorable<bool>(true);
  }

  Errorable<OptChatMetadataEntry> OptChatMetadataEntry::Instantiate(const ProtocolVersion* version, ByteBuffer* buffer) {
    ProceedErrorable(present, bool, buffer->ReadBoolean(), InvalidOptChatMetadataEntryErrorable(buffer->GetReadableBytes()))
    if (present) {
      ProceedErrorable(value, std::string, buffer->ReadString(), InvalidOptChatMetadataEntryErrorable(buffer->GetReadableBytes()))
      return SuccessErrorable<OptChatMetadataEntry>(OptChatMetadataEntry(value));
    } else {
      return SuccessErrorable<OptChatMetadataEntry>(OptChatMetadataEntry());
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