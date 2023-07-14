#pragma once

#include "ShipNet/utils/ordinal/OrdinalRegistry.hpp"
#include <string>

namespace Ship {

  class GameEvent : public Packet {
   private:
    uint8_t event{};
    float value{};

   public:
    static inline const uint32_t PACKET_ORDINAL = OrdinalRegistry::PacketRegistry.RegisterOrdinal();

    GameEvent() = default;
    GameEvent(uint8_t event, float value) : event(event), value(value) {
    }

    ~GameEvent() override = default;

    static Errorable<GameEvent> Instantiate(const PacketHolder& holder) {
      ByteBuffer* buffer = holder.GetCurrentBuffer();
      ProceedErrorable(event, uint8_t, buffer->ReadByte(), InvalidPacketErrorable<GameEvent>(PACKET_ORDINAL))
      ProceedErrorable(value, float, buffer->ReadFloat(), InvalidPacketErrorable<GameEvent>(PACKET_ORDINAL))
      return SuccessErrorable<GameEvent>(GameEvent(event, value));
    }

    Errorable<bool> Write(const ProtocolVersion* version, ByteBuffer* buffer) const override {
      buffer->WriteByte(event);
      buffer->WriteFloat(value);
      return SuccessErrorable<bool>(true);
    }

    [[nodiscard]] uint32_t GetOrdinal() const override {
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
