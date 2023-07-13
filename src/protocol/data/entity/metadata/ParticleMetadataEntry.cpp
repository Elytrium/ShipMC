#include "../../../ProtocolUtils.hpp"
#include "Metadata.hpp"

namespace Ship {

  ParticleMetadataEntry::ParticleMetadataEntry(Ship::AbstractParticle* value) : value(value) {
  }

  Errorable<ParticleMetadataEntry> ParticleMetadataEntry::Instantiate(const ProtocolVersion* version, ByteBuffer* buffer) {
    ProceedErrorable(value, AbstractParticle*, ProtocolUtils::ReadParticle(version, buffer), InvalidParticleMetadataEntryErrorable(buffer->GetReadableBytes()))
    return SuccessErrorable<ParticleMetadataEntry>(ParticleMetadataEntry(value));
  }

  ParticleMetadataEntry::~ParticleMetadataEntry() {
    delete value;
  }

  Errorable<bool> ParticleMetadataEntry::Write(const ProtocolVersion* version, ByteBuffer* buffer) const {
    if (value) {
      ProtocolUtils::WriteParticle(version, buffer, value);
    } else {
      buffer->WriteByte(0xFF);
    }
    return SuccessErrorable<bool>(true);
  }

  MetadataEntryType ParticleMetadataEntry::GetType() const {
    return MetadataEntryType::PARTICLE;
  }

  uint32_t ParticleMetadataEntry::GetOrdinal() const {
    return ORDINAL;
  }

  AbstractParticle* ParticleMetadataEntry::GetValue() const {
    return value;
  }

  void ParticleMetadataEntry::SetValue(AbstractParticle* newValue) {
    delete value;
    value = newValue;
  }
}