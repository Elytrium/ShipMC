#pragma once

#include "../../../utils/ordinal/OrdinalRegistry.hpp"
#include "../Packet.hpp"
#include <string>
#include <utility>

namespace Ship {

  class CustomSoundEffect : public Packet {
   private:
    std::string soundName;
    uint32_t soundCategory;
    uint32_t effectPositionX;
    uint32_t effectPositionY;
    uint32_t effectPositionZ;
    float volume;
    float pitch;
    uint64_t seed;

   public:
    static inline const uint32_t PACKET_ORDINAL = OrdinalRegistry::PacketRegistry.RegisterOrdinal();

    CustomSoundEffect(std::string soundName, uint32_t soundCategory, uint32_t effectPositionX, uint32_t effectPositionY, uint32_t effectPositionZ,
      float volume, float pitch, uint64_t seed)
      : soundName(std::move(soundName)), soundCategory(soundCategory), effectPositionX(effectPositionX), effectPositionY(effectPositionY),
        effectPositionZ(effectPositionZ), volume(volume), pitch(pitch), seed(seed) {
    }

    ~CustomSoundEffect() override = default;

    static Errorable<CustomSoundEffect> Instantiate(const PacketHolder& holder) {
      ByteBuffer* buffer = holder.GetCurrentBuffer();
      const ProtocolVersion* version = holder.GetVersion();
      ProceedErrorable(soundName, std::string, buffer->ReadString(), InvalidPacketErrorable<>(PACKET_ORDINAL))
      ProceedErrorable(soundCategory, uint32_t, buffer->ReadVarInt(), InvalidPacketErrorable<>(PACKET_ORDINAL))
      effectPositionX = buffer->ReadInt();
      effectPositionY = buffer->ReadInt();
      effectPositionZ = buffer->ReadInt();
      ProceedErrorable(volume, float, buffer->ReadFloat(), InvalidPacketErrorable<>(PACKET_ORDINAL))
      ProceedErrorable(pitch, float, buffer->ReadFloat(), InvalidPacketErrorable<>(PACKET_ORDINAL))
      if (version >= &ProtocolVersion::MINECRAFT_1_19) {
        ProceedErrorable(seed, uint64_t, buffer->ReadLong(), InvalidPacketErrorable<>(PACKET_ORDINAL))
      }
    }

    void Write(const ProtocolVersion* version, ByteBuffer* buffer) const override {
      buffer->WriteString(soundName);
      buffer->WriteVarInt(soundCategory);
      buffer->WriteInt(effectPositionX);
      buffer->WriteInt(effectPositionY);
      buffer->WriteInt(effectPositionZ);
      buffer->WriteFloat(volume);
      buffer->WriteFloat(pitch);
      if (version >= &ProtocolVersion::MINECRAFT_1_19) {
        buffer->WriteLong(seed);
      }
    }

    [[nodiscard]] uint32_t GetOrdinal() const override {
      return PACKET_ORDINAL;
    }

    [[nodiscard]] const std::string& GetSoundName() const {
      return soundName;
    }

    [[nodiscard]] uint32_t GetSoundCategory() const {
      return soundCategory;
    }

    [[nodiscard]] uint32_t GetEffectPositionX() const {
      return effectPositionX;
    }

    [[nodiscard]] uint32_t GetEffectPositionY() const {
      return effectPositionY;
    }

    [[nodiscard]] uint32_t GetEffectPositionZ() const {
      return effectPositionZ;
    }

    [[nodiscard]] float GetVolume() const {
      return volume;
    }

    [[nodiscard]] float GetPitch() const {
      return pitch;
    }

    [[nodiscard]] uint64_t GetSeed() const {
      return seed;
    }
  };
}
