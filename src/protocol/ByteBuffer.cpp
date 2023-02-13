#include "../utils/exceptions/Exception.hpp"
#include "../utils/exceptions/InvalidArgumentException.hpp"
#include "Protocol.hpp"
#include "data/profile/GameProfile.hpp"
#include <cmath>
#include <iostream>

namespace Ship {

  const uint32_t ByteBuffer::BYTE_SIZE = INT8_WIDTH / INT_FAST8_WIDTH;
  const uint32_t ByteBuffer::SHORT_SIZE = INT16_WIDTH / INT_FAST8_WIDTH;
  const uint32_t ByteBuffer::INT_SIZE = INT32_WIDTH / INT_FAST8_WIDTH;
  const uint32_t ByteBuffer::LONG_SIZE = INT64_WIDTH / INT_FAST8_WIDTH;
  const uint32_t ByteBuffer::FLOAT_SIZE = INT_SIZE;
  const uint32_t ByteBuffer::DOUBLE_SIZE = LONG_SIZE;
  const uint32_t ByteBuffer::BOOLEAN_SIZE = BYTE_SIZE;
  const uint32_t ByteBuffer::POSITION_SIZE = LONG_SIZE;
  const uint32_t ByteBuffer::ANGLE_SIZE = BYTE_SIZE;
  const uint32_t ByteBuffer::UUID_SIZE = LONG_SIZE * 2;
  
  ByteBuffer::ByteBuffer(size_t cap) {
    singleCapacity = cap;
    auto* buffer = new uint8_t[singleCapacity];
    currentReadBuffer = buffer;
    currentWriteBuffer = buffer;
    buffers.push_back(buffer);
  }

  ByteBuffer::ByteBuffer(uint8_t* buffer, size_t cap) {
    singleCapacity = cap;
    currentReadBuffer = buffer;
    currentWriteBuffer = buffer;
    buffers.push_back(buffer);
  }

  uint32_t ByteBuffer::VarIntBytes(uint32_t input) {
    if ((input & (0xFFFFFFFF << 7)) == 0) {
      return 1;
    } else if ((input & (0xFFFFFFFF << 14)) == 0) {
      return 2;
    } else if ((input & (0xFFFFFFFF << 21)) == 0) {
      return 3;
    } else if ((input & (0xFFFFFFFF << 28)) == 0) {
      return 4;
    } else {
      return 5;
    }
  }

  uint32_t ByteBuffer::VarLongBytes(uint64_t varLong) {
    return 0; // TODO: VarLong
  }

  uint32_t ByteBuffer::StringBytes(const std::string& string) {
    return VarIntBytes(string.size()) + string.size();
  }

  uint32_t ByteBuffer::PropertiesBytes(const std::vector<GameProfileProperty> &properties) {
    uint32_t size = 0;
    for (const GameProfileProperty& property : properties) {
      size += StringBytes(property.GetName()) + StringBytes(property.GetValue()) + StringBytes(property.GetSignature()) + (INT8_WIDTH / INT8_WIDTH);
    }

    return size;
  }

  uint32_t ByteBuffer::ArrayBytes(uint32_t arrayLength) {
    return VarIntBytes(arrayLength) + arrayLength;
  }

  void ByteBuffer::WriteBoolean(bool input) {
    WriteByte(input ? 1 : 0);
  }

  void ByteBuffer::WriteByte(uint8_t input) {
    TryRefreshWriterBuffer();
    ++readableBytes;
    currentWriteBuffer[localWriterIndex++] = input;
  }

  void ByteBuffer::WriteShort(uint16_t input) {
    WriteByte((input >> 8));
    WriteByte(input);
  }

  void ByteBuffer::WriteMedium(uint32_t input) {
    WriteByte((input >> 16));
    WriteByte((input >> 8));
    WriteByte(input);
  }

  void ByteBuffer::WriteInt(uint32_t input) {
    WriteByte((input >> 24));
    WriteByte((input >> 16));
    WriteByte((input >> 8));
    WriteByte(input);
  }

  void ByteBuffer::WriteVarInt(uint32_t input) {
    if ((input & (0xFFFFFFFF << 7)) == 0) {
      WriteByte(input);
    } else if ((input & (0xFFFFFFFF << 14)) == 0) {
      WriteByte(((input & 0x7F) | 0x80));
      WriteByte((input >> 7));
    } else if ((input & (0xFFFFFFFF << 21)) == 0) {
      WriteByte(((input & 0x7F) | 0x80));
      WriteByte((((input >> 7) & 0x7F) | 0x80));
      WriteByte((input >> 14));
    } else if ((input & (0xFFFFFFFF << 28)) == 0) {
      WriteByte(((input & 0x7F) | 0x80));
      WriteByte((((input >> 7) & 0x7F) | 0x80));
      WriteByte((((input >> 14) & 0x7F) | 0x80));
      WriteByte((input >> 21));
    } else {
      WriteByte(((input & 0x7F) | 0x80));
      WriteByte((((input >> 7) & 0x7F) | 0x80));
      WriteByte((((input >> 14) & 0x7F) | 0x80));
      WriteByte((((input >> 21) & 0x7F) | 0x80));
      WriteByte((input >> 28));
    }
  }

  void ByteBuffer::WriteLong(uint64_t input) {
    WriteByte(input >> 56);
    WriteByte(input >> 48);
    WriteByte(input >> 40);
    WriteByte(input >> 32);
    WriteByte(input >> 24);
    WriteByte(input >> 16);
    WriteByte(input >> 8);
    WriteByte(input);
  }

  void ByteBuffer::WriteVarLong(uint64_t input) {
    // TODO: VarLong
  }

  void ByteBuffer::WriteBytes(uint8_t* input, size_t size) {
    size_t bytesIndex = 0;
    TryRefreshWriterBuffer();

    if (localWriterIndex + size >= singleCapacity) {
      std::copy(input, input + singleCapacity - localWriterIndex, currentWriteBuffer + localWriterIndex);
      size_t copiedBytes = singleCapacity - localWriterIndex;
      size -= copiedBytes;
      readableBytes += copiedBytes;
      bytesIndex += copiedBytes;
      localWriterIndex = 0;
      AppendBuffer();

      while (size >= singleCapacity) {
        std::copy(input + bytesIndex, input + bytesIndex + singleCapacity, currentWriteBuffer + localWriterIndex);
        size -= singleCapacity;
        readableBytes += singleCapacity;
        bytesIndex += singleCapacity;
        localWriterIndex = 0;
        AppendBuffer();
      }
    }

    std::copy(input + bytesIndex, input + bytesIndex + size, currentWriteBuffer + localWriterIndex);
    localWriterIndex += size;
    readableBytes += size;
  }

  void ByteBuffer::WriteBytesAndDelete(uint8_t* input, size_t size) {
    if (localWriterIndex == 0 && size == singleCapacity) {
      buffers.pop_back();
      buffers.push_back(input);
    } else {
      WriteBytes(input, size);
      delete[] input;
    }
  }

  void ByteBuffer::WriteBytes(ByteBuffer* input, size_t size) {
    WriteBytesAndDelete(input->ReadBytes(size), size);
  }

  void ByteBuffer::WriteUUID(UUID input) {
    WriteLong(input.GetMostSignificant());
    WriteLong(input.GetLeastSignificant());
  }

  void ByteBuffer::WriteUUIDIntArray(UUID input) {
    WriteInt((int32_t) (input.GetMostSignificant() >> 32));
    WriteInt((int32_t) (input.GetMostSignificant()));
    WriteInt((int32_t) (input.GetLeastSignificant() >> 32));
    WriteInt((int32_t) (input.GetLeastSignificant()));
  }

  void ByteBuffer::WriteDouble(double input) {
    WriteLong((uint64_t) input);
  }

  void ByteBuffer::WriteFloat(float input) {
    WriteInt((uint32_t) input);
  }

  void ByteBuffer::WriteString(const std::string& input) {
    WriteVarInt(input.size());
    WriteBytes((uint8_t*) input.c_str(), input.size());
  }

  void ByteBuffer::WriteProperties(const std::vector<GameProfileProperty> &properties) {
    WriteVarInt(properties.size());
    for (const GameProfileProperty &property : properties) {
      WriteString(property.GetName());
      WriteString(property.GetValue());
      if (property.GetSignature().empty()) {
        WriteBoolean(false);
      } else {
        WriteBoolean(true);
        WriteString(property.GetSignature());
      }
    }
  }

  void ByteBuffer::WritePosition(int x, int y, int z) {
    WriteLong(((x & 0x3FFFFFFULL) << 38) | ((z & 0x3FFFFFFULL) << 12) | (y & 0xFFF));
  }

  void ByteBuffer::WriteAngle(float input) {
    WriteByte((uint8_t) (input * (256.0F / 360.0F)));
  }

  bool ByteBuffer::ReadBoolean() {
    if (readableBytes < 1) {
      throw Exception("Tried to read boolean, but not enough readable bytes");
    }

    return ReadByteUnsafe() != 0;
  }

  uint8_t ByteBuffer::ReadByte() {
    if (readableBytes < 1) {
      throw Exception("Tried to read byte, but not enough readable bytes");
    }

    return ReadByteUnsafe();
  }

  uint8_t ByteBuffer::ReadByteUnsafe() {
    TryRefreshReaderBuffer();
    --readableBytes;
    return currentReadBuffer[localReaderIndex++];
  }

  uint16_t ByteBuffer::ReadShort() {
    if (readableBytes < 2) {
      throw Exception("Tried to read short, but not enough readable bytes");
    }

    return ReadByteUnsafe() << 8 | ReadByteUnsafe();
  }

  uint32_t ByteBuffer::ReadMedium() {
    if (readableBytes < 3) {
      throw Exception("Tried to read medium, but not enough readable bytes");
    }

    return ReadByteUnsafe() << 16 | ReadByteUnsafe() << 8 | ReadByteUnsafe();
  }

  uint32_t ByteBuffer::ReadInt() {
    if (readableBytes < 4) {
      throw Exception("Tried to read int, but not enough readable bytes");
    }

    return ReadByteUnsafe() << 24 | ReadByteUnsafe() << 16 | ReadByteUnsafe() << 8 | ReadByteUnsafe();
  }

  uint32_t ByteBuffer::ReadVarInt() {
    uint32_t decodedVarInt = 0;
    for (uint32_t byteIndex = 0; byteIndex < 5; ++byteIndex) {
      uint8_t byte = ReadByteUnsafe();
      decodedVarInt |= (byte & 0x7F) << byteIndex * 7;
      if ((byte & 0x80) != 128) {
        return decodedVarInt;
      }
    }

    throw Exception("Invalid VarInt");
  }

  uint64_t ByteBuffer::ReadLong() {
    if (readableBytes < 8) {
      throw Exception("Tried to read long, but not enough readable bytes");
    }

    return (uint64_t) ReadByteUnsafe() << 56 | (uint64_t) ReadByteUnsafe() << 48 | (uint64_t) ReadByteUnsafe() << 32 | (uint64_t) ReadByteUnsafe() << 24
         | (uint64_t) ReadByteUnsafe() << 16 | (uint64_t) ReadByteUnsafe() << 8 | (uint64_t) ReadByteUnsafe();
  }

  uint64_t ByteBuffer::ReadVarLong() {
    return 0; // TODO: VarLong
  }

  uint8_t* ByteBuffer::ReadBytes(size_t size) {
    if (readableBytes < size) {
      throw Exception("Tried to read byte array, but not enough readable bytes");
    }

    auto* bytes = new uint8_t[size];
    uint32_t bytesIndex = 0;
    TryRefreshReaderBuffer();

    if (localWriterIndex + size >= singleCapacity) {
      std::copy(currentReadBuffer + localReaderIndex, currentReadBuffer + singleCapacity, bytes);
      uint32_t copiedBytes = singleCapacity - localReaderIndex;
      size -= copiedBytes;
      readableBytes -= copiedBytes;
      bytesIndex += copiedBytes;
      localReaderIndex = 0;
      PopBuffer();

      while (size >= singleCapacity) {
        std::copy(currentReadBuffer, currentReadBuffer + singleCapacity, bytes + bytesIndex);
        size -= singleCapacity;
        readableBytes -= singleCapacity;
        bytesIndex += singleCapacity;
        localReaderIndex = 0;
        PopBuffer();
      }
    }

    std::copy(currentReadBuffer + localReaderIndex, currentReadBuffer + localReaderIndex + size, bytes + bytesIndex);
    localReaderIndex += size;
    readableBytes -= size;
    return bytes;
  }

  UUID ByteBuffer::ReadUUID() {
    return {ReadLong(), ReadLong()};
  }

  UUID ByteBuffer::ReadUUIDIntArray() {
    return {(uint64_t) ReadInt() << 32 | ((uint64_t) ReadInt() & 0xFFFFFFFFLL), (uint64_t) ReadInt() << 32 | ((uint64_t) ReadInt() & 0xFFFFFFFFLL)};
  }

  double ByteBuffer::ReadDouble() {
    return (double) ReadLong();
  }

  float ByteBuffer::ReadFloat() {
    return (float) ReadInt();
  }

  std::string ByteBuffer::ReadString() {
    return ReadString(65536);
  }

  std::string ByteBuffer::ReadString(uint32_t max_size) {
    uint32_t length = ReadVarInt();
    if (length > max_size) {
      throw InvalidArgumentException("Invalid received string size", length);
    }

    return (const char*) ReadBytes(length);
  }

  std::vector<GameProfileProperty> ByteBuffer::ReadProperties() {
    std::vector<GameProfileProperty> properties;
    for (uint32_t i = 0; i < ReadVarInt(); ++i) {
      std::string name = ReadString();
      std::string value = ReadString();
      if (ReadBoolean()) {
        properties.emplace_back(name, value, ReadString());
      } else {
        properties.emplace_back(name, value, "");
      }
    }

    return properties;
  }

  void ByteBuffer::ReadPosition(int& x, int& y, int& z) {
    uint64_t value = ReadLong();
    x = (int) (value >> 38);
    y = (int) (value & 0xFFF);
    z = (int) (value >> 12) & 0x3FFFFFF;

    if (x >= 1 << 25) {
      x -= 1 << 26;
    }

    if (y >= 1 << 11) {
      y -= 1 << 12;
    }

    if (z >= 1 << 25) {
      z -= 1 << 26;
    }
  }

  float ByteBuffer::ReadAngle() {
    return (float) ReadByte() / (256.0F / 360.0F);
  }

  ByteBuffer::~ByteBuffer() {
    Release();
  }

  void ByteBuffer::Release() {
    while (!buffers.empty()) {
      delete[] buffers.front();
      buffers.pop_front();
    }
  }

  ByteBuffer& operator<<(ByteBuffer& buffer, bool input) {
    buffer.WriteBoolean(input);
    return buffer;
  }

  ByteBuffer& operator<<(ByteBuffer& buffer, uint8_t input) {
    buffer.WriteByte(input);
    return buffer;
  }

  ByteBuffer& operator<<(ByteBuffer& buffer, uint16_t input) {
    buffer.WriteShort(input);
    return buffer;
  }

  ByteBuffer& operator<<(ByteBuffer& buffer, uint32_t input) {
    buffer.WriteInt(input);
    return buffer;
  }

  ByteBuffer& operator<<(ByteBuffer& buffer, uint64_t input) {
    buffer.WriteLong(input);
    return buffer;
  }

  ByteBuffer& operator<<(ByteBuffer& buffer, double input) {
    buffer.WriteDouble(input);
    return buffer;
  }

  ByteBuffer& operator<<(ByteBuffer& buffer, float input) {
    buffer.WriteFloat(input);
    return buffer;
  }

  ByteBuffer& operator>>(ByteBuffer& buffer, bool& output) {
    output = buffer.ReadBoolean();
    return buffer;
  }

  ByteBuffer& operator>>(ByteBuffer& buffer, uint8_t& output) {
    output = buffer.ReadByteUnsafe();
    return buffer;
  }

  ByteBuffer& operator>>(ByteBuffer& buffer, uint16_t& output) {
    output = buffer.ReadShort();
    return buffer;
  }

  ByteBuffer& operator>>(ByteBuffer& buffer, uint32_t& output) {
    output = buffer.ReadInt();
    return buffer;
  }

  ByteBuffer& operator>>(ByteBuffer& buffer, uint64_t& output) {
    output = buffer.ReadLong();
    return buffer;
  }

  ByteBuffer& operator>>(ByteBuffer& buffer, double& output) {
    output = buffer.ReadDouble();
    return buffer;
  }

  ByteBuffer& operator>>(ByteBuffer& buffer, float& output) {
    output = buffer.ReadFloat();
    return buffer;
  }

  void ByteBuffer::ResetReaderIndex() {
    localReaderIndex = 0;
    readableBytes = (buffers.size() - 1) * singleCapacity + localWriterIndex;
  }

  void ByteBuffer::ResetWriterIndex() {
    localWriterIndex = 0;
    readableBytes = 0;
  }

  size_t ByteBuffer::GetReadableBytes() const {
    return readableBytes;
  }

  void ByteBuffer::TryRefreshReaderBuffer() {
    if (localReaderIndex >= singleCapacity) {
      delete[] currentReadBuffer;
      localReaderIndex = 0;
      PopBuffer();
    }
  }

  void ByteBuffer::TryRefreshWriterBuffer() {
    if (localWriterIndex >= singleCapacity) {
      localWriterIndex = 0;
      AppendBuffer();
    }
  }

  void ByteBuffer::AppendBuffer() {
    currentWriteBuffer = new uint8_t[singleCapacity];
    buffers.push_back(currentWriteBuffer);
  }

  void ByteBuffer::PopBuffer() {
    delete buffers.front();
    buffers.pop_front();
    currentReadBuffer = buffers.front();
  }

  bool ByteBuffer::CanReadDirect(size_t read_size) const {
    return localReaderIndex + read_size < singleCapacity;
  }

  uint8_t* ByteBuffer::GetDirectReadAddress() {
    return currentReadBuffer + localReaderIndex;
  }

  bool ByteBuffer::CanWriteDirect(size_t write_size) const {
    return localWriterIndex + write_size < singleCapacity;
  }

  uint8_t* ByteBuffer::GetDirectWriteAddress() {
    return currentWriteBuffer + localWriterIndex;
  }

  size_t ByteBuffer::GetReaderIndex() const {
    return localReaderIndex;
  }

  size_t ByteBuffer::GetWriterIndex() const {
    return localWriterIndex;
  }

  size_t ByteBuffer::GetSingleCapacity() const {
    return singleCapacity;
  }
}
