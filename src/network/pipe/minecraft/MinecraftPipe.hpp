#pragma once

#include "../../../protocol/packets/Packet.hpp"
#include "../../../protocol/registry/PacketRegistry.hpp"
#include "../../../utils/ordinal/OrdinalRegistry.hpp"
#include "../FramedPipe.hpp"
#include "libdeflate.h"

namespace Ship {
  class CompressionPipe : public FramedByteBytePipe {
   private:
    libdeflate_compressor* compressor;
    libdeflate_decompressor* decompressor;
    uint32_t maxDecompressLength;
    uint32_t threshold;

   public:
    static inline const uint32_t PIPE_ORDINAL = OrdinalRegistry::ByteBytePipeRegistry.RegisterOrdinal();

    CompressionPipe(size_t reader_buffer_length, size_t writer_buffer_length, libdeflate_compressor* compressor, libdeflate_decompressor* decompressor,
      uint32_t max_decompress_length, uint32_t threshold, uint32_t max_read_size);
    ~CompressionPipe() override;

    void EncodeFrame(ByteBuffer* in, uint32_t frame_size) override;
    void DecodeFrame(ByteBuffer* in, uint32_t frame_size) override;
    uint32_t GetOrdinal() const override;
  };

  class MinecraftFramedBytePacketPipe : public FramedBytePacketPipe {
   private:
    const ProtocolVersion* version;
    const PacketRegistry* directionRegistry;
    const DirectionRegistry* readerRegistry;
    const DirectionRegistry* writerRegistry;
    const PacketDirection readerDirection;
    const PacketDirection writerDirection;
    const int longPacketBufferCapacity;

   public:
    ~MinecraftFramedBytePacketPipe() override = default;

    MinecraftFramedBytePacketPipe(const PacketRegistry* initial_registry, const ProtocolVersion* version, uint32_t max_read_size,
      PacketDirection reader_direction, PacketDirection writer_direction, int long_packet_buffer_capacity);

    const PacketRegistry* GetRegistry();
    void SetRegistry(const PacketRegistry* new_registry);

    const ProtocolVersion* GetProtocolVersion();
    void SetProtocolVersion(const ProtocolVersion* new_protocol_version);

    ByteBuffer* Write(const Packet& in) override;
    Errorable<PacketHolder> ReadPacket(ByteBuffer* in, uint32_t frame_size) override;
  };
} // namespace Ship
