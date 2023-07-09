#include "BuiltInPacketRegistry.hpp"
#include "../packet/handshake/Handshake.hpp"
#include "../packet/login/EncryptionRequest.hpp"
#include "../packet/login/EncryptionResponse.hpp"
#include "../packet/login/LoginPluginMessage.hpp"
#include "../packet/login/LoginPluginResponse.hpp"
#include "../packet/login/LoginStart.hpp"
#include "../packet/login/LoginSuccess.hpp"
#include "../packet/login/SetCompression.hpp"
#include "../packet/play/AcknowledgeBlockChange.hpp"
#include "../packet/play/AcknowledgePlayerDigging.hpp"
#include "../packet/play/ActionBar.hpp"
#include "../packet/play/Advancements.hpp"
#include "../packet/play/AwardStatistics.hpp"
#include "../packet/play/BeaconEffect.hpp"
#include "../packet/play/BlockAction.hpp"
#include "../packet/play/BlockDestroyStage.hpp"
#include "../packet/play/BlockEntityData.hpp"
#include "../packet/play/BlockTagQueryRequest.hpp"
#include "../packet/play/BlockUpdate.hpp"
#include "../packet/play/BoatPaddle.hpp"
#include "../packet/play/BorderCenter.hpp"
#include "../packet/play/BorderRadius.hpp"
#include "../packet/play/BorderRadiusSpeed.hpp"
#include "../packet/play/BorderWarningRadius.hpp"
#include "../packet/play/BorderWarningTime.hpp"
#include "../packet/play/BossBar.hpp"
#include "../packet/play/Camera.hpp"
#include "../packet/play/ChangeRecipeBookSettings.hpp"
#include "../packet/play/ChatSuggestions.hpp"
#include "../packet/play/ChunkData.hpp"
#include "../packet/play/ChunkLight.hpp"
#include "../packet/play/ClearTitle.hpp"
#include "../packet/play/ClickInventoryButton.hpp"
#include "../packet/play/ClickSlot.hpp"
#include "../packet/play/ClientAction.hpp"
#include "../packet/play/ClientChangeDifficulty.hpp"
#include "../packet/play/ClientChatPreview.hpp"
#include "../packet/play/ClientPlayerAbilities.hpp"
#include "../packet/play/ClientPlayerChat.hpp"
#include "../packet/play/ClientSettings.hpp"
#include "../packet/play/CloseInventory.hpp"
#include "../packet/play/CombatEvent.hpp"
#include "../packet/play/Command.hpp"
#include "../packet/play/CommandSuggestionRequest.hpp"
#include "../packet/play/CommandSuggestionResponse.hpp"
#include "../packet/play/ConfirmTeleport.hpp"
#include "../packet/play/ConfirmTransaction.hpp"
#include "../packet/play/Cooldown.hpp"
#include "../packet/play/CraftRecipeRequest.hpp"
#include "../packet/play/CraftRecipeResponse.hpp"
#include "../packet/play/CreativeSlot.hpp"
#include "../packet/play/CustomSoundEffect.hpp"
#include "../packet/play/DeathCombatEvent.hpp"
#include "../packet/play/DeclareCommands.hpp"
#include "../packet/play/DefaultSpawnPosition.hpp"
#include "../packet/play/Digging.hpp"
#include "../packet/play/Disconnect.hpp"
#include "../packet/play/DisguisedChatMessage.hpp"
#include "../packet/play/DisplayObjective.hpp"
#include "../packet/play/EditBook.hpp"
#include "../packet/play/EditSign.hpp"
#include "../packet/play/EndCombatEvent.hpp"
#include "../packet/play/EnterCombatEvent.hpp"
#include "../packet/play/EntityAction.hpp"
#include "../packet/play/EntityAnimation.hpp"
#include "../packet/play/EntityEffect.hpp"
#include "../packet/play/EntityEffectRemove.hpp"
#include "../packet/play/EntityEquipment.hpp"
#include "../packet/play/EntityEvent.hpp"
#include "../packet/play/EntityInteract.hpp"
#include "../packet/play/EntityLookAt.hpp"
#include "../packet/play/EntityMetadata.hpp"
#include "../packet/play/EntityNotMoved.hpp"
#include "../packet/play/EntityPosition.hpp"
#include "../packet/play/EntityPositionAndRotation.hpp"
#include "../packet/play/EntityProperties.hpp"
#include "../packet/play/EntityRemove.hpp"
#include "../packet/play/EntityRotation.hpp"
#include "../packet/play/EntitySoundEffect.hpp"
#include "../packet/play/EntityTeleport.hpp"
#include "../packet/play/EntityVelocity.hpp"
#include "../packet/play/Experience.hpp"
#include "../packet/play/Explosion.hpp"
#include "../packet/play/FeatureFlags.hpp"
#include "../packet/play/GameEvent.hpp"
#include "../packet/play/GenerateStructure.hpp"
#include "../packet/play/HardcodedSoundEffect.hpp"
#include "../packet/play/Health.hpp"
#include "../packet/play/HeldSlot.hpp"
#include "../packet/play/HideMessage.hpp"
#include "../packet/play/InitializeWorldBorder.hpp"
#include "../packet/play/InventoryContent.hpp"
#include "../packet/play/InventoryProperty.hpp"
#include "../packet/play/InventorySlot.hpp"
#include "../packet/play/JoinGame.hpp"
#include "../packet/play/KeepAlive.hpp"
#include "../packet/play/LeadEntities.hpp"
#include "../packet/play/LegacyChat.hpp"
#include "../packet/play/LegacyCraftRecipeResponse.hpp"
#include "../packet/play/LegacyEnchant.hpp"
#include "../packet/play/LegacyRecipeBook.hpp"
#include "../packet/play/LegacyTitle.hpp"
#include "../packet/play/LegacyWorldBorder.hpp"
#include "../packet/play/LockDifficulty.hpp"
#include "../packet/play/MapData.hpp"
#include "../packet/play/MessageAcknowledgment.hpp"
#include "../packet/play/MessageHeader.hpp"
#include "../packet/play/Move.hpp"
#include "../packet/play/MoveGroundOnly.hpp"
#include "../packet/play/MovePositionOnly.hpp"
#include "../packet/play/MoveRotationOnly.hpp"
#include "../packet/play/MoveVehicle.hpp"
#include "../packet/play/Objectives.hpp"
#include "../packet/play/OpenBook.hpp"
#include "../packet/play/OpenHorseInventory.hpp"
#include "../packet/play/OpenInventory.hpp"
#include "../packet/play/OpenSignEditor.hpp"
#include "../packet/play/Particle.hpp"
#include "../packet/play/Passengers.hpp"
#include "../packet/play/PickItem.hpp"
#include "../packet/play/PickupItem.hpp"
#include "../packet/play/Ping.hpp"
#include "../packet/play/PlaceBlock.hpp"
#include "../packet/play/PlayerChatSession.hpp"
#include "../packet/play/PlayerFace.hpp"
#include "../packet/play/PlayerInput.hpp"
#include "../packet/play/PlayerListItem.hpp"
#include "../packet/play/PlayerRemove.hpp"
#include "../packet/play/PluginMessage.hpp"
#include "../packet/play/PositionRotation.hpp"
#include "../packet/play/ProgramCommandBlock.hpp"
#include "../packet/play/ProgramCommandBlockMinecart.hpp"
#include "../packet/play/ProgramJigsawBlock.hpp"
#include "../packet/play/ProgramStructureBlock.hpp"
#include "../packet/play/Recipes.hpp"
#include "../packet/play/RenameItem.hpp"
#include "../packet/play/ResourcePackRequest.hpp"
#include "../packet/play/ResourcePackResponse.hpp"
#include "../packet/play/Respawn.hpp"
#include "../packet/play/Score.hpp"
#include "../packet/play/SculkVibration.hpp"
#include "../packet/play/SectionBlocks.hpp"
#include "../packet/play/SeenRecipe.hpp"
#include "../packet/play/SelectAdvancementsTab.hpp"
#include "../packet/play/SelectTrade.hpp"
#include "../packet/play/ServerChangeDifficulty.hpp"
#include "../packet/play/ServerChatPreview.hpp"
#include "../packet/play/ServerData.hpp"
#include "../packet/play/ServerPlayerAbilities.hpp"
#include "../packet/play/ServerPlayerChat.hpp"
#include "../packet/play/SetDisplayChatPreview.hpp"
#include "../packet/play/SimulationDistance.hpp"
#include "../packet/play/SpawnEntity.hpp"
#include "../packet/play/SpawnExperienceOrb.hpp"
#include "../packet/play/SpawnPainting.hpp"
#include "../packet/play/SpawnPlayer.hpp"
#include "../packet/play/SpawnThunderbolt.hpp"
#include "../packet/play/Spectate.hpp"
#include "../packet/play/StopSound.hpp"
#include "../packet/play/Subtitle.hpp"
#include "../packet/play/SwingArm.hpp"
#include "../packet/play/SystemChat.hpp"
#include "../packet/play/TabHeaderFooter.hpp"
#include "../packet/play/TagQueryRequest.hpp"
#include "../packet/play/TagQueryResponse.hpp"
#include "../packet/play/Tags.hpp"
#include "../packet/play/Teams.hpp"
#include "../packet/play/Title.hpp"
#include "../packet/play/TitleTimes.hpp"
#include "../packet/play/TradeList.hpp"
#include "../packet/play/UnloadChunk.hpp"
#include "../packet/play/UnlockRecipes.hpp"
#include "../packet/play/UseBed.hpp"
#include "../packet/play/UseItem.hpp"
#include "../packet/play/ViewDistance.hpp"
#include "../packet/play/ViewPosition.hpp"
#include "../packet/play/WorldEvent.hpp"
#include "../packet/play/WorldTime.hpp"
#include "../packet/status/StatusPing.hpp"
#include "../packet/status/StatusRequest.hpp"
#include "../packet/status/StatusResponse.hpp"
#include "PacketRegistry.hpp"

namespace Ship {

  PacketRegistry GetHandshakeRegistry() {
    auto* serverbound = new DirectionRegistry();
    serverbound->FillVersionRegistry(new VersionRegistry({Handshake::PACKET_ORDINAL}));

    return {nullptr, serverbound};
  }

  PacketRegistry GetStatusRegistry() {
    auto* clientbound = new DirectionRegistry();
    clientbound->FillVersionRegistry(new VersionRegistry({StatusResponse::PACKET_ORDINAL, StatusPing::PACKET_ORDINAL}));

    auto* serverbound = new DirectionRegistry();
    serverbound->FillVersionRegistry(new VersionRegistry({StatusRequest::PACKET_ORDINAL, StatusPing::PACKET_ORDINAL}));

    return {clientbound, serverbound};
  }

  PacketRegistry GetLoginRegistry() {
    auto* clientbound = new DirectionRegistry();
    clientbound->FillVersionRegistry(new VersionRegistry({Disconnect::PACKET_ORDINAL, EncryptionRequest::PACKET_ORDINAL, LoginSuccess::PACKET_ORDINAL,
      SetCompression::PACKET_ORDINAL, LoginPluginMessage::PACKET_ORDINAL}));

    auto* serverbound = new DirectionRegistry();
    serverbound->FillVersionRegistry(
      new VersionRegistry({LoginStart::PACKET_ORDINAL, EncryptionResponse::PACKET_ORDINAL, LoginPluginResponse::PACKET_ORDINAL}));

    return {clientbound, serverbound};
  }

  PacketRegistry GetPlayRegistry() {
    auto* clientbound = new DirectionRegistry();

    clientbound->RegisterVersion(&MinecraftProtocolVersion::MINECRAFT_1_12_2,
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

    clientbound->RegisterVersion(&MinecraftProtocolVersion::MINECRAFT_1_13,
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

    clientbound->RegisterVersion(&MinecraftProtocolVersion::MINECRAFT_1_14,
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

    clientbound->RegisterVersion(&MinecraftProtocolVersion::MINECRAFT_1_15,
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

    clientbound->RegisterVersion(&MinecraftProtocolVersion::MINECRAFT_1_16_2,
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

    clientbound->RegisterVersion(&MinecraftProtocolVersion::MINECRAFT_1_17,
      new VersionRegistry({SpawnEntity::PACKET_ORDINAL, SpawnExperienceOrb::PACKET_ORDINAL, SpawnEntity::PACKET_ORDINAL, SpawnPainting::PACKET_ORDINAL,
        SpawnPlayer::PACKET_ORDINAL, SkulkVibration::PACKET_ORDINAL, EntityAnimation::PACKET_ORDINAL, AwardStatistics::PACKET_ORDINAL,
        AcknowledgePlayerDigging::PACKET_ORDINAL, BlockDestroyStage::PACKET_ORDINAL, BlockEntityData::PACKET_ORDINAL, BlockAction::PACKET_ORDINAL,
        BlockUpdate::PACKET_ORDINAL, BossBar::PACKET_ORDINAL, ServerChangeDifficulty::PACKET_ORDINAL, LegacyChat::PACKET_ORDINAL,
        ClearTitle::PACKET_ORDINAL, CommandSuggestionResponse::PACKET_ORDINAL, DeclareCommands::PACKET_ORDINAL, CloseInventory::PACKET_ORDINAL,
        InventoryContent::PACKET_ORDINAL, InventoryProperty::PACKET_ORDINAL, InventorySlot::PACKET_ORDINAL, Cooldown::PACKET_ORDINAL,
        PluginMessage::PACKET_ORDINAL, CustomSoundEffect::PACKET_ORDINAL, Disconnect::PACKET_ORDINAL, EntityAnimation::PACKET_ORDINAL,
        Explosion::PACKET_ORDINAL, UnloadChunk::PACKET_ORDINAL, GameEvent::PACKET_ORDINAL, OpenHorseInventory::PACKET_ORDINAL,
        InitializeWorldBorder::PACKET_ORDINAL, KeepAlive::PACKET_ORDINAL, ChunkData::PACKET_ORDINAL, WorldEvent::PACKET_ORDINAL, Particle::PACKET_ORDINAL,
        ChunkLight::PACKET_ORDINAL, JoinGame::PACKET_ORDINAL, MapData::PACKET_ORDINAL, TradeList::PACKET_ORDINAL, EntityPosition::PACKET_ORDINAL,
        EntityPositionAndRotation::PACKET_ORDINAL, EntityRotation::PACKET_ORDINAL, MoveVehicle::PACKET_ORDINAL, OpenBook::PACKET_ORDINAL,
        OpenInventory::PACKET_ORDINAL, OpenSignEditor::PACKET_ORDINAL, Ping::PACKET_ORDINAL, CraftRecipeResponse::PACKET_ORDINAL,
        ServerPlayerAbilities::PACKET_ORDINAL, EndCombatEvent::PACKET_ORDINAL, EnterCombatEvent::PACKET_ORDINAL, DeathCombatEvent::PACKET_ORDINAL,
        PlayerListItem::PACKET_ORDINAL, PlayerFace::PACKET_ORDINAL, PositionRotation::PACKET_ORDINAL, UnlockRecipes::PACKET_ORDINAL,
        EntityRemove::PACKET_ORDINAL, EntityEffectRemove::PACKET_ORDINAL, ResourcePackRequest::PACKET_ORDINAL, Respawn::PACKET_ORDINAL,
        EntityLookAt::PACKET_ORDINAL, SectionBlocks::PACKET_ORDINAL, SelectAdvancementsTab::PACKET_ORDINAL, ActionBar::PACKET_ORDINAL,
        BorderCenter::PACKET_ORDINAL, BorderRadiusSpeed::PACKET_ORDINAL, BorderRadius::PACKET_ORDINAL, BorderWarningTime::PACKET_ORDINAL,
        BorderWarningRadius::PACKET_ORDINAL, Camera::PACKET_ORDINAL, HeldSlot::PACKET_ORDINAL, ViewPosition::PACKET_ORDINAL, ViewDistance::PACKET_ORDINAL,
        DefaultSpawnPosition::PACKET_ORDINAL, DisplayObjective::PACKET_ORDINAL, EntityMetadata::PACKET_ORDINAL, LeadEntities::PACKET_ORDINAL,
        EntityVelocity::PACKET_ORDINAL, EntityEquipment::PACKET_ORDINAL, Experience::PACKET_ORDINAL, Health::PACKET_ORDINAL, Objectives::PACKET_ORDINAL,
        Passengers::PACKET_ORDINAL, Teams::PACKET_ORDINAL, Score::PACKET_ORDINAL, Subtitle::PACKET_ORDINAL, WorldTime::PACKET_ORDINAL,
        Title::PACKET_ORDINAL, TitleTimes::PACKET_ORDINAL, EntitySoundEffect::PACKET_ORDINAL, HardcodedSoundEffect::PACKET_ORDINAL,
        StopSound::PACKET_ORDINAL, TabHeaderFooter::PACKET_ORDINAL, TagQueryResponse::PACKET_ORDINAL, PickupItem::PACKET_ORDINAL,
        EntityTeleport::PACKET_ORDINAL, Advancements::PACKET_ORDINAL, EntityProperties::PACKET_ORDINAL, EntityEffect::PACKET_ORDINAL,
        Recipes::PACKET_ORDINAL, Tags::PACKET_ORDINAL}));

    clientbound->RegisterVersion(&MinecraftProtocolVersion::MINECRAFT_1_18,
      new VersionRegistry({SpawnEntity::PACKET_ORDINAL, SpawnExperienceOrb::PACKET_ORDINAL, SpawnEntity::PACKET_ORDINAL, SpawnPainting::PACKET_ORDINAL,
        SpawnPlayer::PACKET_ORDINAL, SkulkVibration::PACKET_ORDINAL, EntityAnimation::PACKET_ORDINAL, AwardStatistics::PACKET_ORDINAL,
        AcknowledgePlayerDigging::PACKET_ORDINAL, BlockDestroyStage::PACKET_ORDINAL, BlockEntityData::PACKET_ORDINAL, BlockAction::PACKET_ORDINAL,
        BlockUpdate::PACKET_ORDINAL, BossBar::PACKET_ORDINAL, ServerChangeDifficulty::PACKET_ORDINAL, LegacyChat::PACKET_ORDINAL,
        ClearTitle::PACKET_ORDINAL, CommandSuggestionResponse::PACKET_ORDINAL, DeclareCommands::PACKET_ORDINAL, CloseInventory::PACKET_ORDINAL,
        InventoryContent::PACKET_ORDINAL, InventoryProperty::PACKET_ORDINAL, InventorySlot::PACKET_ORDINAL, Cooldown::PACKET_ORDINAL,
        PluginMessage::PACKET_ORDINAL, CustomSoundEffect::PACKET_ORDINAL, Disconnect::PACKET_ORDINAL, EntityAnimation::PACKET_ORDINAL,
        Explosion::PACKET_ORDINAL, UnloadChunk::PACKET_ORDINAL, GameEvent::PACKET_ORDINAL, OpenHorseInventory::PACKET_ORDINAL,
        InitializeWorldBorder::PACKET_ORDINAL, KeepAlive::PACKET_ORDINAL, ChunkData::PACKET_ORDINAL, WorldEvent::PACKET_ORDINAL, Particle::PACKET_ORDINAL,
        ChunkLight::PACKET_ORDINAL, JoinGame::PACKET_ORDINAL, MapData::PACKET_ORDINAL, TradeList::PACKET_ORDINAL, EntityPosition::PACKET_ORDINAL,
        EntityPositionAndRotation::PACKET_ORDINAL, EntityRotation::PACKET_ORDINAL, MoveVehicle::PACKET_ORDINAL, OpenBook::PACKET_ORDINAL,
        OpenInventory::PACKET_ORDINAL, OpenSignEditor::PACKET_ORDINAL, Ping::PACKET_ORDINAL, CraftRecipeResponse::PACKET_ORDINAL,
        ServerPlayerAbilities::PACKET_ORDINAL, EndCombatEvent::PACKET_ORDINAL, EnterCombatEvent::PACKET_ORDINAL, DeathCombatEvent::PACKET_ORDINAL,
        PlayerListItem::PACKET_ORDINAL, PlayerFace::PACKET_ORDINAL, PositionRotation::PACKET_ORDINAL, UnlockRecipes::PACKET_ORDINAL,
        EntityRemove::PACKET_ORDINAL, EntityEffectRemove::PACKET_ORDINAL, ResourcePackRequest::PACKET_ORDINAL, Respawn::PACKET_ORDINAL,
        EntityLookAt::PACKET_ORDINAL, SectionBlocks::PACKET_ORDINAL, SelectAdvancementsTab::PACKET_ORDINAL, ActionBar::PACKET_ORDINAL,
        BorderCenter::PACKET_ORDINAL, BorderRadiusSpeed::PACKET_ORDINAL, BorderRadius::PACKET_ORDINAL, BorderWarningTime::PACKET_ORDINAL,
        BorderWarningRadius::PACKET_ORDINAL, Camera::PACKET_ORDINAL, HeldSlot::PACKET_ORDINAL, ViewPosition::PACKET_ORDINAL, ViewDistance::PACKET_ORDINAL,
        DefaultSpawnPosition::PACKET_ORDINAL, DisplayObjective::PACKET_ORDINAL, EntityMetadata::PACKET_ORDINAL, LeadEntities::PACKET_ORDINAL,
        EntityVelocity::PACKET_ORDINAL, EntityEquipment::PACKET_ORDINAL, Experience::PACKET_ORDINAL, Health::PACKET_ORDINAL, Objectives::PACKET_ORDINAL,
        Passengers::PACKET_ORDINAL, Teams::PACKET_ORDINAL, Score::PACKET_ORDINAL, SimulationDistance::PACKET_ORDINAL, Subtitle::PACKET_ORDINAL,
        WorldTime::PACKET_ORDINAL, Title::PACKET_ORDINAL, TitleTimes::PACKET_ORDINAL, EntitySoundEffect::PACKET_ORDINAL,
        HardcodedSoundEffect::PACKET_ORDINAL, StopSound::PACKET_ORDINAL, TabHeaderFooter::PACKET_ORDINAL, TagQueryResponse::PACKET_ORDINAL,
        PickupItem::PACKET_ORDINAL, EntityTeleport::PACKET_ORDINAL, Advancements::PACKET_ORDINAL, EntityProperties::PACKET_ORDINAL,
        EntityEffect::PACKET_ORDINAL, Recipes::PACKET_ORDINAL, Tags::PACKET_ORDINAL}));

    clientbound->RegisterVersion(&MinecraftProtocolVersion::MINECRAFT_1_19,
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

    clientbound->RegisterVersion(&MinecraftProtocolVersion::MINECRAFT_1_19_1,
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
        SetDisplayChatPreview::PACKET_ORDINAL, DisplayObjective::PACKET_ORDINAL, EntityMetadata::PACKET_ORDINAL, LeadEntities::PACKET_ORDINAL,
        EntityVelocity::PACKET_ORDINAL, EntityEquipment::PACKET_ORDINAL, Experience::PACKET_ORDINAL, Health::PACKET_ORDINAL, Objectives::PACKET_ORDINAL,
        Passengers::PACKET_ORDINAL, Teams::PACKET_ORDINAL, Score::PACKET_ORDINAL, SimulationDistance::PACKET_ORDINAL, Subtitle::PACKET_ORDINAL,
        WorldTime::PACKET_ORDINAL, Title::PACKET_ORDINAL, TitleTimes::PACKET_ORDINAL, EntitySoundEffect::PACKET_ORDINAL,
        HardcodedSoundEffect::PACKET_ORDINAL, StopSound::PACKET_ORDINAL, SystemChat::PACKET_ORDINAL, TabHeaderFooter::PACKET_ORDINAL,
        TagQueryResponse::PACKET_ORDINAL, PickupItem::PACKET_ORDINAL, EntityTeleport::PACKET_ORDINAL, Advancements::PACKET_ORDINAL,
        EntityProperties::PACKET_ORDINAL, EntityEffect::PACKET_ORDINAL, Recipes::PACKET_ORDINAL, Tags::PACKET_ORDINAL}));

    clientbound->RegisterVersion(&MinecraftProtocolVersion::MINECRAFT_1_19_3,
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
        PlayerRemove::PACKET_ORDINAL, PlayerListItem::PACKET_ORDINAL, PlayerFace::PACKET_ORDINAL, PositionRotation::PACKET_ORDINAL,
        UnlockRecipes::PACKET_ORDINAL, EntityRemove::PACKET_ORDINAL, EntityEffectRemove::PACKET_ORDINAL, ResourcePackRequest::PACKET_ORDINAL,
        Respawn::PACKET_ORDINAL, EntityLookAt::PACKET_ORDINAL, SectionBlocks::PACKET_ORDINAL, SelectAdvancementsTab::PACKET_ORDINAL,
        ServerData::PACKET_ORDINAL, ActionBar::PACKET_ORDINAL, BorderCenter::PACKET_ORDINAL, BorderRadiusSpeed::PACKET_ORDINAL,
        BorderRadius::PACKET_ORDINAL, BorderWarningTime::PACKET_ORDINAL, BorderWarningRadius::PACKET_ORDINAL, Camera::PACKET_ORDINAL,
        HeldSlot::PACKET_ORDINAL, ViewPosition::PACKET_ORDINAL, ViewDistance::PACKET_ORDINAL, DefaultSpawnPosition::PACKET_ORDINAL,
        DisplayObjective::PACKET_ORDINAL, EntityMetadata::PACKET_ORDINAL, LeadEntities::PACKET_ORDINAL, EntityVelocity::PACKET_ORDINAL,
        EntityEquipment::PACKET_ORDINAL, Experience::PACKET_ORDINAL, Health::PACKET_ORDINAL, Objectives::PACKET_ORDINAL, Passengers::PACKET_ORDINAL,
        Teams::PACKET_ORDINAL, Score::PACKET_ORDINAL, SimulationDistance::PACKET_ORDINAL, Subtitle::PACKET_ORDINAL, WorldTime::PACKET_ORDINAL,
        Title::PACKET_ORDINAL, TitleTimes::PACKET_ORDINAL, EntitySoundEffect::PACKET_ORDINAL, HardcodedSoundEffect::PACKET_ORDINAL,
        StopSound::PACKET_ORDINAL, SystemChat::PACKET_ORDINAL, TabHeaderFooter::PACKET_ORDINAL, TagQueryResponse::PACKET_ORDINAL,
        PickupItem::PACKET_ORDINAL, EntityTeleport::PACKET_ORDINAL, Advancements::PACKET_ORDINAL, EntityProperties::PACKET_ORDINAL,
        FeatureFlags::PACKET_ORDINAL, EntityEffect::PACKET_ORDINAL, Recipes::PACKET_ORDINAL, Tags::PACKET_ORDINAL}));

    auto* serverbound = new DirectionRegistry();
    serverbound->RegisterVersion(&MinecraftProtocolVersion::MINECRAFT_1_12_2,
      new VersionRegistry(
        {ConfirmTeleport::PACKET_ORDINAL, CommandSuggestionRequest::PACKET_ORDINAL, LegacyChat::PACKET_ORDINAL, ClientAction::PACKET_ORDINAL,
          ClientSettings::PACKET_ORDINAL, ConfirmTransaction::PACKET_ORDINAL, LegacyEnchant::PACKET_ORDINAL, ClickSlot::PACKET_ORDINAL,
          CloseInventory::PACKET_ORDINAL, PluginMessage::PACKET_ORDINAL, EntityInteract::PACKET_ORDINAL, KeepAlive::PACKET_ORDINAL,
          MoveGroundOnly::PACKET_ORDINAL, MovePositionOnly::PACKET_ORDINAL, Move::PACKET_ORDINAL, MoveRotationOnly::PACKET_ORDINAL,
          MoveVehicle::PACKET_ORDINAL, BoatPaddle::PACKET_ORDINAL, CraftRecipeRequest::PACKET_ORDINAL, ClientPlayerAbilities::PACKET_ORDINAL,
          Digging::PACKET_ORDINAL, EntityAction::PACKET_ORDINAL, PlayerInput::PACKET_ORDINAL, LegacyRecipeBook::PACKET_ORDINAL,
          ResourcePackResponse::PACKET_ORDINAL, SelectAdvancementsTab::PACKET_ORDINAL, HeldSlot::PACKET_ORDINAL, EditSign::PACKET_ORDINAL,
          SwingArm::PACKET_ORDINAL, Spectate::PACKET_ORDINAL, Camera::PACKET_ORDINAL, PlaceBlock::PACKET_ORDINAL, UseItem::PACKET_ORDINAL}));

    serverbound->RegisterVersion(&MinecraftProtocolVersion::MINECRAFT_1_13,
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

    serverbound->RegisterVersion(&MinecraftProtocolVersion::MINECRAFT_1_14,
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

    serverbound->RegisterVersion(&MinecraftProtocolVersion::MINECRAFT_1_16_2,
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

    serverbound->RegisterVersion(&MinecraftProtocolVersion::MINECRAFT_1_17,
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

    serverbound->RegisterVersion(&MinecraftProtocolVersion::MINECRAFT_1_18,
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

    serverbound->RegisterVersion(&MinecraftProtocolVersion::MINECRAFT_1_19,
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

    serverbound->RegisterVersion(&MinecraftProtocolVersion::MINECRAFT_1_19_1,
      new VersionRegistry({ConfirmTeleport::PACKET_ORDINAL, BlockTagQueryRequest::PACKET_ORDINAL, ClientChangeDifficulty::PACKET_ORDINAL,
        MessageAcknowledgment::PACKET_ORDINAL, Command::PACKET_ORDINAL, ClientPlayerChat::PACKET_ORDINAL, ClientChatPreview::PACKET_ORDINAL,
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

    serverbound->RegisterVersion(&MinecraftProtocolVersion::MINECRAFT_1_19_3,
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