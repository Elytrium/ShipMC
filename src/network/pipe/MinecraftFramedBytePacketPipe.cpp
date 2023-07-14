#include "../../protocol/registry/PacketRegistry.hpp"
#include "../../protocol/packet/prepared/PreparedPacket.hpp"
#include "../../protocol/packet/prepared/SingleVersionPreparedPacket.hpp"
#include "MinecraftPipe.hpp"

namespace Ship {
  MinecraftFramedBytePacketPipe::MinecraftFramedBytePacketPipe(const PacketRegistry* initial_registry, const ProtocolVersion* version,
    uint32_t max_read_size, const PacketDirection reader_direction, const PacketDirection writer_direction)
    : FramedBytePacketPipe(max_read_size), version(version), directionRegistry(initial_registry),
      readerRegistry(initial_registry->GetRegistry(reader_direction)), writerRegistry(initial_registry->GetRegistry(writer_direction)),
      readerDirection(reader_direction), writerDirection(writer_direction) {
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

  Errorable<bool> MinecraftFramedBytePacketPipe::Write(ByteBuffer* out, const Packet& packet) {
    if (packet.GetOrdinal() == PreparedPacket::PACKET_ORDINAL) {
      ByteBuffer* buffer = ((PreparedPacket&) packet).GetBytes(version);
      out->WriteBytes(buffer, buffer->GetReadableBytes());
      return SuccessErrorable<bool>(true);
    }

    if (packet.GetOrdinal() == SingleVersionPreparedPacket::PACKET_ORDINAL) {
      ByteBuffer* buffer = ((SingleVersionPreparedPacket&) packet).GetBytes();
      out->WriteBytes(buffer, buffer->GetReadableBytes());
      return SuccessErrorable<bool>(true);
    }

    uint32_t packetSize = packet.Size(version);
    ProceedErrorable(packetID, uint32_t, writerRegistry->GetIDByPacket(version, packet), InvalidSerializableWriteErrorable(packet.GetOrdinal()))
    uint32_t packetSizeWithID = packetSize + ByteBuffer::VarIntBytes(packetID);
    out->WriteVarInt(packetSizeWithID);
    out->WriteVarInt(packetID);
    packet.Write(version, out);
    return SuccessErrorable<bool>(true);
  }

  Errorable<PacketHolder> MinecraftFramedBytePacketPipe::ReadPacket(ByteBuffer* in, uint32_t frame_size) {
    uint32_t oldReadableBytes = in->GetReadableBytes();
    ProceedErrorable(packetID, uint32_t, in->ReadVarInt(), InvalidFrameErrorable(oldReadableBytes))
    uint32_t expectedSize = frame_size - (oldReadableBytes - in->GetReadableBytes());
    ProceedErrorable(ordinal, uint32_t, readerRegistry->GetOrdinalByID(version, packetID), InvalidFrameErrorable(oldReadableBytes))

    return SuccessErrorable<PacketHolder>({ordinal, version, in, expectedSize});
  }
}