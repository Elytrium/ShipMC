#include "Protocol.hpp"

namespace Ship {
  void ByteCounter::WriteByte(uint8_t input) {
    writerIndex += BYTE_SIZE;
  }

  void ByteCounter::WriteBoolean(bool input) {
    writerIndex += BOOLEAN_SIZE;
  }
  
  void ByteCounter::WriteShort(uint16_t input) {
    writerIndex += SHORT_SIZE;
  }

  void ByteCounter::WriteMedium(uint32_t input) {
    writerIndex += MEDIUM_SIZE;
  }

  void ByteCounter::WriteInt(uint32_t input) {
    writerIndex += INT_SIZE;
  }

  void ByteCounter::WriteVarInt(uint32_t input) {
    writerIndex += VarIntBytes(input);
  }

  void ByteCounter::WriteLong(uint64_t input) {
    writerIndex += LONG_SIZE;
  }

  void ByteCounter::WriteVarLong(uint64_t input) {
    writerIndex += VarLongBytes(input);
  }

  void ByteCounter::WriteUUID(UUID input) {
    writerIndex += UUID_SIZE;
  }

  void ByteCounter::WriteUUIDIntArray(UUID input) {
    writerIndex += UUID_SIZE;
  }

  void ByteCounter::WriteDouble(double input) {
    writerIndex += DOUBLE_SIZE;
  }

  void ByteCounter::WriteFloat(float input) {
    writerIndex += FLOAT_SIZE;
  }

  void ByteCounter::WriteString(const std::string& input) {
    writerIndex += VarIntBytes(input.size());
    writerIndex += input.size();
  }

  void ByteCounter::WritePosition(int x, int y, int z) {
    writerIndex += POSITION_SIZE;
  }

  void ByteCounter::WriteAngle(float input) {
    writerIndex += ANGLE_SIZE;
  }

  void ByteCounter::WriteBytes(const uint8_t *input, size_t size) {
    writerIndex += size;
  }

  void ByteCounter::WriteBytes(ByteBuffer *buffer, size_t size) {
    writerIndex += size;
  }

  uint8_t ByteCounter::ReadByteUnsafe() {
    return 0;
  }

  void ByteCounter::ReadBytes(uint8_t *output, size_t size) {
  }

  void ByteCounter::WriteBytesAndDelete(const uint8_t *input, size_t size) {
    delete[] input;
  }

  void ByteCounter::Release() {
  }

  void ByteCounter::ResetReaderIndex() {
  }

  size_t ByteCounter::GetReaderIndex() const {
    return 0;
  }

  void ByteCounter::ResetWriterIndex() {
    writerIndex = 0;
  }

  size_t ByteCounter::GetWriterIndex() const {
    return writerIndex;
  }

  size_t ByteCounter::GetReadableBytes() const {
    return SIZE_MAX;
  }

  size_t ByteCounter::GetSingleCapacity() const {
    return SIZE_MAX;
  }

  std::deque<const uint8_t*> ByteCounter::GetDirectBuffers() const {
    return {};
  }

  bool ByteCounter::CanReadDirect(size_t read_size) const {
    return false;
  }

  uint8_t *ByteCounter::GetDirectReadAddress() {
    return nullptr;
  }

  bool ByteCounter::CanWriteDirect(size_t write_size) const {
    return false;
  }

  uint8_t *ByteCounter::GetDirectWriteAddress() {
    return nullptr;
  }

  void ByteCounter::TryRefreshReaderBuffer() {
  }

  void ByteCounter::TryRefreshWriterBuffer() {
  }

  void ByteCounter::AppendBuffer() {
  }

  void ByteCounter::PopBuffer() {
  }

  void ByteCounter::SkipReadBytes(size_t count) {
  }

  void ByteCounter::SkipWriteBytes(size_t count) {
  }
}
