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

    particleRegistry.RegisterConstructor(AmbientEntityEffectParticle::ORDINAL, CreateConstructor<AmbientEntityEffectParticle>());
    particleRegistry.RegisterConstructor(AngryVillagerParticle::ORDINAL, CreateConstructor<AngryVillagerParticle>());
    particleRegistry.RegisterConstructor(BarrierParticle::ORDINAL, CreateConstructor<BarrierParticle>());
    particleRegistry.RegisterConstructor(LightParticle::ORDINAL, CreateConstructor<LightParticle>());
    particleRegistry.RegisterConstructor(BlockParticle::ORDINAL, CreateConstructor<BlockParticle>());
    particleRegistry.RegisterConstructor(BlockMarkerParticle::ORDINAL, CreateConstructor<BlockMarkerParticle>());
    particleRegistry.RegisterConstructor(BubbleParticle::ORDINAL, CreateConstructor<BubbleParticle>());
    particleRegistry.RegisterConstructor(CloudParticle::ORDINAL, CreateConstructor<CloudParticle>());
    particleRegistry.RegisterConstructor(CritParticle::ORDINAL, CreateConstructor<CritParticle>());
    particleRegistry.RegisterConstructor(DamageIndicatorParticle::ORDINAL, CreateConstructor<DamageIndicatorParticle>());
    particleRegistry.RegisterConstructor(DragonBreathParticle::ORDINAL, CreateConstructor<DragonBreathParticle>());
    particleRegistry.RegisterConstructor(DrippingLavaParticle::ORDINAL, CreateConstructor<DrippingLavaParticle>());
    particleRegistry.RegisterConstructor(FallingLavaParticle::ORDINAL, CreateConstructor<FallingLavaParticle>());
    particleRegistry.RegisterConstructor(LandingLavaParticle::ORDINAL, CreateConstructor<LandingLavaParticle>());
    particleRegistry.RegisterConstructor(DrippingWaterParticle::ORDINAL, CreateConstructor<DrippingWaterParticle>());
    particleRegistry.RegisterConstructor(FallingWaterParticle::ORDINAL, CreateConstructor<FallingWaterParticle>());
    particleRegistry.RegisterConstructor(DustParticle::ORDINAL, CreateConstructor<DustParticle>());
    particleRegistry.RegisterConstructor(DustColorTransitionParticle::ORDINAL, CreateConstructor<DustColorTransitionParticle>());
    particleRegistry.RegisterConstructor(EffectParticle::ORDINAL, CreateConstructor<EffectParticle>());
    particleRegistry.RegisterConstructor(ElderGuardianParticle::ORDINAL, CreateConstructor<ElderGuardianParticle>());
    particleRegistry.RegisterConstructor(EnchantedHitParticle::ORDINAL, CreateConstructor<EnchantedHitParticle>());
    particleRegistry.RegisterConstructor(EnchantParticle::ORDINAL, CreateConstructor<EnchantParticle>());
    particleRegistry.RegisterConstructor(EndRodParticle::ORDINAL, CreateConstructor<EndRodParticle>());
    particleRegistry.RegisterConstructor(EntityEffectParticle::ORDINAL, CreateConstructor<EntityEffectParticle>());
    particleRegistry.RegisterConstructor(ExplosionEmitterParticle::ORDINAL, CreateConstructor<ExplosionEmitterParticle>());
    particleRegistry.RegisterConstructor(ExplosionParticle::ORDINAL, CreateConstructor<ExplosionParticle>());
    particleRegistry.RegisterConstructor(SonicBoomParticle::ORDINAL, CreateConstructor<SonicBoomParticle>());
    particleRegistry.RegisterConstructor(FallingDustParticle::ORDINAL, CreateConstructor<FallingDustParticle>());
    particleRegistry.RegisterConstructor(FireworkParticle::ORDINAL, CreateConstructor<FireworkParticle>());
    particleRegistry.RegisterConstructor(FishingParticle::ORDINAL, CreateConstructor<FishingParticle>());
    particleRegistry.RegisterConstructor(FlameParticle::ORDINAL, CreateConstructor<FlameParticle>());
    particleRegistry.RegisterConstructor(SculkSoulParticle::ORDINAL, CreateConstructor<SculkSoulParticle>());
    particleRegistry.RegisterConstructor(SculkChargeParticle::ORDINAL, CreateConstructor<SculkChargeParticle>());
    particleRegistry.RegisterConstructor(SculkChargePopParticle::ORDINAL, CreateConstructor<SculkChargePopParticle>());
    particleRegistry.RegisterConstructor(SoulFireFlameParticle::ORDINAL, CreateConstructor<SoulFireFlameParticle>());
    particleRegistry.RegisterConstructor(SoulParticle::ORDINAL, CreateConstructor<SoulParticle>());
    particleRegistry.RegisterConstructor(FlashParticle::ORDINAL, CreateConstructor<FlashParticle>());
    particleRegistry.RegisterConstructor(HappyVillagerParticle::ORDINAL, CreateConstructor<HappyVillagerParticle>());
    particleRegistry.RegisterConstructor(ComposterParticle::ORDINAL, CreateConstructor<ComposterParticle>());
    particleRegistry.RegisterConstructor(HeartParticle::ORDINAL, CreateConstructor<HeartParticle>());
    particleRegistry.RegisterConstructor(InstantEffectParticle::ORDINAL, CreateConstructor<InstantEffectParticle>());
    particleRegistry.RegisterConstructor(ItemParticle::ORDINAL, CreateConstructor<ItemParticle>());
    particleRegistry.RegisterConstructor(VibrationParticle::ORDINAL, CreateConstructor<VibrationParticle>());
    particleRegistry.RegisterConstructor(ItemSlimeParticle::ORDINAL, CreateConstructor<ItemSlimeParticle>());
    particleRegistry.RegisterConstructor(ItemSnowballParticle::ORDINAL, CreateConstructor<ItemSnowballParticle>());
    particleRegistry.RegisterConstructor(LargeSmokeParticle::ORDINAL, CreateConstructor<LargeSmokeParticle>());
    particleRegistry.RegisterConstructor(LavaParticle::ORDINAL, CreateConstructor<LavaParticle>());
    particleRegistry.RegisterConstructor(MyceliumParticle::ORDINAL, CreateConstructor<MyceliumParticle>());
    particleRegistry.RegisterConstructor(NoteParticle::ORDINAL, CreateConstructor<NoteParticle>());
    particleRegistry.RegisterConstructor(PoofParticle::ORDINAL, CreateConstructor<PoofParticle>());
    particleRegistry.RegisterConstructor(PortalParticle::ORDINAL, CreateConstructor<PortalParticle>());
    particleRegistry.RegisterConstructor(RainParticle::ORDINAL, CreateConstructor<RainParticle>());
    particleRegistry.RegisterConstructor(SmokeParticle::ORDINAL, CreateConstructor<SmokeParticle>());
    particleRegistry.RegisterConstructor(SneezeParticle::ORDINAL, CreateConstructor<SneezeParticle>());
    particleRegistry.RegisterConstructor(SpitParticle::ORDINAL, CreateConstructor<SpitParticle>());
    particleRegistry.RegisterConstructor(SquidInkParticle::ORDINAL, CreateConstructor<SquidInkParticle>());
    particleRegistry.RegisterConstructor(SweepAttackParticle::ORDINAL, CreateConstructor<SweepAttackParticle>());
    particleRegistry.RegisterConstructor(TotemOfUndyingParticle::ORDINAL, CreateConstructor<TotemOfUndyingParticle>());
    particleRegistry.RegisterConstructor(UnderwaterParticle::ORDINAL, CreateConstructor<UnderwaterParticle>());
    particleRegistry.RegisterConstructor(SplashParticle::ORDINAL, CreateConstructor<SplashParticle>());
    particleRegistry.RegisterConstructor(WitchParticle::ORDINAL, CreateConstructor<WitchParticle>());
    particleRegistry.RegisterConstructor(BubblePopParticle::ORDINAL, CreateConstructor<BubblePopParticle>());
    particleRegistry.RegisterConstructor(CurrentDownParticle::ORDINAL, CreateConstructor<CurrentDownParticle>());
    particleRegistry.RegisterConstructor(BubbleColumnUpParticle::ORDINAL, CreateConstructor<BubbleColumnUpParticle>());
    particleRegistry.RegisterConstructor(NautilusParticle::ORDINAL, CreateConstructor<NautilusParticle>());
    particleRegistry.RegisterConstructor(DolphinParticle::ORDINAL, CreateConstructor<DolphinParticle>());
    particleRegistry.RegisterConstructor(CampfireCosySmokeParticle::ORDINAL, CreateConstructor<CampfireCosySmokeParticle>());
    particleRegistry.RegisterConstructor(CampfireSignalSmokeParticle::ORDINAL, CreateConstructor<CampfireSignalSmokeParticle>());
    particleRegistry.RegisterConstructor(DrippingHoneyParticle::ORDINAL, CreateConstructor<DrippingHoneyParticle>());
    particleRegistry.RegisterConstructor(FallingHoneyParticle::ORDINAL, CreateConstructor<FallingHoneyParticle>());
    particleRegistry.RegisterConstructor(LandingHoneyParticle::ORDINAL, CreateConstructor<LandingHoneyParticle>());
    particleRegistry.RegisterConstructor(FallingNectarParticle::ORDINAL, CreateConstructor<FallingNectarParticle>());
    particleRegistry.RegisterConstructor(FallingSporeBlossomParticle::ORDINAL, CreateConstructor<FallingSporeBlossomParticle>());
    particleRegistry.RegisterConstructor(AshParticle::ORDINAL, CreateConstructor<AshParticle>());
    particleRegistry.RegisterConstructor(CrimsonSporeParticle::ORDINAL, CreateConstructor<CrimsonSporeParticle>());
    particleRegistry.RegisterConstructor(WarpedSporeParticle::ORDINAL, CreateConstructor<WarpedSporeParticle>());
    particleRegistry.RegisterConstructor(SporeBlossomAirParticle::ORDINAL, CreateConstructor<SporeBlossomAirParticle>());
    particleRegistry.RegisterConstructor(DrippingObsidianTearParticle::ORDINAL, CreateConstructor<DrippingObsidianTearParticle>());
    particleRegistry.RegisterConstructor(FallingObsidianTearParticle::ORDINAL, CreateConstructor<FallingObsidianTearParticle>());
    particleRegistry.RegisterConstructor(LandingObsidianTearParticle::ORDINAL, CreateConstructor<LandingObsidianTearParticle>());
    particleRegistry.RegisterConstructor(ReversePortalParticle::ORDINAL, CreateConstructor<ReversePortalParticle>());
    particleRegistry.RegisterConstructor(WhiteAshParticle::ORDINAL, CreateConstructor<WhiteAshParticle>());
    particleRegistry.RegisterConstructor(SmallFlameParticle::ORDINAL, CreateConstructor<SmallFlameParticle>());
    particleRegistry.RegisterConstructor(SnowflakeParticle::ORDINAL, CreateConstructor<SnowflakeParticle>());
    particleRegistry.RegisterConstructor(DrippingDripstoneLavaParticle::ORDINAL, CreateConstructor<DrippingDripstoneLavaParticle>());
    particleRegistry.RegisterConstructor(FallingDripstoneLavaParticle::ORDINAL, CreateConstructor<FallingDripstoneLavaParticle>());
    particleRegistry.RegisterConstructor(DrippingDripstoneWaterParticle::ORDINAL, CreateConstructor<DrippingDripstoneWaterParticle>());
    particleRegistry.RegisterConstructor(FallingDripstoneWaterParticle::ORDINAL, CreateConstructor<FallingDripstoneWaterParticle>());
    particleRegistry.RegisterConstructor(GlowSquidInkParticle::ORDINAL, CreateConstructor<GlowSquidInkParticle>());
    particleRegistry.RegisterConstructor(GlowParticle::ORDINAL, CreateConstructor<GlowParticle>());
    particleRegistry.RegisterConstructor(WaxOnParticle::ORDINAL, CreateConstructor<WaxOnParticle>());
    particleRegistry.RegisterConstructor(WaxOffParticle::ORDINAL, CreateConstructor<WaxOffParticle>());
    particleRegistry.RegisterConstructor(ElectricSparkParticle::ORDINAL, CreateConstructor<ElectricSparkParticle>());
    particleRegistry.RegisterConstructor(ScrapeParticle::ORDINAL, CreateConstructor<ScrapeParticle>());
    particleRegistry.RegisterConstructor(ShriekParticle::ORDINAL, CreateConstructor<ShriekParticle>());
    particleRegistry.RegisterConstructor(TakeParticle::ORDINAL, CreateConstructor<TakeParticle>());
    particleRegistry.RegisterConstructor(FootstepParticle::ORDINAL, CreateConstructor<FootstepParticle>());

    return particleRegistry;
  }

  const ConstructorRegistry<AbstractParticle> PARTICLE_REGISTRY = GetParticleRegistry();
}