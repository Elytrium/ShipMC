#pragma once

#include "../../../utils/ordinal/OrdinalRegistry.hpp"
#include "../Packet.hpp"
#include <string>

namespace Ship {

  class HideMessage : public Packet {
   private:
    ByteBuffer* signature;

   public:
    static inline const uint32_t PACKET_ORDINAL = OrdinalRegistry::PacketRegistry.RegisterOrdinal();

    explicit HideMessage(ByteBuffer* signature) : signature(signature) {
    }

    ~HideMessage() override {
      delete signature;
    }

    void Read(const ProtocolVersion* version, ByteBuffer* buffer) override {
      uint32_t size = buffer->GetReadableBytes();
      delete signature;
      signature = new ByteBufferImpl(buffer->ReadBytes(size), size);
    }

    void Write(const ProtocolVersion* version, ByteBuffer* buffer) override {
      buffer->WriteBytes(signature, signature->GetReadableBytes());
    }

    uint32_t GetOrdinal() override {
      return PACKET_ORDINAL;
    }

    [[nodiscard]] ByteBuffer* GetSignature() const {
      return signature;
    }
  };
}
