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

    ~AcknowledgeBlockChange() override = default;

    void Read(const ProtocolVersion* version, ByteBuffer* buffer) override {
      sequence = buffer->ReadVarInt();
    }

    void Write(const ProtocolVersion* version, ByteBuffer* buffer) override {
      buffer->WriteVarInt(sequence);
    }

    uint32_t Size(const ProtocolVersion* version) override {
      return ByteBuffer::VarIntBytes(sequence);
    }

    uint32_t GetOrdinal() override {
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
