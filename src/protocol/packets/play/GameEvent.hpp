#pragma once

#include "../../../utils/ordinal/OrdinalRegistry.hpp"
#include "../Packet.hpp"
#include <string>

namespace Ship {

  class GameEvent : public Packet {
   private:
    uint8_t event;
    float value;

   public:
    static inline const uint32_t PACKET_ORDINAL = OrdinalRegistry::PacketRegistry.RegisterOrdinal();

    GameEvent(uint8_t event, float value) : event(event), value(value) {
    }

    ~GameEvent() override = default;

    void Read(const ProtocolVersion* version, ByteBuffer* buffer) override {
      event = buffer->ReadByte();
      value = buffer->ReadFloat();
    }

    void Write(const ProtocolVersion* version, ByteBuffer* buffer) override {
      buffer->WriteByte(event);
      buffer->WriteFloat(value);
    }

    uint32_t GetOrdinal() override {
      return PACKET_ORDINAL;
    }

    [[nodiscard]] uint8_t GetEvent() const {
      return event;
    }

    [[nodiscard]] float GetValue() const {
      return value;
    }
  };
}
