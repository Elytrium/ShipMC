#pragma once

#include "../../protocol/Protocol.hpp"
#include "./ReadWriteCloser.hpp"

namespace Ship {

  class ReadWriteCloser {
   public:
    virtual ~ReadWriteCloser() = default;
    virtual void Write(ByteBuffer* buffer) {};
    virtual ssize_t Read(uint8_t* buffer, size_t buffer_size) {
      return -1;
    };
    virtual void Close() {};
  };

  class UnixReadWriteCloser : public ReadWriteCloser {
   private:
    int socketFileDescriptor;

   public:
    explicit UnixReadWriteCloser(int socket_file_descriptor);

    void Write(ByteBuffer* buffer) override;
    ssize_t Read(uint8_t* buffer, size_t buffer_size) override;
    void Close() override;
  };

}