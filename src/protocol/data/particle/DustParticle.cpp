#include "Particle.hpp"

namespace Ship {

  DustParticle::DustParticle(float red, float green, float blue, float scale) : red(red), green(green), blue(blue), scale(scale) {
  }

  void DustParticle::Write(const ProtocolVersion* version, ByteBuffer* buffer) {
    buffer->WriteFloat(red);
    buffer->WriteFloat(green);
    buffer->WriteFloat(blue);
    buffer->WriteFloat(scale);
  }

  void DustParticle::Read(const ProtocolVersion* version, ByteBuffer* buffer) {
    red = buffer->ReadFloat();
    green = buffer->ReadFloat();
    blue = buffer->ReadFloat();
    scale = buffer->ReadFloat();
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