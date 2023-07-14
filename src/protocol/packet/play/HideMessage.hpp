#pragma once

#include "ShipNet/utils/ordinal/OrdinalRegistry.hpp"
#include <string>

namespace Ship {

  class HideMessage : public Packet {
   private:
    ByteBuffer* signature{};

   public:
    static inline const uint32_t PACKET_ORDINAL = OrdinalRegistry::PacketRegistry.RegisterOrdinal();

    HideMessage() = default;
    explicit HideMessage(ByteBuffer* signature) : signature(signature) {
    }

    static Errorable<HideMessage> Instantiate(const PacketHolder& holder) {
      ByteBuffer* buffer = holder.GetCurrentBuffer();
      uint32_t size = buffer->GetReadableBytes();
      ProceedErrorable(bytes, uint8_t*, buffer->ReadBytes(size), InvalidPacketErrorable<HideMessage>(PACKET_ORDINAL))
      ByteBuffer* signature = new ByteBufferImpl(bytes, size);
      return SuccessErrorable<HideMessage>(HideMessage(signature));
    }

    ~HideMessage() override {
      delete signature;
    }

    Errorable<bool> Write(const ProtocolVersion* version, ByteBuffer* buffer) const override {
      buffer->WriteBytes(signature, signature->GetReadableBytes());
      return SuccessErrorable<bool>(true);
    }

    [[nodiscard]] uint32_t GetOrdinal() const override {
      return PACKET_ORDINAL;
    }

    [[nodiscard]] ByteBuffer* GetSignature() const {
      return signature;
    }
  };
}
