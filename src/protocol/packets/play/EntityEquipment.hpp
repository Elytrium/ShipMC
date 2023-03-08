#pragma once

#include "../../../utils/ordinal/OrdinalRegistry.hpp"
#include "../Packet.hpp"
#include <string>

namespace Ship {

  class EntityEquipment : public Packet {
   public:
    static inline const uint32_t PACKET_ORDINAL = OrdinalRegistry::PacketRegistry.RegisterOrdinal();
    ~EntityEquipment() override {
    }

    void Write(const ProtocolVersion* version, ByteBuffer* buffer) const override {
    }

    uint32_t GetOrdinal() const override {
      return PACKET_ORDINAL;
    }
  };
}
