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

    void Read(const ProtocolVersion* version, ByteBuffer* buffer) override {
      id = buffer->ReadLong();
    }

    void Write(const ProtocolVersion* version, ByteBuffer* buffer) override {
      buffer->WriteLong(id);
    }

    uint32_t Size(const ProtocolVersion* version) override {
      return (INT64_WIDTH / INT8_WIDTH);
    }

    uint32_t GetOrdinal() override {
      return PACKET_ORDINAL;
    }

    [[nodiscard]] uint64_t GetId() const {
      return id;
    }
  };
}
