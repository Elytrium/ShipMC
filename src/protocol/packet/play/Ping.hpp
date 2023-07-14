#pragma once

#include "ShipNet/utils/ordinal/OrdinalRegistry.hpp"
#include <string>

namespace Ship {

  class Ping : public Packet {
   private:
    uint32_t id{};
    
   public:
    static inline const uint32_t PACKET_ORDINAL = OrdinalRegistry::PacketRegistry.RegisterOrdinal();

    Ping() = default;
    explicit Ping(uint32_t id) : id(id) {
    }

    ~Ping() override = default;

    static Errorable<Ping> Instantiate(const PacketHolder& holder) {
      ByteBuffer* buffer = holder.GetCurrentBuffer();
      ProceedErrorable(id, uint32_t, buffer->ReadInt(), InvalidPacketErrorable<Ping>(PACKET_ORDINAL))
      return SuccessErrorable<Ping>(Ping(id));
    }

    Errorable<bool> Write(const ProtocolVersion* version, ByteBuffer* buffer) const override {
      buffer->WriteInt(id);
      return SuccessErrorable<bool>(true);
    }

    [[nodiscard]] uint32_t GetOrdinal() const override {
      return PACKET_ORDINAL;
    }

    [[nodiscard]] uint32_t GetId() const {
      return id;
    }
  };
}
