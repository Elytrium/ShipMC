#pragma once

#include "../protocol/handlers/PacketHandler.hpp"
#include "../protocol/packets/Packet.hpp"
#include "../utils/threads/EventLoop.hpp"
#include "pipe/Pipe.hpp"
#include "readwritecloser/ReadWriteCloser.hpp"
#include <list>

namespace Ship {

  class Connection {
   private:
    std::list<ByteBytePipe*> pipeline;
    BytePacketPipe* bytePacketPipe;
    PacketHandler* mainPacketHandler;
    std::list<PacketHandler*> packetHandlers;
    ByteBuffer* readerBuffer;
    ByteBuffer* writerBuffer;
    ReadWriteCloser* readWriteCloser;
    EventLoop* eventLoop;
    std::function<void()> onClose;

   public:
    Connection(BytePacketPipe* byte_packet_pipe, PacketHandler* main_packet_handler, size_t reader_buffer_length, size_t writer_buffer_length,
      ReadWriteCloser* read_write_closer, EventLoop* event_loop);

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

    void Write(const Packet& packet);
    void WriteAndFlush(const Packet& packet);

    void WriteDirect(ByteBuffer* buffer);

    ReadWriteCloser* GetReadWriteCloser();
    EventLoop* GetEventLoop();

    void Flush();

    void SetOnClose(const std::function<void()>& on_close);
  };
}
