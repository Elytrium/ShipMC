#include "Metadata.hpp"

namespace Ship {

  PoseMetadataEntry::PoseMetadataEntry(const Ship::Pose& value) : value(value) {
  }

  Errorable<bool> PoseMetadataEntry::Write(const ProtocolVersion* version, ByteBuffer* buffer) const {
    buffer->WriteVarInt((uint32_t) value);
    return SuccessErrorable<bool>(true);
  }

  Errorable<PoseMetadataEntry> PoseMetadataEntry::Instantiate(const ProtocolVersion* version, ByteBuffer* buffer) {
    value = (Pose) buffer->ReadVarInt();
  }

  MetadataEntryType PoseMetadataEntry::GetType() const {
    return MetadataEntryType::POSE;
  }

  uint32_t PoseMetadataEntry::GetOrdinal() const {
    return ORDINAL;
  }

  Pose PoseMetadataEntry::GetValue() const {
    return value;
  }

  void PoseMetadataEntry::SetValue(const Pose& newValue) {
    value = newValue;
  }
}