#include "NBT.hpp"

namespace Ship {
  ByteArrayTag::ByteArrayTag(const std::string &name) : NBT(name) {
  }

  ByteArrayTag::ByteArrayTag(const std::string &name, uint8_t* value, uint32_t valueLength)
    : NBT(name), value((uint8_t *) value), valueLength(valueLength) {
  }

  void ByteArrayTag::Write(ByteBuffer* buffer) {
    buffer->WriteInt(valueLength);
    buffer->WriteBytes(value, valueLength);
  }

  Errorable<bool> ByteArrayTag::Read(ByteBuffer* buffer) {
    delete[] value;

    SetFromErrorable(valueLength, uint32_t, buffer->ReadInt(), InvalidNBTTagErrorable(buffer->GetReadableBytes()))
    SetFromErrorable(value, uint8_t*, buffer->ReadBytes(valueLength), InvalidNBTTagErrorable(buffer->GetReadableBytes()))
    return SuccessErrorable<bool>(true);
  }

  uint32_t ByteArrayTag::GetSize() {
    return sizeof(uint32_t) + valueLength;
  }

  TagType ByteArrayTag::GetType() {
    return TagType::BYTE_ARRAY;
  }

  uint8_t *ByteArrayTag::GetValue() {
    return value;
  }

  uint32_t ByteArrayTag::GetValueLength() const {
    return valueLength;
  }

  void ByteArrayTag::SetValue(uint8_t* newValue, uint32_t newValueLength) {
    value = newValue;
    valueLength = newValueLength;
  }
}