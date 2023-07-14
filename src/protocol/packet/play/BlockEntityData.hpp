#pragma once

#include "ShipNet/utils/ordinal/OrdinalRegistry.hpp"
#include "../../ProtocolUtils.hpp"
#include "../../data/nbt/NBT.hpp"
#include <string>

namespace Ship {

  class BlockEntityData : public Packet {
   private:
    Position location;
    uint32_t type;
    NBT* data;

   public:
    static inline const uint32_t PACKET_ORDINAL = OrdinalRegistry::PacketRegistry.RegisterOrdinal();

    BlockEntityData() = default;

    BlockEntityData(Position location, uint32_t type, NBT* data)
      : location(location), type(type), data(data) {
    }

    static Errorable<BlockEntityData> Instantiate(const PacketHolder& holder) {
      ByteBuffer* buffer = holder.GetCurrentBuffer();
      const ProtocolVersion* version = holder.GetVersion();
      ProceedErrorable(location, Position, ProtocolUtils::ReadPosition(holder.GetVersion(), buffer), InvalidPacketErrorable<BlockEntityData>(PACKET_ORDINAL))
      uint32_t type;
      if (version >= &MinecraftProtocolVersion::MINECRAFT_1_18) {
        SetFromErrorable(type, uint32_t, buffer->ReadVarInt(), InvalidPacketErrorable<BlockEntityData>(PACKET_ORDINAL))
      } else {
        SetFromErrorable(type, uint8_t, buffer->ReadByte(), InvalidPacketErrorable<BlockEntityData>(PACKET_ORDINAL))
      }

      ProceedErrorable(data, NBT*, ProtocolUtils::ReadNBT(buffer), InvalidPacketErrorable<BlockEntityData>(PACKET_ORDINAL));
      return SuccessErrorable<BlockEntityData>({location, type, data});
    }

    ~BlockEntityData() override {
      delete data;
    }

    Errorable<bool> Write(const ProtocolVersion* version, ByteBuffer* buffer) const override {
      ProtocolUtils::WritePosition(version, buffer, location);
      if (version >= &MinecraftProtocolVersion::MINECRAFT_1_18) {
        buffer->WriteVarInt(type);
      } else {
        buffer->WriteByte(type);
      }

      if (data) {
        ProtocolUtils::WriteNBT(buffer, data);
      } else {
        buffer->WriteByte(0);
      }
      return SuccessErrorable<bool>(true);
    }

    [[nodiscard]] uint32_t GetOrdinal() const override {
      return PACKET_ORDINAL;
    }

    [[nodiscard]] Position GetLocation() const {
      return location;
    }

    [[nodiscard]] uint32_t GetType() const {
      return type;
    }

    [[nodiscard]] NBT* GetData() const {
      return data;
    }
  };
}
