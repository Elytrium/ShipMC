#include "Particle.hpp"

namespace Ship {

  DustParticle::DustParticle(float red, float green, float blue, float scale) : red(red), green(green), blue(blue), scale(scale) {
  }

  Errorable<bool> DustParticle::Write(const ProtocolVersion* version, ByteBuffer* buffer) const {
    buffer->WriteFloat(red);
    buffer->WriteFloat(green);
    buffer->WriteFloat(blue);
    buffer->WriteFloat(scale);
    return SuccessErrorable<bool>(true);
  }

  Errorable<DustParticle> DustParticle::Instantiate(const ProtocolVersion* version, ByteBuffer* buffer) {
    ProceedErrorable(red, float, buffer->ReadFloat(), InvalidDustParticleErrorable(buffer->GetReadableBytes()))
    ProceedErrorable(green, float, buffer->ReadFloat(), InvalidDustParticleErrorable(buffer->GetReadableBytes()))
    ProceedErrorable(blue, float, buffer->ReadFloat(), InvalidDustParticleErrorable(buffer->GetReadableBytes()))
    ProceedErrorable(scale, float, buffer->ReadFloat(), InvalidDustParticleErrorable(buffer->GetReadableBytes()))
    return SuccessErrorable<DustParticle>(DustParticle(red, green, blue, scale));
  }

  std::string DustParticle::GetIdentifier() const {
    return "minecraft:dust";
  }

  uint32_t DustParticle::GetOrdinal() const {
    return ORDINAL;
  }

  float DustParticle::GetRed() const {
    return red;
  }

  void DustParticle::SetRed(float newValue) {
    red = newValue;
  }

  float DustParticle::GetGreen() const {
    return green;
  }

  void DustParticle::SetGreen(float newValue) {
    green = newValue;
  }

  float DustParticle::GetBlue() const {
    return blue;
  }

  void DustParticle::SetBlue(float newValue) {
    blue = newValue;
  }

  float DustParticle::GetScale() const {
    return scale;
  }

  void DustParticle::SetScale(float newValue) {
    scale = newValue;
  }
}