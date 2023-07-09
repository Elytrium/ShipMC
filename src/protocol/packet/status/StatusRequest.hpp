#pragma once


#include <string>

namespace Ship {

  class StatusRequest : public Packet {
   public:
    static inline const uint32_t PACKET_ORDINAL = OrdinalRegistry::PacketRegistry.RegisterOrdinal();

    explicit StatusRequest(const PacketHolder& holder) {
    }

    ~StatusRequest() override = default;

    void Write(const ProtocolVersion* version, ByteBuffer* buffer) const override {
    }

    uint32_t GetOrdinal() const override {
      return PACKET_ORDINAL;
    }
  };
}
