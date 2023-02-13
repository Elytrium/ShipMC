#pragma once

#include "../Protocol.hpp"

namespace Ship {

  class Packet : public Serializable {
   public:
    ~Packet() override = default;

    virtual uint32_t GetOrdinal() = 0;
    virtual bool SupportsOn(const ProtocolVersion* version) {
      return true;
    }
  };
}
