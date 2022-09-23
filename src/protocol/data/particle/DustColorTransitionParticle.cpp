#include "Particle.hpp"

namespace Ship {

  DustColorTransitionParticle::DustColorTransitionParticle(
    float fromRed, float fromGreen, float fromBlue, float scale, float toRed, float toGreen, float toBlue)
    : fromRed(fromRed), fromGreen(fromGreen), fromBlue(fromBlue), scale(scale), toRed(toRed), toGreen(toGreen), toBlue(toBlue) {
  }

  void DustColorTransitionParticle::Write(const ProtocolVersion* version, ByteBuffer* buffer) {
    buffer->WriteFloat(fromRed);
    buffer->WriteFloat(fromGreen);
    buffer->WriteFloat(fromBlue);
    buffer->WriteFloat(scale);
    buffer->WriteFloat(toRed);
    buffer->WriteFloat(toGreen);
    buffer->WriteFloat(toBlue);
  }

  void DustColorTransitionParticle::Read(const ProtocolVersion* version, ByteBuffer* buffer) {
    fromRed = buffer->ReadFloat();
    fromGreen = buffer->ReadFloat();
    fromBlue = buffer->ReadFloat();
    scale = buffer->ReadFloat();
    toRed = buffer->ReadFloat();
    toGreen = buffer->ReadFloat();
    toBlue = buffer->ReadFloat();
  }

  uint32_t DustColorTransitionParticle::Size(const ProtocolVersion* version) const {
    return ByteBuffer::FLOAT_SIZE * 7;
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