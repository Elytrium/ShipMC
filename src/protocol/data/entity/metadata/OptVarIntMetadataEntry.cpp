#include "Metadata.hpp"

namespace Ship {

  OptVarIntMetadataEntry::OptVarIntMetadataEntry() = default;

  OptVarIntMetadataEntry::OptVarIntMetadataEntry(const std::optional<uint32_t>& optValue) : optValue(optValue) {
  }

  void OptVarIntMetadataEntry::Write(const ProtocolVersion* version, ByteBuffer* buffer) const {
    buffer->WriteVarInt(optValue.value_or(-1) + 1);
  }

  OptVarIntMetadataEntry::OptVarIntMetadataEntry(const ProtocolVersion* version, ByteBuffer* buffer) {
    uint32_t value = buffer->ReadVarInt();
    if (value) {
      optValue = value - 1;
    } else {
      optValue.reset();
    }
  }

  MetadataEntryType OptVarIntMetadataEntry::GetType() const {
    return MetadataEntryType::OPT_VARINT;
  }

  uint32_t OptVarIntMetadataEntry::GetOrdinal() const {
    return ORDINAL;
  }

  std::optional<uint32_t> OptVarIntMetadataEntry::GetValue() const {
    return optValue;
  }

  void OptVarIntMetadataEntry::SetValue(const std::optional<uint32_t>& newValue) {
    optValue = newValue;
  }
}