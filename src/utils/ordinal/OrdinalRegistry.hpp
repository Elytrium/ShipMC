#pragma once

#include <cstdint>
#include <mutex>

namespace Ship {

  class OrdinalRegistry {
   private:
    uint32_t counter = 0;
    std::mutex mtx;

   public:
    static OrdinalRegistry ByteBytePipeRegistry;
    static OrdinalRegistry PacketRegistry;
    static OrdinalRegistry PacketHandlerRegistry;
    static OrdinalRegistry ParticleRegistry;
    static OrdinalRegistry MetadataEntryRegistry;
    static OrdinalRegistry ErrorableTypeRegistry;

    uint32_t RegisterOrdinal();

    [[nodiscard]] uint32_t GetLastOrdinal() const;
  };

} // Ship
