#pragma once

#include "../../../utils/ordinal/OrdinalRegistry.hpp"
#include "../Packet.hpp"
#include <string>
#include <utility>

namespace Ship {

  class MapIcon {
   private:
    uint32_t type;
    uint8_t x;
    uint8_t z;
    uint8_t direction;
    std::optional<std::string> displayName;

   public:
    MapIcon(uint32_t type, uint8_t x, uint8_t z, uint8_t direction, std::optional<std::string> displayName)
      : type(type), x(x), z(z), direction(direction), displayName(std::move(displayName)) {
    }

    MapIcon() : MapIcon(0, 0, 0, 0, {}) {
    }

    explicit MapIcon(const PacketHolder& holder) {
      ByteBuffer* buffer = holder.GetCurrentBuffer();
      const ProtocolVersion* version = holder.GetVersion();
      if (version >= &ProtocolVersion::MINECRAFT_1_13) {
        type = buffer->ReadVarInt();
        x = buffer->ReadByte();
        z = buffer->ReadByte();
        direction = buffer->ReadByte();
        if (buffer->ReadBoolean()) {
          displayName = buffer->ReadString();
        } else {
          displayName = std::nullopt;
        }
      } else {
        uint8_t directionAndType = buffer->ReadByte();
        direction = directionAndType & 0xF;
        type = (directionAndType & 0xF) >> 4;
        x = buffer->ReadByte();
        z = buffer->ReadByte();
        displayName = std::nullopt;
      }
    }

    [[nodiscard]] uint32_t GetType() const {
      return type;
    }

    void SetType(uint32_t value) {
      type = value;
    }

    [[nodiscard]] uint8_t GetX() const {
      return x;
    }

    void SetX(uint8_t value) {
      x = value;
    }

    [[nodiscard]] uint8_t GetZ() const {
      return z;
    }

    void SetZ(uint8_t value) {
      z = value;
    }

    [[nodiscard]] uint8_t GetDirection() const {
      return direction;
    }

    void SetDirection(uint8_t value) {
      direction = value;
    }

    [[nodiscard]] const std::optional<std::string>& GetDisplayName() const {
      return displayName;
    }

    void SetDisplayName(const std::optional<std::string>& value) {
      displayName = value;
    }
  };

  class MapData : public Packet {
   private:
    uint32_t mapId;
    uint8_t scale;
    bool locked;
    bool trackingPosition;
    std::vector<MapIcon> icons;
    uint8_t columns;
    uint8_t rows;
    uint8_t x;
    uint8_t z;
    uint32_t length;
    uint8_t* data;

   public:
    static inline const uint32_t PACKET_ORDINAL = OrdinalRegistry::PacketRegistry.RegisterOrdinal();

    MapData(uint32_t mapId, uint8_t scale, bool locked, bool trackingPosition, std::vector<MapIcon> icons, uint8_t columns, uint8_t rows, uint8_t x,
      uint8_t z, uint32_t length, uint8_t* data)
      : mapId(mapId), scale(scale), locked(locked), trackingPosition(trackingPosition), icons(std::move(icons)), columns(columns), rows(rows), x(x), z(z),
        length(length), data(data) {
    }

    ~MapData() override {
      delete[] data;
    }

    explicit MapData(const PacketHolder& holder) {
      ByteBuffer* buffer = holder.GetCurrentBuffer();
      const ProtocolVersion* version = holder.GetVersion();
      mapId = buffer->ReadVarInt();
      scale = buffer->ReadByte();
      if (version >= &ProtocolVersion::MINECRAFT_1_17) {
        locked = buffer->ReadBoolean();
        trackingPosition = buffer->ReadBoolean();
      } else {
        trackingPosition = buffer->ReadBoolean();
        if (version >= &ProtocolVersion::MINECRAFT_1_14) {
          locked = buffer->ReadBoolean();
        }
      }
      uint32_t vectorSize = buffer->ReadVarInt();
      for (int i = 0; i < vectorSize; ++i) {
        icons.emplace_back(holder);
      }
      columns = buffer->ReadByte();
      if (columns) {
        rows = buffer->ReadByte();
        x = buffer->ReadByte();
        z = buffer->ReadByte();
        length = buffer->ReadVarInt();
        delete[] data;
        data = buffer->ReadBytes(length);
      }
    }

    void Write(const ProtocolVersion* version, ByteBuffer* buffer) const override {
      buffer->WriteVarInt(mapId);
      buffer->WriteByte(scale);
      if (version >= &ProtocolVersion::MINECRAFT_1_17) {
        buffer->WriteBoolean(locked);
        buffer->WriteBoolean(trackingPosition);
      } else {
        buffer->WriteBoolean(trackingPosition);
        if (version >= &ProtocolVersion::MINECRAFT_1_14) {
          buffer->WriteBoolean(locked);
        }
      }
      buffer->WriteVarInt(icons.size());
      for (const MapIcon& icon : icons) {
        if (version >= &ProtocolVersion::MINECRAFT_1_13) {
          buffer->WriteVarInt(icon.GetType());
          buffer->WriteByte(icon.GetX());
          buffer->WriteByte(icon.GetZ());
          buffer->WriteByte(icon.GetDirection());
          buffer->WriteBoolean(icon.GetDisplayName().has_value());
          if (icon.GetDisplayName()) {
            buffer->WriteString(icon.GetDisplayName().value());
          }
        } else {
          buffer->WriteByte((icon.GetType() & 0xF) << 4 | (icon.GetDirection() & 0xF));
          buffer->WriteByte(icon.GetX());
          buffer->WriteByte(icon.GetZ());
        }
      }
      buffer->WriteByte(columns);
      if (columns) {
        buffer->WriteByte(rows);
        buffer->WriteByte(x);
        buffer->WriteByte(z);
        buffer->WriteVarInt(length);
        buffer->WriteBytes(data, length);
      }
    }

    uint32_t GetOrdinal() const override {
      return PACKET_ORDINAL;
    }

    [[nodiscard]] uint32_t GetMapId() const {
      return mapId;
    }

    [[nodiscard]] uint8_t GetScale() const {
      return scale;
    }

    [[nodiscard]] bool IsLocked() const {
      return locked;
    }

    [[nodiscard]] bool IsTrackingPosition() const {
      return trackingPosition;
    }

    [[nodiscard]] const std::vector<MapIcon>& GetIcons() const {
      return icons;
    }

    [[nodiscard]] uint8_t GetColumns() const {
      return columns;
    }

    [[nodiscard]] uint8_t GetRows() const {
      return rows;
    }

    [[nodiscard]] uint8_t GetX() const {
      return x;
    }

    [[nodiscard]] uint8_t GetZ() const {
      return z;
    }

    [[nodiscard]] uint32_t GetLength() const {
      return length;
    }

    [[nodiscard]] uint8_t* GetData() const {
      return data;
    }
  };
}
