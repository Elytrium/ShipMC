#pragma once

#include "../../../utils/ordinal/OrdinalRegistry.hpp"
#include "../Packet.hpp"
#include <string>

namespace Ship {

  class Disconnect : public Packet {
   private:
    std::string reason;

   public:
    static inline const uint32_t PACKET_ORDINAL = OrdinalRegistry::PacketRegistry.RegisterOrdinal();

    explicit Disconnect(std::string reason) : reason(std::move(reason)) {
    }

    ~Disconnect() override = default;

    void Read(const ProtocolVersion* version, ByteBuffer* buffer) override {
      reason = buffer->ReadString();
    }

    void Write(const ProtocolVersion* version, ByteBuffer* buffer) override {
      buffer->WriteString(reason);
    }

    uint32_t GetOrdinal() override {
      return PACKET_ORDINAL;
    }

    [[nodiscard]] const std::string& GetReason() const {
      return reason;
    }
  };
}
