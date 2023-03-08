#pragma once

#include "../../../utils/ordinal/OrdinalRegistry.hpp"
#include "../Packet.hpp"
#include <string>

namespace Ship {

  class AcknowledgeBlockChange : public Packet {
   private:
    uint32_t sequence;

   public:
    static inline const uint32_t PACKET_ORDINAL = OrdinalRegistry::PacketRegistry.RegisterOrdinal();

    explicit AcknowledgeBlockChange(uint32_t sequence) : sequence(sequence) {
    }

    explicit AcknowledgeBlockChange(const PacketHolder& holder) {
      ByteBuffer* buffer = holder.GetCurrentBuffer();
      sequence = buffer->ReadVarInt();
    }

    ~AcknowledgeBlockChange() override = default;

    void Write(const ProtocolVersion* version, ByteBuffer* buffer) const override {
      buffer->WriteVarInt(sequence);
    }

    uint32_t GetOrdinal() const override {
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
