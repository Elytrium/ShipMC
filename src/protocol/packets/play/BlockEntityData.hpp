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

    ~BlockEntityData() override {
      delete data;
    }

    void Read(const ProtocolVersion* version, ByteBuffer* buffer) override {
      buffer->ReadPosition(locationX, locationY, locationZ);
      if (version >= &ProtocolVersion::MINECRAFT_1_18) {
        type = buffer->ReadVarInt();
      } else {
        type = buffer->ReadByte();
      }

      delete data;
      data = ProtocolUtils::ReadNBT(buffer);
    }

    void Write(const ProtocolVersion* version, ByteBuffer* buffer) override {
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

    uint32_t Size(const ProtocolVersion* version) override {
      if (version >= &ProtocolVersion::MINECRAFT_1_18) {
        return ByteBuffer::POSITION_SIZE + ByteBuffer::VarIntBytes(type) + (data ? data->GetSize() : 1);
      } else {
        return ByteBuffer::POSITION_SIZE + ByteBuffer::BYTE_SIZE + (data ? data->GetSize() : 1);
      }
    }

    uint32_t GetOrdinal() override {
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
