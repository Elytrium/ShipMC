#include "Metadata.hpp"

namespace Ship {

  OptPositionMetadataEntry::OptPositionMetadataEntry() : present(false), x(0), y(0), z(0) {
  }

  OptPositionMetadataEntry::OptPositionMetadataEntry(int x, int y, int z) : present(true), x(x), y(y), z(z) {
  }

  void OptPositionMetadataEntry::Write(const ProtocolVersion* version, ByteBuffer* buffer) const {
    buffer->WriteBoolean(present);
    if (present) {
      buffer->WritePosition(x, y, z);
    }
  }

  OptPositionMetadataEntry::OptPositionMetadataEntry(const ProtocolVersion* version, ByteBuffer* buffer) {
    present = buffer->ReadBoolean();
    if (present) {
      buffer->ReadPosition(x, y, z);
    } else {
      x = y = z = 0;
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

  int OptPositionMetadataEntry::GetX() const {
    return x;
  }

  void OptPositionMetadataEntry::SetX(int value) {
    x = value;
  }

  int OptPositionMetadataEntry::GetY() const {
    return y;
  }

  void OptPositionMetadataEntry::SetY(int value) {
    y = value;
  }

  int OptPositionMetadataEntry::GetZ() const {
    return z;
  }

  void OptPositionMetadataEntry::SetZ(int value) {
    z = value;
  }

  void OptPositionMetadataEntry::Get(bool& outPresent, int& outX, int& outY, int& outZ) const {
    outPresent = present;
    outX = x;
    outY = y;
    outZ = z;
  }

  void OptPositionMetadataEntry::Set(int newX, int newY, int newZ) {
    present = true;
    x = newX;
    y = newY;
    z = newZ;
  }

  void OptPositionMetadataEntry::Reset() {
    present = false;
    x = y = z = 0;
  }
}