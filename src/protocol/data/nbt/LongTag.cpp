#include "NBT.hpp"

namespace Ship {
  LongTag::LongTag(const std::string& name) : NBT(name) {
  }

  LongTag::LongTag(const std::string& name, uint64_t value) : NBT(name), value(value) {
  }

  void LongTag::Read(ByteBuffer* buffer) {
    value = buffer->ReadLong();
  }

  void LongTag::Write(ByteBuffer* buffer) {
    buffer->WriteLong(value);
  }

  uint32_t LongTag::GetSize() {
    return sizeof(uint64_t);
  }

  TagType LongTag::GetType() {
    return TagType::LONG;
  }

  uint64_t LongTag::GetValue() const {
    return value;
  }

  void LongTag::SetValue(uint64_t newValue) {
    value = newValue;
  }
}
