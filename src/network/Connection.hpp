#pragma once

#include "../protocol/handlers/PacketHandler.hpp"
#include "../protocol/packets/Packet.hpp"
#include "../utils/exceptions/InvalidArgumentException.hpp"
#include "pipe/Pipe.hpp"
#include "readwritecloser/ReadWriteCloser.hpp"
#include <list>

namespace Ship {

  class Connection {
   private:
    const ProtocolVersion* version {};
    std::list<ByteBytePipe*> pipeline;
    BytePacketPipe* bytePacketPipe;
    PacketHandler* mainPacketHandler;
    std::list<PacketHandler*> packetHandlers;
    ByteBuffer* readerBuffer;
    ByteBuffer* writerBuffer;
    ReadWriteCloser* readWriteCloser;

   public:
    Connection(BytePacketPipe* byte_packet_pipe, PacketHandler* main_packet_handler, size_t reader_buffer_length, size_t writer_buffer_length,
      ReadWriteCloser* read_write_closer);

    ~Connection();

    void SetBytePacketPipe(BytePacketPipe* newBytePacketPipe);
    BytePacketPipe* GetBytePacketPipe();

    void AppendByteBytePipe(ByteBytePipe* byte_byte_pipe);
    void PrependByteBytePipe(ByteBytePipe* byte_byte_pipe);
    void AppendByteBytePipe(ByteBytePipe* byte_byte_pipe, uint32_t after_ordinal);
    void PrependByteBytePipe(ByteBytePipe* byte_byte_pipe, uint32_t before_ordinal);
    void RemoveByteBytePipe(uint32_t byte_byte_pipe_ordinal);

    void ReplaceMainPacketHandler(PacketHandler* packet_handler);
    void AppendPacketHandler(PacketHandler* packet_handler);
    void PrependPacketHandler(PacketHandler* packet_handler);
    void AppendPacketHandler(PacketHandler* packet_handler, uint32_t after_ordinal);
    void PrependPacketHandler(PacketHandler* packet_handler, uint32_t before_ordinal);
    void RemovePacketHandler(uint32_t packet_handler_ordinal);

    void HandleNewBytes(uint8_t* page, size_t page_size);

    void Write(Packet* packet, bool delete_on_send);
    void WriteAndFlush(Packet* packet, bool delete_on_send);

    void WriteDirect(ByteBuffer* buffer);
    void WriteDirect(ByteBuffer* buffer, size_t length);

    ReadWriteCloser* GetReadWriteCloser();
    const ProtocolVersion* GetProtocolVersion();

    void Flush();
  };
}
