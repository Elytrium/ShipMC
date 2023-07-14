#include "Particle.hpp"

namespace Ship {

  ItemParticle::ItemParticle(const ItemStack& item) : item(item) {
  }

  Errorable<bool> ItemParticle::Write(const ProtocolVersion* version, ByteBuffer* buffer) const {
    item.Write(version, buffer);
    return SuccessErrorable<bool>(true);
  }

  Errorable<ItemParticle> ItemParticle::Instantiate(const ProtocolVersion* version, ByteBuffer* buffer) {
    ProceedErrorable(item, ItemStack, ItemStack::Instantiate(version, buffer), InvalidItemParticleErrorable(buffer->GetReadableBytes()))
    return SuccessErrorable<ItemParticle>(ItemParticle(item));
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