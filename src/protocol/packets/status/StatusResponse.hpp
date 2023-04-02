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

    StatusResponse() = default;

    explicit StatusResponse(std::string status) : status(std::move(status)) {
    }

    static Errorable<StatusResponse> Instantiate(const PacketHolder& holder) {
      ByteBuffer* buffer = holder.GetCurrentBuffer();
      ProceedErrorable(status, std::string, buffer->ReadString(), InvalidPacketErrorable<StatusResponse>(PACKET_ORDINAL))
      return SuccessErrorable<StatusResponse>(StatusResponse(status));
    }

    ~StatusResponse() override = default;

    void Write(const ProtocolVersion* version, ByteBuffer* buffer) const override {
      buffer->WriteString(status);
    }

    [[nodiscard]] uint32_t GetOrdinal() const override {
      return PACKET_ORDINAL;
    }

    [[nodiscard]] const std::string& GetStatus() const {
      return status;
    }
  };
}
