#pragma once

#include "../../protocol/Protocol.hpp"
#include "../../utils/exceptions/Errorable.hpp"
#include "./ReadWriteCloser.hpp"

namespace Ship {

  class ReadWriteCloser {
   public:
    virtual ~ReadWriteCloser() = default;
    virtual Errorable<ssize_t> Write(ByteBuffer* buffer) {
      return SuccessErrorable<ssize_t>(-1);
    };
    virtual Errorable<ssize_t> Read(uint8_t* buffer, size_t buffer_size) {
      return SuccessErrorable<ssize_t>(-1);
    };
    virtual void Close() {};
  };

  class UnixReadWriteCloser : public ReadWriteCloser {
   private:
    int socketFileDescriptor;
    bool closed = false;
    inline void unixClose();

   public:
    explicit UnixReadWriteCloser(int socket_file_descriptor);
    ~UnixReadWriteCloser() override;

    Errorable<ssize_t> Write(ByteBuffer* buffer) override;
    Errorable<ssize_t> Read(uint8_t* buffer, size_t buffer_size) override;
    void Close() override;
  };

}