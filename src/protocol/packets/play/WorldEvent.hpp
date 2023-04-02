#pragma once

#include "../../../utils/ordinal/OrdinalRegistry.hpp"
#include "../Packet.hpp"
#include <string>

namespace Ship {

  class WorldEvent : public Packet {
   private:
    uint32_t event;
    int locationX;
    int locationY;
    int locationZ;
    uint32_t data;
    bool disableRelativeVolume;

   public:
    static inline const uint32_t PACKET_ORDINAL = OrdinalRegistry::PacketRegistry.RegisterOrdinal();

    WorldEvent(uint32_t event, int locationX, int locationY, int locationZ, uint32_t data, bool disableRelativeVolume)
      : event(event), locationX(locationX), locationY(locationY), locationZ(locationZ), data(data), disableRelativeVolume(disableRelativeVolume) {
    }

    ~WorldEvent() override = default;

    static Errorable<WorldEvent> Instantiate(const PacketHolder& holder) {
      ByteBuffer* buffer = holder.GetCurrentBuffer();
      event = buffer->ReadInt();
      buffer->ReadPosition(locationX, locationY, locationZ);
      data = buffer->ReadInt();
      ProceedErrorable(disableRelativeVolume, bool, buffer->ReadBoolean(), InvalidPacketErrorable<>(PACKET_ORDINAL))
    }

    void Write(const ProtocolVersion* version, ByteBuffer* buffer) const override {
      buffer->WriteInt(event);
      buffer->WritePosition(locationX, locationY, locationZ);
      buffer->WriteInt(data);
      buffer->WriteBoolean(disableRelativeVolume);
    }

    uint32_t GetOrdinal() const override {
      return PACKET_ORDINAL;
    }

    [[nodiscard]] uint32_t GetEvent() const {
      return event;
    }

    [[nodiscard]] int GetLocationX() const {
      return locationX;
    }

    [[nodiscard]] int GetLocationY() const {
      return locationY;
    }

    [[nodiscard]] int GetLocationZ() const {
      return locationZ;
    }

    [[nodiscard]] uint32_t GetData() const {
      return data;
    }

    [[nodiscard]] bool IsDisableRelativeVolume() const {
      return disableRelativeVolume;
    }
  };
}
