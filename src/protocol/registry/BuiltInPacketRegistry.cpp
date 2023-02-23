#include "BuiltInPacketRegistry.hpp"
#include "../packets/handshake/Handshake.hpp"
#include "../packets/login/EncryptionRequest.hpp"
#include "../packets/login/EncryptionResponse.hpp"
#include "../packets/login/LoginPluginMessage.hpp"
#include "../packets/login/LoginPluginResponse.hpp"
#include "../packets/login/LoginStart.hpp"
#include "../packets/login/LoginSuccess.hpp"
#include "../packets/login/SetCompression.hpp"
#include "../packets/play/AcknowledgeBlockChange.hpp"
#include "../packets/play/AcknowledgePlayerDigging.hpp"
#include "../packets/play/ActionBar.hpp"
#include "../packets/play/Advancements.hpp"
#include "../packets/play/AwardStatistics.hpp"
#include "../packets/play/BeaconEffect.hpp"
#include "../packets/play/BlockAction.hpp"
#include "../packets/play/BlockDestroyStage.hpp"
#include "../packets/play/BlockEntityData.hpp"
#include "../packets/play/BlockTagQueryRequest.hpp"
#include "../packets/play/BlockUpdate.hpp"
#include "../packets/play/BoatPaddle.hpp"
#include "../packets/play/BorderCenter.hpp"
#include "../packets/play/BorderRadius.hpp"
#include "../packets/play/BorderRadiusSpeed.hpp"
#include "../packets/play/BorderWarningRadius.hpp"
#include "../packets/play/BorderWarningTime.hpp"
#include "../packets/play/BossBar.hpp"
#include "../packets/play/Camera.hpp"
#include "../packets/play/ChangeRecipeBookSettings.hpp"
#include "../packets/play/ChatSuggestions.hpp"
#include "../packets/play/ChunkData.hpp"
#include "../packets/play/ChunkLight.hpp"
#include "../packets/play/ClearTitle.hpp"
#include "../packets/play/ClickInventoryButton.hpp"
#include "../packets/play/ClickSlot.hpp"
#include "../packets/play/ClientAction.hpp"
#include "../packets/play/ClientChangeDifficulty.hpp"
#include "../packets/play/ClientChatPreview.hpp"
#include "../packets/play/ClientPlayerAbilities.hpp"
#include "../packets/play/ClientPlayerChat.hpp"
#include "../packets/play/ClientSettings.hpp"
#include "../packets/play/CloseInventory.hpp"
#include "../packets/play/CombatEvent.hpp"
#include "../packets/play/Command.hpp"
#include "../packets/play/CommandSuggestionRequest.hpp"
#include "../packets/play/CommandSuggestionResponse.hpp"
#include "../packets/play/ConfirmTeleport.hpp"
#include "../packets/play/ConfirmTransaction.hpp"
#include "../packets/play/Cooldown.hpp"
#include "../packets/play/CraftRecipeRequest.hpp"
#include "../packets/play/CraftRecipeResponse.hpp"
#include "../packets/play/CreativeSlot.hpp"
#include "../packets/play/CustomSoundEffect.hpp"
#include "../packets/play/DeathCombatEvent.hpp"
#include "../packets/play/DeclareCommands.hpp"
#include "../packets/play/DefaultSpawnPosition.hpp"
#include "../packets/play/Digging.hpp"
#include "../packets/play/Disconnect.hpp"
#include "../packets/play/DisguisedChatMessage.hpp"
#include "../packets/play/DisplayObjective.hpp"
#include "../packets/play/EditBook.hpp"
#include "../packets/play/EditSign.hpp"
#include "../packets/play/EndCombatEvent.hpp"
#include "../packets/play/EnterCombatEvent.hpp"
#include "../packets/play/EntityAction.hpp"
#include "../packets/play/EntityAnimation.hpp"
#include "../packets/play/EntityEffect.hpp"
#include "../packets/play/EntityEffectRemove.hpp"
#include "../packets/play/EntityEquipment.hpp"
#include "../packets/play/EntityEvent.hpp"
#include "../packets/play/EntityInteract.hpp"
#include "../packets/play/EntityLookAt.hpp"
#include "../packets/play/EntityMetadata.hpp"
#include "../packets/play/EntityNotMoved.hpp"
#include "../packets/play/EntityPosition.hpp"
#include "../packets/play/EntityPositionAndRotation.hpp"
#include "../packets/play/EntityProperties.hpp"
#include "../packets/play/EntityRemove.hpp"
#include "../packets/play/EntityRotation.hpp"
#include "../packets/play/EntitySoundEffect.hpp"
#include "../packets/play/EntityTeleport.hpp"
#include "../packets/play/EntityVelocity.hpp"
#include "../packets/play/Experience.hpp"
#include "../packets/play/Explosion.hpp"
#include "../packets/play/FeatureFlags.hpp"
#include "../packets/play/GameEvent.hpp"
#include "../packets/play/GenerateStructure.hpp"
#include "../packets/play/HardcodedSoundEffect.hpp"
#include "../packets/play/Health.hpp"
#include "../packets/play/HeldSlot.hpp"
#include "../packets/play/HideMessage.hpp"
#include "../packets/play/InitializeWorldBorder.hpp"
#include "../packets/play/InventoryContent.hpp"
#include "../packets/play/InventoryProperty.hpp"
#include "../packets/play/InventorySlot.hpp"
#include "../packets/play/JoinGame.hpp"
#include "../packets/play/KeepAlive.hpp"
#include "../packets/play/LeadEntities.hpp"
#include "../packets/play/LegacyChat.hpp"
#include "../packets/play/LegacyCraftRecipeResponse.hpp"
#include "../packets/play/LegacyEnchant.hpp"
#include "../packets/play/LegacyRecipeBook.hpp"
#include "../packets/play/LegacyTitle.hpp"
#include "../packets/play/LegacyWorldBorder.hpp"
#include "../packets/play/LockDifficulty.hpp"
#include "../packets/play/MapData.hpp"
#include "../packets/play/MessageAcknowledgment.hpp"
#include "../packets/play/MessageHeader.hpp"
#include "../packets/play/Move.hpp"
#include "../packets/play/MoveGroundOnly.hpp"
#include "../packets/play/MovePositionOnly.hpp"
#include "../packets/play/MoveRotationOnly.hpp"
#include "../packets/play/MoveVehicle.hpp"
#include "../packets/play/Objectives.hpp"
#include "../packets/play/OpenBook.hpp"
#include "../packets/play/OpenHorseInventory.hpp"
#include "../packets/play/OpenInventory.hpp"
#include "../packets/play/OpenSignEditor.hpp"
#include "../packets/play/Particle.hpp"
#include "../packets/play/Passengers.hpp"
#include "../packets/play/PickItem.hpp"
#include "../packets/play/PickupItem.hpp"
#include "../packets/play/Ping.hpp"
#include "../packets/play/PlaceBlock.hpp"
#include "../packets/play/PlayerChatSession.hpp"
#include "../packets/play/PlayerFace.hpp"
#include "../packets/play/PlayerInput.hpp"
#include "../packets/play/PlayerListItem.hpp"
#include "../packets/play/PlayerRemove.hpp"
#include "../packets/play/PluginMessage.hpp"
#include "../packets/play/PositionRotation.hpp"
#include "../packets/play/ProgramCommandBlock.hpp"
#include "../packets/play/ProgramCommandBlockMinecart.hpp"
#include "../packets/play/ProgramJigsawBlock.hpp"
#include "../packets/play/ProgramStructureBlock.hpp"
#include "../packets/play/Recipes.hpp"
#include "../packets/play/RenameItem.hpp"
#include "../packets/play/ResourcePackRequest.hpp"
#include "../packets/play/ResourcePackResponse.hpp"
#include "../packets/play/Respawn.hpp"
#include "../packets/play/Score.hpp"
#include "../packets/play/SculkVibration.hpp"
#include "../packets/play/SectionBlocks.hpp"
#include "../packets/play/SeenRecipe.hpp"
#include "../packets/play/SelectAdvancementsTab.hpp"
#include "../packets/play/SelectTrade.hpp"
#include "../packets/play/ServerChangeDifficulty.hpp"
#include "../packets/play/ServerChatPreview.hpp"
#include "../packets/play/ServerData.hpp"
#include "../packets/play/ServerPlayerAbilities.hpp"
#include "../packets/play/ServerPlayerChat.hpp"
#include "../packets/play/SetDisplayChatPreview.hpp"
#include "../packets/play/SimulationDistance.hpp"
#include "../packets/play/SpawnEntity.hpp"
#include "../packets/play/SpawnExperienceOrb.hpp"
#include "../packets/play/SpawnPainting.hpp"
#include "../packets/play/SpawnPlayer.hpp"
#include "../packets/play/SpawnThunderbolt.hpp"
#include "../packets/play/Spectate.hpp"
#include "../packets/play/StopSound.hpp"
#include "../packets/play/Subtitle.hpp"
#include "../packets/play/SwingArm.hpp"
#include "../packets/play/SystemChat.hpp"
#include "../packets/play/TabHeaderFooter.hpp"
#include "../packets/play/TagQueryRequest.hpp"
#include "../packets/play/TagQueryResponse.hpp"
#include "../packets/play/Tags.hpp"
#include "../packets/play/Teams.hpp"
#include "../packets/play/Title.hpp"
#include "../packets/play/TitleTimes.hpp"
#include "../packets/play/TradeList.hpp"
#include "../packets/play/UnloadChunk.hpp"
#include "../packets/play/UnlockRecipes.hpp"
#include "../packets/play/UseBed.hpp"
#include "../packets/play/UseItem.hpp"
#include "../packets/play/ViewDistance.hpp"
#include "../packets/play/ViewPosition.hpp"
#include "../packets/play/WorldEvent.hpp"
#include "../packets/play/WorldTime.hpp"
#include "../packets/status/StatusPing.hpp"
#include "../packets/status/StatusRequest.hpp"
#include "../packets/status/StatusResponse.hpp"

namespace Ship {

  PacketRegistry GetHandshakeRegistry() {
    auto* serverbound = new DirectionRegistry();
    serverbound->RegisterPacketConstructor(Handshake::PACKET_ORDINAL, CreateConstructor<Handshake>());
    serverbound->FillVersionRegistry(new VersionRegistry({Handshake::PACKET_ORDINAL}));

    return {nullptr, serverbound};
  }

  PacketRegistry GetStatusRegistry() {
    auto* clientbound = new DirectionRegistry();
    clientbound->RegisterPacketConstructor(StatusResponse::PACKET_ORDINAL, CreateConstructor<StatusResponse>(std::string {}));
    clientbound->RegisterPacketConstructor(StatusPing::PACKET_ORDINAL, CreateConstructor<StatusPing>(0));
    clientbound->FillVersionRegistry(new VersionRegistry({StatusResponse::PACKET_ORDINAL, StatusPing::PACKET_ORDINAL}));

    auto* serverbound = new DirectionRegistry();
    serverbound->RegisterPacketConstructor(StatusRequest::PACKET_ORDINAL, CreateConstructor<StatusRequest>());
    serverbound->RegisterPacketConstructor(StatusPing::PACKET_ORDINAL, CreateConstructor<StatusPing>(0));
    serverbound->FillVersionRegistry(new VersionRegistry({StatusRequest::PACKET_ORDINAL, StatusPing::PACKET_ORDINAL}));

    return {clientbound, serverbound};
  }

  PacketRegistry GetLoginRegistry() {
    auto* clientbound = new DirectionRegistry();
    clientbound->RegisterPacketConstructor(Disconnect::PACKET_ORDINAL, CreateConstructor<Disconnect>(std::string {}));
    clientbound->RegisterPacketConstructor(EncryptionRequest::PACKET_ORDINAL, CreateConstructor<EncryptionRequest>());
    clientbound->RegisterPacketConstructor(
      LoginSuccess::PACKET_ORDINAL, CreateConstructor<LoginSuccess>(UUID {}, std::string {}, std::vector<GameProfileProperty> {}));
    clientbound->RegisterPacketConstructor(SetCompression::PACKET_ORDINAL, CreateConstructor<SetCompression>(0));
    clientbound->RegisterPacketConstructor(LoginPluginMessage::PACKET_ORDINAL, CreateConstructor<LoginPluginMessage>());
    clientbound->FillVersionRegistry(new VersionRegistry({Disconnect::PACKET_ORDINAL, EncryptionRequest::PACKET_ORDINAL, LoginSuccess::PACKET_ORDINAL,
      SetCompression::PACKET_ORDINAL, LoginPluginMessage::PACKET_ORDINAL}));

    auto* serverbound = new DirectionRegistry();
    serverbound->RegisterPacketConstructor(LoginStart::PACKET_ORDINAL, CreateConstructor<LoginStart>(std::string {}, false, 0, 0, nullptr, 0, nullptr));
    serverbound->RegisterPacketConstructor(EncryptionResponse::PACKET_ORDINAL, CreateConstructor<EncryptionResponse>());
    serverbound->RegisterPacketConstructor(LoginPluginResponse::PACKET_ORDINAL, CreateConstructor<LoginPluginResponse>());
    serverbound->FillVersionRegistry(
      new VersionRegistry({LoginStart::PACKET_ORDINAL, EncryptionResponse::PACKET_ORDINAL, LoginPluginResponse::PACKET_ORDINAL}));

    return {clientbound, serverbound};
  }

  PacketRegistry GetPlayRegistry() {
    auto* clientbound = new DirectionRegistry();

    clientbound->RegisterPacketConstructor(SpawnEntity::PACKET_ORDINAL, CreateConstructor<SpawnEntity>(0, UUID {}, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0));
    clientbound->RegisterPacketConstructor(SpawnExperienceOrb::PACKET_ORDINAL, CreateConstructor<SpawnExperienceOrb>(0, 0, 0, 0, 0));
    clientbound->RegisterPacketConstructor(SpawnThunderbolt::PACKET_ORDINAL, CreateConstructor<SpawnThunderbolt>());
    clientbound->RegisterPacketConstructor(SpawnPainting::PACKET_ORDINAL, CreateConstructor<SpawnPainting>());
    clientbound->RegisterPacketConstructor(SpawnPlayer::PACKET_ORDINAL, CreateConstructor<SpawnPlayer>(0, UUID {}, 0, 0, 0, 0, 0, nullptr));
    clientbound->RegisterPacketConstructor(EntityAnimation::PACKET_ORDINAL, CreateConstructor<EntityAnimation>(0, 0));
    clientbound->RegisterPacketConstructor(AwardStatistics::PACKET_ORDINAL, CreateConstructor<AwardStatistics>(std::vector<Statistic> {}));
    clientbound->RegisterPacketConstructor(AcknowledgeBlockChange::PACKET_ORDINAL, CreateConstructor<AcknowledgeBlockChange>(0));
    clientbound->RegisterPacketConstructor(AcknowledgePlayerDigging::PACKET_ORDINAL, CreateConstructor<AcknowledgePlayerDigging>(0, 0, 0, 0, 0, false));
    clientbound->RegisterPacketConstructor(BlockDestroyStage::PACKET_ORDINAL, CreateConstructor<BlockDestroyStage>(0, 0, 0, 0, 0));
    clientbound->RegisterPacketConstructor(BlockEntityData::PACKET_ORDINAL, CreateConstructor<BlockEntityData>(0, 0, 0, 0, nullptr));
    clientbound->RegisterPacketConstructor(BlockAction::PACKET_ORDINAL, CreateConstructor<BlockAction>(0, 0, 0, 0, 0, 0));
    clientbound->RegisterPacketConstructor(BlockUpdate::PACKET_ORDINAL, CreateConstructor<BlockUpdate>(0, 0, 0, 0));
    clientbound->RegisterPacketConstructor(BossBar::PACKET_ORDINAL, CreateConstructor<BossBar>(UUID {}, nullptr));
    clientbound->RegisterPacketConstructor(ServerChangeDifficulty::PACKET_ORDINAL, CreateConstructor<ServerChangeDifficulty>(Difficulty {}, false));
    clientbound->RegisterPacketConstructor(ServerChatPreview::PACKET_ORDINAL, CreateConstructor<ServerChatPreview>(0, std::nullopt));
    clientbound->RegisterPacketConstructor(ClearTitle::PACKET_ORDINAL, CreateConstructor<ClearTitle>(false));
    clientbound->RegisterPacketConstructor(
      CommandSuggestionResponse::PACKET_ORDINAL, CreateConstructor<CommandSuggestionResponse>(0, 0, 0, std::vector<CommandSuggestion> {}));
    clientbound->RegisterPacketConstructor(DeclareCommands::PACKET_ORDINAL, CreateConstructor<DeclareCommands>());
    clientbound->RegisterPacketConstructor(CloseInventory::PACKET_ORDINAL, CreateConstructor<CloseInventory>(0));
    clientbound->RegisterPacketConstructor(
      InventoryContent::PACKET_ORDINAL, CreateConstructor<InventoryContent>(0, 0, std::vector<ItemStack> {}, ItemStack {}));
    clientbound->RegisterPacketConstructor(InventoryProperty::PACKET_ORDINAL, CreateConstructor<InventoryProperty>(0, 0, 0));
    clientbound->RegisterPacketConstructor(InventorySlot::PACKET_ORDINAL, CreateConstructor<InventorySlot>(0, 0, 0, ItemStack {}));
    clientbound->RegisterPacketConstructor(Cooldown::PACKET_ORDINAL, CreateConstructor<Cooldown>(0, 0));
    clientbound->RegisterPacketConstructor(ChatSuggestions::PACKET_ORDINAL, CreateConstructor<ChatSuggestions>(0, std::vector<std::string> {}));
    clientbound->RegisterPacketConstructor(PluginMessage::PACKET_ORDINAL, CreateConstructor<PluginMessage>(std::string {}, nullptr));
    clientbound->RegisterPacketConstructor(CustomSoundEffect::PACKET_ORDINAL, CreateConstructor<CustomSoundEffect>(std::string {}, 0, 0, 0, 0, 0, 0, 0));
    clientbound->RegisterPacketConstructor(HideMessage::PACKET_ORDINAL, CreateConstructor<HideMessage>(nullptr));
    clientbound->RegisterPacketConstructor(Disconnect::PACKET_ORDINAL, CreateConstructor<Disconnect>(std::string {}));
    clientbound->RegisterPacketConstructor(EntityEvent::PACKET_ORDINAL, CreateConstructor<EntityEvent>(0, 0));
    clientbound->RegisterPacketConstructor(
      Explosion::PACKET_ORDINAL, CreateConstructor<Explosion>(0, 0, 0, 0, std::vector<std::array<uint8_t, 3>> {}, 0, 0, 0));
    clientbound->RegisterPacketConstructor(UnloadChunk::PACKET_ORDINAL, CreateConstructor<UnloadChunk>(0, 0));
    clientbound->RegisterPacketConstructor(GameEvent::PACKET_ORDINAL, CreateConstructor<GameEvent>(0, 0));
    clientbound->RegisterPacketConstructor(OpenHorseInventory::PACKET_ORDINAL, CreateConstructor<OpenHorseInventory>(0, 0, 0));
    clientbound->RegisterPacketConstructor(InitializeWorldBorder::PACKET_ORDINAL, CreateConstructor<InitializeWorldBorder>(0, 0, 0, 0, 0, 0, 0, 0));
    clientbound->RegisterPacketConstructor(KeepAlive::PACKET_ORDINAL, CreateConstructor<KeepAlive>(0));
    clientbound->RegisterPacketConstructor(ChunkData::PACKET_ORDINAL, CreateConstructor<ChunkData>());
    clientbound->RegisterPacketConstructor(WorldEvent::PACKET_ORDINAL, CreateConstructor<WorldEvent>(0, 0, 0, 0, 0, false));
    clientbound->RegisterPacketConstructor(EntitySoundEffect::PACKET_ORDINAL, CreateConstructor<EntitySoundEffect>());
    clientbound->RegisterPacketConstructor(Particle::PACKET_ORDINAL, CreateConstructor<Particle>(nullptr, false, 0, 0, 0, 0, 0, 0, 0, 0));
    clientbound->RegisterPacketConstructor(ChunkLight::PACKET_ORDINAL, CreateConstructor<ChunkLight>());
    clientbound->RegisterPacketConstructor(JoinGame::PACKET_ORDINAL,
      CreateConstructor<JoinGame>(0, Gamemode {}, 0, Difficulty {}, false, 0, 0, false, false, std::set<std::string> {},
        std::map<std::string, Dimension> {}, std::string {}, std::string {}, false, false,
        Dimension {std::string {}, 0, 0, 0, false, 0, false, false, false, false, false, false, false, false, false, 0, std::string {},
          std::optional<uint64_t> {}, std::optional<bool> {}, std::optional<double> {}, std::optional<std::string> {}, 0, 0, 0, 0, nullptr},
        Gamemode {}, nullptr, 0, false, std::pair<std::string, uint64_t> {}, nullptr, nullptr));
    clientbound->RegisterPacketConstructor(
      MapData::PACKET_ORDINAL, CreateConstructor<MapData>(0, 0, false, false, std::vector<MapIcon> {}, 0, 0, 0, 0, 0, nullptr));
    clientbound->RegisterPacketConstructor(TradeList::PACKET_ORDINAL, CreateConstructor<TradeList>(0, std::vector<Trade> {}, 0, 0, false, false));
    clientbound->RegisterPacketConstructor(EntityNotMoved::PACKET_ORDINAL, CreateConstructor<EntityNotMoved>());
    clientbound->RegisterPacketConstructor(EntityPosition::PACKET_ORDINAL, CreateConstructor<EntityPosition>(0, 0, 0, 0, false));
    clientbound->RegisterPacketConstructor(
      EntityPositionAndRotation::PACKET_ORDINAL, CreateConstructor<EntityPositionAndRotation>(0, 0, 0, 0, 0, 0, false));
    clientbound->RegisterPacketConstructor(EntityRotation::PACKET_ORDINAL, CreateConstructor<EntityRotation>(0, 0, 0, false));
    clientbound->RegisterPacketConstructor(MoveVehicle::PACKET_ORDINAL, CreateConstructor<MoveVehicle>(0, 0, 0, 0, 0));
    clientbound->RegisterPacketConstructor(OpenBook::PACKET_ORDINAL, CreateConstructor<OpenBook>(0));
    clientbound->RegisterPacketConstructor(OpenInventory::PACKET_ORDINAL, CreateConstructor<OpenInventory>(0, 0, std::string {}));
    clientbound->RegisterPacketConstructor(OpenSignEditor::PACKET_ORDINAL, CreateConstructor<OpenSignEditor>(0, 0, 0));
    clientbound->RegisterPacketConstructor(Ping::PACKET_ORDINAL, CreateConstructor<Ping>(0));
    clientbound->RegisterPacketConstructor(CraftRecipeResponse::PACKET_ORDINAL, CreateConstructor<CraftRecipeResponse>(0, std::string {}));
    clientbound->RegisterPacketConstructor(LegacyCraftRecipeResponse::PACKET_ORDINAL, CreateConstructor<LegacyCraftRecipeResponse>(0, 0));
    clientbound->RegisterPacketConstructor(
      ServerPlayerAbilities::PACKET_ORDINAL, CreateConstructor<ServerPlayerAbilities>(false, false, false, false, 0, 0));
    clientbound->RegisterPacketConstructor(MessageHeader::PACKET_ORDINAL, CreateConstructor<MessageHeader>(nullptr, UUID {}));
    clientbound->RegisterPacketConstructor(LegacyChat::PACKET_ORDINAL, CreateConstructor<LegacyChat>());
    clientbound->RegisterPacketConstructor(ServerPlayerChat::PACKET_ORDINAL, CreateConstructor<ServerPlayerChat>());
    clientbound->RegisterPacketConstructor(CombatEvent::PACKET_ORDINAL, CreateConstructor<CombatEvent>());
    clientbound->RegisterPacketConstructor(EndCombatEvent::PACKET_ORDINAL, CreateConstructor<EndCombatEvent>(0, 0));
    clientbound->RegisterPacketConstructor(EnterCombatEvent::PACKET_ORDINAL, CreateConstructor<EnterCombatEvent>());
    clientbound->RegisterPacketConstructor(DeathCombatEvent::PACKET_ORDINAL, CreateConstructor<DeathCombatEvent>(0, 0, std::string {}));
    clientbound->RegisterPacketConstructor(PlayerListItem::PACKET_ORDINAL, CreateConstructor<PlayerListItem>(0, std::vector<PlayerListAction*> {}));
    clientbound->RegisterPacketConstructor(PlayerFace::PACKET_ORDINAL, CreateConstructor<PlayerFace>());
    clientbound->RegisterPacketConstructor(PositionRotation::PACKET_ORDINAL, CreateConstructor<PositionRotation>());
    clientbound->RegisterPacketConstructor(UseBed::PACKET_ORDINAL, CreateConstructor<UseBed>());
    clientbound->RegisterPacketConstructor(UnlockRecipes::PACKET_ORDINAL, CreateConstructor<UnlockRecipes>());
    clientbound->RegisterPacketConstructor(EntityRemove::PACKET_ORDINAL, CreateConstructor<EntityRemove>());
    clientbound->RegisterPacketConstructor(EntityEffectRemove::PACKET_ORDINAL, CreateConstructor<EntityEffectRemove>());
    clientbound->RegisterPacketConstructor(ResourcePackRequest::PACKET_ORDINAL, CreateConstructor<ResourcePackRequest>());
    clientbound->RegisterPacketConstructor(Respawn::PACKET_ORDINAL, CreateConstructor<Respawn>());
    clientbound->RegisterPacketConstructor(EntityLookAt::PACKET_ORDINAL, CreateConstructor<EntityLookAt>());
    clientbound->RegisterPacketConstructor(SectionBlocks::PACKET_ORDINAL, CreateConstructor<SectionBlocks>());
    clientbound->RegisterPacketConstructor(SelectAdvancementsTab::PACKET_ORDINAL, CreateConstructor<SelectAdvancementsTab>());
    clientbound->RegisterPacketConstructor(ServerData::PACKET_ORDINAL, CreateConstructor<ServerData>());
    clientbound->RegisterPacketConstructor(ActionBar::PACKET_ORDINAL, CreateConstructor<ActionBar>());
    clientbound->RegisterPacketConstructor(BorderCenter::PACKET_ORDINAL, CreateConstructor<BorderCenter>());
    clientbound->RegisterPacketConstructor(BorderRadiusSpeed::PACKET_ORDINAL, CreateConstructor<BorderRadiusSpeed>());
    clientbound->RegisterPacketConstructor(BorderRadius::PACKET_ORDINAL, CreateConstructor<BorderRadius>());
    clientbound->RegisterPacketConstructor(BorderWarningTime::PACKET_ORDINAL, CreateConstructor<BorderWarningTime>());
    clientbound->RegisterPacketConstructor(BorderWarningRadius::PACKET_ORDINAL, CreateConstructor<BorderWarningRadius>());
    clientbound->RegisterPacketConstructor(LegacyWorldBorder::PACKET_ORDINAL, CreateConstructor<LegacyWorldBorder>());
    clientbound->RegisterPacketConstructor(Camera::PACKET_ORDINAL, CreateConstructor<Camera>());
    clientbound->RegisterPacketConstructor(HeldSlot::PACKET_ORDINAL, CreateConstructor<HeldSlot>());
    clientbound->RegisterPacketConstructor(ViewPosition::PACKET_ORDINAL, CreateConstructor<ViewPosition>());
    clientbound->RegisterPacketConstructor(ViewDistance::PACKET_ORDINAL, CreateConstructor<ViewDistance>());
    clientbound->RegisterPacketConstructor(DefaultSpawnPosition::PACKET_ORDINAL, CreateConstructor<DefaultSpawnPosition>());
    // clientbound->RegisterPacketConstructor(); TODO: SetDisplayChatPreview
    clientbound->RegisterPacketConstructor(DisplayObjective::PACKET_ORDINAL, CreateConstructor<DisplayObjective>());
    clientbound->RegisterPacketConstructor(EntityMetadata::PACKET_ORDINAL, CreateConstructor<EntityMetadata>());
    clientbound->RegisterPacketConstructor(LeadEntities::PACKET_ORDINAL, CreateConstructor<LeadEntities>());
    clientbound->RegisterPacketConstructor(EntityVelocity::PACKET_ORDINAL, CreateConstructor<EntityVelocity>());
    clientbound->RegisterPacketConstructor(EntityEquipment::PACKET_ORDINAL, CreateConstructor<EntityEquipment>());
    clientbound->RegisterPacketConstructor(Experience::PACKET_ORDINAL, CreateConstructor<Experience>());
    clientbound->RegisterPacketConstructor(Health::PACKET_ORDINAL, CreateConstructor<Health>());
    clientbound->RegisterPacketConstructor(Objectives::PACKET_ORDINAL, CreateConstructor<Objectives>());
    clientbound->RegisterPacketConstructor(Passengers::PACKET_ORDINAL, CreateConstructor<Passengers>());
    clientbound->RegisterPacketConstructor(Teams::PACKET_ORDINAL, CreateConstructor<Teams>());
    clientbound->RegisterPacketConstructor(Score::PACKET_ORDINAL, CreateConstructor<Score>());
    clientbound->RegisterPacketConstructor(SimulationDistance::PACKET_ORDINAL, CreateConstructor<SimulationDistance>());
    clientbound->RegisterPacketConstructor(Subtitle::PACKET_ORDINAL, CreateConstructor<Subtitle>());
    clientbound->RegisterPacketConstructor(WorldTime::PACKET_ORDINAL, CreateConstructor<WorldTime>());
    clientbound->RegisterPacketConstructor(LegacyTitle::PACKET_ORDINAL, CreateConstructor<LegacyTitle>());
    clientbound->RegisterPacketConstructor(Title::PACKET_ORDINAL, CreateConstructor<Title>());
    clientbound->RegisterPacketConstructor(TitleTimes::PACKET_ORDINAL, CreateConstructor<TitleTimes>());
    clientbound->RegisterPacketConstructor(EntitySoundEffect::PACKET_ORDINAL, CreateConstructor<EntitySoundEffect>());
    clientbound->RegisterPacketConstructor(HardcodedSoundEffect::PACKET_ORDINAL, CreateConstructor<HardcodedSoundEffect>());
    clientbound->RegisterPacketConstructor(StopSound::PACKET_ORDINAL, CreateConstructor<StopSound>());
    clientbound->RegisterPacketConstructor(SystemChat::PACKET_ORDINAL, CreateConstructor<SystemChat>());
    clientbound->RegisterPacketConstructor(TabHeaderFooter::PACKET_ORDINAL, CreateConstructor<TabHeaderFooter>());
    clientbound->RegisterPacketConstructor(TagQueryResponse::PACKET_ORDINAL, CreateConstructor<TagQueryResponse>());
    clientbound->RegisterPacketConstructor(PickupItem::PACKET_ORDINAL, CreateConstructor<PickupItem>());
    clientbound->RegisterPacketConstructor(EntityTeleport::PACKET_ORDINAL, CreateConstructor<EntityTeleport>());
    clientbound->RegisterPacketConstructor(Advancements::PACKET_ORDINAL, CreateConstructor<Advancements>());
    clientbound->RegisterPacketConstructor(EntityProperties::PACKET_ORDINAL, CreateConstructor<EntityProperties>());
    clientbound->RegisterPacketConstructor(EntityEffect::PACKET_ORDINAL, CreateConstructor<EntityEffect>());
    clientbound->RegisterPacketConstructor(Recipes::PACKET_ORDINAL, CreateConstructor<Recipes>());
    clientbound->RegisterPacketConstructor(Tags::PACKET_ORDINAL, CreateConstructor<Tags>());

    clientbound->RegisterVersion(&ProtocolVersion::MINECRAFT_1_12_2,
      new VersionRegistry({SpawnEntity::PACKET_ORDINAL, SpawnExperienceOrb::PACKET_ORDINAL, SpawnThunderbolt::PACKET_ORDINAL, SpawnEntity::PACKET_ORDINAL,
        SpawnPainting::PACKET_ORDINAL, SpawnPlayer::PACKET_ORDINAL, EntityAnimation::PACKET_ORDINAL, AwardStatistics::PACKET_ORDINAL,
        BlockDestroyStage::PACKET_ORDINAL, BlockEntityData::PACKET_ORDINAL, BlockAction::PACKET_ORDINAL, BlockUpdate::PACKET_ORDINAL,
        BossBar::PACKET_ORDINAL, ServerChangeDifficulty::PACKET_ORDINAL, CommandSuggestionResponse::PACKET_ORDINAL, LegacyChat::PACKET_ORDINAL,
        SectionBlocks::PACKET_ORDINAL, ConfirmTransaction::PACKET_ORDINAL, CloseInventory::PACKET_ORDINAL, OpenInventory::PACKET_ORDINAL,
        InventoryContent::PACKET_ORDINAL, InventoryProperty::PACKET_ORDINAL, InventorySlot::PACKET_ORDINAL, Cooldown::PACKET_ORDINAL,
        PluginMessage::PACKET_ORDINAL, CustomSoundEffect::PACKET_ORDINAL, Disconnect::PACKET_ORDINAL, EntityAnimation::PACKET_ORDINAL,
        Explosion::PACKET_ORDINAL, UnloadChunk::PACKET_ORDINAL, GameEvent::PACKET_ORDINAL, KeepAlive::PACKET_ORDINAL, ChunkData::PACKET_ORDINAL,
        WorldEvent::PACKET_ORDINAL, Particle::PACKET_ORDINAL, JoinGame::PACKET_ORDINAL, MapData::PACKET_ORDINAL, EntityNotMoved::PACKET_ORDINAL,
        EntityPosition::PACKET_ORDINAL, EntityPositionAndRotation::PACKET_ORDINAL, EntityRotation::PACKET_ORDINAL, MoveVehicle::PACKET_ORDINAL,
        OpenSignEditor::PACKET_ORDINAL, LegacyCraftRecipeResponse::PACKET_ORDINAL, ServerPlayerAbilities::PACKET_ORDINAL, CombatEvent::PACKET_ORDINAL,
        PlayerListItem::PACKET_ORDINAL, PositionRotation::PACKET_ORDINAL, UseBed::PACKET_ORDINAL, UnlockRecipes::PACKET_ORDINAL,
        EntityRemove::PACKET_ORDINAL, EntityEffectRemove::PACKET_ORDINAL, ResourcePackRequest::PACKET_ORDINAL, Respawn::PACKET_ORDINAL,
        EntityLookAt::PACKET_ORDINAL, SelectAdvancementsTab::PACKET_ORDINAL, LegacyWorldBorder::PACKET_ORDINAL, Camera::PACKET_ORDINAL,
        HeldSlot::PACKET_ORDINAL, DisplayObjective::PACKET_ORDINAL, EntityMetadata::PACKET_ORDINAL, LeadEntities::PACKET_ORDINAL,
        EntityVelocity::PACKET_ORDINAL, EntityEquipment::PACKET_ORDINAL, Experience::PACKET_ORDINAL, Health::PACKET_ORDINAL, Objectives::PACKET_ORDINAL,
        Passengers::PACKET_ORDINAL, Teams::PACKET_ORDINAL, Score::PACKET_ORDINAL, DefaultSpawnPosition::PACKET_ORDINAL, WorldTime::PACKET_ORDINAL,
        LegacyTitle::PACKET_ORDINAL, HardcodedSoundEffect::PACKET_ORDINAL, TabHeaderFooter::PACKET_ORDINAL, PickupItem::PACKET_ORDINAL,
        EntityTeleport::PACKET_ORDINAL, Advancements::PACKET_ORDINAL, EntityProperties::PACKET_ORDINAL, EntityEffect::PACKET_ORDINAL}));

    clientbound->RegisterVersion(&ProtocolVersion::MINECRAFT_1_13,
      new VersionRegistry({SpawnEntity::PACKET_ORDINAL, SpawnExperienceOrb::PACKET_ORDINAL, SpawnThunderbolt::PACKET_ORDINAL, SpawnEntity::PACKET_ORDINAL,
        SpawnPainting::PACKET_ORDINAL, SpawnPlayer::PACKET_ORDINAL, EntityAnimation::PACKET_ORDINAL, AwardStatistics::PACKET_ORDINAL,
        BlockDestroyStage::PACKET_ORDINAL, BlockEntityData::PACKET_ORDINAL, BlockAction::PACKET_ORDINAL, BlockUpdate::PACKET_ORDINAL,
        BossBar::PACKET_ORDINAL, ServerChangeDifficulty::PACKET_ORDINAL, LegacyChat::PACKET_ORDINAL, SectionBlocks::PACKET_ORDINAL,
        CommandSuggestionResponse::PACKET_ORDINAL, DeclareCommands::PACKET_ORDINAL, ConfirmTransaction::PACKET_ORDINAL, CloseInventory::PACKET_ORDINAL,
        OpenInventory::PACKET_ORDINAL, InventoryContent::PACKET_ORDINAL, InventoryProperty::PACKET_ORDINAL, InventorySlot::PACKET_ORDINAL,
        Cooldown::PACKET_ORDINAL, PluginMessage::PACKET_ORDINAL, CustomSoundEffect::PACKET_ORDINAL, Disconnect::PACKET_ORDINAL,
        EntityAnimation::PACKET_ORDINAL, TagQueryResponse::PACKET_ORDINAL, Explosion::PACKET_ORDINAL, UnloadChunk::PACKET_ORDINAL,
        GameEvent::PACKET_ORDINAL, KeepAlive::PACKET_ORDINAL, ChunkData::PACKET_ORDINAL, WorldEvent::PACKET_ORDINAL, Particle::PACKET_ORDINAL,
        JoinGame::PACKET_ORDINAL, MapData::PACKET_ORDINAL, EntityNotMoved::PACKET_ORDINAL, EntityPosition::PACKET_ORDINAL,
        EntityPositionAndRotation::PACKET_ORDINAL, EntityRotation::PACKET_ORDINAL, MoveVehicle::PACKET_ORDINAL, OpenSignEditor::PACKET_ORDINAL,
        CraftRecipeResponse::PACKET_ORDINAL, ServerPlayerAbilities::PACKET_ORDINAL, CombatEvent::PACKET_ORDINAL, PlayerListItem::PACKET_ORDINAL,
        PlayerFace::PACKET_ORDINAL, PositionRotation::PACKET_ORDINAL, UseBed::PACKET_ORDINAL, UnlockRecipes::PACKET_ORDINAL, EntityRemove::PACKET_ORDINAL,
        EntityEffectRemove::PACKET_ORDINAL, ResourcePackRequest::PACKET_ORDINAL, Respawn::PACKET_ORDINAL, EntityLookAt::PACKET_ORDINAL,
        SelectAdvancementsTab::PACKET_ORDINAL, LegacyWorldBorder::PACKET_ORDINAL, Camera::PACKET_ORDINAL, HeldSlot::PACKET_ORDINAL,
        DisplayObjective::PACKET_ORDINAL, EntityMetadata::PACKET_ORDINAL, LeadEntities::PACKET_ORDINAL, EntityVelocity::PACKET_ORDINAL,
        EntityEquipment::PACKET_ORDINAL, Experience::PACKET_ORDINAL, Health::PACKET_ORDINAL, Objectives::PACKET_ORDINAL, Passengers::PACKET_ORDINAL,
        Teams::PACKET_ORDINAL, Score::PACKET_ORDINAL, DefaultSpawnPosition::PACKET_ORDINAL, WorldTime::PACKET_ORDINAL, LegacyTitle::PACKET_ORDINAL,
        StopSound::PACKET_ORDINAL, HardcodedSoundEffect::PACKET_ORDINAL, TabHeaderFooter::PACKET_ORDINAL, PickupItem::PACKET_ORDINAL,
        EntityTeleport::PACKET_ORDINAL, Advancements::PACKET_ORDINAL, EntityProperties::PACKET_ORDINAL, EntityEffect::PACKET_ORDINAL,
        Recipes::PACKET_ORDINAL, Tags::PACKET_ORDINAL}));

    clientbound->RegisterVersion(&ProtocolVersion::MINECRAFT_1_14,
      new VersionRegistry({SpawnEntity::PACKET_ORDINAL, SpawnExperienceOrb::PACKET_ORDINAL, SpawnThunderbolt::PACKET_ORDINAL, SpawnEntity::PACKET_ORDINAL,
        SpawnPainting::PACKET_ORDINAL, SpawnPlayer::PACKET_ORDINAL, EntityAnimation::PACKET_ORDINAL, AwardStatistics::PACKET_ORDINAL,
        BlockDestroyStage::PACKET_ORDINAL, BlockEntityData::PACKET_ORDINAL, BlockAction::PACKET_ORDINAL, BlockUpdate::PACKET_ORDINAL,
        BossBar::PACKET_ORDINAL, ServerChangeDifficulty::PACKET_ORDINAL, LegacyChat::PACKET_ORDINAL, SectionBlocks::PACKET_ORDINAL,
        CommandSuggestionResponse::PACKET_ORDINAL, DeclareCommands::PACKET_ORDINAL, ConfirmTransaction::PACKET_ORDINAL, CloseInventory::PACKET_ORDINAL,
        InventoryContent::PACKET_ORDINAL, InventoryProperty::PACKET_ORDINAL, InventorySlot::PACKET_ORDINAL, Cooldown::PACKET_ORDINAL,
        PluginMessage::PACKET_ORDINAL, CustomSoundEffect::PACKET_ORDINAL, Disconnect::PACKET_ORDINAL, EntityAnimation::PACKET_ORDINAL,
        Explosion::PACKET_ORDINAL, UnloadChunk::PACKET_ORDINAL, GameEvent::PACKET_ORDINAL, KeepAlive::PACKET_ORDINAL, OpenHorseInventory::PACKET_ORDINAL,
        ChunkData::PACKET_ORDINAL, WorldEvent::PACKET_ORDINAL, Particle::PACKET_ORDINAL, ChunkLight::PACKET_ORDINAL, JoinGame::PACKET_ORDINAL,
        MapData::PACKET_ORDINAL, TradeList::PACKET_ORDINAL, EntityNotMoved::PACKET_ORDINAL, EntityPosition::PACKET_ORDINAL,
        EntityPositionAndRotation::PACKET_ORDINAL, EntityRotation::PACKET_ORDINAL, MoveVehicle::PACKET_ORDINAL, OpenBook::PACKET_ORDINAL,
        OpenInventory::PACKET_ORDINAL, OpenSignEditor::PACKET_ORDINAL, CraftRecipeResponse::PACKET_ORDINAL, ServerPlayerAbilities::PACKET_ORDINAL,
        CombatEvent::PACKET_ORDINAL, PlayerListItem::PACKET_ORDINAL, PlayerFace::PACKET_ORDINAL, PositionRotation::PACKET_ORDINAL,
        UnlockRecipes::PACKET_ORDINAL, EntityRemove::PACKET_ORDINAL, EntityEffectRemove::PACKET_ORDINAL, ResourcePackRequest::PACKET_ORDINAL,
        Respawn::PACKET_ORDINAL, EntityLookAt::PACKET_ORDINAL, SelectAdvancementsTab::PACKET_ORDINAL, LegacyWorldBorder::PACKET_ORDINAL,
        Camera::PACKET_ORDINAL, HeldSlot::PACKET_ORDINAL, ViewPosition::PACKET_ORDINAL, ViewDistance::PACKET_ORDINAL, DisplayObjective::PACKET_ORDINAL,
        EntityMetadata::PACKET_ORDINAL, LeadEntities::PACKET_ORDINAL, EntityVelocity::PACKET_ORDINAL, EntityEquipment::PACKET_ORDINAL,
        Experience::PACKET_ORDINAL, Health::PACKET_ORDINAL, Objectives::PACKET_ORDINAL, Passengers::PACKET_ORDINAL, Teams::PACKET_ORDINAL,
        Score::PACKET_ORDINAL, DefaultSpawnPosition::PACKET_ORDINAL, WorldTime::PACKET_ORDINAL, LegacyTitle::PACKET_ORDINAL,
        EntitySoundEffect::PACKET_ORDINAL, HardcodedSoundEffect::PACKET_ORDINAL, StopSound::PACKET_ORDINAL, TabHeaderFooter::PACKET_ORDINAL,
        TagQueryResponse::PACKET_ORDINAL, PickupItem::PACKET_ORDINAL, EntityTeleport::PACKET_ORDINAL, Advancements::PACKET_ORDINAL,
        EntityProperties::PACKET_ORDINAL, EntityEffect::PACKET_ORDINAL, Recipes::PACKET_ORDINAL, Tags::PACKET_ORDINAL,
        AcknowledgePlayerDigging::PACKET_ORDINAL}));

    clientbound->RegisterVersion(&ProtocolVersion::MINECRAFT_1_15,
      new VersionRegistry({SpawnEntity::PACKET_ORDINAL, SpawnExperienceOrb::PACKET_ORDINAL, SpawnThunderbolt::PACKET_ORDINAL, SpawnEntity::PACKET_ORDINAL,
        SpawnPainting::PACKET_ORDINAL, SpawnPlayer::PACKET_ORDINAL, EntityAnimation::PACKET_ORDINAL, AwardStatistics::PACKET_ORDINAL,
        AcknowledgePlayerDigging::PACKET_ORDINAL, BlockDestroyStage::PACKET_ORDINAL, BlockEntityData::PACKET_ORDINAL, BlockAction::PACKET_ORDINAL,
        BlockUpdate::PACKET_ORDINAL, BossBar::PACKET_ORDINAL, ServerChangeDifficulty::PACKET_ORDINAL, LegacyChat::PACKET_ORDINAL,
        SectionBlocks::PACKET_ORDINAL, CommandSuggestionResponse::PACKET_ORDINAL, DeclareCommands::PACKET_ORDINAL, ConfirmTransaction::PACKET_ORDINAL,
        CloseInventory::PACKET_ORDINAL, InventoryContent::PACKET_ORDINAL, InventoryProperty::PACKET_ORDINAL, InventorySlot::PACKET_ORDINAL,
        Cooldown::PACKET_ORDINAL, PluginMessage::PACKET_ORDINAL, CustomSoundEffect::PACKET_ORDINAL, Disconnect::PACKET_ORDINAL,
        EntityAnimation::PACKET_ORDINAL, Explosion::PACKET_ORDINAL, UnloadChunk::PACKET_ORDINAL, GameEvent::PACKET_ORDINAL, KeepAlive::PACKET_ORDINAL,
        OpenHorseInventory::PACKET_ORDINAL, ChunkData::PACKET_ORDINAL, WorldEvent::PACKET_ORDINAL, Particle::PACKET_ORDINAL, ChunkLight::PACKET_ORDINAL,
        JoinGame::PACKET_ORDINAL, MapData::PACKET_ORDINAL, TradeList::PACKET_ORDINAL, EntityNotMoved::PACKET_ORDINAL, EntityPosition::PACKET_ORDINAL,
        EntityPositionAndRotation::PACKET_ORDINAL, EntityRotation::PACKET_ORDINAL, MoveVehicle::PACKET_ORDINAL, OpenBook::PACKET_ORDINAL,
        OpenInventory::PACKET_ORDINAL, OpenSignEditor::PACKET_ORDINAL, CraftRecipeResponse::PACKET_ORDINAL, ServerPlayerAbilities::PACKET_ORDINAL,
        CombatEvent::PACKET_ORDINAL, PlayerListItem::PACKET_ORDINAL, PlayerFace::PACKET_ORDINAL, PositionRotation::PACKET_ORDINAL,
        UnlockRecipes::PACKET_ORDINAL, EntityRemove::PACKET_ORDINAL, EntityEffectRemove::PACKET_ORDINAL, ResourcePackRequest::PACKET_ORDINAL,
        Respawn::PACKET_ORDINAL, EntityLookAt::PACKET_ORDINAL, SelectAdvancementsTab::PACKET_ORDINAL, LegacyWorldBorder::PACKET_ORDINAL,
        Camera::PACKET_ORDINAL, HeldSlot::PACKET_ORDINAL, ViewPosition::PACKET_ORDINAL, ViewDistance::PACKET_ORDINAL, DisplayObjective::PACKET_ORDINAL,
        EntityMetadata::PACKET_ORDINAL, LeadEntities::PACKET_ORDINAL, EntityVelocity::PACKET_ORDINAL, EntityEquipment::PACKET_ORDINAL,
        Experience::PACKET_ORDINAL, Health::PACKET_ORDINAL, Objectives::PACKET_ORDINAL, Passengers::PACKET_ORDINAL, Teams::PACKET_ORDINAL,
        Score::PACKET_ORDINAL, DefaultSpawnPosition::PACKET_ORDINAL, WorldTime::PACKET_ORDINAL, LegacyTitle::PACKET_ORDINAL,
        EntitySoundEffect::PACKET_ORDINAL, HardcodedSoundEffect::PACKET_ORDINAL, StopSound::PACKET_ORDINAL, TabHeaderFooter::PACKET_ORDINAL,
        TagQueryResponse::PACKET_ORDINAL, PickupItem::PACKET_ORDINAL, EntityTeleport::PACKET_ORDINAL, Advancements::PACKET_ORDINAL,
        EntityProperties::PACKET_ORDINAL, EntityEffect::PACKET_ORDINAL, Recipes::PACKET_ORDINAL, Tags::PACKET_ORDINAL}));

    clientbound->RegisterVersion(&ProtocolVersion::MINECRAFT_1_16_2,
      new VersionRegistry({SpawnEntity::PACKET_ORDINAL, SpawnExperienceOrb::PACKET_ORDINAL, SpawnEntity::PACKET_ORDINAL, SpawnPainting::PACKET_ORDINAL,
        SpawnPlayer::PACKET_ORDINAL, EntityAnimation::PACKET_ORDINAL, AwardStatistics::PACKET_ORDINAL, AcknowledgePlayerDigging::PACKET_ORDINAL,
        BlockDestroyStage::PACKET_ORDINAL, BlockEntityData::PACKET_ORDINAL, BlockAction::PACKET_ORDINAL, BlockUpdate::PACKET_ORDINAL,
        BossBar::PACKET_ORDINAL, ServerChangeDifficulty::PACKET_ORDINAL, LegacyChat::PACKET_ORDINAL, SectionBlocks::PACKET_ORDINAL,
        CommandSuggestionResponse::PACKET_ORDINAL, DeclareCommands::PACKET_ORDINAL, ConfirmTransaction::PACKET_ORDINAL, CloseInventory::PACKET_ORDINAL,
        InventoryContent::PACKET_ORDINAL, InventoryProperty::PACKET_ORDINAL, InventorySlot::PACKET_ORDINAL, Cooldown::PACKET_ORDINAL,
        PluginMessage::PACKET_ORDINAL, CustomSoundEffect::PACKET_ORDINAL, Disconnect::PACKET_ORDINAL, EntityAnimation::PACKET_ORDINAL,
        Explosion::PACKET_ORDINAL, UnloadChunk::PACKET_ORDINAL, GameEvent::PACKET_ORDINAL, KeepAlive::PACKET_ORDINAL, OpenHorseInventory::PACKET_ORDINAL,
        ChunkData::PACKET_ORDINAL, WorldEvent::PACKET_ORDINAL, Particle::PACKET_ORDINAL, ChunkLight::PACKET_ORDINAL, JoinGame::PACKET_ORDINAL,
        MapData::PACKET_ORDINAL, TradeList::PACKET_ORDINAL, EntityNotMoved::PACKET_ORDINAL, EntityPosition::PACKET_ORDINAL,
        EntityPositionAndRotation::PACKET_ORDINAL, EntityRotation::PACKET_ORDINAL, MoveVehicle::PACKET_ORDINAL, OpenBook::PACKET_ORDINAL,
        OpenInventory::PACKET_ORDINAL, OpenSignEditor::PACKET_ORDINAL, CraftRecipeResponse::PACKET_ORDINAL, ServerPlayerAbilities::PACKET_ORDINAL,
        CombatEvent::PACKET_ORDINAL, PlayerListItem::PACKET_ORDINAL, PlayerFace::PACKET_ORDINAL, PositionRotation::PACKET_ORDINAL,
        UnlockRecipes::PACKET_ORDINAL, EntityRemove::PACKET_ORDINAL, EntityEffectRemove::PACKET_ORDINAL, ResourcePackRequest::PACKET_ORDINAL,
        Respawn::PACKET_ORDINAL, EntityLookAt::PACKET_ORDINAL, SelectAdvancementsTab::PACKET_ORDINAL, LegacyWorldBorder::PACKET_ORDINAL,
        Camera::PACKET_ORDINAL, HeldSlot::PACKET_ORDINAL, ViewPosition::PACKET_ORDINAL, ViewDistance::PACKET_ORDINAL, DisplayObjective::PACKET_ORDINAL,
        EntityMetadata::PACKET_ORDINAL, LeadEntities::PACKET_ORDINAL, EntityVelocity::PACKET_ORDINAL, EntityEquipment::PACKET_ORDINAL,
        Experience::PACKET_ORDINAL, Health::PACKET_ORDINAL, Objectives::PACKET_ORDINAL, Passengers::PACKET_ORDINAL, Teams::PACKET_ORDINAL,
        Score::PACKET_ORDINAL, DefaultSpawnPosition::PACKET_ORDINAL, WorldTime::PACKET_ORDINAL, LegacyTitle::PACKET_ORDINAL,
        EntitySoundEffect::PACKET_ORDINAL, HardcodedSoundEffect::PACKET_ORDINAL, StopSound::PACKET_ORDINAL, TabHeaderFooter::PACKET_ORDINAL,
        TagQueryResponse::PACKET_ORDINAL, PickupItem::PACKET_ORDINAL, EntityTeleport::PACKET_ORDINAL, Advancements::PACKET_ORDINAL,
        EntityProperties::PACKET_ORDINAL, EntityEffect::PACKET_ORDINAL, Recipes::PACKET_ORDINAL, Tags::PACKET_ORDINAL}));

    clientbound->RegisterVersion(&ProtocolVersion::MINECRAFT_1_17,
      new VersionRegistry({SpawnEntity::PACKET_ORDINAL, SpawnExperienceOrb::PACKET_ORDINAL, SpawnEntity::PACKET_ORDINAL, SpawnPainting::PACKET_ORDINAL,
        SpawnPlayer::PACKET_ORDINAL,
        SkulkVibration::PACKET_ORDINAL,
        EntityAnimation::PACKET_ORDINAL, AwardStatistics::PACKET_ORDINAL, AcknowledgePlayerDigging::PACKET_ORDINAL, BlockDestroyStage::PACKET_ORDINAL,
        BlockEntityData::PACKET_ORDINAL, BlockAction::PACKET_ORDINAL, BlockUpdate::PACKET_ORDINAL, BossBar::PACKET_ORDINAL,
        ServerChangeDifficulty::PACKET_ORDINAL, LegacyChat::PACKET_ORDINAL, ClearTitle::PACKET_ORDINAL, CommandSuggestionResponse::PACKET_ORDINAL,
        DeclareCommands::PACKET_ORDINAL, CloseInventory::PACKET_ORDINAL, InventoryContent::PACKET_ORDINAL, InventoryProperty::PACKET_ORDINAL,
        InventorySlot::PACKET_ORDINAL, Cooldown::PACKET_ORDINAL, PluginMessage::PACKET_ORDINAL, CustomSoundEffect::PACKET_ORDINAL,
        Disconnect::PACKET_ORDINAL, EntityAnimation::PACKET_ORDINAL, Explosion::PACKET_ORDINAL, UnloadChunk::PACKET_ORDINAL, GameEvent::PACKET_ORDINAL,
        OpenHorseInventory::PACKET_ORDINAL, InitializeWorldBorder::PACKET_ORDINAL, KeepAlive::PACKET_ORDINAL, ChunkData::PACKET_ORDINAL,
        WorldEvent::PACKET_ORDINAL, Particle::PACKET_ORDINAL, ChunkLight::PACKET_ORDINAL, JoinGame::PACKET_ORDINAL, MapData::PACKET_ORDINAL,
        TradeList::PACKET_ORDINAL, EntityPosition::PACKET_ORDINAL, EntityPositionAndRotation::PACKET_ORDINAL, EntityRotation::PACKET_ORDINAL,
        MoveVehicle::PACKET_ORDINAL, OpenBook::PACKET_ORDINAL, OpenInventory::PACKET_ORDINAL, OpenSignEditor::PACKET_ORDINAL, Ping::PACKET_ORDINAL,
        CraftRecipeResponse::PACKET_ORDINAL, ServerPlayerAbilities::PACKET_ORDINAL, EndCombatEvent::PACKET_ORDINAL, EnterCombatEvent::PACKET_ORDINAL,
        DeathCombatEvent::PACKET_ORDINAL, PlayerListItem::PACKET_ORDINAL, PlayerFace::PACKET_ORDINAL, PositionRotation::PACKET_ORDINAL,
        UnlockRecipes::PACKET_ORDINAL, EntityRemove::PACKET_ORDINAL, EntityEffectRemove::PACKET_ORDINAL, ResourcePackRequest::PACKET_ORDINAL,
        Respawn::PACKET_ORDINAL, EntityLookAt::PACKET_ORDINAL, SectionBlocks::PACKET_ORDINAL, SelectAdvancementsTab::PACKET_ORDINAL,
        ActionBar::PACKET_ORDINAL, BorderCenter::PACKET_ORDINAL, BorderRadiusSpeed::PACKET_ORDINAL, BorderRadius::PACKET_ORDINAL,
        BorderWarningTime::PACKET_ORDINAL, BorderWarningRadius::PACKET_ORDINAL, Camera::PACKET_ORDINAL, HeldSlot::PACKET_ORDINAL,
        ViewPosition::PACKET_ORDINAL, ViewDistance::PACKET_ORDINAL, DefaultSpawnPosition::PACKET_ORDINAL, DisplayObjective::PACKET_ORDINAL,
        EntityMetadata::PACKET_ORDINAL, LeadEntities::PACKET_ORDINAL, EntityVelocity::PACKET_ORDINAL, EntityEquipment::PACKET_ORDINAL,
        Experience::PACKET_ORDINAL, Health::PACKET_ORDINAL, Objectives::PACKET_ORDINAL, Passengers::PACKET_ORDINAL, Teams::PACKET_ORDINAL,
        Score::PACKET_ORDINAL, Subtitle::PACKET_ORDINAL, WorldTime::PACKET_ORDINAL, Title::PACKET_ORDINAL, TitleTimes::PACKET_ORDINAL,
        EntitySoundEffect::PACKET_ORDINAL, HardcodedSoundEffect::PACKET_ORDINAL, StopSound::PACKET_ORDINAL, TabHeaderFooter::PACKET_ORDINAL,
        TagQueryResponse::PACKET_ORDINAL, PickupItem::PACKET_ORDINAL, EntityTeleport::PACKET_ORDINAL, Advancements::PACKET_ORDINAL,
        EntityProperties::PACKET_ORDINAL, EntityEffect::PACKET_ORDINAL, Recipes::PACKET_ORDINAL, Tags::PACKET_ORDINAL}));

    clientbound->RegisterVersion(&ProtocolVersion::MINECRAFT_1_18,
      new VersionRegistry({SpawnEntity::PACKET_ORDINAL, SpawnExperienceOrb::PACKET_ORDINAL, SpawnEntity::PACKET_ORDINAL, SpawnPainting::PACKET_ORDINAL,
        SpawnPlayer::PACKET_ORDINAL,
        SkulkVibration::PACKET_ORDINAL,
        EntityAnimation::PACKET_ORDINAL, AwardStatistics::PACKET_ORDINAL, AcknowledgePlayerDigging::PACKET_ORDINAL, BlockDestroyStage::PACKET_ORDINAL,
        BlockEntityData::PACKET_ORDINAL, BlockAction::PACKET_ORDINAL, BlockUpdate::PACKET_ORDINAL, BossBar::PACKET_ORDINAL,
        ServerChangeDifficulty::PACKET_ORDINAL, LegacyChat::PACKET_ORDINAL, ClearTitle::PACKET_ORDINAL, CommandSuggestionResponse::PACKET_ORDINAL,
        DeclareCommands::PACKET_ORDINAL, CloseInventory::PACKET_ORDINAL, InventoryContent::PACKET_ORDINAL, InventoryProperty::PACKET_ORDINAL,
        InventorySlot::PACKET_ORDINAL, Cooldown::PACKET_ORDINAL, PluginMessage::PACKET_ORDINAL, CustomSoundEffect::PACKET_ORDINAL,
        Disconnect::PACKET_ORDINAL, EntityAnimation::PACKET_ORDINAL, Explosion::PACKET_ORDINAL, UnloadChunk::PACKET_ORDINAL, GameEvent::PACKET_ORDINAL,
        OpenHorseInventory::PACKET_ORDINAL, InitializeWorldBorder::PACKET_ORDINAL, KeepAlive::PACKET_ORDINAL, ChunkData::PACKET_ORDINAL,
        WorldEvent::PACKET_ORDINAL, Particle::PACKET_ORDINAL, ChunkLight::PACKET_ORDINAL, JoinGame::PACKET_ORDINAL, MapData::PACKET_ORDINAL,
        TradeList::PACKET_ORDINAL, EntityPosition::PACKET_ORDINAL, EntityPositionAndRotation::PACKET_ORDINAL, EntityRotation::PACKET_ORDINAL,
        MoveVehicle::PACKET_ORDINAL, OpenBook::PACKET_ORDINAL, OpenInventory::PACKET_ORDINAL, OpenSignEditor::PACKET_ORDINAL, Ping::PACKET_ORDINAL,
        CraftRecipeResponse::PACKET_ORDINAL, ServerPlayerAbilities::PACKET_ORDINAL, EndCombatEvent::PACKET_ORDINAL, EnterCombatEvent::PACKET_ORDINAL,
        DeathCombatEvent::PACKET_ORDINAL, PlayerListItem::PACKET_ORDINAL, PlayerFace::PACKET_ORDINAL, PositionRotation::PACKET_ORDINAL,
        UnlockRecipes::PACKET_ORDINAL, EntityRemove::PACKET_ORDINAL, EntityEffectRemove::PACKET_ORDINAL, ResourcePackRequest::PACKET_ORDINAL,
        Respawn::PACKET_ORDINAL, EntityLookAt::PACKET_ORDINAL, SectionBlocks::PACKET_ORDINAL, SelectAdvancementsTab::PACKET_ORDINAL,
        ActionBar::PACKET_ORDINAL, BorderCenter::PACKET_ORDINAL, BorderRadiusSpeed::PACKET_ORDINAL, BorderRadius::PACKET_ORDINAL,
        BorderWarningTime::PACKET_ORDINAL, BorderWarningRadius::PACKET_ORDINAL, Camera::PACKET_ORDINAL, HeldSlot::PACKET_ORDINAL,
        ViewPosition::PACKET_ORDINAL, ViewDistance::PACKET_ORDINAL, DefaultSpawnPosition::PACKET_ORDINAL, DisplayObjective::PACKET_ORDINAL,
        EntityMetadata::PACKET_ORDINAL, LeadEntities::PACKET_ORDINAL, EntityVelocity::PACKET_ORDINAL, EntityEquipment::PACKET_ORDINAL,
        Experience::PACKET_ORDINAL, Health::PACKET_ORDINAL, Objectives::PACKET_ORDINAL, Passengers::PACKET_ORDINAL, Teams::PACKET_ORDINAL,
        Score::PACKET_ORDINAL, SimulationDistance::PACKET_ORDINAL, Subtitle::PACKET_ORDINAL, WorldTime::PACKET_ORDINAL, Title::PACKET_ORDINAL,
        TitleTimes::PACKET_ORDINAL, EntitySoundEffect::PACKET_ORDINAL, HardcodedSoundEffect::PACKET_ORDINAL, StopSound::PACKET_ORDINAL,
        TabHeaderFooter::PACKET_ORDINAL, TagQueryResponse::PACKET_ORDINAL, PickupItem::PACKET_ORDINAL, EntityTeleport::PACKET_ORDINAL,
        Advancements::PACKET_ORDINAL, EntityProperties::PACKET_ORDINAL, EntityEffect::PACKET_ORDINAL, Recipes::PACKET_ORDINAL, Tags::PACKET_ORDINAL}));

    clientbound->RegisterVersion(&ProtocolVersion::MINECRAFT_1_19,
      new VersionRegistry({SpawnEntity::PACKET_ORDINAL, SpawnExperienceOrb::PACKET_ORDINAL, SpawnPlayer::PACKET_ORDINAL, EntityAnimation::PACKET_ORDINAL,
        AwardStatistics::PACKET_ORDINAL, AcknowledgeBlockChange::PACKET_ORDINAL, BlockDestroyStage::PACKET_ORDINAL, BlockEntityData::PACKET_ORDINAL,
        BlockAction::PACKET_ORDINAL, BlockUpdate::PACKET_ORDINAL, BossBar::PACKET_ORDINAL, ServerChangeDifficulty::PACKET_ORDINAL,
        ServerChatPreview::PACKET_ORDINAL, ClearTitle::PACKET_ORDINAL, CommandSuggestionResponse::PACKET_ORDINAL, DeclareCommands::PACKET_ORDINAL,
        CloseInventory::PACKET_ORDINAL, InventoryContent::PACKET_ORDINAL, InventoryProperty::PACKET_ORDINAL, InventorySlot::PACKET_ORDINAL,
        Cooldown::PACKET_ORDINAL, PluginMessage::PACKET_ORDINAL, CustomSoundEffect::PACKET_ORDINAL, Disconnect::PACKET_ORDINAL,
        EntityAnimation::PACKET_ORDINAL, Explosion::PACKET_ORDINAL, UnloadChunk::PACKET_ORDINAL, GameEvent::PACKET_ORDINAL,
        OpenHorseInventory::PACKET_ORDINAL, InitializeWorldBorder::PACKET_ORDINAL, KeepAlive::PACKET_ORDINAL, ChunkData::PACKET_ORDINAL,
        WorldEvent::PACKET_ORDINAL, Particle::PACKET_ORDINAL, ChunkLight::PACKET_ORDINAL, JoinGame::PACKET_ORDINAL, MapData::PACKET_ORDINAL,
        TradeList::PACKET_ORDINAL, EntityPosition::PACKET_ORDINAL, EntityPositionAndRotation::PACKET_ORDINAL, EntityRotation::PACKET_ORDINAL,
        MoveVehicle::PACKET_ORDINAL, OpenBook::PACKET_ORDINAL, OpenInventory::PACKET_ORDINAL, OpenSignEditor::PACKET_ORDINAL, Ping::PACKET_ORDINAL,
        CraftRecipeResponse::PACKET_ORDINAL, ServerPlayerAbilities::PACKET_ORDINAL, ServerPlayerChat::PACKET_ORDINAL, EndCombatEvent::PACKET_ORDINAL,
        EnterCombatEvent::PACKET_ORDINAL, DeathCombatEvent::PACKET_ORDINAL, PlayerListItem::PACKET_ORDINAL, PlayerFace::PACKET_ORDINAL,
        PositionRotation::PACKET_ORDINAL, UnlockRecipes::PACKET_ORDINAL, EntityRemove::PACKET_ORDINAL, EntityEffectRemove::PACKET_ORDINAL,
        ResourcePackRequest::PACKET_ORDINAL, Respawn::PACKET_ORDINAL, EntityLookAt::PACKET_ORDINAL, SectionBlocks::PACKET_ORDINAL,
        SelectAdvancementsTab::PACKET_ORDINAL, ServerData::PACKET_ORDINAL, ActionBar::PACKET_ORDINAL, BorderCenter::PACKET_ORDINAL,
        BorderRadiusSpeed::PACKET_ORDINAL, BorderRadius::PACKET_ORDINAL, BorderWarningTime::PACKET_ORDINAL, BorderWarningRadius::PACKET_ORDINAL,
        Camera::PACKET_ORDINAL, HeldSlot::PACKET_ORDINAL, ViewPosition::PACKET_ORDINAL, ViewDistance::PACKET_ORDINAL, DefaultSpawnPosition::PACKET_ORDINAL,
        DisplayObjective::PACKET_ORDINAL, EntityMetadata::PACKET_ORDINAL, LeadEntities::PACKET_ORDINAL, EntityVelocity::PACKET_ORDINAL,
        EntityEquipment::PACKET_ORDINAL, Experience::PACKET_ORDINAL, Health::PACKET_ORDINAL, Objectives::PACKET_ORDINAL, Passengers::PACKET_ORDINAL,
        Teams::PACKET_ORDINAL, Score::PACKET_ORDINAL, SimulationDistance::PACKET_ORDINAL, Subtitle::PACKET_ORDINAL, WorldTime::PACKET_ORDINAL,
        Title::PACKET_ORDINAL, TitleTimes::PACKET_ORDINAL, EntitySoundEffect::PACKET_ORDINAL, HardcodedSoundEffect::PACKET_ORDINAL,
        StopSound::PACKET_ORDINAL, SystemChat::PACKET_ORDINAL, TabHeaderFooter::PACKET_ORDINAL, TagQueryResponse::PACKET_ORDINAL,
        PickupItem::PACKET_ORDINAL, EntityTeleport::PACKET_ORDINAL, Advancements::PACKET_ORDINAL, EntityProperties::PACKET_ORDINAL,
        EntityEffect::PACKET_ORDINAL, Recipes::PACKET_ORDINAL, Tags::PACKET_ORDINAL}));

    clientbound->RegisterVersion(&ProtocolVersion::MINECRAFT_1_19_1,
      new VersionRegistry({SpawnEntity::PACKET_ORDINAL, SpawnExperienceOrb::PACKET_ORDINAL, SpawnPlayer::PACKET_ORDINAL, EntityAnimation::PACKET_ORDINAL,
        AwardStatistics::PACKET_ORDINAL, AcknowledgeBlockChange::PACKET_ORDINAL, BlockDestroyStage::PACKET_ORDINAL, BlockEntityData::PACKET_ORDINAL,
        BlockAction::PACKET_ORDINAL, BlockUpdate::PACKET_ORDINAL, BossBar::PACKET_ORDINAL, ServerChangeDifficulty::PACKET_ORDINAL,
        ServerChatPreview::PACKET_ORDINAL, ClearTitle::PACKET_ORDINAL, CommandSuggestionResponse::PACKET_ORDINAL, DeclareCommands::PACKET_ORDINAL,
        CloseInventory::PACKET_ORDINAL, InventoryContent::PACKET_ORDINAL, InventoryProperty::PACKET_ORDINAL, InventorySlot::PACKET_ORDINAL,
        Cooldown::PACKET_ORDINAL, ChatSuggestions::PACKET_ORDINAL, PluginMessage::PACKET_ORDINAL, CustomSoundEffect::PACKET_ORDINAL,
        HideMessage::PACKET_ORDINAL, Disconnect::PACKET_ORDINAL, EntityEvent::PACKET_ORDINAL, Explosion::PACKET_ORDINAL, UnloadChunk::PACKET_ORDINAL,
        GameEvent::PACKET_ORDINAL, OpenHorseInventory::PACKET_ORDINAL, InitializeWorldBorder::PACKET_ORDINAL, KeepAlive::PACKET_ORDINAL,
        ChunkData::PACKET_ORDINAL, WorldEvent::PACKET_ORDINAL, Particle::PACKET_ORDINAL, ChunkLight::PACKET_ORDINAL, JoinGame::PACKET_ORDINAL,
        MapData::PACKET_ORDINAL, TradeList::PACKET_ORDINAL, EntityPosition::PACKET_ORDINAL, EntityPositionAndRotation::PACKET_ORDINAL,
        EntityRotation::PACKET_ORDINAL, MoveVehicle::PACKET_ORDINAL, OpenBook::PACKET_ORDINAL, OpenInventory::PACKET_ORDINAL,
        OpenSignEditor::PACKET_ORDINAL, Ping::PACKET_ORDINAL, CraftRecipeResponse::PACKET_ORDINAL, ServerPlayerAbilities::PACKET_ORDINAL,
        MessageHeader::PACKET_ORDINAL, ServerPlayerChat::PACKET_ORDINAL, EndCombatEvent::PACKET_ORDINAL, EnterCombatEvent::PACKET_ORDINAL,
        DeathCombatEvent::PACKET_ORDINAL, PlayerListItem::PACKET_ORDINAL, PlayerFace::PACKET_ORDINAL, PositionRotation::PACKET_ORDINAL,
        UnlockRecipes::PACKET_ORDINAL, EntityRemove::PACKET_ORDINAL, EntityEffectRemove::PACKET_ORDINAL, ResourcePackRequest::PACKET_ORDINAL,
        Respawn::PACKET_ORDINAL, EntityLookAt::PACKET_ORDINAL, SectionBlocks::PACKET_ORDINAL, SelectAdvancementsTab::PACKET_ORDINAL,
        ServerData::PACKET_ORDINAL, ActionBar::PACKET_ORDINAL, BorderCenter::PACKET_ORDINAL, BorderRadiusSpeed::PACKET_ORDINAL,
        BorderRadius::PACKET_ORDINAL, BorderWarningTime::PACKET_ORDINAL, BorderWarningRadius::PACKET_ORDINAL, Camera::PACKET_ORDINAL,
        HeldSlot::PACKET_ORDINAL, ViewPosition::PACKET_ORDINAL, ViewDistance::PACKET_ORDINAL, DefaultSpawnPosition::PACKET_ORDINAL,
        SetDisplayChatPreview::PACKET_ORDINAL,
        DisplayObjective::PACKET_ORDINAL, EntityMetadata::PACKET_ORDINAL, LeadEntities::PACKET_ORDINAL, EntityVelocity::PACKET_ORDINAL,
        EntityEquipment::PACKET_ORDINAL, Experience::PACKET_ORDINAL, Health::PACKET_ORDINAL, Objectives::PACKET_ORDINAL, Passengers::PACKET_ORDINAL,
        Teams::PACKET_ORDINAL, Score::PACKET_ORDINAL, SimulationDistance::PACKET_ORDINAL, Subtitle::PACKET_ORDINAL, WorldTime::PACKET_ORDINAL,
        Title::PACKET_ORDINAL, TitleTimes::PACKET_ORDINAL, EntitySoundEffect::PACKET_ORDINAL, HardcodedSoundEffect::PACKET_ORDINAL,
        StopSound::PACKET_ORDINAL, SystemChat::PACKET_ORDINAL, TabHeaderFooter::PACKET_ORDINAL, TagQueryResponse::PACKET_ORDINAL,
        PickupItem::PACKET_ORDINAL, EntityTeleport::PACKET_ORDINAL, Advancements::PACKET_ORDINAL, EntityProperties::PACKET_ORDINAL,
        EntityEffect::PACKET_ORDINAL, Recipes::PACKET_ORDINAL, Tags::PACKET_ORDINAL}));

    clientbound->RegisterVersion(&ProtocolVersion::MINECRAFT_1_19_3,
      new VersionRegistry({SpawnEntity::PACKET_ORDINAL, SpawnExperienceOrb::PACKET_ORDINAL, SpawnPlayer::PACKET_ORDINAL, EntityAnimation::PACKET_ORDINAL,
        AwardStatistics::PACKET_ORDINAL, AcknowledgeBlockChange::PACKET_ORDINAL, BlockDestroyStage::PACKET_ORDINAL, BlockEntityData::PACKET_ORDINAL,
        BlockAction::PACKET_ORDINAL, BlockUpdate::PACKET_ORDINAL, BossBar::PACKET_ORDINAL, ServerChangeDifficulty::PACKET_ORDINAL,
        ClearTitle::PACKET_ORDINAL, CommandSuggestionResponse::PACKET_ORDINAL, DeclareCommands::PACKET_ORDINAL, CloseInventory::PACKET_ORDINAL,
        InventoryContent::PACKET_ORDINAL, InventoryProperty::PACKET_ORDINAL, InventorySlot::PACKET_ORDINAL, Cooldown::PACKET_ORDINAL,
        ChatSuggestions::PACKET_ORDINAL, PluginMessage::PACKET_ORDINAL, HideMessage::PACKET_ORDINAL, Disconnect::PACKET_ORDINAL,
        DisguisedChatMessage::PACKET_ORDINAL, EntityEvent::PACKET_ORDINAL, Explosion::PACKET_ORDINAL, UnloadChunk::PACKET_ORDINAL,
        GameEvent::PACKET_ORDINAL, OpenHorseInventory::PACKET_ORDINAL, InitializeWorldBorder::PACKET_ORDINAL, KeepAlive::PACKET_ORDINAL,
        ChunkData::PACKET_ORDINAL, WorldEvent::PACKET_ORDINAL, Particle::PACKET_ORDINAL, ChunkLight::PACKET_ORDINAL, JoinGame::PACKET_ORDINAL,
        MapData::PACKET_ORDINAL, TradeList::PACKET_ORDINAL, EntityPosition::PACKET_ORDINAL, EntityPositionAndRotation::PACKET_ORDINAL,
        EntityRotation::PACKET_ORDINAL, MoveVehicle::PACKET_ORDINAL, OpenBook::PACKET_ORDINAL, OpenInventory::PACKET_ORDINAL,
        OpenSignEditor::PACKET_ORDINAL, Ping::PACKET_ORDINAL, CraftRecipeResponse::PACKET_ORDINAL, ServerPlayerAbilities::PACKET_ORDINAL,
        ServerPlayerChat::PACKET_ORDINAL, EndCombatEvent::PACKET_ORDINAL, EnterCombatEvent::PACKET_ORDINAL, DeathCombatEvent::PACKET_ORDINAL,
        PlayerRemove::PACKET_ORDINAL,
        PlayerListItem::PACKET_ORDINAL, PlayerFace::PACKET_ORDINAL, PositionRotation::PACKET_ORDINAL, UnlockRecipes::PACKET_ORDINAL,
        EntityRemove::PACKET_ORDINAL, EntityEffectRemove::PACKET_ORDINAL, ResourcePackRequest::PACKET_ORDINAL, Respawn::PACKET_ORDINAL,
        EntityLookAt::PACKET_ORDINAL, SectionBlocks::PACKET_ORDINAL, SelectAdvancementsTab::PACKET_ORDINAL, ServerData::PACKET_ORDINAL,
        ActionBar::PACKET_ORDINAL, BorderCenter::PACKET_ORDINAL, BorderRadiusSpeed::PACKET_ORDINAL, BorderRadius::PACKET_ORDINAL,
        BorderWarningTime::PACKET_ORDINAL, BorderWarningRadius::PACKET_ORDINAL, Camera::PACKET_ORDINAL, HeldSlot::PACKET_ORDINAL,
        ViewPosition::PACKET_ORDINAL, ViewDistance::PACKET_ORDINAL, DefaultSpawnPosition::PACKET_ORDINAL, DisplayObjective::PACKET_ORDINAL,
        EntityMetadata::PACKET_ORDINAL, LeadEntities::PACKET_ORDINAL, EntityVelocity::PACKET_ORDINAL, EntityEquipment::PACKET_ORDINAL,
        Experience::PACKET_ORDINAL, Health::PACKET_ORDINAL, Objectives::PACKET_ORDINAL, Passengers::PACKET_ORDINAL, Teams::PACKET_ORDINAL,
        Score::PACKET_ORDINAL, SimulationDistance::PACKET_ORDINAL, Subtitle::PACKET_ORDINAL, WorldTime::PACKET_ORDINAL, Title::PACKET_ORDINAL,
        TitleTimes::PACKET_ORDINAL, EntitySoundEffect::PACKET_ORDINAL, HardcodedSoundEffect::PACKET_ORDINAL, StopSound::PACKET_ORDINAL,
        SystemChat::PACKET_ORDINAL, TabHeaderFooter::PACKET_ORDINAL, TagQueryResponse::PACKET_ORDINAL, PickupItem::PACKET_ORDINAL,
        EntityTeleport::PACKET_ORDINAL, Advancements::PACKET_ORDINAL, EntityProperties::PACKET_ORDINAL, FeatureFlags::PACKET_ORDINAL,
        EntityEffect::PACKET_ORDINAL, Recipes::PACKET_ORDINAL, Tags::PACKET_ORDINAL}));

    auto* serverbound = new DirectionRegistry();

    serverbound->RegisterPacketConstructor(ConfirmTeleport::PACKET_ORDINAL, CreateConstructor<ConfirmTeleport>());
    serverbound->RegisterPacketConstructor(BlockTagQueryRequest::PACKET_ORDINAL, CreateConstructor<BlockTagQueryRequest>());
    serverbound->RegisterPacketConstructor(ClientChangeDifficulty::PACKET_ORDINAL, CreateConstructor<ClientChangeDifficulty>());
    serverbound->RegisterPacketConstructor(ClientChatPreview::PACKET_ORDINAL, CreateConstructor<ClientChatPreview>(0, std::string {}));
    serverbound->RegisterPacketConstructor(Command::PACKET_ORDINAL, CreateConstructor<Command>());
    serverbound->RegisterPacketConstructor(CommandSuggestionRequest::PACKET_ORDINAL, CreateConstructor<CommandSuggestionRequest>());
    serverbound->RegisterPacketConstructor(LegacyChat::PACKET_ORDINAL, CreateConstructor<LegacyChat>());
    serverbound->RegisterPacketConstructor(ClientPlayerChat::PACKET_ORDINAL, CreateConstructor<ClientPlayerChat>());
    serverbound->RegisterPacketConstructor(ClientAction::PACKET_ORDINAL, CreateConstructor<ClientAction>());
    serverbound->RegisterPacketConstructor(ClientSettings::PACKET_ORDINAL, CreateConstructor<ClientSettings>());
    serverbound->RegisterPacketConstructor(ConfirmTransaction::PACKET_ORDINAL, CreateConstructor<ConfirmTransaction>());
    serverbound->RegisterPacketConstructor(LegacyEnchant::PACKET_ORDINAL, CreateConstructor<LegacyEnchant>());
    serverbound->RegisterPacketConstructor(ClickInventoryButton::PACKET_ORDINAL, CreateConstructor<ClickInventoryButton>());
    serverbound->RegisterPacketConstructor(ClickSlot::PACKET_ORDINAL, CreateConstructor<ClickSlot>());
    serverbound->RegisterPacketConstructor(CloseInventory::PACKET_ORDINAL, CreateConstructor<CloseInventory>(0));
    serverbound->RegisterPacketConstructor(PluginMessage::PACKET_ORDINAL, CreateConstructor<PluginMessage>(std::string {}, nullptr));
    serverbound->RegisterPacketConstructor(EditBook::PACKET_ORDINAL, CreateConstructor<EditBook>());
    serverbound->RegisterPacketConstructor(TagQueryRequest::PACKET_ORDINAL, CreateConstructor<TagQueryRequest>());
    serverbound->RegisterPacketConstructor(EntityInteract::PACKET_ORDINAL, CreateConstructor<EntityInteract>());
    serverbound->RegisterPacketConstructor(GenerateStructure::PACKET_ORDINAL, CreateConstructor<GenerateStructure>());
    serverbound->RegisterPacketConstructor(KeepAlive::PACKET_ORDINAL, CreateConstructor<KeepAlive>(0));
    serverbound->RegisterPacketConstructor(LockDifficulty::PACKET_ORDINAL, CreateConstructor<LockDifficulty>());
    serverbound->RegisterPacketConstructor(MoveGroundOnly::PACKET_ORDINAL, CreateConstructor<MoveGroundOnly>());
    serverbound->RegisterPacketConstructor(MovePositionOnly::PACKET_ORDINAL, CreateConstructor<MovePositionOnly>());
    serverbound->RegisterPacketConstructor(Move::PACKET_ORDINAL, CreateConstructor<Move>());
    serverbound->RegisterPacketConstructor(MoveRotationOnly::PACKET_ORDINAL, CreateConstructor<MoveRotationOnly>());
    serverbound->RegisterPacketConstructor(MoveVehicle::PACKET_ORDINAL, CreateConstructor<MoveVehicle>(0, 0, 0, 0, 0));
    serverbound->RegisterPacketConstructor(BoatPaddle::PACKET_ORDINAL, CreateConstructor<BoatPaddle>());
    serverbound->RegisterPacketConstructor(PickItem::PACKET_ORDINAL, CreateConstructor<PickItem>());
    serverbound->RegisterPacketConstructor(CraftRecipeRequest::PACKET_ORDINAL, CreateConstructor<CraftRecipeRequest>());
    serverbound->RegisterPacketConstructor(ClientPlayerAbilities::PACKET_ORDINAL, CreateConstructor<ClientPlayerAbilities>());
    serverbound->RegisterPacketConstructor(Digging::PACKET_ORDINAL, CreateConstructor<Digging>());
    serverbound->RegisterPacketConstructor(EntityAction::PACKET_ORDINAL, CreateConstructor<EntityAction>());
    serverbound->RegisterPacketConstructor(PlayerInput::PACKET_ORDINAL, CreateConstructor<PlayerInput>());
    serverbound->RegisterPacketConstructor(SeenRecipe::PACKET_ORDINAL, CreateConstructor<SeenRecipe>());
    serverbound->RegisterPacketConstructor(ChangeRecipeBookSettings::PACKET_ORDINAL, CreateConstructor<ChangeRecipeBookSettings>());
    serverbound->RegisterPacketConstructor(LegacyRecipeBook::PACKET_ORDINAL, CreateConstructor<LegacyRecipeBook>());
    serverbound->RegisterPacketConstructor(RenameItem::PACKET_ORDINAL, CreateConstructor<RenameItem>());
    serverbound->RegisterPacketConstructor(ResourcePackResponse::PACKET_ORDINAL, CreateConstructor<ResourcePackResponse>());
    serverbound->RegisterPacketConstructor(SelectAdvancementsTab::PACKET_ORDINAL, CreateConstructor<SelectAdvancementsTab>());
    serverbound->RegisterPacketConstructor(SelectTrade::PACKET_ORDINAL, CreateConstructor<SelectTrade>());
    serverbound->RegisterPacketConstructor(BeaconEffect::PACKET_ORDINAL, CreateConstructor<BeaconEffect>());
    serverbound->RegisterPacketConstructor(HeldSlot::PACKET_ORDINAL, CreateConstructor<HeldSlot>());
    serverbound->RegisterPacketConstructor(ProgramCommandBlock::PACKET_ORDINAL, CreateConstructor<ProgramCommandBlock>());
    serverbound->RegisterPacketConstructor(ProgramCommandBlockMinecart::PACKET_ORDINAL, CreateConstructor<ProgramCommandBlockMinecart>());
    serverbound->RegisterPacketConstructor(CreativeSlot::PACKET_ORDINAL, CreateConstructor<CreativeSlot>());
    serverbound->RegisterPacketConstructor(ProgramJigsawBlock::PACKET_ORDINAL, CreateConstructor<ProgramJigsawBlock>());
    serverbound->RegisterPacketConstructor(ProgramStructureBlock::PACKET_ORDINAL, CreateConstructor<ProgramStructureBlock>());
    serverbound->RegisterPacketConstructor(EditSign::PACKET_ORDINAL, CreateConstructor<EditSign>());
    serverbound->RegisterPacketConstructor(SwingArm::PACKET_ORDINAL, CreateConstructor<SwingArm>());
    serverbound->RegisterPacketConstructor(Spectate::PACKET_ORDINAL, CreateConstructor<Spectate>());
    serverbound->RegisterPacketConstructor(Camera::PACKET_ORDINAL, CreateConstructor<Camera>());
    serverbound->RegisterPacketConstructor(PlaceBlock::PACKET_ORDINAL, CreateConstructor<PlaceBlock>());
    serverbound->RegisterPacketConstructor(UseItem::PACKET_ORDINAL, CreateConstructor<UseItem>());

    clientbound->RegisterVersion(&ProtocolVersion::MINECRAFT_1_12_2,
      new VersionRegistry({ConfirmTeleport::PACKET_ORDINAL, CommandSuggestionRequest::PACKET_ORDINAL, LegacyChat::PACKET_ORDINAL, ClientAction::PACKET_ORDINAL,
        ClientSettings::PACKET_ORDINAL, ConfirmTransaction::PACKET_ORDINAL, LegacyEnchant::PACKET_ORDINAL, ClickSlot::PACKET_ORDINAL,
        CloseInventory::PACKET_ORDINAL, PluginMessage::PACKET_ORDINAL, EntityInteract::PACKET_ORDINAL, KeepAlive::PACKET_ORDINAL,
        MoveGroundOnly::PACKET_ORDINAL, MovePositionOnly::PACKET_ORDINAL, Move::PACKET_ORDINAL, MoveRotationOnly::PACKET_ORDINAL,
        MoveVehicle::PACKET_ORDINAL, BoatPaddle::PACKET_ORDINAL, CraftRecipeRequest::PACKET_ORDINAL, ClientPlayerAbilities::PACKET_ORDINAL,
        Digging::PACKET_ORDINAL, EntityAction::PACKET_ORDINAL, PlayerInput::PACKET_ORDINAL, LegacyRecipeBook::PACKET_ORDINAL,
        ResourcePackResponse::PACKET_ORDINAL, SelectAdvancementsTab::PACKET_ORDINAL, HeldSlot::PACKET_ORDINAL, EditSign::PACKET_ORDINAL,
        SwingArm::PACKET_ORDINAL, Spectate::PACKET_ORDINAL, Camera::PACKET_ORDINAL, PlaceBlock::PACKET_ORDINAL, UseItem::PACKET_ORDINAL}));

    clientbound->RegisterVersion(&ProtocolVersion::MINECRAFT_1_13,
      new VersionRegistry({ConfirmTeleport::PACKET_ORDINAL, BlockTagQueryRequest::PACKET_ORDINAL, LegacyChat::PACKET_ORDINAL, ClientAction::PACKET_ORDINAL,
        ClientSettings::PACKET_ORDINAL, CommandSuggestionRequest::PACKET_ORDINAL, ConfirmTransaction::PACKET_ORDINAL, LegacyEnchant::PACKET_ORDINAL,
        ClickSlot::PACKET_ORDINAL, CloseInventory::PACKET_ORDINAL, PluginMessage::PACKET_ORDINAL, EditBook::PACKET_ORDINAL,
        TagQueryRequest::PACKET_ORDINAL, EntityInteract::PACKET_ORDINAL, KeepAlive::PACKET_ORDINAL, MoveGroundOnly::PACKET_ORDINAL,
        MovePositionOnly::PACKET_ORDINAL, Move::PACKET_ORDINAL, MoveRotationOnly::PACKET_ORDINAL, MoveVehicle::PACKET_ORDINAL, BoatPaddle::PACKET_ORDINAL,
        PickItem::PACKET_ORDINAL, CraftRecipeRequest::PACKET_ORDINAL, ClientPlayerAbilities::PACKET_ORDINAL, Digging::PACKET_ORDINAL,
        EntityAction::PACKET_ORDINAL, PlayerInput::PACKET_ORDINAL, LegacyRecipeBook::PACKET_ORDINAL, RenameItem::PACKET_ORDINAL,
        ResourcePackResponse::PACKET_ORDINAL, SelectAdvancementsTab::PACKET_ORDINAL, SelectTrade::PACKET_ORDINAL, BeaconEffect::PACKET_ORDINAL,
        HeldSlot::PACKET_ORDINAL, ProgramCommandBlock::PACKET_ORDINAL, ProgramCommandBlockMinecart::PACKET_ORDINAL, CreativeSlot::PACKET_ORDINAL,
        ProgramStructureBlock::PACKET_ORDINAL, EditSign::PACKET_ORDINAL, SwingArm::PACKET_ORDINAL, Spectate::PACKET_ORDINAL, PlaceBlock::PACKET_ORDINAL,
        UseItem::PACKET_ORDINAL}));

    clientbound->RegisterVersion(&ProtocolVersion::MINECRAFT_1_14,
      new VersionRegistry({ConfirmTeleport::PACKET_ORDINAL, BlockTagQueryRequest::PACKET_ORDINAL, ClientChangeDifficulty::PACKET_ORDINAL,
        LegacyChat::PACKET_ORDINAL, ClientAction::PACKET_ORDINAL, ClientSettings::PACKET_ORDINAL, CommandSuggestionRequest::PACKET_ORDINAL,
        ConfirmTransaction::PACKET_ORDINAL, ClickInventoryButton::PACKET_ORDINAL, ClickSlot::PACKET_ORDINAL, CloseInventory::PACKET_ORDINAL,
        PluginMessage::PACKET_ORDINAL, EditBook::PACKET_ORDINAL, TagQueryRequest::PACKET_ORDINAL, EntityInteract::PACKET_ORDINAL,
        KeepAlive::PACKET_ORDINAL, LockDifficulty::PACKET_ORDINAL, MoveGroundOnly::PACKET_ORDINAL, MovePositionOnly::PACKET_ORDINAL, Move::PACKET_ORDINAL,
        MoveRotationOnly::PACKET_ORDINAL, MoveVehicle::PACKET_ORDINAL, BoatPaddle::PACKET_ORDINAL, PickItem::PACKET_ORDINAL,
        CraftRecipeRequest::PACKET_ORDINAL, ClientPlayerAbilities::PACKET_ORDINAL, Digging::PACKET_ORDINAL, EntityAction::PACKET_ORDINAL,
        PlayerInput::PACKET_ORDINAL, LegacyRecipeBook::PACKET_ORDINAL, RenameItem::PACKET_ORDINAL, ResourcePackResponse::PACKET_ORDINAL,
        SelectAdvancementsTab::PACKET_ORDINAL, SelectTrade::PACKET_ORDINAL, BeaconEffect::PACKET_ORDINAL, HeldSlot::PACKET_ORDINAL,
        ProgramCommandBlock::PACKET_ORDINAL, ProgramCommandBlockMinecart::PACKET_ORDINAL, CreativeSlot::PACKET_ORDINAL, ProgramJigsawBlock::PACKET_ORDINAL,
        ProgramStructureBlock::PACKET_ORDINAL, EditSign::PACKET_ORDINAL, SwingArm::PACKET_ORDINAL, Spectate::PACKET_ORDINAL, PlaceBlock::PACKET_ORDINAL,
        UseItem::PACKET_ORDINAL}));

    VersionRegistry serverbound1_15 = VersionRegistry({ConfirmTeleport::PACKET_ORDINAL, BlockTagQueryRequest::PACKET_ORDINAL,
      ClientChangeDifficulty::PACKET_ORDINAL, LegacyChat::PACKET_ORDINAL, ClientAction::PACKET_ORDINAL, ClientSettings::PACKET_ORDINAL,
      CommandSuggestionRequest::PACKET_ORDINAL, ConfirmTransaction::PACKET_ORDINAL, ClickInventoryButton::PACKET_ORDINAL, ClickSlot::PACKET_ORDINAL,
      CloseInventory::PACKET_ORDINAL, PluginMessage::PACKET_ORDINAL, EditBook::PACKET_ORDINAL, TagQueryRequest::PACKET_ORDINAL,
      EntityInteract::PACKET_ORDINAL, KeepAlive::PACKET_ORDINAL, LockDifficulty::PACKET_ORDINAL, MoveGroundOnly::PACKET_ORDINAL,
      MovePositionOnly::PACKET_ORDINAL, Move::PACKET_ORDINAL, MoveRotationOnly::PACKET_ORDINAL, MoveVehicle::PACKET_ORDINAL, BoatPaddle::PACKET_ORDINAL,
      PickItem::PACKET_ORDINAL, CraftRecipeRequest::PACKET_ORDINAL, ClientPlayerAbilities::PACKET_ORDINAL, Digging::PACKET_ORDINAL,
      EntityAction::PACKET_ORDINAL, PlayerInput::PACKET_ORDINAL, LegacyRecipeBook::PACKET_ORDINAL, RenameItem::PACKET_ORDINAL,
      ResourcePackResponse::PACKET_ORDINAL, SelectAdvancementsTab::PACKET_ORDINAL, SelectTrade::PACKET_ORDINAL, BeaconEffect::PACKET_ORDINAL,
      HeldSlot::PACKET_ORDINAL, ProgramCommandBlock::PACKET_ORDINAL, ProgramCommandBlockMinecart::PACKET_ORDINAL, CreativeSlot::PACKET_ORDINAL,
      ProgramJigsawBlock::PACKET_ORDINAL, ProgramStructureBlock::PACKET_ORDINAL, EditSign::PACKET_ORDINAL, SwingArm::PACKET_ORDINAL,
      Spectate::PACKET_ORDINAL, PlaceBlock::PACKET_ORDINAL, UseItem::PACKET_ORDINAL});

    clientbound->RegisterVersion(&ProtocolVersion::MINECRAFT_1_16_2,
      new VersionRegistry({ConfirmTeleport::PACKET_ORDINAL, BlockTagQueryRequest::PACKET_ORDINAL, ClientChangeDifficulty::PACKET_ORDINAL,
        LegacyChat::PACKET_ORDINAL, ClientAction::PACKET_ORDINAL, ClientSettings::PACKET_ORDINAL, CommandSuggestionRequest::PACKET_ORDINAL,
        ConfirmTransaction::PACKET_ORDINAL, ClickInventoryButton::PACKET_ORDINAL, ClickSlot::PACKET_ORDINAL, CloseInventory::PACKET_ORDINAL,
        PluginMessage::PACKET_ORDINAL, EditBook::PACKET_ORDINAL, TagQueryRequest::PACKET_ORDINAL, EntityInteract::PACKET_ORDINAL,
        GenerateStructure::PACKET_ORDINAL, KeepAlive::PACKET_ORDINAL, LockDifficulty::PACKET_ORDINAL, MovePositionOnly::PACKET_ORDINAL,
        Move::PACKET_ORDINAL, MoveRotationOnly::PACKET_ORDINAL, MoveVehicle::PACKET_ORDINAL, MoveGroundOnly::PACKET_ORDINAL, BoatPaddle::PACKET_ORDINAL,
        PickItem::PACKET_ORDINAL, CraftRecipeRequest::PACKET_ORDINAL, ClientPlayerAbilities::PACKET_ORDINAL, Digging::PACKET_ORDINAL,
        EntityAction::PACKET_ORDINAL, PlayerInput::PACKET_ORDINAL, SeenRecipe::PACKET_ORDINAL, ChangeRecipeBookSettings::PACKET_ORDINAL,
        RenameItem::PACKET_ORDINAL, ResourcePackResponse::PACKET_ORDINAL, SelectAdvancementsTab::PACKET_ORDINAL, SelectTrade::PACKET_ORDINAL,
        BeaconEffect::PACKET_ORDINAL, HeldSlot::PACKET_ORDINAL, ProgramCommandBlock::PACKET_ORDINAL, ProgramCommandBlockMinecart::PACKET_ORDINAL,
        CreativeSlot::PACKET_ORDINAL, ProgramJigsawBlock::PACKET_ORDINAL, ProgramStructureBlock::PACKET_ORDINAL, EditSign::PACKET_ORDINAL,
        SwingArm::PACKET_ORDINAL, Spectate::PACKET_ORDINAL, PlaceBlock::PACKET_ORDINAL, UseItem::PACKET_ORDINAL}));

    clientbound->RegisterVersion(&ProtocolVersion::MINECRAFT_1_17,
      new VersionRegistry(
        {ConfirmTeleport::PACKET_ORDINAL, BlockTagQueryRequest::PACKET_ORDINAL, ClientChangeDifficulty::PACKET_ORDINAL, LegacyChat::PACKET_ORDINAL,
          ClientAction::PACKET_ORDINAL, ClientSettings::PACKET_ORDINAL, CommandSuggestionRequest::PACKET_ORDINAL, ClickInventoryButton::PACKET_ORDINAL,
          ClickSlot::PACKET_ORDINAL, CloseInventory::PACKET_ORDINAL, PluginMessage::PACKET_ORDINAL, EditBook::PACKET_ORDINAL,
          TagQueryRequest::PACKET_ORDINAL, EntityInteract::PACKET_ORDINAL, GenerateStructure::PACKET_ORDINAL, KeepAlive::PACKET_ORDINAL,
          LockDifficulty::PACKET_ORDINAL, MovePositionOnly::PACKET_ORDINAL, Move::PACKET_ORDINAL, MoveRotationOnly::PACKET_ORDINAL,
          MoveGroundOnly::PACKET_ORDINAL, MoveVehicle::PACKET_ORDINAL, BoatPaddle::PACKET_ORDINAL, PickItem::PACKET_ORDINAL,
          CraftRecipeRequest::PACKET_ORDINAL, ClientPlayerAbilities::PACKET_ORDINAL, Digging::PACKET_ORDINAL, EntityAction::PACKET_ORDINAL,
          PlayerInput::PACKET_ORDINAL, Ping::PACKET_ORDINAL, SeenRecipe::PACKET_ORDINAL, ChangeRecipeBookSettings::PACKET_ORDINAL,
          RenameItem::PACKET_ORDINAL, ResourcePackResponse::PACKET_ORDINAL, SelectAdvancementsTab::PACKET_ORDINAL, SelectTrade::PACKET_ORDINAL,
          BeaconEffect::PACKET_ORDINAL, HeldSlot::PACKET_ORDINAL, ProgramCommandBlock::PACKET_ORDINAL, ProgramCommandBlockMinecart::PACKET_ORDINAL,
          CreativeSlot::PACKET_ORDINAL, ProgramJigsawBlock::PACKET_ORDINAL, ProgramStructureBlock::PACKET_ORDINAL, EditSign::PACKET_ORDINAL,
          SwingArm::PACKET_ORDINAL, Spectate::PACKET_ORDINAL, PlaceBlock::PACKET_ORDINAL, UseItem::PACKET_ORDINAL}));

    clientbound->RegisterVersion(&ProtocolVersion::MINECRAFT_1_18,
      new VersionRegistry(
        {ConfirmTeleport::PACKET_ORDINAL, BlockTagQueryRequest::PACKET_ORDINAL, ClientChangeDifficulty::PACKET_ORDINAL, LegacyChat::PACKET_ORDINAL,
          ClientAction::PACKET_ORDINAL, ClientSettings::PACKET_ORDINAL, CommandSuggestionRequest::PACKET_ORDINAL, ClickInventoryButton::PACKET_ORDINAL,
          ClickSlot::PACKET_ORDINAL, CloseInventory::PACKET_ORDINAL, PluginMessage::PACKET_ORDINAL, EditBook::PACKET_ORDINAL,
          TagQueryRequest::PACKET_ORDINAL, EntityInteract::PACKET_ORDINAL, GenerateStructure::PACKET_ORDINAL, KeepAlive::PACKET_ORDINAL,
          LockDifficulty::PACKET_ORDINAL, MovePositionOnly::PACKET_ORDINAL, Move::PACKET_ORDINAL, MoveRotationOnly::PACKET_ORDINAL,
          MoveGroundOnly::PACKET_ORDINAL, MoveVehicle::PACKET_ORDINAL, BoatPaddle::PACKET_ORDINAL, PickItem::PACKET_ORDINAL,
          CraftRecipeRequest::PACKET_ORDINAL, ClientPlayerAbilities::PACKET_ORDINAL, Digging::PACKET_ORDINAL, EntityAction::PACKET_ORDINAL,
          PlayerInput::PACKET_ORDINAL, Ping::PACKET_ORDINAL, SeenRecipe::PACKET_ORDINAL, ChangeRecipeBookSettings::PACKET_ORDINAL,
          RenameItem::PACKET_ORDINAL, ResourcePackResponse::PACKET_ORDINAL, SelectAdvancementsTab::PACKET_ORDINAL, SelectTrade::PACKET_ORDINAL,
          BeaconEffect::PACKET_ORDINAL, HeldSlot::PACKET_ORDINAL, ProgramCommandBlock::PACKET_ORDINAL, ProgramCommandBlockMinecart::PACKET_ORDINAL,
          CreativeSlot::PACKET_ORDINAL, ProgramJigsawBlock::PACKET_ORDINAL, ProgramStructureBlock::PACKET_ORDINAL, EditSign::PACKET_ORDINAL,
          SwingArm::PACKET_ORDINAL, Spectate::PACKET_ORDINAL, PlaceBlock::PACKET_ORDINAL, UseItem::PACKET_ORDINAL}));

    clientbound->RegisterVersion(&ProtocolVersion::MINECRAFT_1_19,
      new VersionRegistry({ConfirmTeleport::PACKET_ORDINAL, BlockTagQueryRequest::PACKET_ORDINAL, ClientChangeDifficulty::PACKET_ORDINAL,
        Command::PACKET_ORDINAL, ClientPlayerChat::PACKET_ORDINAL, ClientChatPreview::PACKET_ORDINAL, ClientAction::PACKET_ORDINAL,
        ClientSettings::PACKET_ORDINAL, CommandSuggestionRequest::PACKET_ORDINAL, ClickInventoryButton::PACKET_ORDINAL, ClickSlot::PACKET_ORDINAL,
        CloseInventory::PACKET_ORDINAL, PluginMessage::PACKET_ORDINAL, EditBook::PACKET_ORDINAL, TagQueryRequest::PACKET_ORDINAL,
        EntityInteract::PACKET_ORDINAL, GenerateStructure::PACKET_ORDINAL, KeepAlive::PACKET_ORDINAL, LockDifficulty::PACKET_ORDINAL,
        MovePositionOnly::PACKET_ORDINAL, Move::PACKET_ORDINAL, MoveRotationOnly::PACKET_ORDINAL, MoveGroundOnly::PACKET_ORDINAL,
        MoveVehicle::PACKET_ORDINAL, BoatPaddle::PACKET_ORDINAL, PickItem::PACKET_ORDINAL, CraftRecipeRequest::PACKET_ORDINAL,
        ClientPlayerAbilities::PACKET_ORDINAL, Digging::PACKET_ORDINAL, EntityAction::PACKET_ORDINAL, PlayerInput::PACKET_ORDINAL, Ping::PACKET_ORDINAL,
        SeenRecipe::PACKET_ORDINAL, ChangeRecipeBookSettings::PACKET_ORDINAL, RenameItem::PACKET_ORDINAL, ResourcePackResponse::PACKET_ORDINAL,
        SelectAdvancementsTab::PACKET_ORDINAL, SelectTrade::PACKET_ORDINAL, BeaconEffect::PACKET_ORDINAL, HeldSlot::PACKET_ORDINAL,
        ProgramCommandBlock::PACKET_ORDINAL, ProgramCommandBlockMinecart::PACKET_ORDINAL, CreativeSlot::PACKET_ORDINAL, ProgramJigsawBlock::PACKET_ORDINAL,
        ProgramStructureBlock::PACKET_ORDINAL, EditSign::PACKET_ORDINAL, SwingArm::PACKET_ORDINAL, Spectate::PACKET_ORDINAL, PlaceBlock::PACKET_ORDINAL,
        UseItem::PACKET_ORDINAL}));

    clientbound->RegisterVersion(&ProtocolVersion::MINECRAFT_1_19_1,
      new VersionRegistry({ConfirmTeleport::PACKET_ORDINAL, BlockTagQueryRequest::PACKET_ORDINAL, ClientChangeDifficulty::PACKET_ORDINAL,
        MessageAcknowledgment::PACKET_ORDINAL, // TODO: MessageAcknowledgment
        Command::PACKET_ORDINAL, ClientPlayerChat::PACKET_ORDINAL, ClientChatPreview::PACKET_ORDINAL, ClientAction::PACKET_ORDINAL,
        ClientSettings::PACKET_ORDINAL, CommandSuggestionRequest::PACKET_ORDINAL, ClickInventoryButton::PACKET_ORDINAL, ClickSlot::PACKET_ORDINAL,
        CloseInventory::PACKET_ORDINAL, PluginMessage::PACKET_ORDINAL, EditBook::PACKET_ORDINAL, TagQueryRequest::PACKET_ORDINAL,
        EntityInteract::PACKET_ORDINAL, GenerateStructure::PACKET_ORDINAL, KeepAlive::PACKET_ORDINAL, LockDifficulty::PACKET_ORDINAL,
        MovePositionOnly::PACKET_ORDINAL, Move::PACKET_ORDINAL, MoveRotationOnly::PACKET_ORDINAL, MoveGroundOnly::PACKET_ORDINAL,
        MoveVehicle::PACKET_ORDINAL, BoatPaddle::PACKET_ORDINAL, PickItem::PACKET_ORDINAL, CraftRecipeRequest::PACKET_ORDINAL,
        ClientPlayerAbilities::PACKET_ORDINAL, Digging::PACKET_ORDINAL, EntityAction::PACKET_ORDINAL, PlayerInput::PACKET_ORDINAL, Ping::PACKET_ORDINAL,
        SeenRecipe::PACKET_ORDINAL, ChangeRecipeBookSettings::PACKET_ORDINAL, RenameItem::PACKET_ORDINAL, ResourcePackResponse::PACKET_ORDINAL,
        SelectAdvancementsTab::PACKET_ORDINAL, SelectTrade::PACKET_ORDINAL, BeaconEffect::PACKET_ORDINAL, HeldSlot::PACKET_ORDINAL,
        ProgramCommandBlock::PACKET_ORDINAL, ProgramCommandBlockMinecart::PACKET_ORDINAL, CreativeSlot::PACKET_ORDINAL, ProgramJigsawBlock::PACKET_ORDINAL,
        ProgramStructureBlock::PACKET_ORDINAL, EditSign::PACKET_ORDINAL, SwingArm::PACKET_ORDINAL, Spectate::PACKET_ORDINAL, PlaceBlock::PACKET_ORDINAL,
        UseItem::PACKET_ORDINAL}));

    clientbound->RegisterVersion(&ProtocolVersion::MINECRAFT_1_19_3,
      new VersionRegistry({ConfirmTeleport::PACKET_ORDINAL, BlockTagQueryRequest::PACKET_ORDINAL, ClientChangeDifficulty::PACKET_ORDINAL,
        MessageAcknowledgment::PACKET_ORDINAL, Command::PACKET_ORDINAL, ClientPlayerChat::PACKET_ORDINAL, ClientAction::PACKET_ORDINAL,
        ClientSettings::PACKET_ORDINAL, CommandSuggestionRequest::PACKET_ORDINAL, ClickInventoryButton::PACKET_ORDINAL, ClickSlot::PACKET_ORDINAL,
        CloseInventory::PACKET_ORDINAL, PluginMessage::PACKET_ORDINAL, EditBook::PACKET_ORDINAL, TagQueryRequest::PACKET_ORDINAL,
        EntityInteract::PACKET_ORDINAL, GenerateStructure::PACKET_ORDINAL, KeepAlive::PACKET_ORDINAL, LockDifficulty::PACKET_ORDINAL,
        MovePositionOnly::PACKET_ORDINAL, Move::PACKET_ORDINAL, MoveRotationOnly::PACKET_ORDINAL, MoveGroundOnly::PACKET_ORDINAL,
        MoveVehicle::PACKET_ORDINAL, BoatPaddle::PACKET_ORDINAL, PickItem::PACKET_ORDINAL, CraftRecipeRequest::PACKET_ORDINAL,
        ClientPlayerAbilities::PACKET_ORDINAL, Digging::PACKET_ORDINAL, EntityAction::PACKET_ORDINAL, PlayerInput::PACKET_ORDINAL, Ping::PACKET_ORDINAL,
        PlayerChatSession::PACKET_ORDINAL, SeenRecipe::PACKET_ORDINAL, ChangeRecipeBookSettings::PACKET_ORDINAL, RenameItem::PACKET_ORDINAL,
        ResourcePackResponse::PACKET_ORDINAL, SelectAdvancementsTab::PACKET_ORDINAL, SelectTrade::PACKET_ORDINAL, BeaconEffect::PACKET_ORDINAL,
        HeldSlot::PACKET_ORDINAL, ProgramCommandBlock::PACKET_ORDINAL, ProgramCommandBlockMinecart::PACKET_ORDINAL, CreativeSlot::PACKET_ORDINAL,
        ProgramJigsawBlock::PACKET_ORDINAL, ProgramStructureBlock::PACKET_ORDINAL, EditSign::PACKET_ORDINAL, SwingArm::PACKET_ORDINAL,
        Spectate::PACKET_ORDINAL, PlaceBlock::PACKET_ORDINAL, UseItem::PACKET_ORDINAL}));

    return {clientbound, serverbound};
  }

  const PacketRegistry BuiltInPacketRegistry::HANDSHAKE = GetHandshakeRegistry();
  const PacketRegistry BuiltInPacketRegistry::STATUS = GetStatusRegistry();
  const PacketRegistry BuiltInPacketRegistry::LOGIN = GetLoginRegistry();
  const PacketRegistry BuiltInPacketRegistry::PLAY = GetPlayRegistry();
}