#include "Metadata.hpp"

namespace Ship {

  OptUUIDMetadataEntry::OptUUIDMetadataEntry() = default;

  OptUUIDMetadataEntry::OptUUIDMetadataEntry(const std::optional<UUID>& optValue) : optValue(optValue) {
  }

  void OptUUIDMetadataEntry::Write(const ProtocolVersion* version, ByteBuffer* buffer) {
    buffer->WriteBoolean(optValue.has_value());
    if (optValue) {
      buffer->WriteUUID(optValue.value());
    }
  }

  void OptUUIDMetadataEntry::Read(const ProtocolVersion* version, ByteBuffer* buffer) {
    if (buffer->ReadBoolean()) {
      optValue = buffer->ReadUUID();
    } else {
      optValue.reset();
    }
  }

  uint32_t OptUUIDMetadataEntry::Size(const ProtocolVersion* version) const {
    if (optValue) {
      return ByteBuffer::BOOLEAN_SIZE + ByteBuffer::UUID_SIZE;
    } else {
      return ByteBuffer::BOOLEAN_SIZE;
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