#include "../../utils/exceptions/InvalidArgumentException.hpp"
#include "FramedPipe.hpp"

namespace Ship {
  Packet* FramedBytePacketPipe::Read(ByteBuffer* in) {
    size_t readableBytes = in->GetReadableBytes();
    if (nextReadFrameLength == 0) {
      if (readableBytes == 0) {
        return nullptr;
      }

      nextReadFrameLength = in->ReadVarInt();
      if (nextReadFrameLength > maxReadSize) {
        throw InvalidArgumentException("Invalid packet size: ", nextReadFrameLength);
      }
    }

    if (nextReadFrameLength != 0 && readableBytes >= nextReadFrameLength) {
      Packet* packet = ReadPacket(in, nextReadFrameLength);
      nextReadFrameLength = 0;
      return packet;
    }

    return nullptr;
  }
} // namespace Ship