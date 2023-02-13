#pragma once

#include "../../../utils/ordinal/OrdinalRegistry.hpp"
#include "../Packet.hpp"
#include <string>

namespace Ship {

  class Ping : public Packet {
   private:
    uint32_t id;
    
   public:
    static inline const uint32_t PACKET_ORDINAL = OrdinalRegistry::PacketRegistry.RegisterOrdinal();

    explicit Ping(uint32_t id) : id(id) {
    }

    ~Ping() override = default;

    void Read(const ProtocolVersion* version, ByteBuffer* buffer) override {
      id = buffer->ReadInt();
    }

    void Write(const ProtocolVersion* version, ByteBuffer* buffer) override {
      buffer->WriteInt(id);
    }

    uint32_t GetOrdinal() override {
      return PACKET_ORDINAL;
    }

    [[nodiscard]] uint32_t GetId() const {
      return id;
    }
  };
}
