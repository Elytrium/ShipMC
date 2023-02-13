#include "Particle.hpp"

namespace Ship {

  ItemParticle::ItemParticle(const ItemStack& item) : item(item) {
  }

  void ItemParticle::Write(const ProtocolVersion* version, ByteBuffer* buffer) {
    item.Write(version, buffer);
  }

  void ItemParticle::Read(const ProtocolVersion* version, ByteBuffer* buffer) {
    item.Read(version, buffer);
  }

  std::string ItemParticle::GetIdentifier() const {
    return "minecraft:item";
  }

  uint32_t ItemParticle::GetOrdinal() const {
    return ORDINAL;
  }

  ItemStack ItemParticle::GetItem() const {
    return item;
  }

  void ItemParticle::SetItem(const ItemStack& newValue) {
    item = newValue;
  }
}