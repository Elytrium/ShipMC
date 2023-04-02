#include "../../../protocol/packets/prepared/PreparedPacket.hpp"
#include "../../../protocol/packets/prepared/SingleVersionPreparedPacket.hpp"
#include "../../../protocol/registry/PacketRegistry.hpp"
#include "MinecraftPipe.hpp"

namespace Ship {
  MinecraftFramedBytePacketPipe::MinecraftFramedBytePacketPipe(const PacketRegistry* initial_registry, const ProtocolVersion* version,
    uint32_t max_read_size, const PacketDirection reader_direction, const PacketDirection writer_direction, int long_packet_buffer_capacity)
    : FramedBytePacketPipe(max_read_size), version(version), directionRegistry(initial_registry),
      readerRegistry(initial_registry->GetRegistry(reader_direction)), writerRegistry(initial_registry->GetRegistry(writer_direction)),
      readerDirection(reader_direction), writerDirection(writer_direction), longPacketBufferCapacity(long_packet_buffer_capacity) {
  }

  const PacketRegistry* MinecraftFramedBytePacketPipe::GetRegistry() {
    return directionRegistry;
  }

  void MinecraftFramedBytePacketPipe::SetRegistry(const PacketRegistry* new_registry) {
    directionRegistry = new_registry;
    readerRegistry = new_registry->GetRegistry(readerDirection);
    writerRegistry = new_registry->GetRegistry(writerDirection);
  }

  const ProtocolVersion* MinecraftFramedBytePacketPipe::GetProtocolVersion() {
    return version;
  }

  void MinecraftFramedBytePacketPipe::SetProtocolVersion(const ProtocolVersion* new_protocol_version) {
    version = new_protocol_version;
  }

  ByteBuffer* MinecraftFramedBytePacketPipe::Write(const Packet& packet) {
    if (packet.GetOrdinal() == PreparedPacket::PACKET_ORDINAL) {
      return ((PreparedPacket&) packet).GetBytes(version);
    }

    if (packet.GetOrdinal() == SingleVersionPreparedPacket::PACKET_ORDINAL) {
      return ((SingleVersionPreparedPacket&) packet).GetBytes();
    }

    uint32_t packetSize = packet.Size(version);
    if (packetSize != -1) {
      uint32_t packetID = writerRegistry->GetIDByPacket(version, packet);
      uint32_t packetSizeWithID = packetSize + ByteBuffer::VarIntBytes(packetID);
      auto* buffer = new ByteBufferImpl(packetSizeWithID + ByteBuffer::VarIntBytes(packetSizeWithID));
      buffer->WriteVarInt(packetSizeWithID);
      buffer->WriteVarInt(packetID);
      packet.Write(version, buffer);
      return buffer;
    } else {
      auto* buffer = new ByteBufferImpl(longPacketBufferCapacity);
      packet.Write(version, buffer);
      packetSize = buffer->GetReadableBytes();
      uint32_t packetID = writerRegistry->GetIDByPacket(version, packet);
      uint32_t packetSizeWithID = packetSize + ByteBuffer::VarIntBytes(packetID);
      auto* prefixedBuffer = new ByteBufferImpl(packetSizeWithID + ByteBuffer::VarIntBytes(packetSizeWithID));
      prefixedBuffer->WriteVarInt(packetSizeWithID);
      prefixedBuffer->WriteVarInt(packetID);
      prefixedBuffer->WriteBytes(buffer, packetSize);
      delete buffer;
      return prefixedBuffer;
    }
  }

  Errorable<PacketHolder> MinecraftFramedBytePacketPipe::ReadPacket(ByteBuffer* in, uint32_t frame_size) {
    uint32_t oldReadableBytes = in->GetReadableBytes();
    ProceedErrorable(packetID, uint32_t, in->ReadVarInt(), InvalidPacketErrorable<PacketHolder>(-1))
    uint32_t expectedSize = frame_size - (oldReadableBytes - in->GetReadableBytes());

    return SuccessErrorable<PacketHolder>({readerRegistry->GetOrdinalByID(version, packetID), version, in, expectedSize});
  }
} // namespace Ship