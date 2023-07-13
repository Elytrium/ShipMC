#pragma once

#include "../../../../lib/ShipNet/src/utils/ordinal/OrdinalRegistry.hpp"
#include <string>

namespace Ship {

  class Disconnect : public Packet {
   private:
    std::string reason;

   public:
    static inline const uint32_t PACKET_ORDINAL = OrdinalRegistry::PacketRegistry.RegisterOrdinal();

    explicit Disconnect(std::string reason) : reason(std::move(reason)) {
    }

    Disconnect() = default;

    ~Disconnect() override = default;

    static Errorable<Disconnect> Instantiate(const PacketHolder& holder) {
      ByteBuffer* buffer = holder.GetCurrentBuffer();
      ProceedErrorable(reason, std::string, buffer->ReadString(), InvalidPacketErrorable<Disconnect>(PACKET_ORDINAL))
      return SuccessErrorable<Disconnect>(Disconnect(reason));
    }

    Errorable<bool> Write(const ProtocolVersion* version, ByteBuffer* buffer) const override {
      buffer->WriteString(reason);
      return SuccessErrorable<bool>(true);
    }

    [[nodiscard]] uint32_t GetOrdinal() const override {
      return PACKET_ORDINAL;
    }

    [[nodiscard]] const std::string& GetReason() const {
      return reason;
    }
  };
}
