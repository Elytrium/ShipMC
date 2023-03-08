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

    clientbound->RegisterVersion(&ProtocolVersion::MINECRAFT_1_18,
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
        SetDisplayChatPreview::PACKET_ORDINAL, DisplayObjective::PACKET_ORDINAL, EntityMetadata::PACKET_ORDINAL, LeadEntities::PACKET_ORDINAL,
        EntityVelocity::PACKET_ORDINAL, EntityEquipment::PACKET_ORDINAL, Experience::PACKET_ORDINAL, Health::PACKET_ORDINAL, Objectives::PACKET_ORDINAL,
        Passengers::PACKET_ORDINAL, Teams::PACKET_ORDINAL, Score::PACKET_ORDINAL, SimulationDistance::PACKET_ORDINAL, Subtitle::PACKET_ORDINAL,
        WorldTime::PACKET_ORDINAL, Title::PACKET_ORDINAL, TitleTimes::PACKET_ORDINAL, EntitySoundEffect::PACKET_ORDINAL,
        HardcodedSoundEffect::PACKET_ORDINAL, StopSound::PACKET_ORDINAL, SystemChat::PACKET_ORDINAL, TabHeaderFooter::PACKET_ORDINAL,
        TagQueryResponse::PACKET_ORDINAL, PickupItem::PACKET_ORDINAL, EntityTeleport::PACKET_ORDINAL, Advancements::PACKET_ORDINAL,
        EntityProperties::PACKET_ORDINAL, EntityEffect::PACKET_ORDINAL, Recipes::PACKET_ORDINAL, Tags::PACKET_ORDINAL}));

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
    serverbound->RegisterVersion(&ProtocolVersion::MINECRAFT_1_12_2,
      new VersionRegistry(
        {ConfirmTeleport::PACKET_ORDINAL, CommandSuggestionRequest::PACKET_ORDINAL, LegacyChat::PACKET_ORDINAL, ClientAction::PACKET_ORDINAL,
          ClientSettings::PACKET_ORDINAL, ConfirmTransaction::PACKET_ORDINAL, LegacyEnchant::PACKET_ORDINAL, ClickSlot::PACKET_ORDINAL,
          CloseInventory::PACKET_ORDINAL, PluginMessage::PACKET_ORDINAL, EntityInteract::PACKET_ORDINAL, KeepAlive::PACKET_ORDINAL,
          MoveGroundOnly::PACKET_ORDINAL, MovePositionOnly::PACKET_ORDINAL, Move::PACKET_ORDINAL, MoveRotationOnly::PACKET_ORDINAL,
          MoveVehicle::PACKET_ORDINAL, BoatPaddle::PACKET_ORDINAL, CraftRecipeRequest::PACKET_ORDINAL, ClientPlayerAbilities::PACKET_ORDINAL,
          Digging::PACKET_ORDINAL, EntityAction::PACKET_ORDINAL, PlayerInput::PACKET_ORDINAL, LegacyRecipeBook::PACKET_ORDINAL,
          ResourcePackResponse::PACKET_ORDINAL, SelectAdvancementsTab::PACKET_ORDINAL, HeldSlot::PACKET_ORDINAL, EditSign::PACKET_ORDINAL,
          SwingArm::PACKET_ORDINAL, Spectate::PACKET_ORDINAL, Camera::PACKET_ORDINAL, PlaceBlock::PACKET_ORDINAL, UseItem::PACKET_ORDINAL}));

    serverbound->RegisterVersion(&ProtocolVersion::MINECRAFT_1_13,
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

    serverbound->RegisterVersion(&ProtocolVersion::MINECRAFT_1_14,
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

    serverbound->RegisterVersion(&ProtocolVersion::MINECRAFT_1_16_2,
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

    serverbound->RegisterVersion(&ProtocolVersion::MINECRAFT_1_17,
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

    serverbound->RegisterVersion(&ProtocolVersion::MINECRAFT_1_18,
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

    serverbound->RegisterVersion(&ProtocolVersion::MINECRAFT_1_19,
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

    serverbound->RegisterVersion(&ProtocolVersion::MINECRAFT_1_19_1,
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

    serverbound->RegisterVersion(&ProtocolVersion::MINECRAFT_1_19_3,
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