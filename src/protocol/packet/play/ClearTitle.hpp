#pragma once


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

    explicit ClearTitle(const PacketHolder& holder) {
      ByteBuffer* buffer = holder.GetCurrentBuffer();
      reset = buffer->ReadBoolean();
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
