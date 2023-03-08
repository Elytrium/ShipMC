#pragma once

#include "../../../utils/ordinal/OrdinalRegistry.hpp"
#include "../../ProtocolUtils.hpp"
#include "../../data/nbt/NBT.hpp"
#include "../Packet.hpp"
#include <string>

namespace Ship {

  class BlockEntityData : public Packet {
   private:
    int locationX;
    int locationY;
    int locationZ;
    uint32_t type;
    NBT* data;

   public:
    static inline const uint32_t PACKET_ORDINAL = OrdinalRegistry::PacketRegistry.RegisterOrdinal();

    BlockEntityData(int locationX, int locationY, int locationZ, uint32_t type, NBT* data)
      : locationX(locationX), locationY(locationY), locationZ(locationZ), type(type), data(data) {
    }

    BlockEntityData(const ProtocolVersion* version, ByteBuffer* buffer) {
      buffer->ReadPosition(locationX, locationY, locationZ);
      if (version >= &ProtocolVersion::MINECRAFT_1_18) {
        type = buffer->ReadVarInt();
      } else {
        type = buffer->ReadByte();
      }

      delete data;
      data = ProtocolUtils::ReadNBT(buffer);
    }

    ~BlockEntityData() override {
      delete data;
    }

    void Write(const ProtocolVersion* version, ByteBuffer* buffer) const override {
      buffer->WritePosition(locationX, locationY, locationZ);
      if (version >= &ProtocolVersion::MINECRAFT_1_18) {
        buffer->WriteVarInt(type);
      } else {
        buffer->WriteByte(type);
      }

      if (data) {
        ProtocolUtils::WriteNBT(buffer, data);
      } else {
        buffer->WriteByte(0);
      }
    }

    uint32_t GetOrdinal() const override {
      return PACKET_ORDINAL;
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

    [[nodiscard]] uint32_t GetType() const {
      return type;
    }

    [[nodiscard]] NBT* GetData() const {
      return data;
    }
  };
}
