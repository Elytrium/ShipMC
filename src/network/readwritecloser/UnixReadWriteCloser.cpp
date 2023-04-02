#include "../../utils/threads/EventLoop.hpp"
#include "ReadWriteCloser.hpp"
#include <unistd.h>

namespace Ship {
  UnixReadWriteCloser::UnixReadWriteCloser(int socket_file_descriptor) : socketFileDescriptor(socket_file_descriptor) {
  }

  Errorable<ssize_t> UnixReadWriteCloser::Write(ByteBuffer* buffer) {
    ssize_t totalBytesWritten = 0;
    if (closed) {
      return SuccessErrorable<ssize_t>(totalBytesWritten);
    }

    size_t singleCapacity = buffer->GetSingleCapacity();
    while (buffer->GetReadableBytes() >= singleCapacity - buffer->GetReaderIndex()) {
      ssize_t bytesWritten = write(socketFileDescriptor, buffer->GetDirectReadAddress(), singleCapacity - buffer->GetReaderIndex());
      if (bytesWritten == -1) {
        if (errno == ECONNRESET) {
          Close();
          return SuccessErrorable<ssize_t>(totalBytesWritten);
        }

        return ErrnoErrorable<ssize_t>({});
      }

      buffer->SkipReadBytes(bytesWritten);
      totalBytesWritten += bytesWritten;
    }

    while (buffer->GetReadableBytes() != 0) {
      ssize_t bytesWritten = write(socketFileDescriptor, buffer->GetDirectReadAddress(), buffer->GetReadableBytes());
      if (bytesWritten == -1) {
        if (errno == ECONNRESET) {
          Close();
          return SuccessErrorable<ssize_t>(totalBytesWritten);
        }

        return ErrnoErrorable<ssize_t>({});
      }

      buffer->SkipReadBytes(bytesWritten);
      totalBytesWritten += bytesWritten;
    }

    return SuccessErrorable<ssize_t>(totalBytesWritten);
  }

  Errorable<ssize_t> UnixReadWriteCloser::Read(uint8_t* buffer, size_t buffer_size) {
    if (!closed) {
      ssize_t bytesRead = read(socketFileDescriptor, buffer, buffer_size);
      if (bytesRead == -1) {
        return ErrnoErrorable<ssize_t>(0);
      }

      return SuccessErrorable<ssize_t>(bytesRead);
    } else {
      return SuccessErrorable<ssize_t>(0);
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