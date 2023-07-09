#pragma once

#include <string>
#include <utility>

namespace Ship {

  class LoginDisconnect : public Packet {
   private:
    std::string reason;

   public:
    static inline const uint32_t PACKET_ORDINAL = OrdinalRegistry::PacketRegistry.RegisterOrdinal();

    explicit LoginDisconnect(std::string reason) : reason(std::move(reason)) {
    }

    explicit LoginDisconnect(const PacketHolder& holder) {
      ByteBuffer* buffer = holder.GetCurrentBuffer();
      reason = buffer->ReadString();
    }

    ~LoginDisconnect() override = default;

    void Write(const ProtocolVersion* version, ByteBuffer* buffer) const override {
      buffer->WriteString(reason);
    }

    uint32_t GetOrdinal() const override {
      return PACKET_ORDINAL;
    }

    [[nodiscard]] const std::string& GetReason() const {
      return reason;
    }
  };
}
