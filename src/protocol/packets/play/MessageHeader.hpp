#pragma once

#include "../../../utils/ordinal/OrdinalRegistry.hpp"
#include "../Packet.hpp"
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

    ~MessageHeader() override {
      delete precedingSignature;
    }

    void Read(const ProtocolVersion* version, ByteBuffer* buffer) override {
      delete precedingSignature;
      if (buffer->ReadBoolean()) {
        uint32_t size = buffer->GetReadableBytes() - ByteBuffer::UUID_SIZE;
        precedingSignature = new ByteBuffer(buffer->ReadBytes(size), size);
      } else {
        precedingSignature = nullptr;
      }
      sender = buffer->ReadUUID();
    }

    void Write(const ProtocolVersion* version, ByteBuffer* buffer) override {
      buffer->WriteBoolean(precedingSignature);
      if (precedingSignature) {
        buffer->WriteBytes(precedingSignature, precedingSignature->GetReadableBytes());
      }
      buffer->WriteUUID(sender);
    }

    uint32_t Size(const ProtocolVersion* version) override {
      return ByteBuffer::BOOLEAN_SIZE + (precedingSignature ? precedingSignature->GetReadableBytes() : 0) + ByteBuffer::UUID_SIZE;
    }

    uint32_t GetOrdinal() override {
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
