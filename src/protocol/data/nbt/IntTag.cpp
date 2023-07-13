#include "NBT.hpp"

namespace Ship {
  IntTag::IntTag(const std::string& name) : NBT(name) {
  }

  IntTag::IntTag(const std::string& name, uint32_t value) : NBT(name), value(value) {
  }

  void IntTag::Read(ByteBuffer* buffer) {
    ProceedErrorable(value, ss, buffer->ReadInt, ss)
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
