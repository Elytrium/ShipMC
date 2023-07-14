#pragma once

#include "../../../../lib/ShipNet/src/protocol/registry/ConstructorRegistry.hpp"
#include "../../../../lib/ShipNet/src/utils/ordinal/OrdinalRegistry.hpp"
#include "../../../utils/ordinal/MinecraftOrdinalRegistry.hpp"
#include "../../MinecraftProtocol.hpp"
#include "../ItemStack.hpp"

namespace Ship {

  class AbstractParticle : public Serializable {
   public:
    ~AbstractParticle() override = default;

    [[nodiscard]] virtual std::string GetIdentifier() const = 0;
    [[nodiscard]] virtual uint32_t GetOrdinal() const = 0;
  };
  CreateInvalidArgumentErrorable(InvalidParticleErrorable, AbstractParticle*, "Invalid Particle read");

#define DefineSimpleParticle(ParticleName, Identifier)                                                                 \
  class ParticleName : public AbstractParticle {                                                                       \
   public:                                                                                                             \
    static inline const uint32_t ORDINAL = MinecraftOrdinalRegistry::ParticleRegistry.RegisterOrdinal();               \
                                                                                                                       \
    static Errorable<ParticleName> Instantiate(const ProtocolVersion* version, ByteBuffer* buffer) {                   \
      return SuccessErrorable<ParticleName>({});                                                                       \
    }                                                                                                                  \
                                                                                                                       \
    Errorable<bool> Write(const ProtocolVersion* version, ByteBuffer* buffer) const override {                         \
      return SuccessErrorable<bool>(true);                                                                             \
    }                                                                                                                  \
    [[nodiscard]] std::string GetIdentifier() const override { return Identifier; }                                    \
    [[nodiscard]] uint32_t GetOrdinal() const override { return ORDINAL; }                                             \
  }

  DefineSimpleParticle(AmbientEntityEffectParticle, "minecraft:ambient_entity_effect");
  DefineSimpleParticle(AngryVillagerParticle, "minecraft:angry_villager");
  DefineSimpleParticle(BarrierParticle, "minecraft:barrier");
  DefineSimpleParticle(LightParticle, "minecraft:light");
  DefineSimpleParticle(BubbleParticle, "minecraft:bubble");
  DefineSimpleParticle(CloudParticle, "minecraft:cloud");
  DefineSimpleParticle(CritParticle, "minecraft:crit");
  DefineSimpleParticle(DamageIndicatorParticle, "minecraft:damage_indicator");
  DefineSimpleParticle(DragonBreathParticle, "minecraft:dragon_breath");
  DefineSimpleParticle(DrippingLavaParticle, "minecraft:dripping_lava");
  DefineSimpleParticle(FallingLavaParticle, "minecraft:falling_lava");
  DefineSimpleParticle(LandingLavaParticle, "minecraft:landing_lava");
  DefineSimpleParticle(DrippingWaterParticle, "minecraft:dripping_water");
  DefineSimpleParticle(FallingWaterParticle, "minecraft:falling_water");
  DefineSimpleParticle(EffectParticle, "minecraft:effect");
  DefineSimpleParticle(ElderGuardianParticle, "minecraft:elder_guardian");
  DefineSimpleParticle(EnchantedHitParticle, "minecraft:enchanted_hit");
  DefineSimpleParticle(EnchantParticle, "minecraft:enchant");
  DefineSimpleParticle(EndRodParticle, "minecraft:end_rod");
  DefineSimpleParticle(EntityEffectParticle, "minecraft:entity_effect");
  DefineSimpleParticle(ExplosionEmitterParticle, "minecraft:explosion_emitter");
  DefineSimpleParticle(ExplosionParticle, "minecraft:explosion");
  DefineSimpleParticle(SonicBoomParticle, "minecraft:sonic_boom");
  DefineSimpleParticle(FireworkParticle, "minecraft:firework");
  DefineSimpleParticle(FishingParticle, "minecraft:fishing");
  DefineSimpleParticle(FlameParticle, "minecraft:flame");
  DefineSimpleParticle(SculkSoulParticle, "minecraft:sculk_soul");
  DefineSimpleParticle(SculkChargeParticle, "minecraft:sculk_charge");
  DefineSimpleParticle(SculkChargePopParticle, "minecraft:sculk_charge_pop");
  DefineSimpleParticle(SoulFireFlameParticle, "minecraft:soul_fire_flame");
  DefineSimpleParticle(SoulParticle, "minecraft:soul");
  DefineSimpleParticle(FlashParticle, "minecraft:flash");
  DefineSimpleParticle(HappyVillagerParticle, "minecraft:happy_villager");
  DefineSimpleParticle(ComposterParticle, "minecraft:composter");
  DefineSimpleParticle(HeartParticle, "minecraft:heart");
  DefineSimpleParticle(InstantEffectParticle, "minecraft:instant_effect");
  DefineSimpleParticle(ItemSlimeParticle, "minecraft:item_slime");
  DefineSimpleParticle(ItemSnowballParticle, "minecraft:item_snowball");
  DefineSimpleParticle(LargeSmokeParticle, "minecraft:large_smoke");
  DefineSimpleParticle(LavaParticle, "minecraft:lava");
  DefineSimpleParticle(MyceliumParticle, "minecraft:mycelium");
  DefineSimpleParticle(NoteParticle, "minecraft:note");
  DefineSimpleParticle(PoofParticle, "minecraft:poof");
  DefineSimpleParticle(PortalParticle, "minecraft:portal");
  DefineSimpleParticle(RainParticle, "minecraft:rain");
  DefineSimpleParticle(SmokeParticle, "minecraft:smoke");
  DefineSimpleParticle(SneezeParticle, "minecraft:sneeze");
  DefineSimpleParticle(SpitParticle, "minecraft:spit");
  DefineSimpleParticle(SquidInkParticle, "minecraft:squid_ink");
  DefineSimpleParticle(SweepAttackParticle, "minecraft:sweep_attack");
  DefineSimpleParticle(TotemOfUndyingParticle, "minecraft:totem_of_undying");
  DefineSimpleParticle(UnderwaterParticle, "minecraft:underwater");
  DefineSimpleParticle(SplashParticle, "minecraft:splash");
  DefineSimpleParticle(WitchParticle, "minecraft:witch");
  DefineSimpleParticle(BubblePopParticle, "minecraft:bubble_pop");
  DefineSimpleParticle(CurrentDownParticle, "minecraft:current_down");
  DefineSimpleParticle(BubbleColumnUpParticle, "minecraft:bubble_column_up");
  DefineSimpleParticle(NautilusParticle, "minecraft:nautilus");
  DefineSimpleParticle(DolphinParticle, "minecraft:dolphin");
  DefineSimpleParticle(CampfireCosySmokeParticle, "minecraft:campfire_cosy_smoke");
  DefineSimpleParticle(CampfireSignalSmokeParticle, "minecraft:campfire_signal_smoke");
  DefineSimpleParticle(DrippingHoneyParticle, "minecraft:dripping_honey");
  DefineSimpleParticle(FallingHoneyParticle, "minecraft:falling_honey");
  DefineSimpleParticle(LandingHoneyParticle, "minecraft:landing_honey");
  DefineSimpleParticle(FallingNectarParticle, "minecraft:falling_nectar");
  DefineSimpleParticle(FallingSporeBlossomParticle, "minecraft:falling_spore_blossom");
  DefineSimpleParticle(AshParticle, "minecraft:ash");
  DefineSimpleParticle(CrimsonSporeParticle, "minecraft:crimson_spore");
  DefineSimpleParticle(WarpedSporeParticle, "minecraft:warped_spore");
  DefineSimpleParticle(SporeBlossomAirParticle, "minecraft:spore_blossom_air");
  DefineSimpleParticle(DrippingObsidianTearParticle, "minecraft:dripping_obsidian_tear");
  DefineSimpleParticle(FallingObsidianTearParticle, "minecraft:falling_obsidian_tear");
  DefineSimpleParticle(LandingObsidianTearParticle, "minecraft:landing_obsidian_tear");
  DefineSimpleParticle(ReversePortalParticle, "minecraft:reverse_portal");
  DefineSimpleParticle(WhiteAshParticle, "minecraft:white_ash");
  DefineSimpleParticle(SmallFlameParticle, "minecraft:small_flame");
  DefineSimpleParticle(SnowflakeParticle, "minecraft:snowflake");
  DefineSimpleParticle(DrippingDripstoneLavaParticle, "minecraft:dripping_dripstone_lava");
  DefineSimpleParticle(FallingDripstoneLavaParticle, "minecraft:falling_dripstone_lava");
  DefineSimpleParticle(DrippingDripstoneWaterParticle, "minecraft:dripping_dripstone_water");
  DefineSimpleParticle(FallingDripstoneWaterParticle, "minecraft:falling_dripstone_water");
  DefineSimpleParticle(GlowSquidInkParticle, "minecraft:glow_squid_ink");
  DefineSimpleParticle(GlowParticle, "minecraft:glow");
  DefineSimpleParticle(WaxOnParticle, "minecraft:wax_on");
  DefineSimpleParticle(WaxOffParticle, "minecraft:wax_off");
  DefineSimpleParticle(ElectricSparkParticle, "minecraft:electric_spark");
  DefineSimpleParticle(ScrapeParticle, "minecraft:scrape");
  DefineSimpleParticle(ShriekParticle, "minecraft:shriek");
  DefineSimpleParticle(FootstepParticle, "legacy:footstep");
  DefineSimpleParticle(TakeParticle, "legacy:take");

#undef DefineSimpleParticle

  class BlockParticle : public AbstractParticle {
   private:
    uint32_t blockState{};

   public:
    static inline const uint32_t ORDINAL = MinecraftOrdinalRegistry::ParticleRegistry.RegisterOrdinal();

    BlockParticle() = default;
    explicit BlockParticle(uint32_t blockState);
    static Errorable<BlockParticle> Instantiate(const ProtocolVersion* version, ByteBuffer* buffer);

    Errorable<bool> Write(const ProtocolVersion* version, ByteBuffer* buffer) const override;
    [[nodiscard]] std::string GetIdentifier() const override;
    [[nodiscard]] uint32_t GetOrdinal() const override;

    [[nodiscard]] uint32_t GetBlockState() const;
    void SetBlockState(uint32_t newValue);
  };
  CreateInvalidArgumentErrorable(InvalidBlockParticleErrorable, BlockParticle, "Invalid BlockParticle read");

  class BlockMarkerParticle : public AbstractParticle {
   private:
    uint32_t blockState{};

   public:
    static inline const uint32_t ORDINAL = MinecraftOrdinalRegistry::ParticleRegistry.RegisterOrdinal();

    BlockMarkerParticle() = default;
    explicit BlockMarkerParticle(uint32_t blockState);
    static Errorable<BlockMarkerParticle> Instantiate(const ProtocolVersion* version, ByteBuffer* buffer);

    Errorable<bool> Write(const ProtocolVersion* version, ByteBuffer* buffer) const override;
    [[nodiscard]] std::string GetIdentifier() const override;
    [[nodiscard]] uint32_t GetOrdinal() const override;

    [[nodiscard]] uint32_t GetBlockState() const;
    void SetBlockState(uint32_t newValue);
  };
  CreateInvalidArgumentErrorable(InvalidBlockMarkerParticleErrorable, BlockMarkerParticle, "Invalid BlockMarkerParticle read");

  class DustParticle : public AbstractParticle {
   private:
    float red{};
    float green{};
    float blue{};
    float scale{};

   public:
    static inline const uint32_t ORDINAL = MinecraftOrdinalRegistry::ParticleRegistry.RegisterOrdinal();

    DustParticle() = default;
    explicit DustParticle(float red, float green, float blue, float scale);
    static Errorable<DustParticle> Instantiate(const ProtocolVersion* version, ByteBuffer* buffer);

    Errorable<bool> Write(const ProtocolVersion* version, ByteBuffer* buffer) const override;
    [[nodiscard]] std::string GetIdentifier() const override;
    [[nodiscard]] uint32_t GetOrdinal() const override;

    [[nodiscard]] float GetRed() const;
    void SetRed(float newValue);
    [[nodiscard]] float GetGreen() const;
    void SetGreen(float newValue);
    [[nodiscard]] float GetBlue() const;
    void SetBlue(float newValue);
    [[nodiscard]] float GetScale() const;
    void SetScale(float newValue);
  };
  CreateInvalidArgumentErrorable(InvalidDustParticleErrorable, DustParticle, "Invalid DustParticle read");

  class DustColorTransitionParticle : public AbstractParticle {
   private:
    float fromRed{};
    float fromGreen{};
    float fromBlue{};
    float scale{};
    float toRed{};
    float toGreen{};
    float toBlue{};

   public:
    static inline const uint32_t ORDINAL = MinecraftOrdinalRegistry::ParticleRegistry.RegisterOrdinal();

    DustColorTransitionParticle() = default;
    explicit DustColorTransitionParticle(float fromRed, float fromGreen, float fromBlue, float scale, float toRed, float toGreen, float toBlue);
    static Errorable<DustColorTransitionParticle> Instantiate(const ProtocolVersion* version, ByteBuffer* buffer);

    Errorable<bool> Write(const ProtocolVersion* version, ByteBuffer* buffer) const override;
    [[nodiscard]] std::string GetIdentifier() const override;
    [[nodiscard]] uint32_t GetOrdinal() const override;

    [[nodiscard]] float GetFromRed() const;
    void SetFromRed(float newValue);
    [[nodiscard]] float GetFromGreen() const;
    void SetFromGreen(float newValue);
    [[nodiscard]] float GetFromBlue() const;
    void SetFromBlue(float newValue);
    [[nodiscard]] float GetScale() const;
    void SetScale(float newValue);
    [[nodiscard]] float GetToRed() const;
    void SetToRed(float newValue);
    [[nodiscard]] float GetToGreen() const;
    void SetToGreen(float newValue);
    [[nodiscard]] float GetToBlue() const;
    void SetToBlue(float newValue);
  };
  CreateInvalidArgumentErrorable(InvalidDustColorTransitionParticleErrorable, DustColorTransitionParticle, "Invalid DustColorTransitionParticle read");

  class FallingDustParticle : public AbstractParticle {
   private:
    uint32_t blockState{};

   public:
    static inline const uint32_t ORDINAL = MinecraftOrdinalRegistry::ParticleRegistry.RegisterOrdinal();

    FallingDustParticle() = default;
    explicit FallingDustParticle(uint32_t blockState);
    static Errorable<FallingDustParticle> Instantiate(const ProtocolVersion* version, ByteBuffer* buffer);

    Errorable<bool> Write(const ProtocolVersion* version, ByteBuffer* buffer) const override;
    [[nodiscard]] std::string GetIdentifier() const override;
    [[nodiscard]] uint32_t GetOrdinal() const override;

    [[nodiscard]] uint32_t GetBlockState() const;
    void SetBlockState(uint32_t newValue);
  };
  CreateInvalidArgumentErrorable(InvalidFallingDustParticleErrorable, FallingDustParticle, "Invalid FallingDustParticle read");

  class ItemParticle : public AbstractParticle {
   private:
    ItemStack item{};

   public:
    static inline const uint32_t ORDINAL = MinecraftOrdinalRegistry::ParticleRegistry.RegisterOrdinal();

    ItemParticle() = default;
    explicit ItemParticle(const ItemStack& item);
    static Errorable<ItemParticle> Instantiate(const ProtocolVersion* version, ByteBuffer* buffer);

    Errorable<bool> Write(const ProtocolVersion* version, ByteBuffer* buffer) const override;
    [[nodiscard]] std::string GetIdentifier() const override;
    [[nodiscard]] uint32_t GetOrdinal() const override;

    [[nodiscard]] ItemStack GetItem() const;
    void SetItem(const ItemStack& newValue);
  };
  CreateInvalidArgumentErrorable(InvalidItemParticleErrorable, ItemParticle, "Invalid ItemParticle read");

  class VibrationParticle : public AbstractParticle {
   private:
    std::string sourceType;
    Position blockPosition{};
    uint32_t entityId{};
    float entityEyeHeight{};
    uint32_t ticks{};

   public:
    static inline const uint32_t ORDINAL = MinecraftOrdinalRegistry::ParticleRegistry.RegisterOrdinal();

    VibrationParticle() = default;
    VibrationParticle(std::string sourceType, Position blockPosition, uint32_t entityId, float entityEyeHeight, uint32_t ticks);
    VibrationParticle(Position blockPosition, uint32_t ticks);
    VibrationParticle(uint32_t entityId, float entityEyeHeight, uint32_t ticks);
    VibrationParticle(const std::string& sourceType, uint32_t ticks);
    static Errorable<VibrationParticle> Instantiate(const ProtocolVersion* version, ByteBuffer* buffer);

    Errorable<bool> Write(const ProtocolVersion* version, ByteBuffer* buffer) const override;
    [[nodiscard]] std::string GetIdentifier() const override;
    [[nodiscard]] uint32_t GetOrdinal() const override;

    [[nodiscard]] const std::string& GetSourceType() const;
    void SetSourceType(const std::string& newValue);
    [[nodiscard]] Position GetBlockPosition() const;
    void SetBlockPosition(Position newValue);
    [[nodiscard]] uint32_t GetEntityId() const;
    void SetEntityId(uint32_t newValue);
    [[nodiscard]] float GetEntityEyeHeight() const;
    void SetEntityEyeHeight(float newValue);
    [[nodiscard]] uint32_t GetTicks() const;
    void SetTicks(uint32_t newValue);
  };
  CreateInvalidArgumentErrorable(InvalidVibrationParticleErrorable, VibrationParticle, "Invalid VibrationParticle read");

  extern const ConstructorRegistry<AbstractParticle> PARTICLE_REGISTRY;
}