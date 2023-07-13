#include "../../../ProtocolUtils.hpp"
#include "Metadata.hpp"

namespace Ship {

  PositionMetadataEntry::PositionMetadataEntry(Position position) : position(position) {
  }

  Errorable<bool> PositionMetadataEntry::Write(const ProtocolVersion* version, ByteBuffer* buffer) const {
    ProtocolUtils::WritePosition(version, buffer, position);
    return SuccessErrorable<bool>(true);
  }

  Errorable<PositionMetadataEntry> PositionMetadataEntry::Instantiate(const ProtocolVersion* version, ByteBuffer* buffer) {
    ProceedErrorable(position, Position, ProtocolUtils::ReadPosition(version, buffer), InvalidPositionMetadataEntryErrorable(buffer->GetReadableBytes()))
    return SuccessErrorable<PositionMetadataEntry>(PositionMetadataEntry(position));
  }

  MetadataEntryType PositionMetadataEntry::GetType() const {
    return MetadataEntryType::POSITION;
  }

  uint32_t PositionMetadataEntry::GetOrdinal() const {
    return ORDINAL;
  }

  Position PositionMetadataEntry::GetPosition() const {
    return position;
  }

  void PositionMetadataEntry::SetPosition(Position value) {
    position = value;
  }

  void PositionMetadataEntry::Get(Position& out) const {
    out = position;
  }

  void PositionMetadataEntry::Set(Position newPosition) {
    position = newPosition;
  }
}