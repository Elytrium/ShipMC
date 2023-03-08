#include "Metadata.hpp"
#include <utility>

namespace Ship {

  StringMetadataEntry::StringMetadataEntry(std::string value) : value(std::move(value)) {
  }

  void StringMetadataEntry::Write(const ProtocolVersion* version, ByteBuffer* buffer) const {
    buffer->WriteString(value);
  }

  StringMetadataEntry::StringMetadataEntry(const ProtocolVersion* version, ByteBuffer* buffer) {
    value = buffer->ReadString();
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