#include "NBT.hpp"

namespace Ship {
  DoubleTag::DoubleTag(const std::string& name) : NBT(name) {
  }

  DoubleTag::DoubleTag(const std::string& name, double value) : NBT(name), value(value) {
  }

  void DoubleTag::Read(ByteBuffer* buffer) {
    ProceedErrorable(value, double, buffer->ReadDouble(), InvalidPacketErrorable<>(PACKET_ORDINAL))
  }

  void DoubleTag::Write(ByteBuffer* buffer) {
    buffer->WriteDouble(value);
  }

  uint32_t DoubleTag::GetSize() {
    return sizeof(double);
  }

  TagType DoubleTag::GetType() {
    return TagType::DOUBLE;
  }

  double DoubleTag::GetValue() const {
    return value;
  }

  void DoubleTag::SetValue(double newValue) {
    value = newValue;
  }
}
