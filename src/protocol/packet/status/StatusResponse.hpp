#pragma once


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

    explicit StatusResponse(const PacketHolder& holder) {
      ByteBuffer* buffer = holder.GetCurrentBuffer();
      status = buffer->ReadString();
    }

    ~StatusResponse() override = default;

    void Write(const ProtocolVersion* version, ByteBuffer* buffer) const override {
      buffer->WriteString(status);
    }

    uint32_t GetOrdinal() const override {
      return PACKET_ORDINAL;
    }

    [[nodiscard]] const std::string& GetStatus() const {
      return status;
    }
  };
}
