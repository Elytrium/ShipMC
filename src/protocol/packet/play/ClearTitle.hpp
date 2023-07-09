#pragma once

#include "../../../../lib/ShipNet/src/utils/ordinal/OrdinalRegistry.hpp"
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

    static Errorable<ClearTitle> Instantiate(const PacketHolder& holder) {
      ByteBuffer* buffer = holder.GetCurrentBuffer();
      ProceedErrorable(reset, bool, buffer->ReadBoolean(), InvalidPacketErrorable<>(PACKET_ORDINAL))
    }

    void Write(const ProtocolVersion* version, ByteBuffer* buffer) const override {
      buffer->WriteBoolean(reset);
    }

    uint32_t GetOrdinal() const override {
      return PACKET_ORDINAL;
    }

    [[nodiscard]] bool IsReset() const {
      return reset;
    }
  };
}
