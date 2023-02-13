#include "../../../ProtocolUtils.hpp"
#include "Metadata.hpp"

namespace Ship {

  ParticleMetadataEntry::ParticleMetadataEntry(Ship::AbstractParticle* value) : value(value) {
  }

  ParticleMetadataEntry::~ParticleMetadataEntry() {
    delete value;
  }

  void ParticleMetadataEntry::Write(const ProtocolVersion* version, ByteBuffer* buffer) {
    if (value) {
      ProtocolUtils::WriteParticle(version, buffer, value);
    } else {
      buffer->WriteByte(0xFF);
    }
  }

  void ParticleMetadataEntry::Read(const ProtocolVersion* version, ByteBuffer* buffer) {
    delete value;
    value = ProtocolUtils::ReadParticle(version, buffer);
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