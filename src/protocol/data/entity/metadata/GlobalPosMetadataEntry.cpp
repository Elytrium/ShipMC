#include "../../../ProtocolUtils.hpp"
#include "Metadata.hpp"
#include <utility>

namespace Ship {

  GlobalPosMetadataEntry::GlobalPosMetadataEntry(GlobalPos value) : value(std::move(value)) {
  }

  Errorable<bool> GlobalPosMetadataEntry::Write(const ProtocolVersion* version, ByteBuffer* buffer) const {
    ProtocolUtils::WriteGlobalPos(version, buffer, value);
    return SuccessErrorable<bool>(true);
  }

  Errorable<GlobalPosMetadataEntry> GlobalPosMetadataEntry::Instantiate(const ProtocolVersion* version, ByteBuffer* buffer) {
    ProceedErrorable(value, GlobalPos, ProtocolUtils::ReadGlobalPos(version, buffer), InvalidGlobalPosMetadataEntryErrorable(buffer->GetReadableBytes()))
    return SuccessErrorable<GlobalPosMetadataEntry>(GlobalPosMetadataEntry(value));
  }

  MetadataEntryType GlobalPosMetadataEntry::GetType() const {
    return MetadataEntryType::GLOBAL_POS;
  }

  uint32_t GlobalPosMetadataEntry::GetOrdinal() const {
    return ORDINAL;
  }

  GlobalPos GlobalPosMetadataEntry::GetValue() const {
    return value;
  }

  void GlobalPosMetadataEntry::SetValue(GlobalPos newValue) {
    value = std::move(newValue);
  }
}