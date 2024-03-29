#pragma once

#include "ShipNet/utils/ordinal/OrdinalRegistry.hpp"
#include <string>

namespace Ship {

  class OpenBook : public Packet {
   private:
    uint32_t hand{};

   public:
    static inline const uint32_t PACKET_ORDINAL = OrdinalRegistry::PacketRegistry.RegisterOrdinal();

    OpenBook() = default;
    explicit OpenBook(uint32_t hand) : hand(hand) {
    }

    ~OpenBook() override = default;

    static Errorable<OpenBook> Instantiate(const PacketHolder& holder) {
      ByteBuffer* buffer = holder.GetCurrentBuffer();
      ProceedErrorable(hand, uint32_t, buffer->ReadVarInt(), InvalidPacketErrorable<OpenBook>(PACKET_ORDINAL))
      return SuccessErrorable<OpenBook>(OpenBook(hand));
    }

    Errorable<bool> Write(const ProtocolVersion* version, ByteBuffer* buffer) const override {
      buffer->WriteVarInt(hand);
      return SuccessErrorable<bool>(true);
    }

    [[nodiscard]] uint32_t GetOrdinal() const override {
      return PACKET_ORDINAL;
    }

    [[nodiscard]] uint32_t GetHand() const {
      return hand;
    }
  };
}
