#pragma once

#include "ShipNet/utils/ordinal/OrdinalRegistry.hpp"
#include <string>

namespace Ship {

  class KeepAlive : public Packet {
   private:
    uint64_t id{};

   public:
    static inline const uint32_t PACKET_ORDINAL = OrdinalRegistry::PacketRegistry.RegisterOrdinal();

    KeepAlive() = default;
    explicit KeepAlive(uint64_t id) : id(id) {
    }

    ~KeepAlive() override = default;

    static Errorable<KeepAlive> Instantiate(const PacketHolder& holder) {
      ByteBuffer* buffer = holder.GetCurrentBuffer();
      ProceedErrorable(id, uint64_t, buffer->ReadLong(), InvalidPacketErrorable<KeepAlive>(PACKET_ORDINAL))
      return SuccessErrorable<KeepAlive>(KeepAlive(id));
    }

    Errorable<bool> Write(const ProtocolVersion* version, ByteBuffer* buffer) const override {
      buffer->WriteLong(id);
      return SuccessErrorable<bool>(true);
    }

    [[nodiscard]] uint32_t GetOrdinal() const override {
      return PACKET_ORDINAL;
    }

    [[nodiscard]] uint64_t GetId() const {
      return id;
    }
  };
}
