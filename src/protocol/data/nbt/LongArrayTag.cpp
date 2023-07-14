#include "NBT.hpp"

namespace Ship {
  LongArrayTag::LongArrayTag(const std::string& name) : NBT(name) {
  }

  LongArrayTag::LongArrayTag(const std::string& name, uint64_t* value, uint32_t valueLength)
    : NBT(name), value((uint64_t*) value), valueLength(valueLength) {
  }

  void LongArrayTag::Write(ByteBuffer* buffer) {
    buffer->WriteInt(valueLength);
    buffer->WriteBytes((uint8_t*) value, valueLength * sizeof(uint64_t));
  }

  Errorable<bool> LongArrayTag::Read(ByteBuffer* buffer) {
    delete[] value;

    SetFromErrorable(valueLength, uint32_t, buffer->ReadInt(), InvalidNBTTagErrorable(buffer->GetReadableBytes()))
    ProceedErrorable(valueBytes, uint8_t*, buffer->ReadBytes(valueLength * sizeof(uint64_t)), InvalidNBTTagErrorable(buffer->GetReadableBytes()))
    value = (uint64_t*) valueBytes;
    return SuccessErrorable<bool>(true);
  }

  uint32_t LongArrayTag::GetSize() {
    return sizeof(uint32_t) + (valueLength * sizeof(uint64_t));
  }

  TagType LongArrayTag::GetType() {
    return TagType::LONG_ARRAY;
  }

  uint64_t* LongArrayTag::GetValue() {
    return value;
  }

  uint32_t LongArrayTag::GetValueLength() const {
    return valueLength;
  }

  void LongArrayTag::SetValue(uint64_t* newValue, uint32_t newValueLength) {
    value = newValue;
    valueLength = newValueLength;
  }
}