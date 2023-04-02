#pragma once

#include "../Protocol.hpp"

namespace Ship {

  class PacketHolder {
   private:
    uint32_t ordinal;
    const ProtocolVersion* version;
    ByteBuffer* currentBuffer;
    uint32_t expectedSize;

   public:
    PacketHolder() = default;

    PacketHolder(uint32_t ordinal, const ProtocolVersion* version, ByteBuffer* currentBuffer, uint32_t expectedSize)
      : ordinal(ordinal), version(version), currentBuffer(currentBuffer), expectedSize(expectedSize) {
    }

    [[nodiscard]] uint32_t GetOrdinal() const {
      return ordinal;
    }

    [[nodiscard]] const ProtocolVersion* GetVersion() const {
      return version;
    }

    [[nodiscard]] ByteBuffer* GetCurrentBuffer() const {
      return currentBuffer;
    }

    [[nodiscard]] uint32_t GetExpectedSize() const {
      return expectedSize;
    }
  };

  class Packet : public Serializable {
   public:
    ~Packet() override = default;

    [[nodiscard]] virtual uint32_t GetOrdinal() const = 0;
    virtual bool SupportsOn(const ProtocolVersion* version) {
      // TODO: possibly we should do it in registry
      return true;
    }
  };

  template<typename T>
  class InvalidPacketErrorable : public Errorable<T> {
   public:
    static inline const uint32_t TYPE_ORDINAL = OrdinalRegistry::ErrorableTypeRegistry.RegisterOrdinal();

    explicit InvalidPacketErrorable(uint32_t packet_ordinal) : Errorable<T>(TYPE_ORDINAL, {}, packet_ordinal) {
    }

    void Print(std::ostream o) {
      o << "Invalid packet received, packet ordinal: " << this->GetErrorCode();
    }
  };
}
