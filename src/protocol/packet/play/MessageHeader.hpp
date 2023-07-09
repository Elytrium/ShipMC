#pragma once


#include <string>

namespace Ship {

  class MessageHeader : public Packet {
   private:
    ByteBuffer* precedingSignature;
    UUID sender;

   public:
    static inline const uint32_t PACKET_ORDINAL = OrdinalRegistry::PacketRegistry.RegisterOrdinal();

    MessageHeader(ByteBuffer* precedingSignature, const UUID& sender) : precedingSignature(precedingSignature), sender(sender) {
    }

    explicit MessageHeader(const PacketHolder& holder) {
      ByteBuffer* buffer = holder.GetCurrentBuffer();
      delete precedingSignature;
      if (buffer->ReadBoolean()) {
        uint32_t size = buffer->GetReadableBytes() - ByteBuffer::UUID_SIZE;
        precedingSignature = new ByteBufferImpl(buffer->ReadBytes(size), size);
      } else {
        precedingSignature = nullptr;
      }
      sender = buffer->ReadUUID();
    }

    ~MessageHeader() override {
      delete precedingSignature;
    }

    void Write(const ProtocolVersion* version, ByteBuffer* buffer) const override {
      buffer->WriteBoolean(precedingSignature);
      if (precedingSignature) {
        buffer->WriteBytes(precedingSignature, precedingSignature->GetReadableBytes());
      }
      buffer->WriteUUID(sender);
    }

    uint32_t GetOrdinal() const override {
      return PACKET_ORDINAL;
    }

    [[nodiscard]] ByteBuffer* GetPrecedingSignature() const {
      return precedingSignature;
    }

    [[nodiscard]] const UUID& GetSender() const {
      return sender;
    }
  };
}
