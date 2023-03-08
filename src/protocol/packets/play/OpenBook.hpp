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

    explicit OpenBook(const PacketHolder& holder) {
      ByteBuffer* buffer = holder.GetCurrentBuffer();
      hand = buffer->ReadVarInt();
    }

    void Write(const ProtocolVersion* version, ByteBuffer* buffer) const override {
      buffer->WriteVarInt(hand);
    }

    uint32_t GetOrdinal() const override {
      return PACKET_ORDINAL;
    }

    [[nodiscard]] uint32_t GetHand() const {
      return hand;
    }
  };
}
