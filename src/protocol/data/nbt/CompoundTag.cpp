#include "../../ProtocolUtils.hpp"
#include "NBT.hpp"
#include <utility>

namespace Ship {
  CompoundTag::CompoundTag(const std::string& name) : NBT(name) {
  }

  CompoundTag::CompoundTag(const std::string& name, std::map<std::string, NBT*> map) : NBT(name), map(std::move(map)) {
  }

  void CompoundTag::Write(ByteBuffer* buffer) {
    for (const auto& item : map) {
      ProtocolUtils::WriteNBT(buffer, item.second);
    }

    NBT* end = new EndTag("");
    ProtocolUtils::WriteNBT(buffer, end);
    delete end;
  }

  void CompoundTag::Read(ByteBuffer* buffer) {
    for (const auto& item : map) {
      delete item.second;
    }

    map.clear();
    NBT* nbt = ProtocolUtils::ReadNBT(buffer);
    while (nbt->GetType() != TagType::END) {
      map.emplace(nbt->GetName(), nbt);
      nbt = ProtocolUtils::ReadNBT(buffer);
    }

    delete nbt;
  }

  uint32_t CompoundTag::GetSize() {
    uint32_t size_sum = 1;
    for (const auto& item : map) {
      size_sum += ProtocolUtils::NBTSize(item.second);
    }

    return size_sum;
  }

  TagType CompoundTag::GetType() {
    return TagType::COMPOUND;
  }

  std::optional<NBT*> CompoundTag::GetNBT(const std::string& name) {
    return map[name];
  }

  void CompoundTag::SetNBT(const std::string& name, NBT* value) {
    value->SetName(name);
    map.emplace(name, value);
  }

  void CompoundTag::AddNBT(NBT* value) {
    map.emplace(value->GetName(), value);
  }

  std::optional<bool> CompoundTag::GetBool(const std::string& name) {
    std::optional<NBT*> nbtValue = GetNBT(name);
    if (nbtValue) {
      return ((ByteTag*) nbtValue.value())->GetValue();
    } else {
      return std::nullopt;
    }
  }

  std::optional<uint8_t> CompoundTag::GetByte(const std::string& name) {
    std::optional<NBT*> nbtValue = GetNBT(name);
    if (nbtValue) {
      return ((ByteTag*) nbtValue.value())->GetValue();
    } else {
      return std::nullopt;
    }
  }

  std::optional<uint32_t> CompoundTag::GetInt(const std::string& name) {
    std::optional<NBT*> nbtValue = GetNBT(name);
    if (nbtValue) {
      return ((IntTag*) nbtValue.value())->GetValue();
    } else {
      return std::nullopt;
    }
  }

  std::optional<uint64_t> CompoundTag::GetLong(const std::string& name) {
    std::optional<NBT*> nbtValue = GetNBT(name);
    if (nbtValue) {
      return ((LongTag*) nbtValue.value())->GetValue();
    } else {
      return std::nullopt;
    }
  }

  std::optional<float> CompoundTag::GetFloat(const std::string& name) {
    std::optional<NBT*> nbtValue = GetNBT(name);
    if (nbtValue) {
      return ((FloatTag*) nbtValue.value())->GetValue();
    } else {
      return std::nullopt;
    }
  }

  std::optional<double> CompoundTag::GetDouble(const std::string& name) {
    std::optional<NBT*> nbtValue = GetNBT(name);
    if (nbtValue) {
      return ((DoubleTag*) nbtValue.value())->GetValue();
    } else {
      return std::nullopt;
    }
  }

  std::optional<std::string> CompoundTag::GetString(const std::string& name) {
    std::optional<NBT*> nbtValue = GetNBT(name);
    if (nbtValue) {
      return ((StringTag*) nbtValue.value())->GetValue();
    } else {
      return std::nullopt;
    }
  }
  bool CompoundTag::HasKey(const std::string& name) {
    return map.count(name);
  }
}