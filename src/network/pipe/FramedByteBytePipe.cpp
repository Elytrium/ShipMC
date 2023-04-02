#include "FramedPipe.hpp"

namespace Ship {
  void FramedByteBytePipe::Write(ByteBuffer* in) {
    size_t readableBytes = in->GetReadableBytes();
    if (nextWriteFrameLength == 0) {
      if (readableBytes == 0) {
        return;
      }

      Errorable<uint32_t> nextWriteFrameLengthErrorable = in->ReadVarInt();
      uint32_t frameLength = nextWriteFrameLengthErrorable.GetValue();
      if (nextWriteFrameLengthErrorable.IsSuccess()) {
        nextWriteFrameLength = frameLength;
      } else if (nextWriteFrameLengthErrorable.GetTypeOrdinal() == IncompleteFrameErrorable::TYPE_ORDINAL) {
        return;
      } else {
        return InvalidFrameErrorable(frameLength);
      }
    }

    if (readableBytes >= nextWriteFrameLength) {
      EncodeFrame(in, nextWriteFrameLength);
      nextWriteFrameLength = 0;
    }
  }

  void FramedByteBytePipe::Read(ByteBuffer* in) {
    if (nextReadFrameLength == 0) {
      Errorable<uint32_t> nextReadFrameLengthErrorable = in->ReadVarInt();
      uint32_t frameLength = nextReadFrameLengthErrorable.GetValue();
      if (nextReadFrameLengthErrorable.IsSuccess()) {
        if (frameLength > maxReadSize) {
          return InvalidFrameErrorable(frameLength);
        }

        nextReadFrameLength = frameLength;
      } else if (nextReadFrameLengthErrorable.GetTypeOrdinal() == IncompleteFrameErrorable::TYPE_ORDINAL) {
        return;
      } else {
        return InvalidFrameErrorable(frameLength);
      }
    }

    if (in->GetReadableBytes() >= nextReadFrameLength) {
      DecodeFrame(in, nextReadFrameLength);
      nextReadFrameLength = 0;
    }
  }
} // namespace Ship