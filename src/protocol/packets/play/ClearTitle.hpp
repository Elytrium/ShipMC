#pragma once

#include "../../../utils/ordinal/OrdinalRegistry.hpp"
#include "../Packet.hpp"
#include <string>

namespace Ship {

  class ClearTitle : public Packet {
   private:
    bool reset;

   public:
    static inline const uint32_t PACKET_ORDINAL = OrdinalRegistry::PacketRegistry.RegisterOrdinal();

    explicit ClearTitle(bool reset) : reset(reset) {
    }

    ~ClearTitle() override = default;

    void Read(const ProtocolVersion* version, ByteBuffer* buffer) override {
      reset = buffer->ReadBoolean();
    }

    void Write(const ProtocolVersion* version, ByteBuffer* buffer) override {
      buffer->WriteBoolean(reset);
    }

    uint32_t GetOrdinal() override {
      return PACKET_ORDINAL;
    }

    [[nodiscard]] bool IsReset() const {
      return reset;
    }
  };
}
