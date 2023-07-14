#include "NBT.hpp"

namespace Ship {
  IntTag::IntTag(const std::string& name) : NBT(name) {
  }

  IntTag::IntTag(const std::string& name, uint32_t value) : NBT(name), value(value) {
  }

  Errorable<bool> IntTag::Read(ByteBuffer* buffer) {
    SetFromErrorable(value, uint32_t, buffer->ReadInt(), InvalidNBTTagErrorable(buffer->GetReadableBytes()))
    return SuccessErrorable<bool>(true);
  }

  void IntTag::Write(ByteBuffer* buffer) {
    buffer->WriteInt(value);
  }

  uint32_t IntTag::GetSize() {
    return sizeof(uint32_t);
  }

  TagType IntTag::GetType() {
    return TagType::INT;
  }

  uint32_t IntTag::GetValue() const {
    return value;
  }

  void IntTag::SetValue(uint32_t newValue) {
    value = newValue;
  }
}
