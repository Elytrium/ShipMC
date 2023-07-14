#include "NBT.hpp"

namespace Ship {
  IntArrayTag::IntArrayTag(const std::string& name) : NBT(name) {
  }

  IntArrayTag::IntArrayTag(const std::string& name, uint32_t* value, uint32_t valueLength)
    : NBT(name), value((uint32_t*) value), valueLength(valueLength) {
  }

  void IntArrayTag::Write(ByteBuffer* buffer) {
    buffer->WriteInt(valueLength);
    buffer->WriteBytes((uint8_t*) value, valueLength * sizeof(uint32_t));
  }

  Errorable<bool> IntArrayTag::Read(ByteBuffer* buffer) {
    delete[] value;

    SetFromErrorable(valueLength, uint32_t, buffer->ReadInt(), InvalidNBTTagErrorable(buffer->GetReadableBytes()))
    ProceedErrorable(valueBytes, uint8_t*, buffer->ReadBytes(valueLength * sizeof(uint32_t)), InvalidNBTTagErrorable(buffer->GetReadableBytes()))
    value = (uint32_t*) valueBytes;
    return SuccessErrorable<bool>(true);
  }

  uint32_t IntArrayTag::GetSize() {
    return sizeof(uint32_t) + (valueLength * sizeof(uint32_t));
  }

  TagType IntArrayTag::GetType() {
    return TagType::INT_ARRAY;
  }

  uint32_t* IntArrayTag::GetValue() {
    return value;
  }

  uint32_t IntArrayTag::GetValueLength() const {
    return valueLength;
  }

  void IntArrayTag::SetValue(uint32_t* newValue, uint32_t newValueLength) {
    value = newValue;
    valueLength = newValueLength;
  }
}