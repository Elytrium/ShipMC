#include "Metadata.hpp"

namespace Ship {

  RotationMetadataEntry::RotationMetadataEntry(float x, float y, float z) : x(x), y(y), z(z) {
  }

  void RotationMetadataEntry::Write(const ProtocolVersion* version, ByteBuffer* buffer) {
    buffer->WriteFloat(x);
    buffer->WriteFloat(y);
    buffer->WriteFloat(z);
  }

  void RotationMetadataEntry::Read(const ProtocolVersion* version, ByteBuffer* buffer) {
    x = buffer->ReadFloat();
    y = buffer->ReadFloat();
    z = buffer->ReadFloat();
  }

  MetadataEntryType RotationMetadataEntry::GetType() const {
    return MetadataEntryType::ROTATION;
  }

  uint32_t RotationMetadataEntry::GetOrdinal() const {
    return ORDINAL;
  }

  float RotationMetadataEntry::GetX() const {
    return x;
  }

  void RotationMetadataEntry::SetX(float value) {
    x = value;
  }

  float RotationMetadataEntry::GetY() const {
    return y;
  }

  void RotationMetadataEntry::SetY(float value) {
    y = value;
  }

  float RotationMetadataEntry::GetZ() const {
    return z;
  }

  void RotationMetadataEntry::SetZ(float value) {
    z = value;
  }

  void RotationMetadataEntry::Get(float& outX, float& outY, float& outZ) const {
    outX = x;
    outY = y;
    outZ = z;
  }

  void RotationMetadataEntry::Set(float newX, float newY, float newZ) {
    x = newX;
    y = newY;
    z = newZ;
  }
}