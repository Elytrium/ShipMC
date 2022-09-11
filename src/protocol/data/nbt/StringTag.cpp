#include <utility>

#include "NBT.hpp"

namespace Ship {
  StringTag::StringTag(const std::string& name) : NBT(name) {
  }

  StringTag::StringTag(const std::string& name, std::string value) : NBT(name), value(std::move(value)) {
  }

  void StringTag::Write(ByteBuffer* buffer) {
    buffer->WriteShort(value.size());
    buffer->WriteBytes((uint8_t*) value.data(), value.size());
  }

  void StringTag::Read(ByteBuffer* buffer) {
    uint32_t valueLength = buffer->ReadShort();
    value = (char*) buffer->ReadBytes(valueLength * sizeof(uint16_t));
  }

  uint32_t StringTag::GetSize() {
    return sizeof(uint16_t) + value.size();
  }

  TagType StringTag::GetType() {
    return TagType::STRING;
  }

  std::string StringTag::GetValue() {
    return value;
  }

  void StringTag::SetValue(const std::string& newValue) {
    value = newValue;
  }
}
