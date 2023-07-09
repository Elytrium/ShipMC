#pragma once

#include "../../../lib/ShipNet/src/utils/ordinal/OrdinalRegistry.hpp"

namespace Ship {
  class MinecraftOrdinalRegistry {
   public:
    static OrdinalRegistry ParticleRegistry;
    static OrdinalRegistry MetadataEntryRegistry;
  };
}
