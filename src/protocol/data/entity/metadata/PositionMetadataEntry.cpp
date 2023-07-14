#include "../../../ProtocolUtils.hpp"
#include "Metadata.hpp"

namespace Ship {

  PositionMetadataEntry::PositionMetadataEntry(Position position) : value(position) {
  }

  Errorable<bool> PositionMetadataEntry::Write(const ProtocolVersion* version, ByteBuffer* buffer) const {
    ProtocolUtils::WritePosition(version, buffer, value);
    return SuccessErrorable<bool>(true);
  }

  Errorable<PositionMetadataEntry> PositionMetadataEntry::Instantiate(const ProtocolVersion* version, ByteBuffer* buffer) {
    ProceedErrorable(value, Position, ProtocolUtils::ReadPosition(version, buffer), InvalidPositionMetadataEntryErrorable(buffer->GetReadableBytes()))
    return SuccessErrorable<PositionMetadataEntry>(PositionMetadataEntry(value));
  }

  MetadataEntryType PositionMetadataEntry::GetType() const {
    return MetadataEntryType::POSITION;
  }

  uint32_t PositionMetadataEntry::GetOrdinal() const {
    return ORDINAL;
  }

  Position PositionMetadataEntry::GetValue() const {
    return value;
  }

  void PositionMetadataEntry::SetValue(Position newValue) {
    value = newValue;
  }
}