#pragma once

#include "../utils/exceptions/InvalidArgumentException.hpp"
#include "data/profile/GameProfile.hpp"
#include "data/uuid/UUID.hpp"
#include <deque>
#include <string>
#include <utility>
#include <vector>

namespace Ship {

  class ProtocolVersion {
   private:
    uint32_t ordinal;
    uint32_t packetIDOrdinal;
    uint32_t protocolID;
    std::string displayVersion;

   public:
    static const ProtocolVersion UNKNOWN;
    static const ProtocolVersion MINECRAFT_1_12_2;
    static const ProtocolVersion MINECRAFT_1_13;
    static const ProtocolVersion MINECRAFT_1_13_1;
    static const ProtocolVersion MINECRAFT_1_13_2;
    static const ProtocolVersion MINECRAFT_1_14;
    static const ProtocolVersion MINECRAFT_1_14_1;
    static const ProtocolVersion MINECRAFT_1_14_2;
    static const ProtocolVersion MINECRAFT_1_14_3;
    static const ProtocolVersion MINECRAFT_1_14_4;
    static const ProtocolVersion MINECRAFT_1_15;
    static const ProtocolVersion MINECRAFT_1_15_1;
    static const ProtocolVersion MINECRAFT_1_15_2;
    static const ProtocolVersion MINECRAFT_1_16_2;
    static const ProtocolVersion MINECRAFT_1_16_3;
    static const ProtocolVersion MINECRAFT_1_16_4;
    static const ProtocolVersion MINECRAFT_1_17;
    static const ProtocolVersion MINECRAFT_1_17_1;
    static const ProtocolVersion MINECRAFT_1_18;
    static const ProtocolVersion MINECRAFT_1_18_2;
    static const ProtocolVersion MINECRAFT_1_19;
    static const ProtocolVersion MINECRAFT_1_19_1;

    static const ProtocolVersion MINIMUM_VERSION;
    static const ProtocolVersion MAXIMUM_VERSION;

    ProtocolVersion();
    ProtocolVersion(uint32_t ordinal, uint32_t packet_id_ordinal, uint32_t protocol_id, std::string display_version);

    [[nodiscard]] uint32_t GetOrdinal() const;
    [[nodiscard]] uint32_t GetPacketIDOrdinal() const;
    [[nodiscard]] uint32_t GetProtocolID() const;
    [[nodiscard]] const std::string& GetDisplayVersion() const;

    bool operator<(ProtocolVersion * other) const {
      return this->protocolID < other->protocolID;
    };

    bool operator>(const ProtocolVersion* other) const {
      return this->protocolID > other->protocolID;
    };

    bool operator<=(const ProtocolVersion* other) const {
      return this->protocolID <= other->protocolID;
    };

    bool operator>=(const ProtocolVersion* other) const {
      return this->protocolID >= other->protocolID;
    };

    bool operator==(const ProtocolVersion* other) const {
      return this->protocolID == other->protocolID;
    };

    static void Init();

    static const ProtocolVersion* FromProtocolID(uint32_t protocol_id);

    static const ProtocolVersion* FromOrdinal(uint32_t ordinal);
  };

  class ByteBuffer {
   private:
    std::deque<uint8_t*> buffers;
    size_t singleCapacity;
    uint8_t* currentReadBuffer;
    uint8_t* currentWriteBuffer;
    size_t localReaderIndex = 0;
    size_t localWriterIndex = 0;
    size_t readableBytes = 0;

   public:
    explicit ByteBuffer(size_t singleCapacity);
    ByteBuffer(uint8_t* buffer, size_t singleCapacity);

    ~ByteBuffer();

    void WriteBoolean(bool input);
    void WriteByte(uint8_t input);
    void WriteShort(uint16_t input);
    void WriteMedium(uint32_t input);
    void WriteInt(uint32_t input);
    void WriteVarInt(uint32_t input);
    void WriteLong(uint64_t input);
    void WriteBytes(uint8_t* input, size_t size);
    void WriteBytesAndDelete(uint8_t* input, size_t size);
    void WriteBytes(ByteBuffer* input, size_t size);
    void WriteUUID(UUID input);
    void WriteUUIDIntArray(UUID input);
    void WriteDouble(double input);
    void WriteFloat(float input);
    void WriteString(const std::string& input);
    void WriteProperties(const std::vector<GameProfileProperty> &properties);

    bool ReadBoolean();
    uint8_t ReadByte();
    uint8_t ReadByteUnsafe();
    uint16_t ReadShort();
    uint32_t ReadMedium();
    uint32_t ReadInt();
    uint32_t ReadVarInt();
    uint64_t ReadLong();
    uint8_t* ReadBytes(size_t size);
    double ReadDouble();
    float ReadFloat();
    UUID ReadUUID();
    UUID ReadUUIDIntArray();
    std::string ReadString();
    std::string ReadString(uint32_t max_size);
    std::vector<GameProfileProperty> ReadProperties();

    friend ByteBuffer& operator<<(ByteBuffer& buffer, bool input);
    friend ByteBuffer& operator<<(ByteBuffer& buffer, uint8_t input);
    friend ByteBuffer& operator<<(ByteBuffer& buffer, uint16_t input);
    friend ByteBuffer& operator<<(ByteBuffer& buffer, uint32_t input);
    friend ByteBuffer& operator<<(ByteBuffer& buffer, uint64_t input);
    friend ByteBuffer& operator<<(ByteBuffer& buffer, double input);
    friend ByteBuffer& operator<<(ByteBuffer& buffer, float input);

    friend ByteBuffer& operator>>(ByteBuffer& buffer, bool& output);
    friend ByteBuffer& operator>>(ByteBuffer& buffer, uint8_t& output);
    friend ByteBuffer& operator>>(ByteBuffer& buffer, uint16_t& output);
    friend ByteBuffer& operator>>(ByteBuffer& buffer, uint32_t& output);
    friend ByteBuffer& operator>>(ByteBuffer& buffer, uint64_t& output);
    friend ByteBuffer& operator>>(ByteBuffer& buffer, double& input);
    friend ByteBuffer& operator>>(ByteBuffer& buffer, float& input);

    void Release();
    void ResetReaderIndex();
    [[nodiscard]] size_t GetReaderIndex() const;
    void ResetWriterIndex();
    [[nodiscard]] size_t GetWriterIndex() const;
    [[nodiscard]] size_t GetReadableBytes() const;
    [[nodiscard]] size_t GetSingleCapacity() const;
    void TryRefreshReaderBuffer();
    void TryRefreshWriterBuffer();
    void AppendBuffer();
    void PopBuffer();

    [[nodiscard]] bool CanReadDirect(size_t read_size) const;
    uint8_t* GetDirectReadAddress();

    [[nodiscard]] bool CanWriteDirect(size_t write_size) const;
    uint8_t* GetDirectWriteAddress();

    static uint32_t VarIntBytes(uint32_t varInt);
    static uint32_t StringBytes(const std::string& string);
    static uint32_t PropertiesBytes(const std::vector<GameProfileProperty> &properties);
    static uint32_t ArrayBytes(uint32_t arrayLength);
  };
}
