#include "OrdinalRegistry.hpp"

namespace Ship {
  OrdinalRegistry OrdinalRegistry::ByteBytePipeRegistry = OrdinalRegistry();
  OrdinalRegistry OrdinalRegistry::PacketRegistry = OrdinalRegistry();
  OrdinalRegistry OrdinalRegistry::PacketHandlerRegistry = OrdinalRegistry();
  OrdinalRegistry OrdinalRegistry::ParticleRegistry = OrdinalRegistry();
  OrdinalRegistry OrdinalRegistry::MetadataEntryRegistry = OrdinalRegistry();

  uint32_t OrdinalRegistry::RegisterOrdinal() {
    mtx.lock();
    uint32_t ordinal = counter++;
    mtx.unlock();

    return ordinal;
  }

  uint32_t OrdinalRegistry::GetLastOrdinal() const {
    return counter;
  }
} // Ship