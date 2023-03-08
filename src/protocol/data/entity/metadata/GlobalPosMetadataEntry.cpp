#include "Metadata.hpp"
#include <utility>

namespace Ship {

  GlobalPosMetadataEntry::GlobalPosMetadataEntry(std::string dimension, int x, int y, int z) : dimension(std::move(dimension)), x(x), y(y), z(z) {
  }

  void GlobalPosMetadataEntry::Write(const ProtocolVersion* version, ByteBuffer* buffer) const {
    buffer->WriteString(dimension);
    buffer->WritePosition(x, y, z);
  }

  GlobalPosMetadataEntry::GlobalPosMetadataEntry(const ProtocolVersion* version, ByteBuffer* buffer) {
    dimension = buffer->ReadString();
    buffer->ReadPosition(x, y, z);
  }

  MetadataEntryType GlobalPosMetadataEntry::GetType() const {
    return MetadataEntryType::GLOBAL_POS;
  }

  uint32_t GlobalPosMetadataEntry::GetOrdinal() const {
    return ORDINAL;
  }

  std::string GlobalPosMetadataEntry::GetDimension() const {
    return dimension;
  }

  void GlobalPosMetadataEntry::SetDimension(const std::string& value) {
    dimension = value;
  }

  int GlobalPosMetadataEntry::GetX() const {
    return x;
  }

  void GlobalPosMetadataEntry::SetX(int value) {
    x = value;
  }

  int GlobalPosMetadataEntry::GetY() const {
    return y;
  }

  void GlobalPosMetadataEntry::SetY(int value) {
    y = value;
  }

  int GlobalPosMetadataEntry::GetZ() const {
    return z;
  }

  void GlobalPosMetadataEntry::SetZ(int value) {
    z = value;
  }

  void GlobalPosMetadataEntry::Get(std::string& outDimension, int& outX, int& outY, int& outZ) const {
    outDimension = dimension;
    outX = x;
    outY = y;
    outZ = z;
  }

  void GlobalPosMetadataEntry::Set(const std::string& newDimension, int newX, int newY, int newZ) {
    dimension = newDimension;
    x = newX;
    y = newY;
    z = newZ;
  }
}