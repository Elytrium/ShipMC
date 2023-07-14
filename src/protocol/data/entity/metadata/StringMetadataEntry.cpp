#include "Metadata.hpp"
#include <utility>

namespace Ship {

  StringMetadataEntry::StringMetadataEntry(std::string value) : value(std::move(value)) {
  }

  Errorable<bool> StringMetadataEntry::Write(const ProtocolVersion* version, ByteBuffer* buffer) const {
    buffer->WriteString(value);
    return SuccessErrorable<bool>(true);
  }

  Errorable<StringMetadataEntry> StringMetadataEntry::Instantiate(const ProtocolVersion* version, ByteBuffer* buffer) {
    ProceedErrorable(value, std::string, buffer->ReadString(), InvalidStringMetadataEntryErrorable(buffer->GetReadableBytes()))
    return SuccessErrorable<StringMetadataEntry>(StringMetadataEntry(value));
  }

  MetadataEntryType StringMetadataEntry::GetType() const {
    return MetadataEntryType::STRING;
  }

  uint32_t StringMetadataEntry::GetOrdinal() const {
    return ORDINAL;
  }

  std::string StringMetadataEntry::GetValue() const {
    return value;
  }

  void StringMetadataEntry::SetValue(std::string newValue) {
    value = std::move(newValue);
  }
}