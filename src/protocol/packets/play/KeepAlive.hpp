#pragma once

#include "../../../utils/ordinal/OrdinalRegistry.hpp"
#include "../Packet.hpp"
#include <string>

namespace Ship {

  class KeepAlive : public Packet {
   private:
    uint64_t id;

   public:
    static inline const uint32_t PACKET_ORDINAL = OrdinalRegistry::PacketRegistry.RegisterOrdinal();

    explicit KeepAlive(uint64_t id) : id(id) {
    }

    ~KeepAlive() override = default;

    explicit KeepAlive(const PacketHolder& holder) {
      ByteBuffer* buffer = holder.GetCurrentBuffer();
      id = buffer->ReadLong();
    }

    void Write(const ProtocolVersion* version, ByteBuffer* buffer) const override {
      buffer->WriteLong(id);
    }

    uint32_t GetOrdinal() const override {
      return PACKET_ORDINAL;
    }

    [[nodiscard]] uint64_t GetId() const {
      return id;
    }
  };
}
