#pragma once

#include "../../../utils/ordinal/OrdinalRegistry.hpp"
#include "../Packet.hpp"
#include <string>

namespace Ship {

  class BorderWarningTime : public Packet {
   public:
    static inline const uint32_t PACKET_ORDINAL = OrdinalRegistry::PacketRegistry.RegisterOrdinal();
    ~BorderWarningTime() override {
    }

    void Read(const ProtocolVersion* version, ByteBuffer* buffer) override {
    }

    void Write(const ProtocolVersion* version, ByteBuffer* buffer) override {
    }

    uint32_t Size(const ProtocolVersion* version) override {
      return 0;
    }

    uint32_t GetOrdinal() override {
      return PACKET_ORDINAL;
    }
  };
}
