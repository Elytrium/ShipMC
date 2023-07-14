#pragma once

#include "ShipNet/utils/ordinal/OrdinalRegistry.hpp"
#include <string>
#include <utility>

namespace Ship {

  class CustomSoundEffect : public Packet {
   private:
    std::string soundName;
    uint32_t soundCategory{};
    uint32_t effectPositionX{};
    uint32_t effectPositionY{};
    uint32_t effectPositionZ{};
    float volume{};
    float pitch{};
    uint64_t seed{};

   public:
    static inline const uint32_t PACKET_ORDINAL = OrdinalRegistry::PacketRegistry.RegisterOrdinal();

    CustomSoundEffect() = default;
    CustomSoundEffect(std::string soundName, uint32_t soundCategory, uint32_t effectPositionX, uint32_t effectPositionY, uint32_t effectPositionZ,
      float volume, float pitch, uint64_t seed)
      : soundName(std::move(soundName)), soundCategory(soundCategory), effectPositionX(effectPositionX), effectPositionY(effectPositionY),
        effectPositionZ(effectPositionZ), volume(volume), pitch(pitch), seed(seed) {
    }

    ~CustomSoundEffect() override = default;

    static Errorable<CustomSoundEffect> Instantiate(const PacketHolder& holder) {
      ByteBuffer* buffer = holder.GetCurrentBuffer();
      const ProtocolVersion* version = holder.GetVersion();
      ProceedErrorable(soundName, std::string, buffer->ReadString(), InvalidPacketErrorable<CustomSoundEffect>(PACKET_ORDINAL))
      ProceedErrorable(soundCategory, uint32_t, buffer->ReadVarInt(), InvalidPacketErrorable<CustomSoundEffect>(PACKET_ORDINAL))
      ProceedErrorable(effectPositionX, uint32_t, buffer->ReadInt(), InvalidPacketErrorable<CustomSoundEffect>(PACKET_ORDINAL))
      ProceedErrorable(effectPositionY, uint32_t, buffer->ReadInt(), InvalidPacketErrorable<CustomSoundEffect>(PACKET_ORDINAL))
      ProceedErrorable(effectPositionZ, uint32_t, buffer->ReadInt(), InvalidPacketErrorable<CustomSoundEffect>(PACKET_ORDINAL))
      ProceedErrorable(volume, float, buffer->ReadFloat(), InvalidPacketErrorable<CustomSoundEffect>(PACKET_ORDINAL))
      ProceedErrorable(pitch, float, buffer->ReadFloat(), InvalidPacketErrorable<CustomSoundEffect>(PACKET_ORDINAL))

      uint64_t seed = 0;
      if (version >= &MinecraftProtocolVersion::MINECRAFT_1_19) {
        SetFromErrorable(seed, uint64_t, buffer->ReadLong(), InvalidPacketErrorable<CustomSoundEffect>(PACKET_ORDINAL))
      }

      return SuccessErrorable<CustomSoundEffect>(CustomSoundEffect(soundName, soundCategory, effectPositionX, effectPositionY, effectPositionZ, volume, pitch, seed));
    }

    Errorable<bool> Write(const ProtocolVersion* version, ByteBuffer* buffer) const override {
      buffer->WriteString(soundName);
      buffer->WriteVarInt(soundCategory);
      buffer->WriteInt(effectPositionX);
      buffer->WriteInt(effectPositionY);
      buffer->WriteInt(effectPositionZ);
      buffer->WriteFloat(volume);
      buffer->WriteFloat(pitch);
      if (version >= &MinecraftProtocolVersion::MINECRAFT_1_19) {
        buffer->WriteLong(seed);
      }
      return SuccessErrorable<bool>(true);
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
