#include "../../../ProtocolUtils.hpp"
#include "Metadata.hpp"

namespace Ship {

  OptPositionMetadataEntry::OptPositionMetadataEntry() : optValue(std::nullopt) {
  }

  OptPositionMetadataEntry::OptPositionMetadataEntry(Position position) : optValue(position) {
  }

  Errorable<bool> OptPositionMetadataEntry::Write(const ProtocolVersion* version, ByteBuffer* buffer) const {
    buffer->WriteBoolean(optValue.has_value());
    if (optValue.has_value()) {
      ProtocolUtils::WritePosition(version, buffer, optValue.value());
    }
    return SuccessErrorable<bool>(true);
  }

  Errorable<OptPositionMetadataEntry> OptPositionMetadataEntry::Instantiate(const ProtocolVersion* version, ByteBuffer* buffer) {
    ProceedErrorable(present, bool, buffer->ReadBoolean(), InvalidOptPositionMetadataEntryErrorable(buffer->GetReadableBytes()))
    if (present) {
      ProceedErrorable(optValue, Position, ProtocolUtils::ReadPosition(version, buffer), InvalidOptPositionMetadataEntryErrorable(buffer->GetReadableBytes()))
      return SuccessErrorable<OptPositionMetadataEntry>(OptPositionMetadataEntry(optValue));
    } else {
      return SuccessErrorable<OptPositionMetadataEntry>({});
    }
  }

  MetadataEntryType OptPositionMetadataEntry::GetType() const {
    return MetadataEntryType::OPT_POSITION;
  }

  uint32_t OptPositionMetadataEntry::GetOrdinal() const {
    return ORDINAL;
  }

  std::optional<Position> OptPositionMetadataEntry::GetValue() const {
    return optValue;
  }

  void OptPositionMetadataEntry::SetValue(const std::optional<Position>& value) {
    optValue = value;
  }

  void OptPositionMetadataEntry::Reset() {
    optValue = std::nullopt;
  }
}