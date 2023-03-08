#pragma once

#include "../../../utils/ordinal/OrdinalRegistry.hpp"
#include "../Packet.hpp"
#include <string>

namespace Ship {

  class StatusRequest : public Packet {
   public:
    static inline const uint32_t PACKET_ORDINAL = OrdinalRegistry::PacketRegistry.RegisterOrdinal();

    StatusRequest(const ProtocolVersion* version, ByteBuffer* buffer) {
    }

    ~StatusRequest() override = default;

    void Write(const ProtocolVersion* version, ByteBuffer* buffer) const override {
    }

    uint32_t GetOrdinal() const override {
      return PACKET_ORDINAL;
    }
  };
}
