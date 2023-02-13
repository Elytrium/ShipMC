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

    ~SetCompression() override = default;

    void Read(const ProtocolVersion* version, ByteBuffer* buffer) override {
      threshold = buffer->ReadVarInt();
    }

    void Write(const ProtocolVersion* version, ByteBuffer* buffer) override {
      buffer->WriteVarInt(threshold);
    }

    uint32_t GetOrdinal() override {
      return PACKET_ORDINAL;
    }

    [[nodiscard]] uint32_t GetThreshold() const {
      return threshold;
    }
  };
}
