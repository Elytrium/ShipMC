#include "../../../Ship.hpp"
#include "../../../utils/exceptions/InvalidArgumentException.hpp"
#include "MinecraftPipe.hpp"

namespace Ship {
  thread_local uint8_t* localCompressionBuffer = new uint8_t[MAX_PACKET_SIZE];
  thread_local uint8_t* localDecompressionBuffer = new uint8_t[MAX_PACKET_SIZE];

  void CompressionPipe::EncodeFrame(ByteBuffer* in, uint32_t frame_size) {
    ByteBuffer* buffer = GetWriterBuffer();

    if (frame_size < threshold) {
      buffer->WriteVarInt(frame_size + 1);
      buffer->WriteByte(0);
      buffer->WriteBytes(in, frame_size);
      return;
    }

    uint8_t* compressionInputAddress;
    bool directRead = in->CanReadDirect(frame_size);
    if (directRead) {
      compressionInputAddress = in->GetDirectReadAddress();
    } else {
      in->ReadBytes(localDecompressionBuffer, frame_size);
      compressionInputAddress = localDecompressionBuffer;
    }

    size_t compressionSizeAvailable = frame_size + 2 + 4 + 4; // uncompressed (frame_size), zlib header (2), dict id (4), checksum (4)
    size_t compressedSize = libdeflate_zlib_compress(compressor, compressionInputAddress, frame_size, localCompressionBuffer, compressionSizeAvailable);

    buffer->WriteVarInt(compressedSize + ByteBuffer::VarIntBytes(frame_size));
    buffer->WriteVarInt(frame_size);
    buffer->WriteBytes(localCompressionBuffer, compressedSize);

    if (directRead) {
      in->SkipReadBytes(frame_size);
    }
  }

  void CompressionPipe::DecodeFrame(ByteBuffer* in, uint32_t frame_size) {
    ByteBuffer* buffer = GetReaderBuffer();
    uint32_t decompressedSize = in->ReadVarInt();
    if (decompressedSize == 0) {
      decompressedSize = frame_size - 1;
      buffer->WriteVarInt(decompressedSize);
      buffer->WriteBytes(in, decompressedSize);
      return;
    }

    if (decompressedSize < threshold || decompressedSize > maxDecompressLength) {
      throw InvalidArgumentException("Invalid decompressed size: ", maxDecompressLength);
    }

    buffer->WriteVarInt(decompressedSize);
    uint32_t compressedSize = frame_size - ByteBuffer::VarIntBytes(decompressedSize);

    uint8_t* compressionInputAddress;
    bool directRead = in->CanReadDirect(compressedSize);
    if (directRead) {
      compressionInputAddress = in->GetDirectReadAddress();
    } else {
      in->ReadBytes(localCompressionBuffer, compressedSize);
      compressionInputAddress = localCompressionBuffer;
    }

    uint8_t* compressionOutputAddress;
    bool directWrite = buffer->CanWriteDirect(decompressedSize);
    if (directWrite) {
      compressionOutputAddress = buffer->GetDirectWriteAddress();
    } else {
      compressionOutputAddress = localDecompressionBuffer;
    }

    libdeflate_zlib_decompress(decompressor, compressionInputAddress, compressedSize, compressionOutputAddress, decompressedSize, nullptr);

    if (directRead) {
      in->SkipReadBytes(compressedSize);
    }

    if (directWrite) {
      buffer->SkipWriteBytes(decompressedSize);
    } else {
      buffer->WriteBytes(compressionOutputAddress, decompressedSize);
    }
  }

  CompressionPipe::CompressionPipe(size_t reader_buffer_length, size_t writer_buffer_length, libdeflate_compressor* compressor,
    libdeflate_decompressor* decompressor, uint32_t max_decompress_length, uint32_t threshold, uint32_t max_read_size)
    : FramedByteBytePipe(reader_buffer_length, writer_buffer_length, max_read_size), compressor(compressor), decompressor(decompressor),
      maxDecompressLength(max_decompress_length), threshold(threshold) {
  }

  CompressionPipe::~CompressionPipe() {
    libdeflate_free_compressor(compressor);
    libdeflate_free_decompressor(decompressor);
  }

  uint32_t CompressionPipe::GetOrdinal() const {
    return PIPE_ORDINAL;
  }
} // namespace Ship