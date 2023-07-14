#include "NBT.hpp"

namespace Ship {
  LongTag::LongTag(const std::string& name) : NBT(name) {
  }

  LongTag::LongTag(const std::string& name, uint64_t value) : NBT(name), value(value) {
  }

  Errorable<bool> LongTag::Read(ByteBuffer* buffer) {
    SetFromErrorable(value, uint64_t, buffer->ReadLong(), InvalidNBTTagErrorable(buffer->GetReadableBytes()))
    return SuccessErrorable<bool>(true);
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
