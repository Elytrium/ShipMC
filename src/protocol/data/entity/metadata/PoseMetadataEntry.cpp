#include "Metadata.hpp"

namespace Ship {

  PoseMetadataEntry::PoseMetadataEntry(const Ship::Pose& value) : value(value) {
  }

  Errorable<bool> PoseMetadataEntry::Write(const ProtocolVersion* version, ByteBuffer* buffer) const {
    buffer->WriteVarInt((uint32_t) value);
    return SuccessErrorable<bool>(true);
  }

  Errorable<PoseMetadataEntry> PoseMetadataEntry::Instantiate(const ProtocolVersion* version, ByteBuffer* buffer) {
    ProceedErrorable(id, uint32_t, buffer->ReadVarInt(), InvalidPoseMetadataEntryErrorable(buffer->GetReadableBytes()))
    return SuccessErrorable<PoseMetadataEntry>(PoseMetadataEntry((Pose) id));
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