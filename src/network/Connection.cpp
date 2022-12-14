#include "Connection.hpp"
#include <iostream>

namespace Ship {
  Connection::Connection(BytePacketPipe* bytePacketPipe, size_t reader_buffer_length, size_t writer_buffer_length, ReadWriteCloser* read_write_closer)
    : bytePacketPipe(bytePacketPipe), readerBuffer(new ByteBuffer(reader_buffer_length)), writerBuffer(new ByteBuffer(writer_buffer_length)),
      readWriteCloser(read_write_closer) {
  }

  Connection::~Connection() {
    delete bytePacketPipe;
    delete readerBuffer;
    delete writerBuffer;
    delete readWriteCloser;
  }

  void Connection::SetBytePacketPipe(BytePacketPipe* newBytePacketPipe) {
    delete bytePacketPipe;
    bytePacketPipe = newBytePacketPipe;
  }

  BytePacketPipe* Connection::GetBytePacketPipe() {
    return bytePacketPipe;
  }

  void Connection::AppendByteBytePipe(ByteBytePipe* byte_byte_pipe) {
    pipeline.push_back(byte_byte_pipe);
  }

  void Connection::PrependByteBytePipe(ByteBytePipe* byte_byte_pipe) {
    pipeline.push_front(byte_byte_pipe);
  }

  void Connection::AppendByteBytePipe(ByteBytePipe* byte_byte_pipe, uint32_t after_ordinal) {
    auto afterIterator = pipeline.begin();
    while (afterIterator != pipeline.end()) {
      if ((*afterIterator)->GetOrdinal() == after_ordinal) {
        pipeline.insert(++afterIterator, byte_byte_pipe);
        return;
      }
    }
  }

  void Connection::PrependByteBytePipe(ByteBytePipe* byte_byte_pipe, uint32_t before_ordinal) {
    auto beforeIterator = pipeline.begin();
    while (beforeIterator != pipeline.end()) {
      if ((*beforeIterator)->GetOrdinal() == before_ordinal) {
        pipeline.insert(beforeIterator, byte_byte_pipe);
        return;
      }
    }
  }

  void Connection::RemoveByteBytePipe(uint32_t byte_byte_pipe_ordinal) {
    pipeline.remove_if([byte_byte_pipe_ordinal](ByteBytePipe*& pipe) {
      return byte_byte_pipe_ordinal == pipe->GetOrdinal();
    });
  }

  void Connection::AppendPacketHandler(PacketHandler* byteBytePipe) {
    packetHandlers.push_back(byteBytePipe);
  }

  void Connection::PrependPacketHandler(PacketHandler* byteBytePipe) {
    packetHandlers.push_front(byteBytePipe);
  }

  void Connection::AppendPacketHandler(PacketHandler* byteBytePipe, uint32_t afterOrdinal) {
    auto afterIterator = packetHandlers.begin();
    while (afterIterator != packetHandlers.end()) {
      if ((*afterIterator)->GetOrdinal() == afterOrdinal) {
        packetHandlers.insert(++afterIterator, byteBytePipe);
        return;
      }
    }
  }

  void Connection::PrependPacketHandler(PacketHandler* byteBytePipe, uint32_t beforeOrdinal) {
    auto beforeIterator = packetHandlers.begin();
    while (beforeIterator != packetHandlers.end()) {
      if ((*beforeIterator)->GetOrdinal() == beforeOrdinal) {
        packetHandlers.insert(beforeIterator, byteBytePipe);
        return;
      }
    }
  }

  void Connection::RemovePacketHandler(uint32_t byteByteOrdinal) {
    pipeline.remove_if([byteByteOrdinal](ByteBytePipe*& pipe) {
      return byteByteOrdinal == pipe->GetOrdinal();
    });
  }

  void Connection::HandleNewBytes(uint8_t* page, size_t page_size) {
    ByteBuffer* currentBuffer = readerBuffer;
    currentBuffer->WriteBytes(page, page_size);

    for (const auto& byteBytePipe : pipeline) {
      byteBytePipe->Read(currentBuffer);
      currentBuffer = byteBytePipe->GetReaderBuffer();
    }

    Packet* packet = bytePacketPipe->Read(currentBuffer);
    if (packet != nullptr) {
      for (const auto& item : packetHandlers) {
        if (item->Handle(version, packet)) {
          break;
        }
      }
    }
  }

  void Connection::Write(Packet* packet, bool delete_on_send) {
    ByteBuffer* initBuffer = bytePacketPipe->WriteWithoutDeletion(packet);
    ByteBuffer* buffer = initBuffer;

    if (delete_on_send) {
      delete packet;
    }

    for (auto byteBytePipeIterator = pipeline.rbegin(); byteBytePipeIterator != pipeline.rend(); ++byteBytePipeIterator) {
      ByteBytePipe* pipe = *byteBytePipeIterator;
      pipe->Write(buffer);
      buffer = pipe->GetWriterBuffer();
    }

    WriteDirect(buffer);
    delete initBuffer;
  }

  void Connection::WriteAndFlush(Packet* packet, bool delete_on_send) {
    Write(packet, delete_on_send);
    Flush();
  }

  void Connection::WriteDirect(ByteBuffer* buffer) {
    writerBuffer->WriteBytes(buffer, buffer->GetReadableBytes());
  }

  void Connection::WriteDirect(ByteBuffer* buffer, size_t length) {
    if (buffer->GetReadableBytes() < length) {
      throw InvalidArgumentException("Incorrect length in WriteDirect: ", length);
    }

    writerBuffer->WriteBytes(buffer, length);
  }

  ReadWriteCloser* Connection::GetReadWriteCloser() {
    return readWriteCloser;
  }

  void Connection::Flush() {
    readWriteCloser->Write(writerBuffer);
  }
}
