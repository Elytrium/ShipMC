#pragma once

#include "metadata/ParsedMetadata.hpp"

namespace Ship {

  class EntityMetadata : public ParsedMetadata {
   private:
    union {
      struct {
        uint8_t onFire : 1;
        uint8_t crouching : 1;
        uint8_t riding : 1; // Unused
        uint8_t sprinting : 1;
        uint8_t swimming : 1; // Unused in 1.12.2
        uint8_t invisible : 1;
        uint8_t hasGlowingEffect : 1;
        uint8_t flyingWithElyta : 1;
      };

      uint8_t value;
    } flags {};
    uint32_t airTicks = 300;
    std::optional<std::string> customName;
    bool customNameVisible = false;
    bool silent = false;
    bool hasNoGravity = false;
    Pose pose = Pose::STANDING;
    uint32_t frozenTicks = 0;

   public:
    EntityMetadata() = default;
    ~EntityMetadata() override = default;

    static uint8_t MaximumEntries(const ProtocolVersion* version) {
      if (version >= &ProtocolVersion::MINECRAFT_1_14) {
        if (version >= &ProtocolVersion::MINECRAFT_1_17) {
          return 8;
        }
        return 7;
      }
      return 6;
    }

    void Read(Metadata* metadata, const ProtocolVersion* version) override {
      flags.value = metadata->GetByte(0).value_or(0);
      airTicks = metadata->GetVarInt(1).value_or(300);
      customName = metadata->GetOptChat(2).value_or(std::nullopt);
      customNameVisible = metadata->GetBoolean(3).value_or(false);
      silent = metadata->GetBoolean(4).value_or(false);
      hasNoGravity = metadata->GetBoolean(5).value_or(false);
      if (version >= &ProtocolVersion::MINECRAFT_1_14) {
        pose = metadata->GetPose(6).value_or(Pose::STANDING);
        if (version >= &ProtocolVersion::MINECRAFT_1_17) {
          frozenTicks = metadata->GetVarInt(7).value_or(0);
        }
      }
    }

    void Write(Metadata* metadata, const ProtocolVersion* version) override {
      if (flags.value) {
        metadata->Set(0, new ByteMetadataEntry(flags.value));
      }

      if (airTicks != 300) {
        metadata->Set(1, new VarIntMetadataEntry(airTicks));
      }

      if (customName) {
        metadata->Set(2, new OptChatMetadataEntry(customName));
      }

      if (customNameVisible) {
        metadata->Set(3, new BooleanMetadataEntry(customNameVisible));
      }

      if (silent) {
        metadata->Set(4, new BooleanMetadataEntry(silent));
      }

      if (hasNoGravity) {
        metadata->Set(5, new BooleanMetadataEntry(hasNoGravity));
      }

      if (version >= &ProtocolVersion::MINECRAFT_1_14) {
        if (pose != Pose::STANDING) {
          metadata->Set(6, new PoseMetadataEntry(pose));
        }

        if (version >= &ProtocolVersion::MINECRAFT_1_17) {
          if (frozenTicks) {
            metadata->Set(7, new VarIntMetadataEntry(frozenTicks));
          }
        }
      }
    }

    [[nodiscard]] bool IsOnFire() const {
      return flags.onFire;
    }

    void SetOnFire(bool value) {
      flags.onFire = value;
    }

    [[nodiscard]] bool IsCrouching() const {
      return flags.crouching;
    }

    void SetCrouching(bool value) {
      flags.crouching = value;
    }

    [[nodiscard]] bool IsRiding() const {
      return flags.riding;
    }

    void SetRiding(bool value) {
      flags.riding = value;
    }

    [[nodiscard]] bool IsSprinting() const {
      return flags.sprinting;
    }

    void SetSprinting(bool value) {
      flags.sprinting = value;
    }

    [[nodiscard]] bool IsSwimming() const {
      return flags.swimming;
    }

    void SetSwimming(bool value) {
      flags.swimming = value;
    }

    [[nodiscard]] bool IsInvisible() const {
      return flags.invisible;
    }

    void SetInvisible(bool value) {
      flags.invisible = value;
    }

    [[nodiscard]] bool HasGlowingEffect() const {
      return flags.hasGlowingEffect;
    }

    void SetHasGlowingEffect(bool value) {
      flags.hasGlowingEffect = value;
    }

    [[nodiscard]] bool IsFlyingWithElytra() const {
      return flags.flyingWithElyta;
    }

    void SetFlyingWithElytra(bool value) {
      flags.flyingWithElyta = value;
    }

    [[nodiscard]] uint32_t GetAirTicks() const {
      return airTicks;
    }

    void SetAirTicks(uint32_t value) {
      airTicks = value;
    }

    [[nodiscard]] std::optional<std::string> GetCustomName() const {
      return customName;
    }

    void SetCustomName(const std::optional<std::string>& value) {
      customName = value;
    }

    [[nodiscard]] bool IsCustomNameVisible() const {
      return customNameVisible;
    }

    void SetCustomNameVisible(bool value) {
      customNameVisible = value;
    }

    [[nodiscard]] bool IsSilent() const {
      return silent;
    }

    void SetSilent(bool value) {
      silent = value;
    }

    [[nodiscard]] bool HasNoGravity() const {
      return hasNoGravity;
    }

    void SetHasNoGravity(bool value) {
      hasNoGravity = value;
    }

    [[nodiscard]] Pose GetPose() const {
      return pose;
    }

    void SetPose(const Pose& value) {
      pose = value;
    }

    [[nodiscard]] uint32_t GetFrozenTicks() const {
      return frozenTicks;
    }

    void SetFrozenTicks(uint32_t value) {
      frozenTicks = value;
    }
  };
}