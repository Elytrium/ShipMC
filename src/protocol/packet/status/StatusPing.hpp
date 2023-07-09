#pragma once

#include "../../../../lib/ShipNet/src/utils/ordinal/OrdinalRegistry.hpp"
#include <string>

namespace Ship {

  class StatusPing : public Packet {
   private:
    uint64_t id;

   public:
    static inline const uint32_t PACKET_ORDINAL = OrdinalRegistry::PacketRegistry.RegisterOrdinal();

    StatusPing() = default;

    explicit StatusPing(uint64_t id) : id(id) {}

    ~StatusPing() override = default;

    static Errorable<StatusPing> Instantiate(const PacketHolder& holder) {
      ByteBuffer* buffer = holder.GetCurrentBuffer();
      ProceedErrorable(id, uint64_t, buffer->ReadLong(), InvalidPacketErrorable<StatusPing>(PACKET_ORDINAL))
      return SuccessErrorable<StatusPing>(StatusPing(id));
    }

    void Write(const ProtocolVersion* version, ByteBuffer* buffer) const override {
      buffer->WriteLong(id);
    }

    [[nodiscard]] uint32_t GetOrdinal() const override {
      return PACKET_ORDINAL;
    }

    [[nodiscard]] uint64_t GetId() const {
      return id;
    }
  };
}
