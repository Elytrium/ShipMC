#pragma once

#include "../../../../lib/ShipNet/src/utils/ordinal/OrdinalRegistry.hpp"
#include <string>

namespace Ship {

  class WorldEvent : public Packet {
   private:
    uint32_t event;
    Position location;
    uint32_t data;
    bool disableRelativeVolume;

   public:
    static inline const uint32_t PACKET_ORDINAL = OrdinalRegistry::PacketRegistry.RegisterOrdinal();

    WorldEvent(uint32_t event, Position location, uint32_t data, bool disableRelativeVolume)
      : event(event), location(location), data(data), disableRelativeVolume(disableRelativeVolume) {
    }

    ~WorldEvent() override = default;

    static Errorable<WorldEvent> Instantiate(const PacketHolder& holder) {
      ByteBuffer* buffer = holder.GetCurrentBuffer();
      event = buffer->ReadInt();
      ProceedErrorable(location, Position, ProtocolUtils::ReadPosition(holder.GetVersion(), buffer), InvalidPacketErrorable<>(PACKET_ORDINAL));
      data = buffer->ReadInt();
      ProceedErrorable(disableRelativeVolume, bool, buffer->ReadBoolean(), InvalidPacketErrorable<>(PACKET_ORDINAL))
    }

    Errorable<bool> Write(const ProtocolVersion* version, ByteBuffer* buffer) const override {
      buffer->WriteInt(event);
      ProtocolUtils::WritePosition(version, buffer, location);
      buffer->WriteInt(data);
      buffer->WriteBoolean(disableRelativeVolume);
      return SuccessErrorable<bool>(true);
    }

    uint32_t GetOrdinal() const override {
      return PACKET_ORDINAL;
    }

    [[nodiscard]] uint32_t GetEvent() const {
      return event;
    }

    [[nodiscard]] Position GetLocation() const {
      return location;
    }

    [[nodiscard]] uint32_t GetData() const {
      return data;
    }

    [[nodiscard]] bool IsDisableRelativeVolume() const {
      return disableRelativeVolume;
    }
  };
}
