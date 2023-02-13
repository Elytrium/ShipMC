#pragma once

#include "../../../utils/ordinal/OrdinalRegistry.hpp"
#include "../Packet.hpp"
#include <string>

namespace Ship {

  class OpenBook : public Packet {
   private:
    uint32_t hand;

   public:
    static inline const uint32_t PACKET_ORDINAL = OrdinalRegistry::PacketRegistry.RegisterOrdinal();

    explicit OpenBook(uint32_t hand) : hand(hand) {
    }

    ~OpenBook() override = default;

    void Read(const ProtocolVersion* version, ByteBuffer* buffer) override {
      hand = buffer->ReadVarInt();
    }

    void Write(const ProtocolVersion* version, ByteBuffer* buffer) override {
      buffer->WriteVarInt(hand);
    }

    uint32_t Size(const ProtocolVersion* version) override {
      return ByteBuffer::VarIntBytes(hand);
    }

    uint32_t GetOrdinal() override {
      return PACKET_ORDINAL;
    }

    [[nodiscard]] uint32_t GetHand() const {
      return hand;
    }
  };
}
