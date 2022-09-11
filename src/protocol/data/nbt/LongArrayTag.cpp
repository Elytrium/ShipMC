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

  void LongArrayTag::Read(ByteBuffer* buffer) {
    delete[] value;

    valueLength = buffer->ReadInt();
    value = (uint64_t*) buffer->ReadBytes(valueLength * sizeof(uint64_t));
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