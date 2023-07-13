#include "Particle.hpp"

namespace Ship {

  ItemParticle::ItemParticle(const ItemStack& item) : item(item) {
  }

  Errorable<bool> ItemParticle::Write(const ProtocolVersion* version, ByteBuffer* buffer) const {
    item.Write(version, buffer);
    return SuccessErrorable<bool>(true);
  }

  ItemParticle::ItemParticle(const ProtocolVersion* version, ByteBuffer* buffer) {
    item = ItemStack(version, buffer);
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