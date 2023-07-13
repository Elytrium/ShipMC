#pragma once

#include "../../../../lib/ShipNet/src/utils/ordinal/OrdinalRegistry.hpp"
#include <string>

namespace Ship {

  class AcknowledgeBlockChange : public Packet {
   private:
    uint32_t sequence{};

   public:
    static inline const uint32_t PACKET_ORDINAL = OrdinalRegistry::PacketRegistry.RegisterOrdinal();

    AcknowledgeBlockChange() = default;

    explicit AcknowledgeBlockChange(uint32_t sequence) : sequence(sequence) {
    }

    static Errorable<AcknowledgeBlockChange> Instantiate(const PacketHolder& holder) {
      ByteBuffer* buffer = holder.GetCurrentBuffer();
      ProceedErrorable(sequence, uint32_t, buffer->ReadVarInt(), InvalidPacketErrorable<AcknowledgeBlockChange>(PACKET_ORDINAL))
      return SuccessErrorable<AcknowledgeBlockChange>(AcknowledgeBlockChange(sequence));
    }

    ~AcknowledgeBlockChange() override = default;

    Errorable<bool> Write(const ProtocolVersion* version, ByteBuffer* buffer) const override {
      buffer->WriteVarInt(sequence);
      return SuccessErrorable<bool>(true);
    }

    [[nodiscard]] uint32_t GetOrdinal() const override {
      return PACKET_ORDINAL;
    }

    [[nodiscard]] uint32_t GetSequence() const {
      return sequence;
    }

    void SetSequence(uint32_t value) {
      sequence = value;
    }
  };
}
