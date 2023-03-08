#include "Metadata.hpp"

namespace Ship {

  OptUUIDMetadataEntry::OptUUIDMetadataEntry() = default;

  OptUUIDMetadataEntry::OptUUIDMetadataEntry(const std::optional<UUID>& optValue) : optValue(optValue) {
  }

  void OptUUIDMetadataEntry::Write(const ProtocolVersion* version, ByteBuffer* buffer) const {
    buffer->WriteBoolean(optValue.has_value());
    if (optValue) {
      buffer->WriteUUID(optValue.value());
    }
  }

  OptUUIDMetadataEntry::OptUUIDMetadataEntry(const ProtocolVersion* version, ByteBuffer* buffer) {
    if (buffer->ReadBoolean()) {
      optValue = buffer->ReadUUID();
    } else {
      optValue.reset();
    }
  }

  MetadataEntryType OptUUIDMetadataEntry::GetType() const {
    return MetadataEntryType::OPT_UUID;
  }

  uint32_t OptUUIDMetadataEntry::GetOrdinal() const {
    return ORDINAL;
  }

  std::optional<UUID> OptUUIDMetadataEntry::GetValue() const {
    return optValue;
  }

  void OptUUIDMetadataEntry::SetValue(const std::optional<UUID>& newValue) {
    optValue = newValue;
  }
}