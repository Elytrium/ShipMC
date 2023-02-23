#pragma once

#include "../../../utils/ordinal/OrdinalRegistry.hpp"
#include "../Packet.hpp"

namespace Ship {

  class FeatureFlags : public Packet {
   public:
    static inline const uint32_t PACKET_ORDINAL = OrdinalRegistry::PacketRegistry.RegisterOrdinal();
    ~FeatureFlags() override {
    }

    void Read(const ProtocolVersion* version, ByteBuffer* buffer) override {
    }

    void Write(const ProtocolVersion* version, ByteBuffer* buffer) override {
    }

    uint32_t GetOrdinal() override {
      return PACKET_ORDINAL;
    }
  };
}
