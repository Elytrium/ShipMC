#include "../utils/exceptions/Exception.hpp"
#include "../utils/exceptions/InvalidArgumentException.hpp"
#include "Protocol.hpp"
#include "data/profile/GameProfile.hpp"
#include <cmath>

namespace Ship {

  const uint32_t ByteBuffer::BYTE_SIZE = 1;
  const uint32_t ByteBuffer::SHORT_SIZE = 2;
  const uint32_t ByteBuffer::MEDIUM_SIZE = 3;
  const uint32_t ByteBuffer::INT_SIZE = 4;
  const uint32_t ByteBuffer::LONG_SIZE = 8;
  const uint32_t ByteBuffer::FLOAT_SIZE = INT_SIZE;
  const uint32_t ByteBuffer::DOUBLE_SIZE = LONG_SIZE;
  const uint32_t ByteBuffer::BOOLEAN_SIZE = BYTE_SIZE;
  const uint32_t ByteBuffer::POSITION_SIZE = LONG_SIZE;
  const uint32_t ByteBuffer::ANGLE_SIZE = BYTE_SIZE;
  const uint32_t ByteBuffer::UUID_SIZE = LONG_SIZE * 2;

  ByteBuffer::~ByteBuffer() = default;

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

  uint32_t ByteBuffer::VarLongBytes(uint64_t input) {
    if ((input & (0xFFFFFFFFFFFFFFFFULL << 7)) == 0) {
      return 1;
    } else if ((input & (0xFFFFFFFFFFFFFFFFULL << 14)) == 0) {
      return 2;
    } else if ((input & (0xFFFFFFFFFFFFFFFFULL << 21)) == 0) {
      return 3;
    } else if ((input & (0xFFFFFFFFFFFFFFFFULL << 28)) == 0) {
      return 4;
    } else if ((input & (0xFFFFFFFFFFFFFFFFULL << 35)) == 0) {
      return 5;
    } else if ((input & (0xFFFFFFFFFFFFFFFFULL << 42)) == 0) {
      return 6;
    } else if ((input & (0xFFFFFFFFFFFFFFFFULL << 49)) == 0) {
      return 7;
    } else if ((input & (0xFFFFFFFFFFFFFFFFULL << 56)) == 0) {
      return 8;
    } else if ((input & (0xFFFFFFFFFFFFFFFFULL << 63)) == 0) {
      return 9;
    } else {
      return 10;
    }
  }

  uint32_t ByteBuffer::StringBytes(const std::string& string) {
    return VarIntBytes(string.size()) + string.size();
  }

  uint32_t ByteBuffer::PropertiesBytes(const std::vector<GameProfileProperty> &properties) {
    uint32_t size = 0;
    for (const GameProfileProperty& property : properties) {
      size += StringBytes(property.GetName()) + StringBytes(property.GetValue()) + StringBytes(property.GetSignature()) + BYTE_SIZE;
    }

    return size;
  }

  uint32_t ByteBuffer::ArrayBytes(uint32_t arrayLength) {
    return VarIntBytes(arrayLength) + arrayLength;
  }

  void ByteBuffer::WriteBoolean(bool input) {
    WriteByte(input ? 1 : 0);
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
    while (true) {
      if ((input & ~0x7F) == 0) {
        WriteByte(input);
        return;
      }

      WriteByte((input & 0x7F) | 0x80);
      input >>= 7;
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
    while (true) {
      if ((input & ~0x7FULL) == 0) {
        WriteByte(input);
        return;
      }

      WriteByte((input & 0x7FULL) | 0x80ULL);
      input >>= 7;
    }
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
    WriteLong(*((uint64_t*) &input));
  }

  void ByteBuffer::WriteFloat(float input) {
    WriteInt(*((uint32_t*) &input));
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
    if (GetReadableBytes() < 1) {
      throw Exception("Tried to read boolean, but not enough readable bytes");
    }

    return ReadByteUnsafe() != 0;
  }

  uint8_t ByteBuffer::ReadByte() {
    if (GetReadableBytes() < 1) {
      throw Exception("Tried to read byte, but not enough readable bytes");
    }

    return ReadByteUnsafe();
  }

  uint16_t ByteBuffer::ReadShort() {
    if (GetReadableBytes() < 2) {
      throw Exception("Tried to read short, but not enough readable bytes");
    }

    return ReadByteUnsafe() << 8 | ReadByteUnsafe();
  }

  uint32_t ByteBuffer::ReadMedium() {
    if (GetReadableBytes() < 3) {
      throw Exception("Tried to read medium, but not enough readable bytes");
    }

    return ReadByteUnsafe() << 16 | ReadByteUnsafe() << 8 | ReadByteUnsafe();
  }

  uint32_t ByteBuffer::ReadInt() {
    if (GetReadableBytes() < 4) {
      throw Exception("Tried to read int, but not enough readable bytes");
    }

    return ReadByteUnsafe() << 24 | ReadByteUnsafe() << 16 | ReadByteUnsafe() << 8 | ReadByteUnsafe();
  }

  uint32_t ByteBuffer::ReadVarInt() {
    uint32_t decodedVarInt = 0;
    for (uint32_t byteIndex = 0; byteIndex < 5; ++byteIndex) {
      uint8_t byte = ReadByteUnsafe();
      decodedVarInt |= (byte & 0x7F) << byteIndex * 7;
      if ((byte & 0x80) == 0) {
        return decodedVarInt;
      }
    }

    throw Exception("Invalid VarInt");
  }

  uint64_t ByteBuffer::ReadLong() {
    if (GetReadableBytes() < 8) {
      throw Exception("Tried to read long, but not enough readable bytes");
    }

    return (uint64_t) ReadByteUnsafe() << 56 | (uint64_t) ReadByteUnsafe() << 48 | (uint64_t) ReadByteUnsafe() << 40 | (uint64_t) ReadByteUnsafe() << 32
         | (uint64_t) ReadByteUnsafe() << 24 | (uint64_t) ReadByteUnsafe() << 16 | (uint64_t) ReadByteUnsafe() << 8 | (uint64_t) ReadByteUnsafe();
  }

  uint64_t ByteBuffer::ReadVarLong() {
    uint64_t decodedVarLong = 0;
    for (uint32_t byteIndex = 0; byteIndex < 10; ++byteIndex) {
      uint8_t byte = ReadByteUnsafe();
      decodedVarLong |= ((uint64_t) (byte & 0x7FULL)) << byteIndex * 7;
      if ((byte & 0x80) == 0) {
        return decodedVarLong;
      }
    }

    throw Exception("Invalid VarLong");
  }

  UUID ByteBuffer::ReadUUID() {
    return {ReadLong(), ReadLong()};
  }

  UUID ByteBuffer::ReadUUIDIntArray() {
    return {(uint64_t) ReadInt() << 32 | ((uint64_t) ReadInt() & 0xFFFFFFFFLL), (uint64_t) ReadInt() << 32 | ((uint64_t) ReadInt() & 0xFFFFFFFFLL)};
  }

  double ByteBuffer::ReadDouble() {
    uint64_t value = ReadLong();
    return *((double*) &value);
  }

  float ByteBuffer::ReadFloat() {
    uint32_t value = ReadInt();
    return *((float*) &value);
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

  uint8_t* ByteBuffer::ReadBytes(size_t size) {
    auto* bytes = new uint8_t[size];
    ReadBytes(bytes, size);
    return bytes;
  }

  ByteBufferImpl::ByteBufferImpl(size_t cap) {
    singleCapacity = cap;
    auto* buffer = new uint8_t[singleCapacity];
    currentReadBuffer = buffer;
    currentWriteBuffer = buffer;
    buffers.push_back(buffer);
  }

  ByteBufferImpl::ByteBufferImpl(uint8_t* buffer, size_t cap) {
    singleCapacity = cap;
    currentReadBuffer = buffer;
    currentWriteBuffer = buffer;
    buffers.push_back(buffer);
  }

  ByteBufferImpl::ByteBufferImpl(ByteBuffer* buffer) {
    readableBytes = buffer->GetReadableBytes();
    singleCapacity = buffer->GetSingleCapacity();
    localReaderIndex = buffer->GetReaderIndex();
    localWriterIndex = buffer->GetWriterIndex();
    currentReadBuffer = buffer->GetDirectReadAddress() - localReaderIndex;
    currentWriteBuffer = buffer->GetDirectWriteAddress() - localWriterIndex;
    buffers = buffer->GetDirectBuffers();
  }

  uint8_t ByteBufferImpl::ReadByteUnsafe() {
    TryRefreshReaderBuffer();
    --readableBytes;
    return currentReadBuffer[localReaderIndex++];
  }

  void ByteBufferImpl::WriteByte(uint8_t input) {
    TryRefreshWriterBuffer();
    ++readableBytes;
    currentWriteBuffer[localWriterIndex++] = input;
  }

  void ByteBufferImpl::WriteBytes(uint8_t* input, size_t size) {
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

  void ByteBufferImpl::WriteBytesAndDelete(uint8_t* input, size_t size) {
    if (localWriterIndex == 0 && size == singleCapacity) {
      buffers.pop_back();
      buffers.push_back(input);
    } else {
      WriteBytes(input, size);
      delete[] input;
    }
  }

  void ByteBufferImpl::WriteBytes(ByteBuffer* input, size_t size) {
    WriteBytesAndDelete(input->ReadBytes(size), size);
  }

  void ByteBufferImpl::ReadBytes(uint8_t* output, size_t size) {
    if (GetReadableBytes() < size) {
      throw Exception("Tried to read byte array, but not enough readable bytes");
    }

    uint32_t bytesIndex = 0;
    TryRefreshReaderBuffer();

    if (localWriterIndex + size >= singleCapacity) {
      std::copy(currentReadBuffer + localReaderIndex, currentReadBuffer + singleCapacity, output);
      uint32_t copiedBytes = singleCapacity - localReaderIndex;
      size -= copiedBytes;
      readableBytes -= copiedBytes;
      bytesIndex += copiedBytes;
      localReaderIndex = 0;
      PopBuffer();

      while (size >= singleCapacity) {
        std::copy(currentReadBuffer, currentReadBuffer + singleCapacity, output + bytesIndex);
        size -= singleCapacity;
        readableBytes -= singleCapacity;
        bytesIndex += singleCapacity;
        localReaderIndex = 0;
        PopBuffer();
      }
    }

    std::copy(currentReadBuffer + localReaderIndex, currentReadBuffer + localReaderIndex + size, output + bytesIndex);
    localReaderIndex += size;
    readableBytes -= size;
  }

  ByteBufferImpl::~ByteBufferImpl() {
    ByteBufferImpl::Release();
  }

  void ByteBufferImpl::Release() {
    while (!buffers.empty()) {
      delete[] buffers.front();
      buffers.pop_front();
    }
  }

  void ByteBufferImpl::ResetReaderIndex() {
    localReaderIndex = 0;
    readableBytes = (buffers.size() - 1) * singleCapacity + localWriterIndex;
  }

  void ByteBufferImpl::ResetWriterIndex() {
    localWriterIndex = 0;
    readableBytes = 0;
  }

  size_t ByteBufferImpl::GetReadableBytes() const {
    return readableBytes;
  }

  void ByteBufferImpl::TryRefreshReaderBuffer() {
    if (localReaderIndex >= singleCapacity) {
      delete[] currentReadBuffer;
      localReaderIndex = 0;
      PopBuffer();
    }
  }

  void ByteBufferImpl::TryRefreshWriterBuffer() {
    if (localWriterIndex >= singleCapacity) {
      localWriterIndex = 0;
      AppendBuffer();
    }
  }

  void ByteBufferImpl::AppendBuffer() {
    currentWriteBuffer = new uint8_t[singleCapacity];
    buffers.push_back(currentWriteBuffer);
  }

  void ByteBufferImpl::PopBuffer() {
    delete buffers.front();
    buffers.pop_front();
    currentReadBuffer = buffers.front();
  }

  bool ByteBufferImpl::CanReadDirect(size_t read_size) const {
    return localReaderIndex + read_size < singleCapacity;
  }

  uint8_t* ByteBufferImpl::GetDirectReadAddress() {
    return currentReadBuffer + localReaderIndex;
  }

  bool ByteBufferImpl::CanWriteDirect(size_t write_size) const {
    return localWriterIndex + write_size < singleCapacity;
  }

  uint8_t* ByteBufferImpl::GetDirectWriteAddress() {
    return currentWriteBuffer + localWriterIndex;
  }

  size_t ByteBufferImpl::GetReaderIndex() const {
    return localReaderIndex;
  }

  size_t ByteBufferImpl::GetWriterIndex() const {
    return localWriterIndex;
  }

  size_t ByteBufferImpl::GetSingleCapacity() const {
    return singleCapacity;
  }

  std::deque<uint8_t*> ByteBufferImpl::GetDirectBuffers() const {
    return buffers;
  }
}
