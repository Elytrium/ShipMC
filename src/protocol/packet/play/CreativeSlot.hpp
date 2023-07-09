#pragma once

#include "../../../../lib/ShipNet/src/utils/ordinal/OrdinalRegistry.hpp"
#include <string>

namespace Ship {

  class CreativeSlot : public Packet {
   public:
    static inline const uint32_t PACKET_ORDINAL = OrdinalRegistry::PacketRegistry.RegisterOrdinal();
    ~CreativeSlot() override {
    }

    void Write(const ProtocolVersion* version, ByteBuffer* buffer) const override {
    }

    uint32_t GetOrdinal() const override {
      return PACKET_ORDINAL;
    }
  };
}