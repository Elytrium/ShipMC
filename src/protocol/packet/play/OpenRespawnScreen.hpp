#pragma once

#include "ShipNet/protocol/packet/Packet.hpp"
#include "ShipNet/utils/ordinal/OrdinalRegistry.hpp"
#include <string>

namespace Ship {

  class OpenRespawnScreen : public Packet {
   public:
    static inline const uint32_t PACKET_ORDINAL = OrdinalRegistry::PacketRegistry.RegisterOrdinal();
    ~OpenRespawnScreen() override = default;

    Errorable<bool> Write(const ProtocolVersion* version, ByteBuffer* buffer) const override {
      return SuccessErrorable<bool>(true);
    }

    [[nodiscard]] uint32_t GetOrdinal() const override {
      return PACKET_ORDINAL;
    }
  };
}
