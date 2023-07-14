#include "NBT.hpp"

namespace Ship {
  FloatTag::FloatTag(const std::string& name) : NBT(name) {
  }

  FloatTag::FloatTag(const std::string& name, float value) : NBT(name), value(value) {
  }

  Errorable<bool> FloatTag::Read(ByteBuffer* buffer) {
    SetFromErrorable(value, float, buffer->ReadFloat(), InvalidNBTTagErrorable(buffer->GetReadableBytes()))
    return SuccessErrorable<bool>(true);
  }

  void FloatTag::Write(ByteBuffer* buffer) {
    buffer->WriteFloat(value);
  }

  uint32_t FloatTag::GetSize() {
    return sizeof(float);
  }

  TagType FloatTag::GetType() {
    return TagType::FLOAT;
  }

  float FloatTag::GetValue() const {
    return value;
  }

  void FloatTag::SetValue(float newValue) {
    value = newValue;
  }
}