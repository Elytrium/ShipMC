#include "../../utils/exceptions/Exception.hpp"
#include "../eventloop/EventLoop.hpp"
#include "ReadWriteCloser.hpp"
#include <csignal>

namespace Ship {
  UnixReadWriteCloser::UnixReadWriteCloser(int socket_file_descriptor) : socketFileDescriptor(socket_file_descriptor) {
  }

  void UnixReadWriteCloser::Write(ByteBuffer* buffer) {
    size_t singleCapacity = buffer->GetSingleCapacity();
    size_t readableBytesInSingleBuffer = singleCapacity - buffer->GetReaderIndex();
    if (readableBytesInSingleBuffer != 0) {
      if (write(socketFileDescriptor, buffer->GetDirectReadAddress(), readableBytesInSingleBuffer) != 0) {
        throw Exception("Error while flushing writer");
      }
      buffer->TryRefreshReaderBuffer();
    }

    while (buffer->GetReadableBytes() >= singleCapacity) {
      if (write(socketFileDescriptor, buffer->GetDirectReadAddress(), singleCapacity)) {
        throw Exception("Error while flushing writer");
      }
      buffer->TryRefreshReaderBuffer();
    }

    size_t readableBytesLeft = buffer->GetReadableBytes();
    if (readableBytesLeft != 0) {
      if (write(socketFileDescriptor, buffer->GetDirectReadAddress(), readableBytesLeft)) {
        throw Exception("Error while flushing writer");
      }
    }
  }

  ssize_t UnixReadWriteCloser::Read(uint8_t* buffer, size_t buffer_size) {
    return read(socketFileDescriptor, buffer, buffer_size);
  }

  void UnixReadWriteCloser::Close() {
    close(socketFileDescriptor);
  }
}