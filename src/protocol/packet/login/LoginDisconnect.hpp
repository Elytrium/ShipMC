#pragma once

#include "../../../../lib/ShipNet/src/utils/ordinal/OrdinalRegistry.hpp"
#include <string>
#include <utility>

namespace Ship {

  class LoginDisconnect : public Packet {
   private:
    std::string reason;

   public:
    static inline const uint32_t PACKET_ORDINAL = OrdinalRegistry::PacketRegistry.RegisterOrdinal();

    LoginDisconnect() = default;

    explicit LoginDisconnect(std::string reason) : reason(std::move(reason)) {
    }

    static Errorable<LoginDisconnect> Instantiate(const PacketHolder& holder) {
      ByteBuffer* buffer = holder.GetCurrentBuffer();
      ProceedErrorable(reason, std::string, buffer->ReadString(), InvalidPacketErrorable<LoginDisconnect>(PACKET_ORDINAL))
      return SuccessErrorable<LoginDisconnect>(LoginDisconnect(reason));
    }

    ~LoginDisconnect() override = default;

    Errorable<bool> Write(const ProtocolVersion* version, ByteBuffer* buffer) const override {
      buffer->WriteString(reason);
      return SuccessErrorable<bool>(true);
    }

    uint32_t GetOrdinal() const override {
      return PACKET_ORDINAL;
    }

    [[nodiscard]] const std::string& GetReason() const {
      return reason;
    }
  };
}
