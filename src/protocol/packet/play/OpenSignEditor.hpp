#pragma once

#include "../../../../lib/ShipNet/src/utils/ordinal/OrdinalRegistry.hpp"
#include <string>

namespace Ship {

  class OpenSignEditor : public Packet {
   private:
    Position location{};

   public:
    static inline const uint32_t PACKET_ORDINAL = OrdinalRegistry::PacketRegistry.RegisterOrdinal();

    OpenSignEditor() = default;

    explicit OpenSignEditor(Position location) : location(location) {
    }

    ~OpenSignEditor() override = default;

    static Errorable<OpenSignEditor> Instantiate(const PacketHolder& holder) {
      ByteBuffer* buffer = holder.GetCurrentBuffer();
      ProceedErrorable(location, Position, ProtocolUtils::ReadPosition(holder.GetVersion(), buffer), InvalidPacketErrorable<OpenSignEditor>(PACKET_ORDINAL))
      return SuccessErrorable<OpenSignEditor>(OpenSignEditor(location));
    }

    Errorable<bool> Write(const ProtocolVersion* version, ByteBuffer* buffer) const override {
      ProtocolUtils::WritePosition(version, buffer, location);
      return SuccessErrorable<bool>(true);
    }

    [[nodiscard]] uint32_t GetOrdinal() const override {
      return PACKET_ORDINAL;
    }

    [[nodiscard]] Position GetLocation() const {
      return location;
    }
  };
}
