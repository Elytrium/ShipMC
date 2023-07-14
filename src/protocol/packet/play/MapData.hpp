#pragma once

#include "../../../../lib/ShipNet/src/utils/ordinal/OrdinalRegistry.hpp"
#include <string>
#include <utility>

namespace Ship {

  class MapIcon {
   private:
    uint32_t type{};
    uint8_t x{};
    uint8_t z{};
    uint8_t direction{};
    std::optional<std::string> displayName;

   public:
    MapIcon() = default;

    MapIcon(uint32_t type, uint8_t x, uint8_t z, uint8_t direction)
      : type(type), x(x), z(z), direction(direction) {
    }

    MapIcon(uint32_t type, uint8_t x, uint8_t z, uint8_t direction, std::string displayName)
      : type(type), x(x), z(z), direction(direction), displayName(std::move(displayName)) {
    }

    MapIcon(uint32_t type, uint8_t x, uint8_t z, uint8_t direction, std::optional<std::string> displayName)
      : type(type), x(x), z(z), direction(direction), displayName(std::move(displayName)) {
    }

    static Errorable<MapIcon> Instantiate(const PacketHolder& holder);

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

  CreateInvalidArgumentErrorable(InvalidMapIconErrorable, MapIcon, "Invalid MapIcon read");
  
  Errorable<MapIcon> MapIcon::Instantiate(const PacketHolder& holder) {
    ByteBuffer* buffer = holder.GetCurrentBuffer();
    const ProtocolVersion* version = holder.GetVersion();
    if (version >= &MinecraftProtocolVersion::MINECRAFT_1_13) {
      ProceedErrorable(type, uint32_t, buffer->ReadVarInt(), InvalidMapIconErrorable(buffer->GetReadableBytes()))
      ProceedErrorable(x, uint8_t, buffer->ReadByte(), InvalidMapIconErrorable(buffer->GetReadableBytes()))
      ProceedErrorable(z, uint8_t, buffer->ReadByte(), InvalidMapIconErrorable(buffer->GetReadableBytes()))
      ProceedErrorable(direction, uint8_t, buffer->ReadByte(), InvalidMapIconErrorable(buffer->GetReadableBytes()))
      std::optional<std::string> displayName;

      ProceedErrorable(hasDisplayName, bool, buffer->ReadBoolean(), InvalidMapIconErrorable(buffer->GetReadableBytes()))
      if (hasDisplayName) {
        SetFromErrorable(displayName, std::string, buffer->ReadString(), InvalidMapIconErrorable(buffer->GetReadableBytes()))
      }

      return SuccessErrorable<MapIcon>(MapIcon(type, x, z, direction, displayName));
    } else {
      ProceedErrorable(directionAndType, uint8_t, buffer->ReadByte(), InvalidMapIconErrorable(buffer->GetReadableBytes()))
      uint8_t direction = directionAndType & 0xF;
      uint32_t type = (directionAndType & 0xF) >> 4;
      ProceedErrorable(x, uint8_t, buffer->ReadByte(), InvalidMapIconErrorable(buffer->GetReadableBytes()))
      ProceedErrorable(z, uint8_t, buffer->ReadByte(), InvalidMapIconErrorable(buffer->GetReadableBytes()))
      return SuccessErrorable<MapIcon>(MapIcon(type, x, z, direction, std::nullopt));
    }
  }

  class MapData : public Packet {
   private:
    uint32_t mapId{};
    uint8_t scale{};
    bool locked{};
    bool trackingPosition{};
    std::vector<MapIcon> icons;
    uint8_t columns{};
    uint8_t rows{};
    uint8_t x{};
    uint8_t z{};
    uint32_t length{};
    uint8_t* data{};

   public:
    static inline const uint32_t PACKET_ORDINAL = OrdinalRegistry::PacketRegistry.RegisterOrdinal();

    MapData() = default;
    MapData(uint32_t mapId, uint8_t scale, bool locked, bool trackingPosition, std::vector<MapIcon> icons)
      : mapId(mapId), scale(scale), locked(locked), trackingPosition(trackingPosition), icons(std::move(icons)) {
    }

    MapData(uint32_t mapId, uint8_t scale, bool locked, bool trackingPosition, std::vector<MapIcon> icons, uint8_t columns, uint8_t rows, uint8_t x,
      uint8_t z, uint32_t length, uint8_t* data)
      : mapId(mapId), scale(scale), locked(locked), trackingPosition(trackingPosition), icons(std::move(icons)), columns(columns), rows(rows), x(x), z(z),
        length(length), data(data) {
    }

    ~MapData() override {
      delete[] data;
    }

    static Errorable<MapData> Instantiate(const PacketHolder& holder) {
      ByteBuffer* buffer = holder.GetCurrentBuffer();
      const ProtocolVersion* version = holder.GetVersion();
      ProceedErrorable(mapId, uint32_t, buffer->ReadVarInt(), InvalidPacketErrorable<MapData>(PACKET_ORDINAL))
      ProceedErrorable(scale, uint8_t, buffer->ReadByte(), InvalidPacketErrorable<MapData>(PACKET_ORDINAL))

      bool locked;
      bool trackingPosition;
      std::vector<MapIcon> icons;

      if (version >= &MinecraftProtocolVersion::MINECRAFT_1_17) {
        SetFromErrorable(locked, bool, buffer->ReadBoolean(), InvalidPacketErrorable<MapData>(PACKET_ORDINAL))
        SetFromErrorable(trackingPosition, bool, buffer->ReadBoolean(), InvalidPacketErrorable<MapData>(PACKET_ORDINAL))
      } else {
        SetFromErrorable(trackingPosition, bool, buffer->ReadBoolean(), InvalidPacketErrorable<MapData>(PACKET_ORDINAL))
        if (version >= &MinecraftProtocolVersion::MINECRAFT_1_14) {
          SetFromErrorable(locked, bool, buffer->ReadBoolean(), InvalidPacketErrorable<MapData>(PACKET_ORDINAL))
        }
      }

      ProceedErrorable(vectorSize, uint32_t, buffer->ReadVarInt(), InvalidPacketErrorable<MapData>(PACKET_ORDINAL))
      for (int i = 0; i < vectorSize; ++i) {
        ProceedErrorable(icon, MapIcon, MapIcon::Instantiate(holder), InvalidPacketErrorable<MapData>(PACKET_ORDINAL))
        icons.push_back(icon);
      }
      ProceedErrorable(columns, uint8_t, buffer->ReadByte(), InvalidPacketErrorable<MapData>(PACKET_ORDINAL))
      if (columns) {
        ProceedErrorable(rows, uint8_t, buffer->ReadByte(), InvalidPacketErrorable<MapData>(PACKET_ORDINAL))
        ProceedErrorable(x, uint8_t, buffer->ReadByte(), InvalidPacketErrorable<MapData>(PACKET_ORDINAL))
        ProceedErrorable(z, uint8_t, buffer->ReadByte(), InvalidPacketErrorable<MapData>(PACKET_ORDINAL))
        ProceedErrorable(length, uint32_t, buffer->ReadVarInt(), InvalidPacketErrorable<MapData>(PACKET_ORDINAL))
        ProceedErrorable(data, uint8_t*, buffer->ReadBytes(length), InvalidPacketErrorable<MapData>(PACKET_ORDINAL))
        return SuccessErrorable<MapData>(MapData(mapId, scale, locked, trackingPosition, icons, columns, rows, x, z, length, data));
      } else {
        return SuccessErrorable<MapData>(MapData(mapId, scale, locked, trackingPosition, icons));
      }
    }

    Errorable<bool> Write(const ProtocolVersion* version, ByteBuffer* buffer) const override {
      buffer->WriteVarInt(mapId);
      buffer->WriteByte(scale);
      if (version >= &MinecraftProtocolVersion::MINECRAFT_1_17) {
        buffer->WriteBoolean(locked);
        buffer->WriteBoolean(trackingPosition);
      } else {
        buffer->WriteBoolean(trackingPosition);
        if (version >= &MinecraftProtocolVersion::MINECRAFT_1_14) {
          buffer->WriteBoolean(locked);
        }
      }
      buffer->WriteVarInt(icons.size());
      for (const MapIcon& icon : icons) {
        if (version >= &MinecraftProtocolVersion::MINECRAFT_1_13) {
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
      return SuccessErrorable<bool>(true);
    }

    [[nodiscard]] uint32_t GetOrdinal() const override {
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
