#pragma once

#include "../../../utils/ordinal/OrdinalRegistry.hpp"
#include "../Packet.hpp"
#include <string>

namespace Ship {

  class SetCompression : public Packet {
   private:
    uint32_t threshold;

   public:
    static inline const uint32_t PACKET_ORDINAL = OrdinalRegistry::PacketRegistry.RegisterOrdinal();

    explicit SetCompression(uint32_t threshold) : threshold(threshold) {}

    explicit SetCompression(const PacketHolder& holder) {
      ByteBuffer* buffer = holder.GetCurrentBuffer();
      threshold = buffer->ReadVarInt();
    }

    ~SetCompression() override = default;

    void Write(const ProtocolVersion* version, ByteBuffer* buffer) const override {
      buffer->WriteVarInt(threshold);
    }

    uint32_t GetOrdinal() const override {
      return PACKET_ORDINAL;
    }

    [[nodiscard]] uint32_t GetThreshold() const {
      return threshold;
    }
  };
}
