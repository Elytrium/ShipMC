#include "NBT.hpp"

namespace Ship {
  ShortTag::ShortTag(const std::string& name) : NBT(name) {
  }

  ShortTag::ShortTag(const std::string& name, uint16_t value) : NBT(name), value(value) {
  }

  Errorable<bool> ShortTag::Read(ByteBuffer* buffer) {
    SetFromErrorable(value, uint16_t, buffer->ReadShort(), InvalidNBTTagErrorable(buffer->GetReadableBytes()))
    return SuccessErrorable<bool>(true);
  }

  void ShortTag::Write(ByteBuffer* buffer) {
    buffer->WriteShort(value);
  }

  uint32_t ShortTag::GetSize() {
    return sizeof(uint16_t);
  }

  TagType ShortTag::GetType() {
    return TagType::SHORT;
  }

  uint16_t ShortTag::GetValue() const {
    return value;
  }

  void ShortTag::SetValue(uint16_t newValue) {
    value = newValue;
  }
}
