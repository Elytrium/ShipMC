#include "NBT.hpp"

namespace Ship {
  ByteTag::ByteTag(const std::string& name) : NBT(name) {
  }

  ByteTag::ByteTag(const std::string& name, uint8_t value) : NBT(name), value(value) {
  }

  void ByteTag::Read(ByteBuffer* buffer) {
    ProceedErrorable(value, uint8_t, buffer->ReadByte(), InvalidPacketErrorable<>(PACKET_ORDINAL))
  }

  void ByteTag::Write(ByteBuffer* buffer) {
    buffer->WriteByte(value);
  }

  uint32_t ByteTag::GetSize() {
    return sizeof(uint8_t);
  }

  TagType ByteTag::GetType() {
    return TagType::BYTE;
  }

  uint8_t ByteTag::GetValue() const {
    return value;
  }

  void ByteTag::SetValue(uint8_t newValue) {
    value = newValue;
  }
}
