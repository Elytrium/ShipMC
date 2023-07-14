#pragma once

#include "ShipNet/utils/ordinal/OrdinalRegistry.hpp"
#include <string>

namespace Ship {

  class SetCompression : public Packet {
   private:
    uint32_t threshold{};

   public:
    static inline const uint32_t PACKET_ORDINAL = OrdinalRegistry::PacketRegistry.RegisterOrdinal();

    SetCompression() = default;
    explicit SetCompression(uint32_t threshold) : threshold(threshold) {}

    static Errorable<SetCompression> Instantiate(const PacketHolder& holder) {
      ByteBuffer* buffer = holder.GetCurrentBuffer();
      ProceedErrorable(threshold, uint32_t, buffer->ReadVarInt(), InvalidPacketErrorable<SetCompression>(PACKET_ORDINAL))
      return SuccessErrorable<SetCompression>(SetCompression(threshold));
    }

    ~SetCompression() override = default;

    Errorable<bool> Write(const ProtocolVersion* version, ByteBuffer* buffer) const override {
      buffer->WriteVarInt(threshold);
      return SuccessErrorable<bool>(true);
    }

    [[nodiscard]] uint32_t GetOrdinal() const override {
      return PACKET_ORDINAL;
    }

    [[nodiscard]] uint32_t GetThreshold() const {
      return threshold;
    }
  };
}
