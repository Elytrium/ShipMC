#include "../../../ProtocolUtils.hpp"
#include "Metadata.hpp"

namespace Ship {

  OptPositionMetadataEntry::OptPositionMetadataEntry() : present(false), position() {
  }

  OptPositionMetadataEntry::OptPositionMetadataEntry(Position position) : present(true), position(position) {
  }

  Errorable<bool> OptPositionMetadataEntry::Write(const ProtocolVersion* version, ByteBuffer* buffer) const {
    buffer->WriteBoolean(present);
    if (present) {
    }
    return SuccessErrorable<bool>(true);
  }

  Errorable<OptPositionMetadataEntry> OptPositionMetadataEntry::Instantiate(const ProtocolVersion* version, ByteBuffer* buffer) {
    ProceedErrorable(present, bool, buffer->ReadBoolean(), InvalidOptPositionMetadataEntryErrorable(buffer->GetReadableBytes()))
    if (present) {
      ProceedErrorable(position, Position, ProtocolUtils::ReadPosition(version, buffer), InvalidOptPositionMetadataEntryErrorable(buffer->GetReadableBytes()))
      return SuccessErrorable<OptPositionMetadataEntry>(OptPositionMetadataEntry(position));
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

  bool OptPositionMetadataEntry::IsPresent() const {
    return present;
  }

  void OptPositionMetadataEntry::SetPresent(bool value) {
    present = value;
  }

  Position OptPositionMetadataEntry::GetPosition() const {
    return position;
  }

  void OptPositionMetadataEntry::SetPosition(Position value) {
    position = value;
  }

  void OptPositionMetadataEntry::Get(bool& outPresent, Position& out) const {
    outPresent = present;
    out = position;
  }

  void OptPositionMetadataEntry::Set(Position newPosition) {
    present = true;
    position = newPosition;
  }

  void OptPositionMetadataEntry::Reset() {
    present = false;
    position = {};
  }
}