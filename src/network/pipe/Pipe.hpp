#pragma once

#include "../../protocol/Protocol.hpp"
#include "../../protocol/packets/Packet.hpp"

namespace Ship {
  class ByteBytePipe {
   private:
    ByteBuffer* readerBuffer;
    ByteBuffer* writerBuffer;

   public:
    ByteBytePipe(size_t reader_buffer_length, size_t writer_buffer_length)
      : readerBuffer(new ByteBufferImpl(reader_buffer_length)), writerBuffer(new ByteBufferImpl(writer_buffer_length)) {
    }
    ByteBytePipe(ByteBuffer* reader_buffer, ByteBuffer* writer_buffer) : readerBuffer(reader_buffer), writerBuffer(writer_buffer) {
    }

    virtual ~ByteBytePipe() {
      delete readerBuffer;
      delete writerBuffer;
    };

    ByteBuffer* GetReaderBuffer() {
      return readerBuffer;
    }

    ByteBuffer* GetWriterBuffer() {
      return writerBuffer;
    }

    virtual void Read(ByteBuffer* in) {};
    virtual void Write(ByteBuffer* in) {};
    virtual uint32_t GetOrdinal() const = 0;
  };

  class BytePacketPipe {
   public:
    BytePacketPipe() = default;

    virtual ~BytePacketPipe() = default;

    virtual PacketHolder Read(ByteBuffer* in) = 0;
    virtual ByteBuffer* Write(const Packet& in) = 0;
  };
} // namespace Ship