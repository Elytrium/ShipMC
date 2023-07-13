#pragma once

#include "../../../../lib/ShipNet/src/utils/ordinal/OrdinalRegistry.hpp"
#include <string>

namespace Ship {

  class SingleVersionPreparedPacket : public Packet {
   private:
    ByteBuffer* unknownBytes;

   public:
    static inline const uint32_t PACKET_ORDINAL = OrdinalRegistry::PacketRegistry.RegisterOrdinal();

    explicit SingleVersionPreparedPacket(ByteBuffer* unknownBytes) : unknownBytes(unknownBytes) {
    }

    static Errorable<SingleVersionPreparedPacket> Instantiate(const PacketHolder& holder) {
      ByteBuffer* buffer = holder.GetCurrentBuffer(); // TODO: we should possibly copy the buffer
      return SuccessErrorable<SingleVersionPreparedPacket>(SingleVersionPreparedPacket(buffer));
    }

    ~SingleVersionPreparedPacket() override {
      delete unknownBytes;
    }

    Errorable<bool> Write(const ProtocolVersion* version, ByteBuffer* buffer) const override {
      buffer->WriteBytes(new ByteBufferImpl(unknownBytes), unknownBytes->GetReadableBytes());
      return SuccessErrorable<bool>(true);
    }

    uint32_t Size(const ProtocolVersion* version) const override {
      return unknownBytes->GetReadableBytes();
    }

    [[nodiscard]] uint32_t GetOrdinal() const override {
      return PACKET_ORDINAL;
    }

    ByteBuffer* GetBytes() {
      return unknownBytes;
    }
  };
}
