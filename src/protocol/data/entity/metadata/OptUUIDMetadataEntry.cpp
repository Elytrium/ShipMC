#include "Metadata.hpp"

namespace Ship {

  OptUUIDMetadataEntry::OptUUIDMetadataEntry() = default;

  OptUUIDMetadataEntry::OptUUIDMetadataEntry(const std::optional<UUID>& optValue) : optValue(optValue) {
  }

  Errorable<bool> OptUUIDMetadataEntry::Write(const ProtocolVersion* version, ByteBuffer* buffer) const {
    buffer->WriteBoolean(optValue.has_value());
    if (optValue) {
      buffer->WriteUUID(optValue.value());
    }
    return SuccessErrorable<bool>(true);
  }

  Errorable<OptUUIDMetadataEntry> OptUUIDMetadataEntry::Instantiate(const ProtocolVersion* version, ByteBuffer* buffer) {
    ProceedErrorable(present, bool, buffer->ReadBoolean(), InvalidOptUUIDMetadataEntryErrorable(buffer->GetReadableBytes()))
    if (present) {
      ProceedErrorable(value, UUID, buffer->ReadUUID(), InvalidOptUUIDMetadataEntryErrorable(buffer->GetReadableBytes()))
      return SuccessErrorable<OptUUIDMetadataEntry>(OptUUIDMetadataEntry(value));
    } else {
      return SuccessErrorable<OptUUIDMetadataEntry>({});
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