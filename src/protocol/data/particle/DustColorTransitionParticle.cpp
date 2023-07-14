#include "Particle.hpp"

namespace Ship {

  DustColorTransitionParticle::DustColorTransitionParticle(
    float fromRed, float fromGreen, float fromBlue, float scale, float toRed, float toGreen, float toBlue)
    : fromRed(fromRed), fromGreen(fromGreen), fromBlue(fromBlue), scale(scale), toRed(toRed), toGreen(toGreen), toBlue(toBlue) {
  }

  Errorable<bool> DustColorTransitionParticle::Write(const ProtocolVersion* version, ByteBuffer* buffer) const {
    buffer->WriteFloat(fromRed);
    buffer->WriteFloat(fromGreen);
    buffer->WriteFloat(fromBlue);
    buffer->WriteFloat(scale);
    buffer->WriteFloat(toRed);
    buffer->WriteFloat(toGreen);
    buffer->WriteFloat(toBlue);
    return SuccessErrorable<bool>(true);
  }

  Errorable<DustColorTransitionParticle> DustColorTransitionParticle::Instantiate(const ProtocolVersion* version, ByteBuffer* buffer) {
    ProceedErrorable(fromRed, float, buffer->ReadFloat(), InvalidDustColorTransitionParticleErrorable(buffer->GetReadableBytes()))
    ProceedErrorable(fromGreen, float, buffer->ReadFloat(), InvalidDustColorTransitionParticleErrorable(buffer->GetReadableBytes()))
    ProceedErrorable(fromBlue, float, buffer->ReadFloat(), InvalidDustColorTransitionParticleErrorable(buffer->GetReadableBytes()))
    ProceedErrorable(scale, float, buffer->ReadFloat(), InvalidDustColorTransitionParticleErrorable(buffer->GetReadableBytes()))
    ProceedErrorable(toRed, float, buffer->ReadFloat(), InvalidDustColorTransitionParticleErrorable(buffer->GetReadableBytes()))
    ProceedErrorable(toGreen, float, buffer->ReadFloat(), InvalidDustColorTransitionParticleErrorable(buffer->GetReadableBytes()))
    ProceedErrorable(toBlue, float, buffer->ReadFloat(), InvalidDustColorTransitionParticleErrorable(buffer->GetReadableBytes()))
    return SuccessErrorable<DustColorTransitionParticle>(DustColorTransitionParticle(fromRed, fromGreen, fromBlue, scale, toRed, toGreen, toBlue));
  }

  std::string DustColorTransitionParticle::GetIdentifier() const {
    return "minecraft:dust_color_transition";
  }

  uint32_t DustColorTransitionParticle::GetOrdinal() const {
    return ORDINAL;
  }

  float DustColorTransitionParticle::GetFromRed() const {
    return fromRed;
  }

  void DustColorTransitionParticle::SetFromRed(float newValue) {
    fromRed = newValue;
  }

  float DustColorTransitionParticle::GetFromGreen() const {
    return fromGreen;
  }

  void DustColorTransitionParticle::SetFromGreen(float newValue) {
    fromGreen = newValue;
  }

  float DustColorTransitionParticle::GetFromBlue() const {
    return fromBlue;
  }

  void DustColorTransitionParticle::SetFromBlue(float newValue) {
    fromBlue = newValue;
  }

  float DustColorTransitionParticle::GetScale() const {
    return scale;
  }

  void DustColorTransitionParticle::SetScale(float newValue) {
    scale = newValue;
  }

  float DustColorTransitionParticle::GetToRed() const {
    return toRed;
  }
  void DustColorTransitionParticle::SetToRed(float newValue) {
    toRed = newValue;
  }

  float DustColorTransitionParticle::GetToGreen() const {
    return toGreen;
  }

  void DustColorTransitionParticle::SetToGreen(float newValue) {
    toGreen = newValue;
  }

  float DustColorTransitionParticle::GetToBlue() const {
    return toBlue;
  }

  void DustColorTransitionParticle::SetToBlue(float newValue) {
    toBlue = newValue;
  }
}