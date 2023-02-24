#include "../../utils/exceptions/ErrnoException.hpp"
#include "../../utils/exceptions/Exception.hpp"
#include "../eventloop/EventLoop.hpp"
#include "ReadWriteCloser.hpp"
#include <unistd.h>

namespace Ship {
  thread_local char* readWriteCloserErrorBuffer = new char[64];

  UnixReadWriteCloser::UnixReadWriteCloser(int socket_file_descriptor) : socketFileDescriptor(socket_file_descriptor) {
  }

  void UnixReadWriteCloser::Write(ByteBuffer* buffer) {
    if (closed) {
      return;
    }

    size_t singleCapacity = buffer->GetSingleCapacity();
    size_t readableBytesInSingleBuffer = singleCapacity - buffer->GetReaderIndex();
    if (readableBytesInSingleBuffer != 0) {
      if (write(socketFileDescriptor, buffer->GetDirectReadAddress(), readableBytesInSingleBuffer) == -1) {
        if (errno == ECONNRESET) {
          Close();
          return;
        }

        throw ErrnoException(readWriteCloserErrorBuffer, 64);
      }
      buffer->TryRefreshReaderBuffer();
    }

    while (buffer->GetReadableBytes() >= singleCapacity) {
      if (write(socketFileDescriptor, buffer->GetDirectReadAddress(), singleCapacity) == -1) {
        if (errno == ECONNRESET) {
          Close();
          return;
        }

        throw ErrnoException(readWriteCloserErrorBuffer, 64);
      }
      buffer->TryRefreshReaderBuffer();
    }

    size_t readableBytesLeft = buffer->GetReadableBytes();
    if (readableBytesLeft != 0) {
      if (write(socketFileDescriptor, buffer->GetDirectReadAddress(), readableBytesLeft) == -1) {
        if (errno == ECONNRESET) {
          Close();
          return;
        }

        throw ErrnoException(readWriteCloserErrorBuffer, 64);
      }

      buffer->TryRefreshReaderBuffer();
    }
  }

  ssize_t UnixReadWriteCloser::Read(uint8_t* buffer, size_t buffer_size) {
    if (!closed) {
      return read(socketFileDescriptor, buffer, buffer_size);
    } else {
      return 0;
    }
  }

  UnixReadWriteCloser::~UnixReadWriteCloser() {
    unixClose();
  }

  void UnixReadWriteCloser::Close() {
    unixClose();
  }

  inline void UnixReadWriteCloser::unixClose() {
    if (!closed) {
      closed = true;
      close(socketFileDescriptor);
    }
  }
}