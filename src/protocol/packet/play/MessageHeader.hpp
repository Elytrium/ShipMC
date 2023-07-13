#pragma once

#include "../../../../lib/ShipNet/src/utils/ordinal/OrdinalRegistry.hpp"
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

    static Errorable<MessageHeader> Instantiate(const PacketHolder& holder) {
      ByteBuffer* buffer = holder.GetCurrentBuffer();
      delete precedingSignature;
      ProceedErrorable(hasSignature, bool, buffer->ReadBoolean(), ss)
      if (hasSignature) {
        uint32_t size = buffer->GetReadableBytes() - ByteBuffer::UUID_SIZE;
        precedingSignature = new ByteBufferImpl(buffer->ReadBytes(size), size);
      } else {
        precedingSignature = nullptr;
      }
      ProceedErrorable(sender, UUID, buffer->ReadUUID(), InvalidPacketErrorable<>(PACKET_ORDINAL))
    }

    ~MessageHeader() override {
      delete precedingSignature;
    }

    Errorable<bool> Write(const ProtocolVersion* version, ByteBuffer* buffer) const override {
      buffer->WriteBoolean(precedingSignature);
      if (precedingSignature) {
        buffer->WriteBytes(precedingSignature, precedingSignature->GetReadableBytes());
      }
      buffer->WriteUUID(sender);
      return SuccessErrorable<bool>(true);
    }

    [[nodiscard]] uint32_t GetOrdinal() const override {
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
