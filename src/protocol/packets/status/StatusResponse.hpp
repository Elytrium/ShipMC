#pragma once

#include "../../../utils/ordinal/OrdinalRegistry.hpp"
#include "../Packet.hpp"
#include <string>
#include <utility>

namespace Ship {

  class StatusResponse : public Packet {
   private:
    std::string status;

   public:
    static inline const uint32_t PACKET_ORDINAL = OrdinalRegistry::PacketRegistry.RegisterOrdinal();

    explicit StatusResponse(std::string status) : status(std::move(status)) {
    }

    ~StatusResponse() override = default;

    void Read(const ProtocolVersion* version, ByteBuffer* buffer) override {
      status = buffer->ReadString();
    }

    void Write(const ProtocolVersion* version, ByteBuffer* buffer) override {
      buffer->WriteString(status);
    }

    uint32_t GetOrdinal() override {
      return PACKET_ORDINAL;
    }

    [[nodiscard]] const std::string& GetStatus() const {
      return status;
    }
  };
}
