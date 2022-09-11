#include "ProtocolUtils.hpp"

namespace Ship {
  void ProtocolUtils::WriteNBT(ByteBuffer *buffer, NBT *nbt) {
    buffer->WriteByte(nbt->GetType());
    buffer->WriteString(nbt->GetName());
    nbt->Write(buffer);
  }

  NBT *ProtocolUtils::ReadNBT(ByteBuffer *buffer) {
    auto type = (TagType) buffer->ReadByte();

    if (type == TagType::END) {
      return new EndTag("");
    }

    NBT *nbt = NBT::Create(type, buffer->ReadString());
    nbt->Read(buffer);
    return nbt;
  }
} // Ship