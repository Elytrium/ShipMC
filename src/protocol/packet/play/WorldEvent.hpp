#pragma once

#include "../../../../lib/ShipNet/src/utils/ordinal/OrdinalRegistry.hpp"
#include <string>

namespace Ship {

  class WorldEvent : public Packet {
   private:
    uint32_t event{};
    Position location{};
    uint32_t data{};
    bool disableRelativeVolume{};

   public:
    static inline const uint32_t PACKET_ORDINAL = OrdinalRegistry::PacketRegistry.RegisterOrdinal();

    WorldEvent() = default;
    WorldEvent(uint32_t event, Position location, uint32_t data, bool disableRelativeVolume)
      : event(event), location(location), data(data), disableRelativeVolume(disableRelativeVolume) {
    }

    ~WorldEvent() override = default;

    static Errorable<WorldEvent> Instantiate(const PacketHolder& holder) {
      ByteBuffer* buffer = holder.GetCurrentBuffer();
      ProceedErrorable(event, uint32_t, buffer->ReadInt(), InvalidPacketErrorable<WorldEvent>(PACKET_ORDINAL))
      ProceedErrorable(location, Position, ProtocolUtils::ReadPosition(holder.GetVersion(), buffer), InvalidPacketErrorable<WorldEvent>(PACKET_ORDINAL));
      ProceedErrorable(data, uint32_t, buffer->ReadInt(), InvalidPacketErrorable<WorldEvent>(PACKET_ORDINAL))
      ProceedErrorable(disableRelativeVolume, bool, buffer->ReadBoolean(), InvalidPacketErrorable<WorldEvent>(PACKET_ORDINAL))
      return SuccessErrorable<WorldEvent>(WorldEvent(event, location, data, disableRelativeVolume));
    }

    Errorable<bool> Write(const ProtocolVersion* version, ByteBuffer* buffer) const override {
      buffer->WriteInt(event);
      ProtocolUtils::WritePosition(version, buffer, location);
      buffer->WriteInt(data);
      buffer->WriteBoolean(disableRelativeVolume);
      return SuccessErrorable<bool>(true);
    }

    [[nodiscard]] uint32_t GetOrdinal() const override {
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
