#include "Metadata.hpp"

namespace Ship {

  OptPositionMetadataEntry::OptPositionMetadataEntry() : present(false), position() {
  }

  OptPositionMetadataEntry::OptPositionMetadataEntry(Position position) : present(true), position(position) {
  }

  void OptPositionMetadataEntry::Write(const ProtocolVersion* version, ByteBuffer* buffer) const {
    buffer->WriteBoolean(present);
    if (present) {
      buffer->WritePosition(position);
    }
  }

  OptPositionMetadataEntry::OptPositionMetadataEntry(const ProtocolVersion* version, ByteBuffer* buffer) {
    ProceedErrorable(present, bool, buffer->ReadBoolean(), InvalidPacketErrorable<>(PACKET_ORDINAL))
    if (present) {
      position = buffer->ReadPosition();
    } else {
      position = Position();
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

  void OptPositionMetadataEntry::Get(bool& outPresent, Position& out) const {
    outPresent = present;
    out = position;
  }

  void OptPositionMetadataEntry::Set(Position value) {
    present = true;
    position = value;
  }

  void OptPositionMetadataEntry::Reset() {
    present = false;
    position = Position();
  }
}