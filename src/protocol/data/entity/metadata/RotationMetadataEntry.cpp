#include "../../../ProtocolUtils.hpp"
#include "Metadata.hpp"

namespace Ship {

  RotationMetadataEntry::RotationMetadataEntry(Rotation rotation) : value(rotation) {
  }

  Errorable<bool> RotationMetadataEntry::Write(const ProtocolVersion* version, ByteBuffer* buffer) const {
    ProtocolUtils::WriteRotation(version, buffer, value);
    return SuccessErrorable<bool>(true);
  }

  Errorable<RotationMetadataEntry> RotationMetadataEntry::Instantiate(const ProtocolVersion* version, ByteBuffer* buffer) {
    ProceedErrorable(value, Rotation, ProtocolUtils::ReadRotation(version, buffer), InvalidRotationMetadataEntryErrorable(buffer->GetReadableBytes()))
    return SuccessErrorable<RotationMetadataEntry>(RotationMetadataEntry(value));
  }

  MetadataEntryType RotationMetadataEntry::GetType() const {
    return MetadataEntryType::ROTATION;
  }

  uint32_t RotationMetadataEntry::GetOrdinal() const {
    return ORDINAL;
  }

  Rotation RotationMetadataEntry::GetValue() const {
    return value;
  }

  void RotationMetadataEntry::SetValue(Rotation newValue) {
    value = newValue;
  }
}