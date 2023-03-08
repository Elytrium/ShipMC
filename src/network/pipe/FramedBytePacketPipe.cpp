#include "../../utils/exceptions/InvalidArgumentException.hpp"
#include "FramedPipe.hpp"

namespace Ship {
  PacketHolder FramedBytePacketPipe::Read(ByteBuffer* in) {
    size_t readableBytes = in->GetReadableBytes();
    if (nextReadFrameLength == 0) {
      if (readableBytes == 0) {
        throw IncompleteFrameException();
      }

      try {
        nextReadFrameLength = in->ReadVarInt();
        if (nextReadFrameLength > maxReadSize) {
          throw InvalidArgumentException("Invalid packet size: ", nextReadFrameLength);
        }
      } catch (const IncompleteVarIntException& exception) {
        throw IncompleteFrameException();
      }
    }

    if (nextReadFrameLength != 0 && readableBytes >= nextReadFrameLength) {
      PacketHolder packet = ReadPacket(in, nextReadFrameLength);
      nextReadFrameLength = 0;
      return packet;
    }

    throw IncompleteFrameException();
  }
} // namespace Ship