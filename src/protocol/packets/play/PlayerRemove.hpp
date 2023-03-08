#pragma once

#include "../../../utils/ordinal/OrdinalRegistry.hpp"
#include "../Packet.hpp"

namespace Ship {

  class PlayerRemove : public Packet {
   public:
    static inline const uint32_t PACKET_ORDINAL = OrdinalRegistry::PacketRegistry.RegisterOrdinal();
    ~PlayerRemove() override {
    }

    void Write(const ProtocolVersion* version, ByteBuffer* buffer) const override {
    }

    uint32_t GetOrdinal() const override {
      return PACKET_ORDINAL;
    }
  };
}
