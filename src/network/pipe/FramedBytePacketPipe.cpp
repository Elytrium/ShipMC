#include "FramedPipe.hpp"

namespace Ship {
  Errorable<PacketHolder> FramedBytePacketPipe::Read(ByteBuffer* in) {
    size_t readableBytes = in->GetReadableBytes();
    if (nextReadFrameLength == 0) {
      if (readableBytes == 0) {
        return IncompleteFrameErrorable(readableBytes);
      }

      Errorable<uint32_t> nextReadFrameLengthErrorable = in->ReadVarInt();
      uint32_t frameLength = nextReadFrameLengthErrorable.GetValue();
      if (nextReadFrameLengthErrorable.IsSuccess()) {
        if (frameLength > maxReadSize) {
          return InvalidFrameErrorable(frameLength);
        }

        nextReadFrameLength = frameLength;
      } else if (nextReadFrameLengthErrorable.GetTypeOrdinal() != IncompleteFrameErrorable::TYPE_ORDINAL) {
        return InvalidFrameErrorable(frameLength);
      }
    }

    if (nextReadFrameLength != 0 && readableBytes >= nextReadFrameLength) {
      Errorable<PacketHolder> packet = ReadPacket(in, nextReadFrameLength);
      nextReadFrameLength = 0;
      return packet;
    }

    return IncompleteFrameErrorable(readableBytes);
  }
} // namespace Ship