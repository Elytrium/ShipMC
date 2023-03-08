#include "Metadata.hpp"

namespace Ship {

  PositionMetadataEntry::PositionMetadataEntry(int x, int y, int z) : x(x), y(y), z(z) {
  }

  void PositionMetadataEntry::Write(const ProtocolVersion* version, ByteBuffer* buffer) const {
    buffer->WritePosition(x, y, z);
  }

  PositionMetadataEntry::PositionMetadataEntry(const ProtocolVersion* version, ByteBuffer* buffer) {
    buffer->ReadPosition(x, y, z);
  }

  MetadataEntryType PositionMetadataEntry::GetType() const {
    return MetadataEntryType::POSITION;
  }

  uint32_t PositionMetadataEntry::GetOrdinal() const {
    return ORDINAL;
  }

  int PositionMetadataEntry::GetX() const {
    return x;
  }

  void PositionMetadataEntry::SetX(int value) {
    x = value;
  }

  int PositionMetadataEntry::GetY() const {
    return y;
  }

  void PositionMetadataEntry::SetY(int value) {
    y = value;
  }

  int PositionMetadataEntry::GetZ() const {
    return z;
  }

  void PositionMetadataEntry::SetZ(int value) {
    z = value;
  }

  void PositionMetadataEntry::Get(int& outX, int& outY, int& outZ) const {
    outX = x;
    outY = y;
    outZ = z;
  }

  void PositionMetadataEntry::Set(int newX, int newY, int newZ) {
    x = newX;
    y = newY;
    z = newZ;
  }
}