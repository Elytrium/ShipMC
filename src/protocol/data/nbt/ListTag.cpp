#include "NBT.hpp"
#include <algorithm>
#include <numeric>
#include <utility>

namespace Ship {
  ListTag::ListTag(const std::string& name) : NBT(name) {
  }

  ListTag::ListTag(const std::string& name, std::list<NBT*> list) : NBT(name), list(std::move(list)) {
  }

  void ListTag::Write(ByteBuffer* buffer) {
    uint32_t size = list.size();
    if (size == 0) {
      buffer->WriteByte(0);
      buffer->WriteInt(0);
      return;
    }

    buffer->WriteByte(list.front()->GetType());
    buffer->WriteInt(size);
    for (const auto& item : list) {
      item->Write(buffer);
    }
  }

  void ListTag::Read(ByteBuffer* buffer) {
    for (const auto& item : list) {
      delete item;
    }

    list.clear();
    auto type = (TagType) buffer->ReadByte();
    uint32_t valueLength = buffer->ReadInt();

    for (uint32_t i = 0; i < valueLength; ++i) {
      NBT* nbt = NBT::Create(type, "");
      nbt->Read(buffer);
      list.push_back(nbt);
    }
  }

  uint32_t ListTag::GetSize() {
    uint32_t size_sum = sizeof(uint8_t) + sizeof(uint32_t);
    for (const auto& item : list) {
      size_sum += item->GetSize();
    }

    return size_sum;
  }

  TagType ListTag::GetType() {
    return TagType::LIST;
  }

  std::list<NBT*>& ListTag::GetList() {
    return list;
  }
}