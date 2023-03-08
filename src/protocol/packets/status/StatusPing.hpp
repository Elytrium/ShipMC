#pragma once

#include "../../../utils/ordinal/OrdinalRegistry.hpp"
#include "../Packet.hpp"
#include <string>

namespace Ship {

  class StatusPing : public Packet {
   private:
    uint64_t id;

   public:
    static inline const uint32_t PACKET_ORDINAL = OrdinalRegistry::PacketRegistry.RegisterOrdinal();

    explicit StatusPing(uint64_t id) : id(id) {}

    ~StatusPing() override = default;

    StatusPing(const ProtocolVersion* version, ByteBuffer* buffer) {
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
