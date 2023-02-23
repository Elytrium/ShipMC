#include "../../utils/exceptions/InvalidArgumentException.hpp"
#include "FramedPipe.hpp"

namespace Ship {
  void FramedByteBytePipe::Write(ByteBuffer* in) {
    size_t readableBytes = in->GetReadableBytes();
    if (nextWriteFrameLength == 0) {
      if (readableBytes == 0) {
        return;
      }

      try {
        nextWriteFrameLength = in->ReadVarInt();
      } catch (const IncompleteVarIntException& exception) {
        return;
      }
    }

    if (readableBytes >= nextWriteFrameLength) {
      EncodeFrame(in, nextWriteFrameLength);
      nextWriteFrameLength = 0;
    }
  }

  void FramedByteBytePipe::Read(ByteBuffer* in) {
    if (nextReadFrameLength == 0) {
      try {
        nextReadFrameLength = in->ReadVarInt();
      } catch (const IncompleteVarIntException& exception) {
        return;
      }

      if (nextReadFrameLength > maxReadSize) {
        throw InvalidArgumentException("Invalid frame size: ", nextReadFrameLength);
      }
    }

    if (in->GetReadableBytes() >= nextReadFrameLength) {
      DecodeFrame(in, nextReadFrameLength);
      nextReadFrameLength = 0;
    }
  }
} // namespace Ship