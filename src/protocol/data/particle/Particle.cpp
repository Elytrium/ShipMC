#include "Particle.hpp"
#include "../../MinecraftProtocol.hpp"

namespace Ship {

  ConstructorRegistry<AbstractParticle> GetParticleRegistry() {
    ConstructorRegistry<AbstractParticle> particleRegistry(MinecraftProtocolVersion::VERSIONS, {
      MinecraftProtocolVersion::MINECRAFT_1_12_2,
      MinecraftProtocolVersion::MINECRAFT_1_13,
      MinecraftProtocolVersion::MINECRAFT_1_14,
      MinecraftProtocolVersion::MINECRAFT_1_15,
      MinecraftProtocolVersion::MINECRAFT_1_16_2,
      MinecraftProtocolVersion::MINECRAFT_1_17,
      MinecraftProtocolVersion::MINECRAFT_1_18,
      MinecraftProtocolVersion::MINECRAFT_1_19,
    });

    particleRegistry.RegisterVersion(&MinecraftProtocolVersion::MINECRAFT_1_12_2,
      new VersionRegistry({PoofParticle::ORDINAL, ExplosionParticle::ORDINAL, ExplosionEmitterParticle::ORDINAL, FireworkParticle::ORDINAL,
        BubbleParticle::ORDINAL, SplashParticle::ORDINAL, FishingParticle::ORDINAL, UnderwaterParticle::ORDINAL, UnderwaterParticle::ORDINAL,
        CritParticle::ORDINAL, EnchantedHitParticle::ORDINAL, SmokeParticle::ORDINAL, LargeSmokeParticle::ORDINAL, EffectParticle::ORDINAL,
        InstantEffectParticle::ORDINAL, EntityEffectParticle::ORDINAL, AmbientEntityEffectParticle::ORDINAL, WitchParticle::ORDINAL,
        DrippingWaterParticle::ORDINAL, DrippingLavaParticle::ORDINAL, AngryVillagerParticle::ORDINAL, HappyVillagerParticle::ORDINAL,
        MyceliumParticle::ORDINAL, NoteParticle::ORDINAL, PortalParticle::ORDINAL, EnchantParticle::ORDINAL, FlameParticle::ORDINAL, LavaParticle::ORDINAL,
        FootstepParticle::ORDINAL, CloudParticle::ORDINAL, DustParticle::ORDINAL, PoofParticle::ORDINAL, ItemSnowballParticle::ORDINAL,
        ItemSlimeParticle::ORDINAL, HeartParticle::ORDINAL, BarrierParticle::ORDINAL, ItemParticle::ORDINAL, BlockParticle::ORDINAL,
        BlockParticle::ORDINAL, RainParticle::ORDINAL, TakeParticle::ORDINAL, ElderGuardianParticle::ORDINAL, DragonBreathParticle::ORDINAL,
        EndRodParticle::ORDINAL, SweepAttackParticle::ORDINAL, FallingDustParticle::ORDINAL, TotemOfUndyingParticle::ORDINAL, SpitParticle::ORDINAL}));

    particleRegistry.RegisterVersion(&MinecraftProtocolVersion::MINECRAFT_1_13,
      new VersionRegistry({AmbientEntityEffectParticle::ORDINAL, AngryVillagerParticle::ORDINAL, BarrierParticle::ORDINAL, BlockParticle::ORDINAL,
        BubbleParticle::ORDINAL, CloudParticle::ORDINAL, CritParticle::ORDINAL, DamageIndicatorParticle::ORDINAL, DragonBreathParticle::ORDINAL,
        DrippingLavaParticle::ORDINAL, DrippingWaterParticle::ORDINAL, DustParticle::ORDINAL, EffectParticle::ORDINAL, ElderGuardianParticle::ORDINAL,
        EnchantedHitParticle::ORDINAL, EnchantParticle::ORDINAL, EndRodParticle::ORDINAL, EntityEffectParticle::ORDINAL, ExplosionEmitterParticle::ORDINAL,
        ExplosionParticle::ORDINAL, FallingDustParticle::ORDINAL, FireworkParticle::ORDINAL, FishingParticle::ORDINAL, FlameParticle::ORDINAL,
        HappyVillagerParticle::ORDINAL, HeartParticle::ORDINAL, InstantEffectParticle::ORDINAL, ItemParticle::ORDINAL, ItemSlimeParticle::ORDINAL,
        ItemSnowballParticle::ORDINAL, LargeSmokeParticle::ORDINAL, LavaParticle::ORDINAL, MyceliumParticle::ORDINAL, NoteParticle::ORDINAL,
        PoofParticle::ORDINAL, PortalParticle::ORDINAL, RainParticle::ORDINAL, SmokeParticle::ORDINAL, SpitParticle::ORDINAL, SquidInkParticle::ORDINAL,
        SweepAttackParticle::ORDINAL, TotemOfUndyingParticle::ORDINAL, UnderwaterParticle::ORDINAL, SplashParticle::ORDINAL, WitchParticle::ORDINAL,
        BubblePopParticle::ORDINAL, CurrentDownParticle::ORDINAL, BubbleColumnUpParticle::ORDINAL, NautilusParticle::ORDINAL, DolphinParticle::ORDINAL}));

    particleRegistry.RegisterVersion(&MinecraftProtocolVersion::MINECRAFT_1_14,
      new VersionRegistry({AmbientEntityEffectParticle::ORDINAL, AngryVillagerParticle::ORDINAL, BarrierParticle::ORDINAL, BlockParticle::ORDINAL,
        BubbleParticle::ORDINAL, CloudParticle::ORDINAL, CritParticle::ORDINAL, DamageIndicatorParticle::ORDINAL, DragonBreathParticle::ORDINAL,
        DrippingLavaParticle::ORDINAL, FallingLavaParticle::ORDINAL, LandingLavaParticle::ORDINAL, DrippingWaterParticle::ORDINAL,
        FallingWaterParticle::ORDINAL, DustParticle::ORDINAL, EffectParticle::ORDINAL, ElderGuardianParticle::ORDINAL, EnchantedHitParticle::ORDINAL,
        EnchantParticle::ORDINAL, EndRodParticle::ORDINAL, EntityEffectParticle::ORDINAL, ExplosionEmitterParticle::ORDINAL, ExplosionParticle::ORDINAL,
        FallingDustParticle::ORDINAL, FireworkParticle::ORDINAL, FishingParticle::ORDINAL, FlameParticle::ORDINAL, FlashParticle::ORDINAL,
        HappyVillagerParticle::ORDINAL, ComposterParticle::ORDINAL, HeartParticle::ORDINAL, InstantEffectParticle::ORDINAL, ItemParticle::ORDINAL,
        ItemSlimeParticle::ORDINAL, ItemSnowballParticle::ORDINAL, LargeSmokeParticle::ORDINAL, LavaParticle::ORDINAL, MyceliumParticle::ORDINAL,
        NoteParticle::ORDINAL, PoofParticle::ORDINAL, PortalParticle::ORDINAL, RainParticle::ORDINAL, SmokeParticle::ORDINAL, SneezeParticle::ORDINAL,
        SpitParticle::ORDINAL, SquidInkParticle::ORDINAL, SweepAttackParticle::ORDINAL, TotemOfUndyingParticle::ORDINAL, UnderwaterParticle::ORDINAL,
        SplashParticle::ORDINAL, WitchParticle::ORDINAL, BubblePopParticle::ORDINAL, CurrentDownParticle::ORDINAL, BubbleColumnUpParticle::ORDINAL,
        NautilusParticle::ORDINAL, DolphinParticle::ORDINAL, CampfireCosySmokeParticle::ORDINAL, CampfireSignalSmokeParticle::ORDINAL}));

    particleRegistry.RegisterVersion(&MinecraftProtocolVersion::MINECRAFT_1_15,
      new VersionRegistry({AmbientEntityEffectParticle::ORDINAL, AngryVillagerParticle::ORDINAL, BarrierParticle::ORDINAL, BlockParticle::ORDINAL,
        BubbleParticle::ORDINAL, CloudParticle::ORDINAL, CritParticle::ORDINAL, DamageIndicatorParticle::ORDINAL, DragonBreathParticle::ORDINAL,
        DrippingLavaParticle::ORDINAL, FallingLavaParticle::ORDINAL, LandingLavaParticle::ORDINAL, DrippingWaterParticle::ORDINAL,
        FallingWaterParticle::ORDINAL, DustParticle::ORDINAL, EffectParticle::ORDINAL, ElderGuardianParticle::ORDINAL, EnchantedHitParticle::ORDINAL,
        EnchantParticle::ORDINAL, EndRodParticle::ORDINAL, EntityEffectParticle::ORDINAL, ExplosionEmitterParticle::ORDINAL, ExplosionParticle::ORDINAL,
        FallingDustParticle::ORDINAL, FireworkParticle::ORDINAL, FishingParticle::ORDINAL, FlameParticle::ORDINAL, FlashParticle::ORDINAL,
        HappyVillagerParticle::ORDINAL, ComposterParticle::ORDINAL, HeartParticle::ORDINAL, InstantEffectParticle::ORDINAL, ItemParticle::ORDINAL,
        ItemSlimeParticle::ORDINAL, ItemSnowballParticle::ORDINAL, LargeSmokeParticle::ORDINAL, LavaParticle::ORDINAL, MyceliumParticle::ORDINAL,
        NoteParticle::ORDINAL, PoofParticle::ORDINAL, PortalParticle::ORDINAL, RainParticle::ORDINAL, SmokeParticle::ORDINAL, SneezeParticle::ORDINAL,
        SpitParticle::ORDINAL, SquidInkParticle::ORDINAL, SweepAttackParticle::ORDINAL, TotemOfUndyingParticle::ORDINAL, UnderwaterParticle::ORDINAL,
        SplashParticle::ORDINAL, WitchParticle::ORDINAL, BubblePopParticle::ORDINAL, CurrentDownParticle::ORDINAL, BubbleColumnUpParticle::ORDINAL,
        NautilusParticle::ORDINAL, DolphinParticle::ORDINAL, CampfireCosySmokeParticle::ORDINAL, CampfireSignalSmokeParticle::ORDINAL,
        DrippingHoneyParticle::ORDINAL, FallingHoneyParticle::ORDINAL, LandingHoneyParticle::ORDINAL, FallingNectarParticle::ORDINAL}));

    particleRegistry.RegisterVersion(&MinecraftProtocolVersion::MINECRAFT_1_16_2,
      new VersionRegistry({AmbientEntityEffectParticle::ORDINAL, AngryVillagerParticle::ORDINAL, BarrierParticle::ORDINAL, BlockParticle::ORDINAL,
        BubbleParticle::ORDINAL, CloudParticle::ORDINAL, CritParticle::ORDINAL, DamageIndicatorParticle::ORDINAL, DragonBreathParticle::ORDINAL,
        DrippingLavaParticle::ORDINAL, FallingLavaParticle::ORDINAL, LandingLavaParticle::ORDINAL, DrippingWaterParticle::ORDINAL,
        FallingWaterParticle::ORDINAL, DustParticle::ORDINAL, EffectParticle::ORDINAL, ElderGuardianParticle::ORDINAL, EnchantedHitParticle::ORDINAL,
        EnchantParticle::ORDINAL, EndRodParticle::ORDINAL, EntityEffectParticle::ORDINAL, ExplosionEmitterParticle::ORDINAL, ExplosionParticle::ORDINAL,
        FallingDustParticle::ORDINAL, FireworkParticle::ORDINAL, FishingParticle::ORDINAL, FlameParticle::ORDINAL, SoulFireFlameParticle::ORDINAL,
        SoulParticle::ORDINAL, FlashParticle::ORDINAL, HappyVillagerParticle::ORDINAL, ComposterParticle::ORDINAL, HeartParticle::ORDINAL,
        InstantEffectParticle::ORDINAL, ItemParticle::ORDINAL, ItemSlimeParticle::ORDINAL, ItemSnowballParticle::ORDINAL, LargeSmokeParticle::ORDINAL,
        LavaParticle::ORDINAL, MyceliumParticle::ORDINAL, NoteParticle::ORDINAL, PoofParticle::ORDINAL, PortalParticle::ORDINAL, RainParticle::ORDINAL,
        SmokeParticle::ORDINAL, SneezeParticle::ORDINAL, SpitParticle::ORDINAL, SquidInkParticle::ORDINAL, SweepAttackParticle::ORDINAL,
        TotemOfUndyingParticle::ORDINAL, UnderwaterParticle::ORDINAL, SplashParticle::ORDINAL, WitchParticle::ORDINAL, BubblePopParticle::ORDINAL,
        CurrentDownParticle::ORDINAL, BubbleColumnUpParticle::ORDINAL, NautilusParticle::ORDINAL, DolphinParticle::ORDINAL,
        CampfireCosySmokeParticle::ORDINAL, CampfireSignalSmokeParticle::ORDINAL, DrippingHoneyParticle::ORDINAL, FallingHoneyParticle::ORDINAL,
        LandingHoneyParticle::ORDINAL, FallingNectarParticle::ORDINAL, AshParticle::ORDINAL, CrimsonSporeParticle::ORDINAL, WarpedSporeParticle::ORDINAL,
        DrippingObsidianTearParticle::ORDINAL, FallingObsidianTearParticle::ORDINAL, LandingObsidianTearParticle::ORDINAL, ReversePortalParticle::ORDINAL,
        WhiteAshParticle::ORDINAL}));

    particleRegistry.RegisterVersion(&MinecraftProtocolVersion::MINECRAFT_1_17,
      new VersionRegistry({AmbientEntityEffectParticle::ORDINAL, AngryVillagerParticle::ORDINAL, BarrierParticle::ORDINAL, LightParticle::ORDINAL,
        BlockParticle::ORDINAL, BubbleParticle::ORDINAL, CloudParticle::ORDINAL, CritParticle::ORDINAL, DamageIndicatorParticle::ORDINAL,
        DragonBreathParticle::ORDINAL, DrippingLavaParticle::ORDINAL, FallingLavaParticle::ORDINAL, LandingLavaParticle::ORDINAL,
        DrippingWaterParticle::ORDINAL, FallingWaterParticle::ORDINAL, DustParticle::ORDINAL, DustColorTransitionParticle::ORDINAL,
        EffectParticle::ORDINAL, ElderGuardianParticle::ORDINAL, EnchantedHitParticle::ORDINAL, EnchantParticle::ORDINAL, EndRodParticle::ORDINAL,
        EntityEffectParticle::ORDINAL, ExplosionEmitterParticle::ORDINAL, ExplosionParticle::ORDINAL, FallingDustParticle::ORDINAL,
        FireworkParticle::ORDINAL, FishingParticle::ORDINAL, FlameParticle::ORDINAL, SoulFireFlameParticle::ORDINAL, SoulParticle::ORDINAL,
        FlashParticle::ORDINAL, HappyVillagerParticle::ORDINAL, ComposterParticle::ORDINAL, HeartParticle::ORDINAL, InstantEffectParticle::ORDINAL,
        ItemParticle::ORDINAL, VibrationParticle::ORDINAL, ItemSlimeParticle::ORDINAL, ItemSnowballParticle::ORDINAL, LargeSmokeParticle::ORDINAL,
        LavaParticle::ORDINAL, MyceliumParticle::ORDINAL, NoteParticle::ORDINAL, PoofParticle::ORDINAL, PortalParticle::ORDINAL, RainParticle::ORDINAL,
        SmokeParticle::ORDINAL, SneezeParticle::ORDINAL, SpitParticle::ORDINAL, SquidInkParticle::ORDINAL, SweepAttackParticle::ORDINAL,
        TotemOfUndyingParticle::ORDINAL, UnderwaterParticle::ORDINAL, SplashParticle::ORDINAL, WitchParticle::ORDINAL, BubblePopParticle::ORDINAL,
        CurrentDownParticle::ORDINAL, BubbleColumnUpParticle::ORDINAL, NautilusParticle::ORDINAL, DolphinParticle::ORDINAL,
        CampfireCosySmokeParticle::ORDINAL, CampfireSignalSmokeParticle::ORDINAL, DrippingHoneyParticle::ORDINAL, FallingHoneyParticle::ORDINAL,
        LandingHoneyParticle::ORDINAL, FallingNectarParticle::ORDINAL, FallingSporeBlossomParticle::ORDINAL, AshParticle::ORDINAL,
        CrimsonSporeParticle::ORDINAL, WarpedSporeParticle::ORDINAL, SporeBlossomAirParticle::ORDINAL, DrippingObsidianTearParticle::ORDINAL,
        FallingObsidianTearParticle::ORDINAL, LandingObsidianTearParticle::ORDINAL, ReversePortalParticle::ORDINAL, WhiteAshParticle::ORDINAL,
        SmallFlameParticle::ORDINAL, SnowflakeParticle::ORDINAL, DrippingDripstoneLavaParticle::ORDINAL, FallingDripstoneLavaParticle::ORDINAL,
        DrippingDripstoneWaterParticle::ORDINAL, FallingDripstoneWaterParticle::ORDINAL, GlowSquidInkParticle::ORDINAL, GlowParticle::ORDINAL,
        WaxOnParticle::ORDINAL, WaxOffParticle::ORDINAL, ElectricSparkParticle::ORDINAL, ScrapeParticle::ORDINAL}));

    particleRegistry.RegisterVersion(&MinecraftProtocolVersion::MINECRAFT_1_18,
      new VersionRegistry({AmbientEntityEffectParticle::ORDINAL, AngryVillagerParticle::ORDINAL, BlockParticle::ORDINAL, BlockMarkerParticle::ORDINAL,
        BubbleParticle::ORDINAL, CloudParticle::ORDINAL, CritParticle::ORDINAL, DamageIndicatorParticle::ORDINAL, DragonBreathParticle::ORDINAL,
        DrippingLavaParticle::ORDINAL, FallingLavaParticle::ORDINAL, LandingLavaParticle::ORDINAL, DrippingWaterParticle::ORDINAL,
        FallingWaterParticle::ORDINAL, DustParticle::ORDINAL, DustColorTransitionParticle::ORDINAL, EffectParticle::ORDINAL,
        ElderGuardianParticle::ORDINAL, EnchantedHitParticle::ORDINAL, EnchantParticle::ORDINAL, EndRodParticle::ORDINAL, EntityEffectParticle::ORDINAL,
        ExplosionEmitterParticle::ORDINAL, ExplosionParticle::ORDINAL, FallingDustParticle::ORDINAL, FireworkParticle::ORDINAL, FishingParticle::ORDINAL,
        FlameParticle::ORDINAL, SoulFireFlameParticle::ORDINAL, SoulParticle::ORDINAL, FlashParticle::ORDINAL, HappyVillagerParticle::ORDINAL,
        ComposterParticle::ORDINAL, HeartParticle::ORDINAL, InstantEffectParticle::ORDINAL, ItemParticle::ORDINAL, VibrationParticle::ORDINAL,
        ItemSlimeParticle::ORDINAL, ItemSnowballParticle::ORDINAL, LargeSmokeParticle::ORDINAL, LavaParticle::ORDINAL, MyceliumParticle::ORDINAL,
        NoteParticle::ORDINAL, PoofParticle::ORDINAL, PortalParticle::ORDINAL, RainParticle::ORDINAL, SmokeParticle::ORDINAL, SneezeParticle::ORDINAL,
        SpitParticle::ORDINAL, SquidInkParticle::ORDINAL, SweepAttackParticle::ORDINAL, TotemOfUndyingParticle::ORDINAL, UnderwaterParticle::ORDINAL,
        SplashParticle::ORDINAL, WitchParticle::ORDINAL, BubblePopParticle::ORDINAL, CurrentDownParticle::ORDINAL, BubbleColumnUpParticle::ORDINAL,
        NautilusParticle::ORDINAL, DolphinParticle::ORDINAL, CampfireCosySmokeParticle::ORDINAL, CampfireSignalSmokeParticle::ORDINAL,
        DrippingHoneyParticle::ORDINAL, FallingHoneyParticle::ORDINAL, LandingHoneyParticle::ORDINAL, FallingNectarParticle::ORDINAL,
        FallingSporeBlossomParticle::ORDINAL, AshParticle::ORDINAL, CrimsonSporeParticle::ORDINAL, WarpedSporeParticle::ORDINAL,
        SporeBlossomAirParticle::ORDINAL, DrippingObsidianTearParticle::ORDINAL, FallingObsidianTearParticle::ORDINAL,
        LandingObsidianTearParticle::ORDINAL, ReversePortalParticle::ORDINAL, WhiteAshParticle::ORDINAL, SmallFlameParticle::ORDINAL,
        SnowflakeParticle::ORDINAL, DrippingDripstoneLavaParticle::ORDINAL, FallingDripstoneLavaParticle::ORDINAL, DrippingDripstoneWaterParticle::ORDINAL,
        FallingDripstoneWaterParticle::ORDINAL, GlowSquidInkParticle::ORDINAL, GlowParticle::ORDINAL, WaxOnParticle::ORDINAL, WaxOffParticle::ORDINAL,
        ElectricSparkParticle::ORDINAL, ScrapeParticle::ORDINAL}));

    particleRegistry.RegisterVersion(&MinecraftProtocolVersion::MINECRAFT_1_19,
      new VersionRegistry({AmbientEntityEffectParticle::ORDINAL, AngryVillagerParticle::ORDINAL, BlockParticle::ORDINAL, BlockMarkerParticle::ORDINAL,
        BubbleParticle::ORDINAL, CloudParticle::ORDINAL, CritParticle::ORDINAL, DamageIndicatorParticle::ORDINAL, DragonBreathParticle::ORDINAL,
        DrippingLavaParticle::ORDINAL, FallingLavaParticle::ORDINAL, LandingLavaParticle::ORDINAL, DrippingWaterParticle::ORDINAL,
        FallingWaterParticle::ORDINAL, DustParticle::ORDINAL, DustColorTransitionParticle::ORDINAL, EffectParticle::ORDINAL,
        ElderGuardianParticle::ORDINAL, EnchantedHitParticle::ORDINAL, EnchantParticle::ORDINAL, EndRodParticle::ORDINAL, EntityEffectParticle::ORDINAL,
        ExplosionEmitterParticle::ORDINAL, ExplosionParticle::ORDINAL, SonicBoomParticle::ORDINAL, FallingDustParticle::ORDINAL, FireworkParticle::ORDINAL,
        FishingParticle::ORDINAL, FlameParticle::ORDINAL, SculkSoulParticle::ORDINAL, SculkChargeParticle::ORDINAL, SculkChargePopParticle::ORDINAL,
        SoulFireFlameParticle::ORDINAL, SoulParticle::ORDINAL, FlashParticle::ORDINAL, HappyVillagerParticle::ORDINAL, ComposterParticle::ORDINAL,
        HeartParticle::ORDINAL, InstantEffectParticle::ORDINAL, ItemParticle::ORDINAL, VibrationParticle::ORDINAL, ItemSlimeParticle::ORDINAL,
        ItemSnowballParticle::ORDINAL, LargeSmokeParticle::ORDINAL, LavaParticle::ORDINAL, MyceliumParticle::ORDINAL, NoteParticle::ORDINAL,
        PoofParticle::ORDINAL, PortalParticle::ORDINAL, RainParticle::ORDINAL, SmokeParticle::ORDINAL, SneezeParticle::ORDINAL, SpitParticle::ORDINAL,
        SquidInkParticle::ORDINAL, SweepAttackParticle::ORDINAL, TotemOfUndyingParticle::ORDINAL, UnderwaterParticle::ORDINAL, SplashParticle::ORDINAL,
        WitchParticle::ORDINAL, BubblePopParticle::ORDINAL, CurrentDownParticle::ORDINAL, BubbleColumnUpParticle::ORDINAL, NautilusParticle::ORDINAL,
        DolphinParticle::ORDINAL, CampfireCosySmokeParticle::ORDINAL, CampfireSignalSmokeParticle::ORDINAL, DrippingHoneyParticle::ORDINAL,
        FallingHoneyParticle::ORDINAL, LandingHoneyParticle::ORDINAL, FallingNectarParticle::ORDINAL, FallingSporeBlossomParticle::ORDINAL,
        AshParticle::ORDINAL, CrimsonSporeParticle::ORDINAL, WarpedSporeParticle::ORDINAL, SporeBlossomAirParticle::ORDINAL,
        DrippingObsidianTearParticle::ORDINAL, FallingObsidianTearParticle::ORDINAL, LandingObsidianTearParticle::ORDINAL, ReversePortalParticle::ORDINAL,
        WhiteAshParticle::ORDINAL, SmallFlameParticle::ORDINAL, SnowflakeParticle::ORDINAL, DrippingDripstoneLavaParticle::ORDINAL,
        FallingDripstoneLavaParticle::ORDINAL, DrippingDripstoneWaterParticle::ORDINAL, FallingDripstoneWaterParticle::ORDINAL,
        GlowSquidInkParticle::ORDINAL, GlowParticle::ORDINAL, WaxOnParticle::ORDINAL, WaxOffParticle::ORDINAL, ElectricSparkParticle::ORDINAL,
        ShriekParticle::ORDINAL}));

    particleRegistry.RegisterConstructor(AmbientEntityEffectParticle::ORDINAL, WrapConstructor<AbstractParticle, AmbientEntityEffectParticle>());
    particleRegistry.RegisterConstructor(AngryVillagerParticle::ORDINAL, WrapConstructor<AbstractParticle, AngryVillagerParticle>());
    particleRegistry.RegisterConstructor(BarrierParticle::ORDINAL, WrapConstructor<AbstractParticle, BarrierParticle>());
    particleRegistry.RegisterConstructor(LightParticle::ORDINAL, WrapConstructor<AbstractParticle, LightParticle>());
    particleRegistry.RegisterConstructor(BlockParticle::ORDINAL, WrapConstructor<AbstractParticle, BlockParticle>());
    particleRegistry.RegisterConstructor(BlockMarkerParticle::ORDINAL, WrapConstructor<AbstractParticle, BlockMarkerParticle>());
    particleRegistry.RegisterConstructor(BubbleParticle::ORDINAL, WrapConstructor<AbstractParticle, BubbleParticle>());
    particleRegistry.RegisterConstructor(CloudParticle::ORDINAL, WrapConstructor<AbstractParticle, CloudParticle>());
    particleRegistry.RegisterConstructor(CritParticle::ORDINAL, WrapConstructor<AbstractParticle, CritParticle>());
    particleRegistry.RegisterConstructor(DamageIndicatorParticle::ORDINAL, WrapConstructor<AbstractParticle, DamageIndicatorParticle>());
    particleRegistry.RegisterConstructor(DragonBreathParticle::ORDINAL, WrapConstructor<AbstractParticle, DragonBreathParticle>());
    particleRegistry.RegisterConstructor(DrippingLavaParticle::ORDINAL, WrapConstructor<AbstractParticle, DrippingLavaParticle>());
    particleRegistry.RegisterConstructor(FallingLavaParticle::ORDINAL, WrapConstructor<AbstractParticle, FallingLavaParticle>());
    particleRegistry.RegisterConstructor(LandingLavaParticle::ORDINAL, WrapConstructor<AbstractParticle, LandingLavaParticle>());
    particleRegistry.RegisterConstructor(DrippingWaterParticle::ORDINAL, WrapConstructor<AbstractParticle, DrippingWaterParticle>());
    particleRegistry.RegisterConstructor(FallingWaterParticle::ORDINAL, WrapConstructor<AbstractParticle, FallingWaterParticle>());
    particleRegistry.RegisterConstructor(DustParticle::ORDINAL, WrapConstructor<AbstractParticle, DustParticle>());
    particleRegistry.RegisterConstructor(DustColorTransitionParticle::ORDINAL, WrapConstructor<AbstractParticle, DustColorTransitionParticle>());
    particleRegistry.RegisterConstructor(EffectParticle::ORDINAL, WrapConstructor<AbstractParticle, EffectParticle>());
    particleRegistry.RegisterConstructor(ElderGuardianParticle::ORDINAL, WrapConstructor<AbstractParticle, ElderGuardianParticle>());
    particleRegistry.RegisterConstructor(EnchantedHitParticle::ORDINAL, WrapConstructor<AbstractParticle, EnchantedHitParticle>());
    particleRegistry.RegisterConstructor(EnchantParticle::ORDINAL, WrapConstructor<AbstractParticle, EnchantParticle>());
    particleRegistry.RegisterConstructor(EndRodParticle::ORDINAL, WrapConstructor<AbstractParticle, EndRodParticle>());
    particleRegistry.RegisterConstructor(EntityEffectParticle::ORDINAL, WrapConstructor<AbstractParticle, EntityEffectParticle>());
    particleRegistry.RegisterConstructor(ExplosionEmitterParticle::ORDINAL, WrapConstructor<AbstractParticle, ExplosionEmitterParticle>());
    particleRegistry.RegisterConstructor(ExplosionParticle::ORDINAL, WrapConstructor<AbstractParticle, ExplosionParticle>());
    particleRegistry.RegisterConstructor(SonicBoomParticle::ORDINAL, WrapConstructor<AbstractParticle, SonicBoomParticle>());
    particleRegistry.RegisterConstructor(FallingDustParticle::ORDINAL, WrapConstructor<AbstractParticle, FallingDustParticle>());
    particleRegistry.RegisterConstructor(FireworkParticle::ORDINAL, WrapConstructor<AbstractParticle, FireworkParticle>());
    particleRegistry.RegisterConstructor(FishingParticle::ORDINAL, WrapConstructor<AbstractParticle, FishingParticle>());
    particleRegistry.RegisterConstructor(FlameParticle::ORDINAL, WrapConstructor<AbstractParticle, FlameParticle>());
    particleRegistry.RegisterConstructor(SculkSoulParticle::ORDINAL, WrapConstructor<AbstractParticle, SculkSoulParticle>());
    particleRegistry.RegisterConstructor(SculkChargeParticle::ORDINAL, WrapConstructor<AbstractParticle, SculkChargeParticle>());
    particleRegistry.RegisterConstructor(SculkChargePopParticle::ORDINAL, WrapConstructor<AbstractParticle, SculkChargePopParticle>());
    particleRegistry.RegisterConstructor(SoulFireFlameParticle::ORDINAL, WrapConstructor<AbstractParticle, SoulFireFlameParticle>());
    particleRegistry.RegisterConstructor(SoulParticle::ORDINAL, WrapConstructor<AbstractParticle, SoulParticle>());
    particleRegistry.RegisterConstructor(FlashParticle::ORDINAL, WrapConstructor<AbstractParticle, FlashParticle>());
    particleRegistry.RegisterConstructor(HappyVillagerParticle::ORDINAL, WrapConstructor<AbstractParticle, HappyVillagerParticle>());
    particleRegistry.RegisterConstructor(ComposterParticle::ORDINAL, WrapConstructor<AbstractParticle, ComposterParticle>());
    particleRegistry.RegisterConstructor(HeartParticle::ORDINAL, WrapConstructor<AbstractParticle, HeartParticle>());
    particleRegistry.RegisterConstructor(InstantEffectParticle::ORDINAL, WrapConstructor<AbstractParticle, InstantEffectParticle>());
    particleRegistry.RegisterConstructor(ItemParticle::ORDINAL, WrapConstructor<AbstractParticle, ItemParticle>());
    particleRegistry.RegisterConstructor(VibrationParticle::ORDINAL, WrapConstructor<AbstractParticle, VibrationParticle>());
    particleRegistry.RegisterConstructor(ItemSlimeParticle::ORDINAL, WrapConstructor<AbstractParticle, ItemSlimeParticle>());
    particleRegistry.RegisterConstructor(ItemSnowballParticle::ORDINAL, WrapConstructor<AbstractParticle, ItemSnowballParticle>());
    particleRegistry.RegisterConstructor(LargeSmokeParticle::ORDINAL, WrapConstructor<AbstractParticle, LargeSmokeParticle>());
    particleRegistry.RegisterConstructor(LavaParticle::ORDINAL, WrapConstructor<AbstractParticle, LavaParticle>());
    particleRegistry.RegisterConstructor(MyceliumParticle::ORDINAL, WrapConstructor<AbstractParticle, MyceliumParticle>());
    particleRegistry.RegisterConstructor(NoteParticle::ORDINAL, WrapConstructor<AbstractParticle, NoteParticle>());
    particleRegistry.RegisterConstructor(PoofParticle::ORDINAL, WrapConstructor<AbstractParticle, PoofParticle>());
    particleRegistry.RegisterConstructor(PortalParticle::ORDINAL, WrapConstructor<AbstractParticle, PortalParticle>());
    particleRegistry.RegisterConstructor(RainParticle::ORDINAL, WrapConstructor<AbstractParticle, RainParticle>());
    particleRegistry.RegisterConstructor(SmokeParticle::ORDINAL, WrapConstructor<AbstractParticle, SmokeParticle>());
    particleRegistry.RegisterConstructor(SneezeParticle::ORDINAL, WrapConstructor<AbstractParticle, SneezeParticle>());
    particleRegistry.RegisterConstructor(SpitParticle::ORDINAL, WrapConstructor<AbstractParticle, SpitParticle>());
    particleRegistry.RegisterConstructor(SquidInkParticle::ORDINAL, WrapConstructor<AbstractParticle, SquidInkParticle>());
    particleRegistry.RegisterConstructor(SweepAttackParticle::ORDINAL, WrapConstructor<AbstractParticle, SweepAttackParticle>());
    particleRegistry.RegisterConstructor(TotemOfUndyingParticle::ORDINAL, WrapConstructor<AbstractParticle, TotemOfUndyingParticle>());
    particleRegistry.RegisterConstructor(UnderwaterParticle::ORDINAL, WrapConstructor<AbstractParticle, UnderwaterParticle>());
    particleRegistry.RegisterConstructor(SplashParticle::ORDINAL, WrapConstructor<AbstractParticle, SplashParticle>());
    particleRegistry.RegisterConstructor(WitchParticle::ORDINAL, WrapConstructor<AbstractParticle, WitchParticle>());
    particleRegistry.RegisterConstructor(BubblePopParticle::ORDINAL, WrapConstructor<AbstractParticle, BubblePopParticle>());
    particleRegistry.RegisterConstructor(CurrentDownParticle::ORDINAL, WrapConstructor<AbstractParticle, CurrentDownParticle>());
    particleRegistry.RegisterConstructor(BubbleColumnUpParticle::ORDINAL, WrapConstructor<AbstractParticle, BubbleColumnUpParticle>());
    particleRegistry.RegisterConstructor(NautilusParticle::ORDINAL, WrapConstructor<AbstractParticle, NautilusParticle>());
    particleRegistry.RegisterConstructor(DolphinParticle::ORDINAL, WrapConstructor<AbstractParticle, DolphinParticle>());
    particleRegistry.RegisterConstructor(CampfireCosySmokeParticle::ORDINAL, WrapConstructor<AbstractParticle, CampfireCosySmokeParticle>());
    particleRegistry.RegisterConstructor(CampfireSignalSmokeParticle::ORDINAL, WrapConstructor<AbstractParticle, CampfireSignalSmokeParticle>());
    particleRegistry.RegisterConstructor(DrippingHoneyParticle::ORDINAL, WrapConstructor<AbstractParticle, DrippingHoneyParticle>());
    particleRegistry.RegisterConstructor(FallingHoneyParticle::ORDINAL, WrapConstructor<AbstractParticle, FallingHoneyParticle>());
    particleRegistry.RegisterConstructor(LandingHoneyParticle::ORDINAL, WrapConstructor<AbstractParticle, LandingHoneyParticle>());
    particleRegistry.RegisterConstructor(FallingNectarParticle::ORDINAL, WrapConstructor<AbstractParticle, FallingNectarParticle>());
    particleRegistry.RegisterConstructor(FallingSporeBlossomParticle::ORDINAL, WrapConstructor<AbstractParticle, FallingSporeBlossomParticle>());
    particleRegistry.RegisterConstructor(AshParticle::ORDINAL, WrapConstructor<AbstractParticle, AshParticle>());
    particleRegistry.RegisterConstructor(CrimsonSporeParticle::ORDINAL, WrapConstructor<AbstractParticle, CrimsonSporeParticle>());
    particleRegistry.RegisterConstructor(WarpedSporeParticle::ORDINAL, WrapConstructor<AbstractParticle, WarpedSporeParticle>());
    particleRegistry.RegisterConstructor(SporeBlossomAirParticle::ORDINAL, WrapConstructor<AbstractParticle, SporeBlossomAirParticle>());
    particleRegistry.RegisterConstructor(DrippingObsidianTearParticle::ORDINAL, WrapConstructor<AbstractParticle, DrippingObsidianTearParticle>());
    particleRegistry.RegisterConstructor(FallingObsidianTearParticle::ORDINAL, WrapConstructor<AbstractParticle, FallingObsidianTearParticle>());
    particleRegistry.RegisterConstructor(LandingObsidianTearParticle::ORDINAL, WrapConstructor<AbstractParticle, LandingObsidianTearParticle>());
    particleRegistry.RegisterConstructor(ReversePortalParticle::ORDINAL, WrapConstructor<AbstractParticle, ReversePortalParticle>());
    particleRegistry.RegisterConstructor(WhiteAshParticle::ORDINAL, WrapConstructor<AbstractParticle, WhiteAshParticle>());
    particleRegistry.RegisterConstructor(SmallFlameParticle::ORDINAL, WrapConstructor<AbstractParticle, SmallFlameParticle>());
    particleRegistry.RegisterConstructor(SnowflakeParticle::ORDINAL, WrapConstructor<AbstractParticle, SnowflakeParticle>());
    particleRegistry.RegisterConstructor(DrippingDripstoneLavaParticle::ORDINAL, WrapConstructor<AbstractParticle, DrippingDripstoneLavaParticle>());
    particleRegistry.RegisterConstructor(FallingDripstoneLavaParticle::ORDINAL, WrapConstructor<AbstractParticle, FallingDripstoneLavaParticle>());
    particleRegistry.RegisterConstructor(DrippingDripstoneWaterParticle::ORDINAL, WrapConstructor<AbstractParticle, DrippingDripstoneWaterParticle>());
    particleRegistry.RegisterConstructor(FallingDripstoneWaterParticle::ORDINAL, WrapConstructor<AbstractParticle, FallingDripstoneWaterParticle>());
    particleRegistry.RegisterConstructor(GlowSquidInkParticle::ORDINAL, WrapConstructor<AbstractParticle, GlowSquidInkParticle>());
    particleRegistry.RegisterConstructor(GlowParticle::ORDINAL, WrapConstructor<AbstractParticle, GlowParticle>());
    particleRegistry.RegisterConstructor(WaxOnParticle::ORDINAL, WrapConstructor<AbstractParticle, WaxOnParticle>());
    particleRegistry.RegisterConstructor(WaxOffParticle::ORDINAL, WrapConstructor<AbstractParticle, WaxOffParticle>());
    particleRegistry.RegisterConstructor(ElectricSparkParticle::ORDINAL, WrapConstructor<AbstractParticle, ElectricSparkParticle>());
    particleRegistry.RegisterConstructor(ScrapeParticle::ORDINAL, WrapConstructor<AbstractParticle, ScrapeParticle>());
    particleRegistry.RegisterConstructor(ShriekParticle::ORDINAL, WrapConstructor<AbstractParticle, ShriekParticle>());
    particleRegistry.RegisterConstructor(TakeParticle::ORDINAL, WrapConstructor<AbstractParticle, TakeParticle>());
    particleRegistry.RegisterConstructor(FootstepParticle::ORDINAL, WrapConstructor<AbstractParticle, FootstepParticle>());

    return particleRegistry;
  }

  const ConstructorRegistry<AbstractParticle> PARTICLE_REGISTRY = GetParticleRegistry();
}