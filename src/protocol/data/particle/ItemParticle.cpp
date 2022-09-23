#include "Particle.hpp"

namespace Ship {

  ItemParticle::ItemParticle(const ItemStack& item) : item(item) {
  }

  void ItemParticle::Write(const ProtocolVersion* version, ByteBuffer* buffer) {
    item.Write(buffer);
  }

  void ItemParticle::Read(const ProtocolVersion* version, ByteBuffer* buffer) {
    item.Read(buffer);
  }

  uint32_t ItemParticle::Size(const ProtocolVersion* version) const {
    return item.Size();
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