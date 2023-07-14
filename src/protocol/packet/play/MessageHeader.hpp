#pragma once

#include "../../../../lib/ShipNet/src/utils/ordinal/OrdinalRegistry.hpp"
#include <string>

namespace Ship {

  class MessageHeader : public Packet {
   private:
    ByteBuffer* precedingSignature{};
    UUID sender{};

   public:
    static inline const uint32_t PACKET_ORDINAL = OrdinalRegistry::PacketRegistry.RegisterOrdinal();

    MessageHeader() = default;
    MessageHeader(ByteBuffer* precedingSignature, const UUID& sender) : precedingSignature(precedingSignature), sender(sender) {
    }

    static Errorable<MessageHeader> Instantiate(const PacketHolder& holder) {
      ByteBuffer* buffer = holder.GetCurrentBuffer();
      ProceedErrorable(hasSignature, bool, buffer->ReadBoolean(), InvalidPacketErrorable<MessageHeader>(PACKET_ORDINAL))
      ByteBuffer* precedingSignature;
      if (hasSignature) {
        uint32_t size = buffer->GetReadableBytes() - ByteBuffer::UUID_SIZE;
        ProceedErrorable(bytes, uint8_t*, buffer->ReadBytes(size), InvalidPacketErrorable<MessageHeader>(PACKET_ORDINAL))
        precedingSignature = new ByteBufferImpl(bytes, size);
      }

      ProceedErrorable(sender, UUID, buffer->ReadUUID(), InvalidPacketErrorable<MessageHeader>(PACKET_ORDINAL))
      return SuccessErrorable<MessageHeader>(MessageHeader(precedingSignature, sender));
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
