#include "../../../ProtocolUtils.hpp"
#include "Metadata.hpp"
#include <utility>

namespace Ship {

  GlobalPosMetadataEntry::GlobalPosMetadataEntry(std::string dimension, Position position) : dimension(std::move(dimension)), position(position) {
  }

  Errorable<bool> GlobalPosMetadataEntry::Write(const ProtocolVersion* version, ByteBuffer* buffer) const {
    buffer->WriteString(dimension);
    ProtocolUtils::WritePosition(version, buffer, position);
    return SuccessErrorable<bool>(true);
  }

  Errorable<GlobalPosMetadataEntry> GlobalPosMetadataEntry::Instantiate(const ProtocolVersion* version, ByteBuffer* buffer) {
    ProceedErrorable(dimension, std::string, buffer->ReadString(), InvalidGlobalPosMetadataEntryErrorable(buffer->GetReadableBytes()))
    ProceedErrorable(position, Position, ProtocolUtils::ReadPosition(version, buffer), InvalidGlobalPosMetadataEntryErrorable(buffer->GetReadableBytes()))
    return SuccessErrorable<GlobalPosMetadataEntry>(GlobalPosMetadataEntry(dimension, position));
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

  void GlobalPosMetadataEntry::Get(std::string& outDimension, Position& outPosition) const {
    outDimension = dimension;
    outPosition = position;
  }

  void GlobalPosMetadataEntry::Set(const std::string& newDimension, Position newPosition) {
    dimension = newDimension;
    position = newPosition;
  }

  Position GlobalPosMetadataEntry::GetPosition() const {
    return position;
  }

  void GlobalPosMetadataEntry::SetPosition(Position value) {
    position = value;
  }
}