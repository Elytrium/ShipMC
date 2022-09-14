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
#include "../packets/play/ChunkData.hpp"
#include "../packets/play/ChunkLight.hpp"
#include "../packets/play/ClearTitle.hpp"
#include "../packets/play/ClickInventoryButton.hpp"
#include "../packets/play/ClickSlot.hpp"
#include "../packets/play/ClientAction.hpp"
#include "../packets/play/ClientChangeDifficulty.hpp"
#include "../packets/play/ClientSettings.hpp"
#include "../packets/play/CloseInventory.hpp"
#include "../packets/play/CombatEvent.hpp"
#include "../packets/play/CommandSuggestionRequest.hpp"
#include "../packets/play/CommandSuggestionResponse.hpp"
#include "../packets/play/ConfirmTeleport.hpp"
#include "../packets/play/ConfirmTransaction.hpp"
#include "../packets/play/Cooldown.hpp"
#include "../packets/play/CraftRecipeRequest.hpp"
#include "../packets/play/CraftRecipeResponse.hpp"
#include "../packets/play/CreativeSlot.hpp"
#include "../packets/play/CustomSoundEffect.hpp"
#include "../packets/play/DeclareCommands.hpp"
#include "../packets/play/DefaultSpawnPosition.hpp"
#include "../packets/play/Digging.hpp"
#include "../packets/play/Disconnect.hpp"
#include "../packets/play/DisplayObjective.hpp"
#include "../packets/play/EditBook.hpp"
#include "../packets/play/EditSign.hpp"
#include "../packets/play/EntityAction.hpp"
#include "../packets/play/EntityAnimation.hpp"
#include "../packets/play/EntityEffect.hpp"
#include "../packets/play/EntityEffectRemove.hpp"
#include "../packets/play/EntityEquipment.hpp"
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
#include "../packets/play/GameEvent.hpp"
#include "../packets/play/GenerateStructure.hpp"
#include "../packets/play/HardcodedSoundEffect.hpp"
#include "../packets/play/Health.hpp"
#include "../packets/play/HeldSlot.hpp"
#include "../packets/play/InventoryContent.hpp"
#include "../packets/play/InventoryProperty.hpp"
#include "../packets/play/InventorySlot.hpp"
#include "../packets/play/JoinGame.hpp"
#include "../packets/play/KeepAlive.hpp"
#include "../packets/play/LeadEntities.hpp"
#include "../packets/play/LegacyChat.hpp"
#include "../packets/play/LegacyEnchant.hpp"
#include "../packets/play/LegacyRecipeBook.hpp"
#include "../packets/play/LegacyTitle.hpp"
#include "../packets/play/LegacyWorldBorder.hpp"
#include "../packets/play/LockDifficulty.hpp"
#include "../packets/play/MapData.hpp"
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
#include "../packets/play/PlayerAbilities.hpp"
#include "../packets/play/PlayerFace.hpp"
#include "../packets/play/PlayerInput.hpp"
#include "../packets/play/PlayerListItem.hpp"
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
#include "../packets/play/SectionBlocks.hpp"
#include "../packets/play/SeenRecipe.hpp"
#include "../packets/play/SelectAdvancementsTab.hpp"
#include "../packets/play/SelectTrade.hpp"
#include "../packets/play/ServerChangeDifficulty.hpp"
#include "../packets/play/SpawnEntity.hpp"
#include "../packets/play/SpawnExperienceOrb.hpp"
#include "../packets/play/SpawnPainting.hpp"
#include "../packets/play/SpawnPlayer.hpp"
#include "../packets/play/SpawnThunderbolt.hpp"
#include "../packets/play/Spectate.hpp"
#include "../packets/play/StopSound.hpp"
#include "../packets/play/Subtitle.hpp"
#include "../packets/play/SwingArm.hpp"
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
#include "../packets/play/WorldTime.hpp"
#include "../packets/status/StatusPing.hpp"
#include "../packets/status/StatusRequest.hpp"
#include "../packets/status/StatusResponse.hpp"

namespace Ship {

  PacketRegistry GetHandshakeRegistry() {
    VersionRegistry* serverboundRegistry = DirectionRegistry::NewVersionRegistry();

    for (uint32_t i = ProtocolVersion::MINIMUM_VERSION.GetPacketIDOrdinal(); i <= ProtocolVersion::MAXIMUM_VERSION.GetPacketIDOrdinal(); ++i) {
      serverboundRegistry[i].RegisterPacket(Handshake::PACKET_ORDINAL, 0x00);
    }

    return {DirectionRegistry(nullptr), DirectionRegistry(serverboundRegistry)};
  }

  PacketRegistry GetStatusRegistry() {
    VersionRegistry* clientboundRegistry = DirectionRegistry::NewVersionRegistry();

    for (uint32_t i = ProtocolVersion::MINIMUM_VERSION.GetPacketIDOrdinal(); i <= ProtocolVersion::MAXIMUM_VERSION.GetPacketIDOrdinal(); ++i) {
      clientboundRegistry[i].RegisterPacket(StatusResponse::PACKET_ORDINAL, 0x00);
      clientboundRegistry[i].RegisterPacket(StatusPing::PACKET_ORDINAL, 0x01);
    }

    VersionRegistry* serverboundRegistry = DirectionRegistry::NewVersionRegistry();

    for (uint32_t i = ProtocolVersion::MINIMUM_VERSION.GetPacketIDOrdinal(); i <= ProtocolVersion::MAXIMUM_VERSION.GetPacketIDOrdinal(); ++i) {
      serverboundRegistry[i].RegisterPacket(StatusRequest::PACKET_ORDINAL, 0x00);
      serverboundRegistry[i].RegisterPacket(StatusPing::PACKET_ORDINAL, 0x01);
    }

    return {DirectionRegistry(clientboundRegistry), DirectionRegistry(serverboundRegistry)};
  }

  PacketRegistry GetLoginRegistry() {
    VersionRegistry* clientboundRegistry = DirectionRegistry::NewVersionRegistry();

    for (uint32_t i = ProtocolVersion::MINIMUM_VERSION.GetPacketIDOrdinal(); i <= ProtocolVersion::MAXIMUM_VERSION.GetPacketIDOrdinal(); ++i) {
      clientboundRegistry[i].RegisterPacket(Disconnect::PACKET_ORDINAL, 0x00);
      clientboundRegistry[i].RegisterPacket(EncryptionRequest::PACKET_ORDINAL, 0x01);
      clientboundRegistry[i].RegisterPacket(LoginSuccess::PACKET_ORDINAL, 0x02);
      clientboundRegistry[i].RegisterPacket(SetCompression::PACKET_ORDINAL, 0x03);
      clientboundRegistry[i].RegisterPacket(LoginPluginMessage::PACKET_ORDINAL, 0x04);
    }

    VersionRegistry* serverboundRegistry = DirectionRegistry::NewVersionRegistry();

    for (uint32_t i = ProtocolVersion::MINIMUM_VERSION.GetPacketIDOrdinal(); i <= ProtocolVersion::MAXIMUM_VERSION.GetPacketIDOrdinal(); ++i) {
      serverboundRegistry[i].RegisterPacket(LoginStart::PACKET_ORDINAL, 0x00);
      serverboundRegistry[i].RegisterPacket(EncryptionResponse::PACKET_ORDINAL, 0x01);
      serverboundRegistry[i].RegisterPacket(LoginPluginResponse::PACKET_ORDINAL, 0x02);
    }

    return {DirectionRegistry(clientboundRegistry), DirectionRegistry(serverboundRegistry)};
  }

  PacketRegistry GetPlayRegistry() {
    VersionRegistry* clientboundRegistry = DirectionRegistry::NewVersionRegistry();

    VersionRegistry* clientbound1_12_2 = clientboundRegistry + ProtocolVersion::MINECRAFT_1_12_2.GetPacketIDOrdinal();
    clientbound1_12_2->RegisterPacket(SpawnEntity::PACKET_ORDINAL, 0x00);
    clientbound1_12_2->RegisterPacket(SpawnExperienceOrb::PACKET_ORDINAL, 0x01);
    clientbound1_12_2->RegisterPacket(SpawnThunderbolt::PACKET_ORDINAL, 0x02);
    clientbound1_12_2->RegisterPacket(SpawnEntity::PACKET_ORDINAL, 0x03);
    clientbound1_12_2->RegisterPacket(SpawnPainting::PACKET_ORDINAL, 0x04);
    clientbound1_12_2->RegisterPacket(SpawnPlayer::PACKET_ORDINAL, 0x05);
    clientbound1_12_2->RegisterPacket(EntityAnimation::PACKET_ORDINAL, 0x06);
    clientbound1_12_2->RegisterPacket(AwardStatistics::PACKET_ORDINAL, 0x07);
    clientbound1_12_2->RegisterPacket(BlockDestroyStage::PACKET_ORDINAL, 0x08);
    clientbound1_12_2->RegisterPacket(BlockEntityData::PACKET_ORDINAL, 0x09);
    clientbound1_12_2->RegisterPacket(BlockAction::PACKET_ORDINAL, 0x0A);
    clientbound1_12_2->RegisterPacket(BlockUpdate::PACKET_ORDINAL, 0x0B);
    clientbound1_12_2->RegisterPacket(BossBar::PACKET_ORDINAL, 0x0C);
    clientbound1_12_2->RegisterPacket(ServerChangeDifficulty::PACKET_ORDINAL, 0x0D);
    clientbound1_12_2->RegisterPacket(CommandSuggestionResponse::PACKET_ORDINAL, 0x0E);
    clientbound1_12_2->RegisterPacket(LegacyChat::PACKET_ORDINAL, 0x0F);
    clientbound1_12_2->RegisterPacket(SectionBlocks::PACKET_ORDINAL, 0x10);
    clientbound1_12_2->RegisterPacket(ConfirmTransaction::PACKET_ORDINAL, 0x11);
    clientbound1_12_2->RegisterPacket(CloseInventory::PACKET_ORDINAL, 0x12);
    clientbound1_12_2->RegisterPacket(OpenInventory::PACKET_ORDINAL, 0x13);
    clientbound1_12_2->RegisterPacket(InventoryContent::PACKET_ORDINAL, 0x14);
    clientbound1_12_2->RegisterPacket(InventoryProperty::PACKET_ORDINAL, 0x15);
    clientbound1_12_2->RegisterPacket(InventorySlot::PACKET_ORDINAL, 0x16);
    clientbound1_12_2->RegisterPacket(Cooldown::PACKET_ORDINAL, 0x17);
    clientbound1_12_2->RegisterPacket(PluginMessage::PACKET_ORDINAL, 0x18);
    clientbound1_12_2->RegisterPacket(CustomSoundEffect::PACKET_ORDINAL, 0x19);
    clientbound1_12_2->RegisterPacket(Disconnect::PACKET_ORDINAL, 0x1A);
    clientbound1_12_2->RegisterPacket(EntityAnimation::PACKET_ORDINAL, 0x1B);
    clientbound1_12_2->RegisterPacket(Explosion::PACKET_ORDINAL, 0x1C);
    clientbound1_12_2->RegisterPacket(UnloadChunk::PACKET_ORDINAL, 0x1D);
    clientbound1_12_2->RegisterPacket(GameEvent::PACKET_ORDINAL, 0x1E);
    clientbound1_12_2->RegisterPacket(KeepAlive::PACKET_ORDINAL, 0x1F);
    clientbound1_12_2->RegisterPacket(ChunkData::PACKET_ORDINAL, 0x20);
    clientbound1_12_2->RegisterPacket(EntitySoundEffect::PACKET_ORDINAL, 0x21);
    clientbound1_12_2->RegisterPacket(Particle::PACKET_ORDINAL, 0x22);
    clientbound1_12_2->RegisterPacket(JoinGame::PACKET_ORDINAL, 0x23);
    clientbound1_12_2->RegisterPacket(MapData::PACKET_ORDINAL, 0x24);
    clientbound1_12_2->RegisterPacket(EntityNotMoved::PACKET_ORDINAL, 0x25);
    clientbound1_12_2->RegisterPacket(EntityPosition::PACKET_ORDINAL, 0x26);
    clientbound1_12_2->RegisterPacket(EntityPositionAndRotation::PACKET_ORDINAL, 0x27);
    clientbound1_12_2->RegisterPacket(EntityRotation::PACKET_ORDINAL, 0x28);
    clientbound1_12_2->RegisterPacket(MoveVehicle::PACKET_ORDINAL, 0x29);
    clientbound1_12_2->RegisterPacket(OpenSignEditor::PACKET_ORDINAL, 0x2A);
    clientbound1_12_2->RegisterPacket(CraftRecipeResponse::PACKET_ORDINAL, 0x2B);
    clientbound1_12_2->RegisterPacket(PlayerAbilities::PACKET_ORDINAL, 0x2C);
    clientbound1_12_2->RegisterPacket(CombatEvent::PACKET_ORDINAL, 0x2D);
    clientbound1_12_2->RegisterPacket(PlayerListItem::PACKET_ORDINAL, 0x2E);
    clientbound1_12_2->RegisterPacket(PositionRotation::PACKET_ORDINAL, 0x2F);
    clientbound1_12_2->RegisterPacket(UseBed::PACKET_ORDINAL, 0x30);
    clientbound1_12_2->RegisterPacket(UnlockRecipes::PACKET_ORDINAL, 0x31);
    clientbound1_12_2->RegisterPacket(EntityRemove::PACKET_ORDINAL, 0x32);
    clientbound1_12_2->RegisterPacket(EntityEffectRemove::PACKET_ORDINAL, 0x33);
    clientbound1_12_2->RegisterPacket(ResourcePackRequest::PACKET_ORDINAL, 0x34);
    clientbound1_12_2->RegisterPacket(Respawn::PACKET_ORDINAL, 0x35);
    clientbound1_12_2->RegisterPacket(EntityLookAt::PACKET_ORDINAL, 0x36);
    clientbound1_12_2->RegisterPacket(SelectAdvancementsTab::PACKET_ORDINAL, 0x37);
    clientbound1_12_2->RegisterPacket(LegacyWorldBorder::PACKET_ORDINAL, 0x38);
    clientbound1_12_2->RegisterPacket(Camera::PACKET_ORDINAL, 0x39);
    clientbound1_12_2->RegisterPacket(HeldSlot::PACKET_ORDINAL, 0x3A);
    clientbound1_12_2->RegisterPacket(DisplayObjective::PACKET_ORDINAL, 0x3B);
    clientbound1_12_2->RegisterPacket(EntityMetadata::PACKET_ORDINAL, 0x3C);
    clientbound1_12_2->RegisterPacket(LeadEntities::PACKET_ORDINAL, 0x3D);
    clientbound1_12_2->RegisterPacket(EntityVelocity::PACKET_ORDINAL, 0x3E);
    clientbound1_12_2->RegisterPacket(EntityEquipment::PACKET_ORDINAL, 0x3F);
    clientbound1_12_2->RegisterPacket(Experience::PACKET_ORDINAL, 0x40);
    clientbound1_12_2->RegisterPacket(Health::PACKET_ORDINAL, 0x41);
    clientbound1_12_2->RegisterPacket(Objectives::PACKET_ORDINAL, 0x42);
    clientbound1_12_2->RegisterPacket(Passengers::PACKET_ORDINAL, 0x43);
    clientbound1_12_2->RegisterPacket(Teams::PACKET_ORDINAL, 0x44);
    clientbound1_12_2->RegisterPacket(Score::PACKET_ORDINAL, 0x45);
    clientbound1_12_2->RegisterPacket(DefaultSpawnPosition::PACKET_ORDINAL, 0x46);
    clientbound1_12_2->RegisterPacket(WorldTime::PACKET_ORDINAL, 0x47);
    clientbound1_12_2->RegisterPacket(LegacyTitle::PACKET_ORDINAL, 0x48);
    clientbound1_12_2->RegisterPacket(HardcodedSoundEffect::PACKET_ORDINAL, 0x49);
    clientbound1_12_2->RegisterPacket(TabHeaderFooter::PACKET_ORDINAL, 0x4A);
    clientbound1_12_2->RegisterPacket(PickupItem::PACKET_ORDINAL, 0x4B);
    clientbound1_12_2->RegisterPacket(EntityTeleport::PACKET_ORDINAL, 0x4C);
    clientbound1_12_2->RegisterPacket(Advancements::PACKET_ORDINAL, 0x4D);
    clientbound1_12_2->RegisterPacket(EntityProperties::PACKET_ORDINAL, 0x4E);
    clientbound1_12_2->RegisterPacket(EntityEffect::PACKET_ORDINAL, 0x4F);

    VersionRegistry* clientbound1_13 = clientboundRegistry + ProtocolVersion::MINECRAFT_1_13.GetPacketIDOrdinal();
    clientbound1_13->RegisterPacket(SpawnEntity::PACKET_ORDINAL, 0x00);
    clientbound1_13->RegisterPacket(SpawnExperienceOrb::PACKET_ORDINAL, 0x01);
    clientbound1_13->RegisterPacket(SpawnThunderbolt::PACKET_ORDINAL, 0x02);
    clientbound1_13->RegisterPacket(SpawnEntity::PACKET_ORDINAL, 0x03);
    clientbound1_13->RegisterPacket(SpawnPainting::PACKET_ORDINAL, 0x04);
    clientbound1_13->RegisterPacket(SpawnPlayer::PACKET_ORDINAL, 0x05);
    clientbound1_13->RegisterPacket(EntityAnimation::PACKET_ORDINAL, 0x06);
    clientbound1_13->RegisterPacket(AwardStatistics::PACKET_ORDINAL, 0x07);
    clientbound1_13->RegisterPacket(BlockDestroyStage::PACKET_ORDINAL, 0x08);
    clientbound1_13->RegisterPacket(BlockEntityData::PACKET_ORDINAL, 0x09);
    clientbound1_13->RegisterPacket(BlockAction::PACKET_ORDINAL, 0x0A);
    clientbound1_13->RegisterPacket(BlockUpdate::PACKET_ORDINAL, 0x0B);
    clientbound1_13->RegisterPacket(BossBar::PACKET_ORDINAL, 0x0C);
    clientbound1_13->RegisterPacket(ServerChangeDifficulty::PACKET_ORDINAL, 0x0D);
    clientbound1_13->RegisterPacket(LegacyChat::PACKET_ORDINAL, 0x0E);
    clientbound1_13->RegisterPacket(SectionBlocks::PACKET_ORDINAL, 0x0F);
    clientbound1_13->RegisterPacket(CommandSuggestionResponse::PACKET_ORDINAL, 0x10);
    clientbound1_13->RegisterPacket(DeclareCommands::PACKET_ORDINAL, 0x11);
    clientbound1_13->RegisterPacket(ConfirmTransaction::PACKET_ORDINAL, 0x12);
    clientbound1_13->RegisterPacket(CloseInventory::PACKET_ORDINAL, 0x13);
    clientbound1_13->RegisterPacket(OpenInventory::PACKET_ORDINAL, 0x14);
    clientbound1_13->RegisterPacket(InventoryContent::PACKET_ORDINAL, 0x15);
    clientbound1_13->RegisterPacket(InventoryProperty::PACKET_ORDINAL, 0x16);
    clientbound1_13->RegisterPacket(InventorySlot::PACKET_ORDINAL, 0x17);
    clientbound1_13->RegisterPacket(Cooldown::PACKET_ORDINAL, 0x18);
    clientbound1_13->RegisterPacket(PluginMessage::PACKET_ORDINAL, 0x19);
    clientbound1_13->RegisterPacket(CustomSoundEffect::PACKET_ORDINAL, 0x1A);
    clientbound1_13->RegisterPacket(Disconnect::PACKET_ORDINAL, 0x1B);
    clientbound1_13->RegisterPacket(EntityAnimation::PACKET_ORDINAL, 0x1C);
    clientbound1_13->RegisterPacket(TagQueryResponse::PACKET_ORDINAL, 0x1D);
    clientbound1_13->RegisterPacket(Explosion::PACKET_ORDINAL, 0x1E);
    clientbound1_13->RegisterPacket(UnloadChunk::PACKET_ORDINAL, 0x1F);
    clientbound1_13->RegisterPacket(GameEvent::PACKET_ORDINAL, 0x20);
    clientbound1_13->RegisterPacket(KeepAlive::PACKET_ORDINAL, 0x21);
    clientbound1_13->RegisterPacket(ChunkData::PACKET_ORDINAL, 0x22);
    clientbound1_13->RegisterPacket(EntitySoundEffect::PACKET_ORDINAL, 0x23);
    clientbound1_13->RegisterPacket(Particle::PACKET_ORDINAL, 0x24);
    clientbound1_13->RegisterPacket(JoinGame::PACKET_ORDINAL, 0x25);
    clientbound1_13->RegisterPacket(MapData::PACKET_ORDINAL, 0x26);
    clientbound1_13->RegisterPacket(EntityNotMoved::PACKET_ORDINAL, 0x27);
    clientbound1_13->RegisterPacket(EntityPosition::PACKET_ORDINAL, 0x28);
    clientbound1_13->RegisterPacket(EntityPositionAndRotation::PACKET_ORDINAL, 0x29);
    clientbound1_13->RegisterPacket(EntityRotation::PACKET_ORDINAL, 0x2A);
    clientbound1_13->RegisterPacket(MoveVehicle::PACKET_ORDINAL, 0x2B);
    clientbound1_13->RegisterPacket(OpenSignEditor::PACKET_ORDINAL, 0x2C);
    clientbound1_13->RegisterPacket(CraftRecipeResponse::PACKET_ORDINAL, 0x2D);
    clientbound1_13->RegisterPacket(PlayerAbilities::PACKET_ORDINAL, 0x2E);
    clientbound1_13->RegisterPacket(CombatEvent::PACKET_ORDINAL, 0x2F);
    clientbound1_13->RegisterPacket(PlayerListItem::PACKET_ORDINAL, 0x30);
    clientbound1_13->RegisterPacket(PlayerFace::PACKET_ORDINAL, 0x31);
    clientbound1_13->RegisterPacket(PositionRotation::PACKET_ORDINAL, 0x32);
    clientbound1_13->RegisterPacket(UseBed::PACKET_ORDINAL, 0x33);
    clientbound1_13->RegisterPacket(UnlockRecipes::PACKET_ORDINAL, 0x34);
    clientbound1_13->RegisterPacket(EntityRemove::PACKET_ORDINAL, 0x35);
    clientbound1_13->RegisterPacket(EntityEffectRemove::PACKET_ORDINAL, 0x36);
    clientbound1_13->RegisterPacket(ResourcePackRequest::PACKET_ORDINAL, 0x37);
    clientbound1_13->RegisterPacket(Respawn::PACKET_ORDINAL, 0x38);
    clientbound1_13->RegisterPacket(EntityLookAt::PACKET_ORDINAL, 0x39);
    clientbound1_13->RegisterPacket(SelectAdvancementsTab::PACKET_ORDINAL, 0x3A);
    clientbound1_13->RegisterPacket(LegacyWorldBorder::PACKET_ORDINAL, 0x3B);
    clientbound1_13->RegisterPacket(Camera::PACKET_ORDINAL, 0x3C);
    clientbound1_13->RegisterPacket(HeldSlot::PACKET_ORDINAL, 0x3D);
    clientbound1_13->RegisterPacket(DisplayObjective::PACKET_ORDINAL, 0x3E);
    clientbound1_13->RegisterPacket(EntityMetadata::PACKET_ORDINAL, 0x3F);
    clientbound1_13->RegisterPacket(LeadEntities::PACKET_ORDINAL, 0x40);
    clientbound1_13->RegisterPacket(EntityVelocity::PACKET_ORDINAL, 0x41);
    clientbound1_13->RegisterPacket(EntityEquipment::PACKET_ORDINAL, 0x42);
    clientbound1_13->RegisterPacket(Experience::PACKET_ORDINAL, 0x43);
    clientbound1_13->RegisterPacket(Health::PACKET_ORDINAL, 0x44);
    clientbound1_13->RegisterPacket(Objectives::PACKET_ORDINAL, 0x45);
    clientbound1_13->RegisterPacket(Passengers::PACKET_ORDINAL, 0x46);
    clientbound1_13->RegisterPacket(Teams::PACKET_ORDINAL, 0x47);
    clientbound1_13->RegisterPacket(Score::PACKET_ORDINAL, 0x48);
    clientbound1_13->RegisterPacket(DefaultSpawnPosition::PACKET_ORDINAL, 0x49);
    clientbound1_13->RegisterPacket(WorldTime::PACKET_ORDINAL, 0x4A);
    clientbound1_13->RegisterPacket(LegacyTitle::PACKET_ORDINAL, 0x4B);
    clientbound1_13->RegisterPacket(StopSound::PACKET_ORDINAL, 0x4C);
    clientbound1_13->RegisterPacket(HardcodedSoundEffect::PACKET_ORDINAL, 0x4D);
    clientbound1_13->RegisterPacket(TabHeaderFooter::PACKET_ORDINAL, 0x4E);
    clientbound1_13->RegisterPacket(PickupItem::PACKET_ORDINAL, 0x4F);
    clientbound1_13->RegisterPacket(EntityTeleport::PACKET_ORDINAL, 0x50);
    clientbound1_13->RegisterPacket(Advancements::PACKET_ORDINAL, 0x51);
    clientbound1_13->RegisterPacket(EntityProperties::PACKET_ORDINAL, 0x52);
    clientbound1_13->RegisterPacket(EntityEffect::PACKET_ORDINAL, 0x53);
    clientbound1_13->RegisterPacket(Recipes::PACKET_ORDINAL, 0x53);
    clientbound1_13->RegisterPacket(Tags::PACKET_ORDINAL, 0x53);

    VersionRegistry* clientbound1_14 = clientboundRegistry + ProtocolVersion::MINECRAFT_1_14.GetPacketIDOrdinal();
    clientbound1_14->RegisterPacket(SpawnEntity::PACKET_ORDINAL, 0x00);
    clientbound1_14->RegisterPacket(SpawnExperienceOrb::PACKET_ORDINAL, 0x01);
    clientbound1_14->RegisterPacket(SpawnThunderbolt::PACKET_ORDINAL, 0x02);
    clientbound1_14->RegisterPacket(SpawnEntity::PACKET_ORDINAL, 0x03);
    clientbound1_14->RegisterPacket(SpawnPainting::PACKET_ORDINAL, 0x04);
    clientbound1_14->RegisterPacket(SpawnPlayer::PACKET_ORDINAL, 0x05);
    clientbound1_14->RegisterPacket(EntityAnimation::PACKET_ORDINAL, 0x06);
    clientbound1_14->RegisterPacket(AwardStatistics::PACKET_ORDINAL, 0x07);
    clientbound1_14->RegisterPacket(BlockDestroyStage::PACKET_ORDINAL, 0x08);
    clientbound1_14->RegisterPacket(BlockEntityData::PACKET_ORDINAL, 0x09);
    clientbound1_14->RegisterPacket(BlockAction::PACKET_ORDINAL, 0x0A);
    clientbound1_14->RegisterPacket(BlockUpdate::PACKET_ORDINAL, 0x0B);
    clientbound1_14->RegisterPacket(BossBar::PACKET_ORDINAL, 0x0C);
    clientbound1_14->RegisterPacket(ServerChangeDifficulty::PACKET_ORDINAL, 0x0D);
    clientbound1_14->RegisterPacket(LegacyChat::PACKET_ORDINAL, 0x0E);
    clientbound1_14->RegisterPacket(SectionBlocks::PACKET_ORDINAL, 0x0F);
    clientbound1_14->RegisterPacket(CommandSuggestionResponse::PACKET_ORDINAL, 0x10);
    clientbound1_14->RegisterPacket(DeclareCommands::PACKET_ORDINAL, 0x11);
    clientbound1_14->RegisterPacket(ConfirmTransaction::PACKET_ORDINAL, 0x12);
    clientbound1_14->RegisterPacket(CloseInventory::PACKET_ORDINAL, 0x13);
    clientbound1_14->RegisterPacket(InventoryContent::PACKET_ORDINAL, 0x14);
    clientbound1_14->RegisterPacket(InventoryProperty::PACKET_ORDINAL, 0x15);
    clientbound1_14->RegisterPacket(InventorySlot::PACKET_ORDINAL, 0x16);
    clientbound1_14->RegisterPacket(Cooldown::PACKET_ORDINAL, 0x17);
    clientbound1_14->RegisterPacket(PluginMessage::PACKET_ORDINAL, 0x18);
    clientbound1_14->RegisterPacket(CustomSoundEffect::PACKET_ORDINAL, 0x19);
    clientbound1_14->RegisterPacket(Disconnect::PACKET_ORDINAL, 0x1A);
    clientbound1_14->RegisterPacket(EntityAnimation::PACKET_ORDINAL, 0x1B);
    clientbound1_14->RegisterPacket(Explosion::PACKET_ORDINAL, 0x1C);
    clientbound1_14->RegisterPacket(UnloadChunk::PACKET_ORDINAL, 0x1D);
    clientbound1_14->RegisterPacket(GameEvent::PACKET_ORDINAL, 0x1E);
    clientbound1_14->RegisterPacket(KeepAlive::PACKET_ORDINAL, 0x1F);
    clientbound1_14->RegisterPacket(OpenHorseInventory::PACKET_ORDINAL, 0x20);
    clientbound1_14->RegisterPacket(ChunkData::PACKET_ORDINAL, 0x21);
    clientbound1_14->RegisterPacket(EntitySoundEffect::PACKET_ORDINAL, 0x22);
    clientbound1_14->RegisterPacket(Particle::PACKET_ORDINAL, 0x23);
    clientbound1_14->RegisterPacket(ChunkLight::PACKET_ORDINAL, 0x24);
    clientbound1_14->RegisterPacket(JoinGame::PACKET_ORDINAL, 0x25);
    clientbound1_14->RegisterPacket(MapData::PACKET_ORDINAL, 0x26);
    clientbound1_14->RegisterPacket(TradeList::PACKET_ORDINAL, 0x27);
    clientbound1_14->RegisterPacket(EntityNotMoved::PACKET_ORDINAL, 0x28);
    clientbound1_14->RegisterPacket(EntityPosition::PACKET_ORDINAL, 0x29);
    clientbound1_14->RegisterPacket(EntityPositionAndRotation::PACKET_ORDINAL, 0x2A);
    clientbound1_14->RegisterPacket(EntityRotation::PACKET_ORDINAL, 0x2B);
    clientbound1_14->RegisterPacket(MoveVehicle::PACKET_ORDINAL, 0x2C);
    clientbound1_14->RegisterPacket(OpenBook::PACKET_ORDINAL, 0x2D);
    clientbound1_14->RegisterPacket(OpenInventory::PACKET_ORDINAL, 0x2E);
    clientbound1_14->RegisterPacket(OpenSignEditor::PACKET_ORDINAL, 0x2F);
    clientbound1_14->RegisterPacket(CraftRecipeResponse::PACKET_ORDINAL, 0x30);
    clientbound1_14->RegisterPacket(PlayerAbilities::PACKET_ORDINAL, 0x31);
    clientbound1_14->RegisterPacket(CombatEvent::PACKET_ORDINAL, 0x32);
    clientbound1_14->RegisterPacket(PlayerListItem::PACKET_ORDINAL, 0x33);
    clientbound1_14->RegisterPacket(PlayerFace::PACKET_ORDINAL, 0x34);
    clientbound1_14->RegisterPacket(PositionRotation::PACKET_ORDINAL, 0x35);
    clientbound1_14->RegisterPacket(UnlockRecipes::PACKET_ORDINAL, 0x36);
    clientbound1_14->RegisterPacket(EntityRemove::PACKET_ORDINAL, 0x37);
    clientbound1_14->RegisterPacket(EntityEffectRemove::PACKET_ORDINAL, 0x38);
    clientbound1_14->RegisterPacket(ResourcePackRequest::PACKET_ORDINAL, 0x39);
    clientbound1_14->RegisterPacket(Respawn::PACKET_ORDINAL, 0x3A);
    clientbound1_14->RegisterPacket(EntityLookAt::PACKET_ORDINAL, 0x3B);
    clientbound1_14->RegisterPacket(SelectAdvancementsTab::PACKET_ORDINAL, 0x3C);
    clientbound1_14->RegisterPacket(LegacyWorldBorder::PACKET_ORDINAL, 0x3D);
    clientbound1_14->RegisterPacket(Camera::PACKET_ORDINAL, 0x3E);
    clientbound1_14->RegisterPacket(HeldSlot::PACKET_ORDINAL, 0x3F);
    clientbound1_14->RegisterPacket(ViewPosition::PACKET_ORDINAL, 0x40);
    clientbound1_14->RegisterPacket(ViewDistance::PACKET_ORDINAL, 0x41);
    clientbound1_14->RegisterPacket(DisplayObjective::PACKET_ORDINAL, 0x42);
    clientbound1_14->RegisterPacket(EntityMetadata::PACKET_ORDINAL, 0x43);
    clientbound1_14->RegisterPacket(LeadEntities::PACKET_ORDINAL, 0x44);
    clientbound1_14->RegisterPacket(EntityVelocity::PACKET_ORDINAL, 0x45);
    clientbound1_14->RegisterPacket(EntityEquipment::PACKET_ORDINAL, 0x46);
    clientbound1_14->RegisterPacket(Experience::PACKET_ORDINAL, 0x47);
    clientbound1_14->RegisterPacket(Health::PACKET_ORDINAL, 0x48);
    clientbound1_14->RegisterPacket(Objectives::PACKET_ORDINAL, 0x49);
    clientbound1_14->RegisterPacket(Passengers::PACKET_ORDINAL, 0x4A);
    clientbound1_14->RegisterPacket(Teams::PACKET_ORDINAL, 0x4B);
    clientbound1_14->RegisterPacket(Score::PACKET_ORDINAL, 0x4C);
    clientbound1_14->RegisterPacket(DefaultSpawnPosition::PACKET_ORDINAL, 0x4D);
    clientbound1_14->RegisterPacket(WorldTime::PACKET_ORDINAL, 0x4E);
    clientbound1_14->RegisterPacket(LegacyTitle::PACKET_ORDINAL, 0x4F);
    clientbound1_14->RegisterPacket(EntitySoundEffect::PACKET_ORDINAL, 0x50);
    clientbound1_14->RegisterPacket(HardcodedSoundEffect::PACKET_ORDINAL, 0x51);
    clientbound1_14->RegisterPacket(StopSound::PACKET_ORDINAL, 0x52);
    clientbound1_14->RegisterPacket(TabHeaderFooter::PACKET_ORDINAL, 0x53);
    clientbound1_14->RegisterPacket(TagQueryResponse::PACKET_ORDINAL, 0x54);
    clientbound1_14->RegisterPacket(PickupItem::PACKET_ORDINAL, 0x55);
    clientbound1_14->RegisterPacket(EntityTeleport::PACKET_ORDINAL, 0x56);
    clientbound1_14->RegisterPacket(Advancements::PACKET_ORDINAL, 0x57);
    clientbound1_14->RegisterPacket(EntityProperties::PACKET_ORDINAL, 0x58);
    clientbound1_14->RegisterPacket(EntityEffect::PACKET_ORDINAL, 0x59);
    clientbound1_14->RegisterPacket(Recipes::PACKET_ORDINAL, 0x5A);
    clientbound1_14->RegisterPacket(Tags::PACKET_ORDINAL, 0x5B);
    clientbound1_14->RegisterPacket(AcknowledgeBlockChange::PACKET_ORDINAL, 0x5C);

    VersionRegistry* clientbound1_15 = clientboundRegistry + ProtocolVersion::MINECRAFT_1_15.GetPacketIDOrdinal();
    clientbound1_15->RegisterPacket(SpawnEntity::PACKET_ORDINAL, 0x00);
    clientbound1_15->RegisterPacket(SpawnExperienceOrb::PACKET_ORDINAL, 0x01);
    clientbound1_15->RegisterPacket(SpawnThunderbolt::PACKET_ORDINAL, 0x02);
    clientbound1_15->RegisterPacket(SpawnEntity::PACKET_ORDINAL, 0x03);
    clientbound1_15->RegisterPacket(SpawnPainting::PACKET_ORDINAL, 0x04);
    clientbound1_15->RegisterPacket(SpawnPlayer::PACKET_ORDINAL, 0x05);
    clientbound1_15->RegisterPacket(EntityAnimation::PACKET_ORDINAL, 0x06);
    clientbound1_15->RegisterPacket(AwardStatistics::PACKET_ORDINAL, 0x07);
    clientbound1_15->RegisterPacket(AcknowledgeBlockChange::PACKET_ORDINAL, 0x08);
    clientbound1_15->RegisterPacket(BlockDestroyStage::PACKET_ORDINAL, 0x09);
    clientbound1_15->RegisterPacket(BlockEntityData::PACKET_ORDINAL, 0x0A);
    clientbound1_15->RegisterPacket(BlockAction::PACKET_ORDINAL, 0x0B);
    clientbound1_15->RegisterPacket(BlockUpdate::PACKET_ORDINAL, 0x0C);
    clientbound1_15->RegisterPacket(BossBar::PACKET_ORDINAL, 0x0D);
    clientbound1_15->RegisterPacket(ServerChangeDifficulty::PACKET_ORDINAL, 0x0E);
    clientbound1_15->RegisterPacket(LegacyChat::PACKET_ORDINAL, 0x0F);
    clientbound1_15->RegisterPacket(SectionBlocks::PACKET_ORDINAL, 0x10);
    clientbound1_15->RegisterPacket(CommandSuggestionResponse::PACKET_ORDINAL, 0x11);
    clientbound1_15->RegisterPacket(DeclareCommands::PACKET_ORDINAL, 0x12);
    clientbound1_15->RegisterPacket(ConfirmTransaction::PACKET_ORDINAL, 0x13);
    clientbound1_15->RegisterPacket(CloseInventory::PACKET_ORDINAL, 0x14);
    clientbound1_15->RegisterPacket(InventoryContent::PACKET_ORDINAL, 0x15);
    clientbound1_15->RegisterPacket(InventoryProperty::PACKET_ORDINAL, 0x16);
    clientbound1_15->RegisterPacket(InventorySlot::PACKET_ORDINAL, 0x17);
    clientbound1_15->RegisterPacket(Cooldown::PACKET_ORDINAL, 0x18);
    clientbound1_15->RegisterPacket(PluginMessage::PACKET_ORDINAL, 0x19);
    clientbound1_15->RegisterPacket(CustomSoundEffect::PACKET_ORDINAL, 0x1A);
    clientbound1_15->RegisterPacket(Disconnect::PACKET_ORDINAL, 0x1B);
    clientbound1_15->RegisterPacket(EntityAnimation::PACKET_ORDINAL, 0x1C);
    clientbound1_15->RegisterPacket(Explosion::PACKET_ORDINAL, 0x1D);
    clientbound1_15->RegisterPacket(UnloadChunk::PACKET_ORDINAL, 0x1E);
    clientbound1_15->RegisterPacket(GameEvent::PACKET_ORDINAL, 0x1F);
    clientbound1_15->RegisterPacket(KeepAlive::PACKET_ORDINAL, 0x20);
    clientbound1_15->RegisterPacket(OpenHorseInventory::PACKET_ORDINAL, 0x21);
    clientbound1_15->RegisterPacket(ChunkData::PACKET_ORDINAL, 0x22);
    clientbound1_15->RegisterPacket(EntitySoundEffect::PACKET_ORDINAL, 0x23);
    clientbound1_15->RegisterPacket(Particle::PACKET_ORDINAL, 0x24);
    clientbound1_15->RegisterPacket(ChunkLight::PACKET_ORDINAL, 0x25);
    clientbound1_15->RegisterPacket(JoinGame::PACKET_ORDINAL, 0x26);
    clientbound1_15->RegisterPacket(MapData::PACKET_ORDINAL, 0x27);
    clientbound1_15->RegisterPacket(TradeList::PACKET_ORDINAL, 0x28);
    clientbound1_15->RegisterPacket(EntityNotMoved::PACKET_ORDINAL, 0x29);
    clientbound1_15->RegisterPacket(EntityPosition::PACKET_ORDINAL, 0x2A);
    clientbound1_15->RegisterPacket(EntityPositionAndRotation::PACKET_ORDINAL, 0x2B);
    clientbound1_15->RegisterPacket(EntityRotation::PACKET_ORDINAL, 0x2C);
    clientbound1_15->RegisterPacket(MoveVehicle::PACKET_ORDINAL, 0x2D);
    clientbound1_15->RegisterPacket(OpenBook::PACKET_ORDINAL, 0x2E);
    clientbound1_15->RegisterPacket(OpenInventory::PACKET_ORDINAL, 0x2D);
    clientbound1_15->RegisterPacket(OpenSignEditor::PACKET_ORDINAL, 0x30);
    clientbound1_15->RegisterPacket(CraftRecipeResponse::PACKET_ORDINAL, 0x31);
    clientbound1_15->RegisterPacket(PlayerAbilities::PACKET_ORDINAL, 0x32);
    clientbound1_15->RegisterPacket(CombatEvent::PACKET_ORDINAL, 0x33);
    clientbound1_15->RegisterPacket(PlayerListItem::PACKET_ORDINAL, 0x34);
    clientbound1_15->RegisterPacket(PlayerFace::PACKET_ORDINAL, 0x35);
    clientbound1_15->RegisterPacket(PositionRotation::PACKET_ORDINAL, 0x36);
    clientbound1_15->RegisterPacket(UnlockRecipes::PACKET_ORDINAL, 0x37);
    clientbound1_15->RegisterPacket(EntityRemove::PACKET_ORDINAL, 0x38);
    clientbound1_15->RegisterPacket(EntityEffectRemove::PACKET_ORDINAL, 0x39);
    clientbound1_15->RegisterPacket(ResourcePackRequest::PACKET_ORDINAL, 0x3A);
    clientbound1_15->RegisterPacket(Respawn::PACKET_ORDINAL, 0x3B);
    clientbound1_15->RegisterPacket(EntityLookAt::PACKET_ORDINAL, 0x3C);
    clientbound1_15->RegisterPacket(SelectAdvancementsTab::PACKET_ORDINAL, 0x3D);
    clientbound1_15->RegisterPacket(LegacyWorldBorder::PACKET_ORDINAL, 0x3E);
    clientbound1_15->RegisterPacket(Camera::PACKET_ORDINAL, 0x3F);
    clientbound1_15->RegisterPacket(HeldSlot::PACKET_ORDINAL, 0x40);
    clientbound1_15->RegisterPacket(ViewPosition::PACKET_ORDINAL, 0x41);
    clientbound1_15->RegisterPacket(ViewDistance::PACKET_ORDINAL, 0x42);
    clientbound1_15->RegisterPacket(DisplayObjective::PACKET_ORDINAL, 0x43);
    clientbound1_15->RegisterPacket(EntityMetadata::PACKET_ORDINAL, 0x44);
    clientbound1_15->RegisterPacket(LeadEntities::PACKET_ORDINAL, 0x45);
    clientbound1_15->RegisterPacket(EntityVelocity::PACKET_ORDINAL, 0x46);
    clientbound1_15->RegisterPacket(EntityEquipment::PACKET_ORDINAL, 0x47);
    clientbound1_15->RegisterPacket(Experience::PACKET_ORDINAL, 0x48);
    clientbound1_15->RegisterPacket(Health::PACKET_ORDINAL, 0x49);
    clientbound1_15->RegisterPacket(Objectives::PACKET_ORDINAL, 0x4A);
    clientbound1_15->RegisterPacket(Passengers::PACKET_ORDINAL, 0x4B);
    clientbound1_15->RegisterPacket(Teams::PACKET_ORDINAL, 0x4C);
    clientbound1_15->RegisterPacket(Score::PACKET_ORDINAL, 0x4D);
    clientbound1_15->RegisterPacket(DefaultSpawnPosition::PACKET_ORDINAL, 0x4E);
    clientbound1_15->RegisterPacket(WorldTime::PACKET_ORDINAL, 0x4F);
    clientbound1_15->RegisterPacket(LegacyTitle::PACKET_ORDINAL, 0x50);
    clientbound1_15->RegisterPacket(EntitySoundEffect::PACKET_ORDINAL, 0x51);
    clientbound1_15->RegisterPacket(HardcodedSoundEffect::PACKET_ORDINAL, 0x52);
    clientbound1_15->RegisterPacket(StopSound::PACKET_ORDINAL, 0x53);
    clientbound1_15->RegisterPacket(TabHeaderFooter::PACKET_ORDINAL, 0x54);
    clientbound1_15->RegisterPacket(TagQueryResponse::PACKET_ORDINAL, 0x55);
    clientbound1_15->RegisterPacket(PickupItem::PACKET_ORDINAL, 0x56);
    clientbound1_15->RegisterPacket(EntityTeleport::PACKET_ORDINAL, 0x57);
    clientbound1_15->RegisterPacket(Advancements::PACKET_ORDINAL, 0x58);
    clientbound1_15->RegisterPacket(EntityProperties::PACKET_ORDINAL, 0x59);
    clientbound1_15->RegisterPacket(EntityEffect::PACKET_ORDINAL, 0x5A);
    clientbound1_15->RegisterPacket(Recipes::PACKET_ORDINAL, 0x5B);
    clientbound1_15->RegisterPacket(Tags::PACKET_ORDINAL, 0x5C);

    // VersionRegistry* clientbound1_16 = clientboundRegistry + ProtocolVersion::MINECRAFT_1_16.GetPacketIDOrdinal();
    // clientbound1_16->RegisterPacket(SpawnEntity::PACKET_ORDINAL, 0x00);
    // clientbound1_16->RegisterPacket(SpawnExperienceOrb::PACKET_ORDINAL, 0x01);
    // clientbound1_16->RegisterPacket(SpawnEntity::PACKET_ORDINAL, 0x02);
    // clientbound1_16->RegisterPacket(SpawnPainting::PACKET_ORDINAL, 0x03);
    // clientbound1_16->RegisterPacket(SpawnPlayer::PACKET_ORDINAL, 0x04);
    // clientbound1_16->RegisterPacket(EntityAnimation::PACKET_ORDINAL, 0x05);
    // clientbound1_16->RegisterPacket(AwardStatistics::PACKET_ORDINAL, 0x06);
    // clientbound1_16->RegisterPacket(AcknowledgeBlockChange::PACKET_ORDINAL, 0x07);
    // clientbound1_16->RegisterPacket(BlockDestroyStage::PACKET_ORDINAL, 0x08);
    // clientbound1_16->RegisterPacket(BlockEntityData::PACKET_ORDINAL, 0x09);
    // clientbound1_16->RegisterPacket(BlockAction::PACKET_ORDINAL, 0x0A);
    // clientbound1_16->RegisterPacket(BlockUpdate::PACKET_ORDINAL, 0x0B);
    // clientbound1_16->RegisterPacket(BossBar::PACKET_ORDINAL, 0x0C);
    // clientbound1_16->RegisterPacket(ServerChangeDifficulty::PACKET_ORDINAL, 0x0D);
    // clientbound1_16->RegisterPacket(LegacyChat::PACKET_ORDINAL, 0x0E);
    // clientbound1_16->RegisterPacket(SectionBlocks::PACKET_ORDINAL, 0x0F);
    // clientbound1_16->RegisterPacket(CommandSuggestionResponse::PACKET_ORDINAL, 0x10);
    // clientbound1_16->RegisterPacket(DeclareCommands::PACKET_ORDINAL, 0x11);
    // clientbound1_16->RegisterPacket(ConfirmTransaction::PACKET_ORDINAL, 0x12);
    // clientbound1_16->RegisterPacket(CloseInventory::PACKET_ORDINAL, 0x13);
    // clientbound1_16->RegisterPacket(InventoryContent::PACKET_ORDINAL, 0x14);
    // clientbound1_16->RegisterPacket(InventoryProperty::PACKET_ORDINAL, 0x15);
    // clientbound1_16->RegisterPacket(InventorySlot::PACKET_ORDINAL, 0x16);
    // clientbound1_16->RegisterPacket(Cooldown::PACKET_ORDINAL, 0x17);
    // clientbound1_16->RegisterPacket(PluginMessage::PACKET_ORDINAL, 0x18);
    // clientbound1_16->RegisterPacket(CustomSoundEffect::PACKET_ORDINAL, 0x19);
    // clientbound1_16->RegisterPacket(Disconnect::PACKET_ORDINAL, 0x1A);
    // clientbound1_16->RegisterPacket(EntityAnimation::PACKET_ORDINAL, 0x1B);
    // clientbound1_16->RegisterPacket(Explosion::PACKET_ORDINAL, 0x1C);
    // clientbound1_16->RegisterPacket(UnloadChunk::PACKET_ORDINAL, 0x1D);
    // clientbound1_16->RegisterPacket(GameEvent::PACKET_ORDINAL, 0x1E);
    // clientbound1_16->RegisterPacket(KeepAlive::PACKET_ORDINAL, 0x1F);
    // clientbound1_16->RegisterPacket(OpenHorseInventory::PACKET_ORDINAL, 0x20);
    // clientbound1_16->RegisterPacket(ChunkData::PACKET_ORDINAL, 0x21);
    // clientbound1_16->RegisterPacket(EntitySoundEffect::PACKET_ORDINAL, 0x22);
    // clientbound1_16->RegisterPacket(Particle::PACKET_ORDINAL, 0x23);
    // clientbound1_16->RegisterPacket(ChunkLight::PACKET_ORDINAL, 0x24);
    // clientbound1_16->RegisterPacket(JoinGame::PACKET_ORDINAL, 0x25);
    // clientbound1_16->RegisterPacket(MapData::PACKET_ORDINAL, 0x26);
    // clientbound1_16->RegisterPacket(TradeList::PACKET_ORDINAL, 0x27);
    // clientbound1_16->RegisterPacket(EntityNotMoved::PACKET_ORDINAL, 0x28);
    // clientbound1_16->RegisterPacket(EntityPosition::PACKET_ORDINAL, 0x29);
    // clientbound1_16->RegisterPacket(EntityPositionAndRotation::PACKET_ORDINAL, 0x2A);
    // clientbound1_16->RegisterPacket(EntityRotation::PACKET_ORDINAL, 0x2B);
    // clientbound1_16->RegisterPacket(MoveVehicle::PACKET_ORDINAL, 0x2C);
    // clientbound1_16->RegisterPacket(OpenBook::PACKET_ORDINAL, 0x2D);
    // clientbound1_16->RegisterPacket(OpenInventory::PACKET_ORDINAL, 0x2E);
    // clientbound1_16->RegisterPacket(OpenSignEditor::PACKET_ORDINAL, 0x2D);
    // clientbound1_16->RegisterPacket(CraftRecipeResponse::PACKET_ORDINAL, 0x30);
    // clientbound1_16->RegisterPacket(PlayerAbilities::PACKET_ORDINAL, 0x31);
    // clientbound1_16->RegisterPacket(CombatEvent::PACKET_ORDINAL, 0x32);
    // clientbound1_16->RegisterPacket(PlayerListItem::PACKET_ORDINAL, 0x33);
    // clientbound1_16->RegisterPacket(PlayerFace::PACKET_ORDINAL, 0x34);
    // clientbound1_16->RegisterPacket(PositionRotation::PACKET_ORDINAL, 0x35);
    // clientbound1_16->RegisterPacket(UnlockRecipes::PACKET_ORDINAL, 0x36);
    // clientbound1_16->RegisterPacket(EntityRemove::PACKET_ORDINAL, 0x37);
    // clientbound1_16->RegisterPacket(EntityEffectRemove::PACKET_ORDINAL, 0x38);
    // clientbound1_16->RegisterPacket(ResourcePackRequest::PACKET_ORDINAL, 0x39);
    // clientbound1_16->RegisterPacket(Respawn::PACKET_ORDINAL, 0x3A);
    // clientbound1_16->RegisterPacket(EntityLookAt::PACKET_ORDINAL, 0x3B);
    // clientbound1_16->RegisterPacket(SelectAdvancementsTab::PACKET_ORDINAL, 0x3C);
    // clientbound1_16->RegisterPacket(LegacyWorldBorder::PACKET_ORDINAL, 0x3D);
    // clientbound1_16->RegisterPacket(Camera::PACKET_ORDINAL, 0x3E);
    // clientbound1_16->RegisterPacket(HeldSlot::PACKET_ORDINAL, 0x3F);
    // clientbound1_16->RegisterPacket(ViewPosition::PACKET_ORDINAL, 0x40);
    // clientbound1_16->RegisterPacket(ViewDistance::PACKET_ORDINAL, 0x41);
    // clientbound1_16->RegisterPacket(DisplayObjective::PACKET_ORDINAL, 0x42);
    // clientbound1_16->RegisterPacket(EntityMetadata::PACKET_ORDINAL, 0x43);
    // clientbound1_16->RegisterPacket(LeadEntities::PACKET_ORDINAL, 0x44);
    // clientbound1_16->RegisterPacket(EntityVelocity::PACKET_ORDINAL, 0x45);
    // clientbound1_16->RegisterPacket(EntityEquipment::PACKET_ORDINAL, 0x46);
    // clientbound1_16->RegisterPacket(Experience::PACKET_ORDINAL, 0x47);
    // clientbound1_16->RegisterPacket(Health::PACKET_ORDINAL, 0x48);
    // clientbound1_16->RegisterPacket(Objectives::PACKET_ORDINAL, 0x49);
    // clientbound1_16->RegisterPacket(Passengers::PACKET_ORDINAL, 0x4A);
    // clientbound1_16->RegisterPacket(Teams::PACKET_ORDINAL, 0x4B);
    // clientbound1_16->RegisterPacket(Score::PACKET_ORDINAL, 0x4C);
    // clientbound1_16->RegisterPacket(DefaultSpawnPosition::PACKET_ORDINAL, 0x4D);
    // clientbound1_16->RegisterPacket(WorldTime::PACKET_ORDINAL, 0x4E);
    // clientbound1_16->RegisterPacket(LegacyTitle::PACKET_ORDINAL, 0x4F);
    // clientbound1_16->RegisterPacket(EntitySoundEffect::PACKET_ORDINAL, 0x50);
    // clientbound1_16->RegisterPacket(HardcodedSoundEffect::PACKET_ORDINAL, 0x51);
    // clientbound1_16->RegisterPacket(StopSound::PACKET_ORDINAL, 0x52);
    // clientbound1_16->RegisterPacket(TabHeaderFooter::PACKET_ORDINAL, 0x53);
    // clientbound1_16->RegisterPacket(TagQueryResponse::PACKET_ORDINAL, 0x54);
    // clientbound1_16->RegisterPacket(PickupItem::PACKET_ORDINAL, 0x55);
    // clientbound1_16->RegisterPacket(EntityTeleport::PACKET_ORDINAL, 0x56);
    // clientbound1_16->RegisterPacket(Advancements::PACKET_ORDINAL, 0x57);
    // clientbound1_16->RegisterPacket(EntityProperties::PACKET_ORDINAL, 0x58);
    // clientbound1_16->RegisterPacket(EntityEffect::PACKET_ORDINAL, 0x59);
    // clientbound1_16->RegisterPacket(Recipes::PACKET_ORDINAL, 0x5A);
    // clientbound1_16->RegisterPacket(Tags::PACKET_ORDINAL, 0x5B);

    VersionRegistry* clientbound1_16_2 = clientboundRegistry + ProtocolVersion::MINECRAFT_1_16_2.GetPacketIDOrdinal();
    clientbound1_16_2->RegisterPacket(SpawnEntity::PACKET_ORDINAL, 0x00);
    clientbound1_16_2->RegisterPacket(SpawnExperienceOrb::PACKET_ORDINAL, 0x01);
    clientbound1_16_2->RegisterPacket(SpawnEntity::PACKET_ORDINAL, 0x02);
    clientbound1_16_2->RegisterPacket(SpawnPainting::PACKET_ORDINAL, 0x03);
    clientbound1_16_2->RegisterPacket(SpawnPlayer::PACKET_ORDINAL, 0x04);
    clientbound1_16_2->RegisterPacket(EntityAnimation::PACKET_ORDINAL, 0x05);
    clientbound1_16_2->RegisterPacket(AwardStatistics::PACKET_ORDINAL, 0x06);
    clientbound1_16_2->RegisterPacket(AcknowledgeBlockChange::PACKET_ORDINAL, 0x07);
    clientbound1_16_2->RegisterPacket(BlockDestroyStage::PACKET_ORDINAL, 0x08);
    clientbound1_16_2->RegisterPacket(BlockEntityData::PACKET_ORDINAL, 0x09);
    clientbound1_16_2->RegisterPacket(BlockAction::PACKET_ORDINAL, 0x0A);
    clientbound1_16_2->RegisterPacket(BlockUpdate::PACKET_ORDINAL, 0x0B);
    clientbound1_16_2->RegisterPacket(BossBar::PACKET_ORDINAL, 0x0C);
    clientbound1_16_2->RegisterPacket(ServerChangeDifficulty::PACKET_ORDINAL, 0x0D);
    clientbound1_16_2->RegisterPacket(LegacyChat::PACKET_ORDINAL, 0x0E);
    clientbound1_16_2->RegisterPacket(SectionBlocks::PACKET_ORDINAL, 0x0F);
    clientbound1_16_2->RegisterPacket(CommandSuggestionResponse::PACKET_ORDINAL, 0x10);
    clientbound1_16_2->RegisterPacket(DeclareCommands::PACKET_ORDINAL, 0x11);
    clientbound1_16_2->RegisterPacket(ConfirmTransaction::PACKET_ORDINAL, 0x12);
    clientbound1_16_2->RegisterPacket(CloseInventory::PACKET_ORDINAL, 0x13);
    clientbound1_16_2->RegisterPacket(InventoryContent::PACKET_ORDINAL, 0x14);
    clientbound1_16_2->RegisterPacket(InventoryProperty::PACKET_ORDINAL, 0x15);
    clientbound1_16_2->RegisterPacket(InventorySlot::PACKET_ORDINAL, 0x16);
    clientbound1_16_2->RegisterPacket(Cooldown::PACKET_ORDINAL, 0x17);
    clientbound1_16_2->RegisterPacket(PluginMessage::PACKET_ORDINAL, 0x18);
    clientbound1_16_2->RegisterPacket(CustomSoundEffect::PACKET_ORDINAL, 0x19);
    clientbound1_16_2->RegisterPacket(Disconnect::PACKET_ORDINAL, 0x1A);
    clientbound1_16_2->RegisterPacket(EntityAnimation::PACKET_ORDINAL, 0x1B);
    clientbound1_16_2->RegisterPacket(Explosion::PACKET_ORDINAL, 0x1C);
    clientbound1_16_2->RegisterPacket(UnloadChunk::PACKET_ORDINAL, 0x1D);
    clientbound1_16_2->RegisterPacket(GameEvent::PACKET_ORDINAL, 0x1E);
    clientbound1_16_2->RegisterPacket(KeepAlive::PACKET_ORDINAL, 0x1F);
    clientbound1_16_2->RegisterPacket(OpenHorseInventory::PACKET_ORDINAL, 0x20);
    clientbound1_16_2->RegisterPacket(ChunkData::PACKET_ORDINAL, 0x21);
    clientbound1_16_2->RegisterPacket(EntitySoundEffect::PACKET_ORDINAL, 0x22);
    clientbound1_16_2->RegisterPacket(Particle::PACKET_ORDINAL, 0x23);
    clientbound1_16_2->RegisterPacket(ChunkLight::PACKET_ORDINAL, 0x24);
    clientbound1_16_2->RegisterPacket(JoinGame::PACKET_ORDINAL, 0x25);
    clientbound1_16_2->RegisterPacket(MapData::PACKET_ORDINAL, 0x26);
    clientbound1_16_2->RegisterPacket(TradeList::PACKET_ORDINAL, 0x27);
    clientbound1_16_2->RegisterPacket(EntityNotMoved::PACKET_ORDINAL, 0x28);
    clientbound1_16_2->RegisterPacket(EntityPosition::PACKET_ORDINAL, 0x29);
    clientbound1_16_2->RegisterPacket(EntityPositionAndRotation::PACKET_ORDINAL, 0x2A);
    clientbound1_16_2->RegisterPacket(EntityRotation::PACKET_ORDINAL, 0x2B);
    clientbound1_16_2->RegisterPacket(MoveVehicle::PACKET_ORDINAL, 0x2C);
    clientbound1_16_2->RegisterPacket(OpenBook::PACKET_ORDINAL, 0x2D);
    clientbound1_16_2->RegisterPacket(OpenInventory::PACKET_ORDINAL, 0x2E);
    clientbound1_16_2->RegisterPacket(OpenSignEditor::PACKET_ORDINAL, 0x2D);
    clientbound1_16_2->RegisterPacket(CraftRecipeResponse::PACKET_ORDINAL, 0x30);
    clientbound1_16_2->RegisterPacket(PlayerAbilities::PACKET_ORDINAL, 0x31);
    clientbound1_16_2->RegisterPacket(CombatEvent::PACKET_ORDINAL, 0x32);
    clientbound1_16_2->RegisterPacket(PlayerListItem::PACKET_ORDINAL, 0x33);
    clientbound1_16_2->RegisterPacket(PlayerFace::PACKET_ORDINAL, 0x34);
    clientbound1_16_2->RegisterPacket(PositionRotation::PACKET_ORDINAL, 0x35);
    clientbound1_16_2->RegisterPacket(UnlockRecipes::PACKET_ORDINAL, 0x36);
    clientbound1_16_2->RegisterPacket(EntityRemove::PACKET_ORDINAL, 0x37);
    clientbound1_16_2->RegisterPacket(EntityEffectRemove::PACKET_ORDINAL, 0x38);
    clientbound1_16_2->RegisterPacket(ResourcePackRequest::PACKET_ORDINAL, 0x39);
    clientbound1_16_2->RegisterPacket(Respawn::PACKET_ORDINAL, 0x3A);
    clientbound1_16_2->RegisterPacket(EntityLookAt::PACKET_ORDINAL, 0x3B);
    clientbound1_16_2->RegisterPacket(SelectAdvancementsTab::PACKET_ORDINAL, 0x3C);
    clientbound1_16_2->RegisterPacket(LegacyWorldBorder::PACKET_ORDINAL, 0x3D);
    clientbound1_16_2->RegisterPacket(Camera::PACKET_ORDINAL, 0x3E);
    clientbound1_16_2->RegisterPacket(HeldSlot::PACKET_ORDINAL, 0x3F);
    clientbound1_16_2->RegisterPacket(ViewPosition::PACKET_ORDINAL, 0x40);
    clientbound1_16_2->RegisterPacket(ViewDistance::PACKET_ORDINAL, 0x41);
    clientbound1_16_2->RegisterPacket(DisplayObjective::PACKET_ORDINAL, 0x42);
    clientbound1_16_2->RegisterPacket(EntityMetadata::PACKET_ORDINAL, 0x43);
    clientbound1_16_2->RegisterPacket(LeadEntities::PACKET_ORDINAL, 0x44);
    clientbound1_16_2->RegisterPacket(EntityVelocity::PACKET_ORDINAL, 0x45);
    clientbound1_16_2->RegisterPacket(EntityEquipment::PACKET_ORDINAL, 0x46);
    clientbound1_16_2->RegisterPacket(Experience::PACKET_ORDINAL, 0x47);
    clientbound1_16_2->RegisterPacket(Health::PACKET_ORDINAL, 0x48);
    clientbound1_16_2->RegisterPacket(Objectives::PACKET_ORDINAL, 0x49);
    clientbound1_16_2->RegisterPacket(Passengers::PACKET_ORDINAL, 0x4A);
    clientbound1_16_2->RegisterPacket(Teams::PACKET_ORDINAL, 0x4B);
    clientbound1_16_2->RegisterPacket(Score::PACKET_ORDINAL, 0x4C);
    clientbound1_16_2->RegisterPacket(DefaultSpawnPosition::PACKET_ORDINAL, 0x4D);
    clientbound1_16_2->RegisterPacket(WorldTime::PACKET_ORDINAL, 0x4E);
    clientbound1_16_2->RegisterPacket(LegacyTitle::PACKET_ORDINAL, 0x4F);
    clientbound1_16_2->RegisterPacket(EntitySoundEffect::PACKET_ORDINAL, 0x50);
    clientbound1_16_2->RegisterPacket(HardcodedSoundEffect::PACKET_ORDINAL, 0x51);
    clientbound1_16_2->RegisterPacket(StopSound::PACKET_ORDINAL, 0x52);
    clientbound1_16_2->RegisterPacket(TabHeaderFooter::PACKET_ORDINAL, 0x53);
    clientbound1_16_2->RegisterPacket(TagQueryResponse::PACKET_ORDINAL, 0x54);
    clientbound1_16_2->RegisterPacket(PickupItem::PACKET_ORDINAL, 0x55);
    clientbound1_16_2->RegisterPacket(EntityTeleport::PACKET_ORDINAL, 0x56);
    clientbound1_16_2->RegisterPacket(Advancements::PACKET_ORDINAL, 0x57);
    clientbound1_16_2->RegisterPacket(EntityProperties::PACKET_ORDINAL, 0x58);
    clientbound1_16_2->RegisterPacket(EntityEffect::PACKET_ORDINAL, 0x59);
    clientbound1_16_2->RegisterPacket(Recipes::PACKET_ORDINAL, 0x5A);
    clientbound1_16_2->RegisterPacket(Tags::PACKET_ORDINAL, 0x5B);

    VersionRegistry* clientbound1_17 = clientboundRegistry + ProtocolVersion::MINECRAFT_1_17.GetPacketIDOrdinal();
    clientbound1_17->RegisterPacket(SpawnEntity::PACKET_ORDINAL, 0x00);
    clientbound1_17->RegisterPacket(SpawnExperienceOrb::PACKET_ORDINAL, 0x01);
    clientbound1_17->RegisterPacket(SpawnEntity::PACKET_ORDINAL, 0x02);
    clientbound1_17->RegisterPacket(SpawnPainting::PACKET_ORDINAL, 0x03);
    clientbound1_17->RegisterPacket(SpawnPlayer::PACKET_ORDINAL, 0x04);
    //    clientbound1_17->RegisterPacket(SkulkVibration::PACKET_ORDINAL, 0x05); //TODO: SkulkVibration
    clientbound1_17->RegisterPacket(EntityAnimation::PACKET_ORDINAL, 0x06);
    clientbound1_17->RegisterPacket(AwardStatistics::PACKET_ORDINAL, 0x07);
    clientbound1_17->RegisterPacket(AcknowledgeBlockChange::PACKET_ORDINAL, 0x08);
    clientbound1_17->RegisterPacket(BlockDestroyStage::PACKET_ORDINAL, 0x09);
    clientbound1_17->RegisterPacket(BlockEntityData::PACKET_ORDINAL, 0x0A);
    clientbound1_17->RegisterPacket(BlockAction::PACKET_ORDINAL, 0x0B);
    clientbound1_17->RegisterPacket(BlockUpdate::PACKET_ORDINAL, 0x0C);
    clientbound1_17->RegisterPacket(BossBar::PACKET_ORDINAL, 0x0D);
    clientbound1_17->RegisterPacket(ServerChangeDifficulty::PACKET_ORDINAL, 0x0E);
    clientbound1_17->RegisterPacket(LegacyChat::PACKET_ORDINAL, 0x0F);
    clientbound1_17->RegisterPacket(ClearTitle::PACKET_ORDINAL, 0x10);
    clientbound1_17->RegisterPacket(CommandSuggestionResponse::PACKET_ORDINAL, 0x11);
    clientbound1_17->RegisterPacket(DeclareCommands::PACKET_ORDINAL, 0x12);
    //    clientbound1_17->RegisterPacket(ConfirmTransaction::PACKET_ORDINAL, 0x12);
    clientbound1_17->RegisterPacket(CloseInventory::PACKET_ORDINAL, 0x13);
    clientbound1_17->RegisterPacket(InventoryContent::PACKET_ORDINAL, 0x14);
    clientbound1_17->RegisterPacket(InventoryProperty::PACKET_ORDINAL, 0x15);
    clientbound1_17->RegisterPacket(InventorySlot::PACKET_ORDINAL, 0x16);
    clientbound1_17->RegisterPacket(Cooldown::PACKET_ORDINAL, 0x17);
    clientbound1_17->RegisterPacket(PluginMessage::PACKET_ORDINAL, 0x18);
    clientbound1_17->RegisterPacket(CustomSoundEffect::PACKET_ORDINAL, 0x19);
    clientbound1_17->RegisterPacket(Disconnect::PACKET_ORDINAL, 0x1A);
    clientbound1_17->RegisterPacket(EntityAnimation::PACKET_ORDINAL, 0x1B);
    clientbound1_17->RegisterPacket(Explosion::PACKET_ORDINAL, 0x1C);
    clientbound1_17->RegisterPacket(UnloadChunk::PACKET_ORDINAL, 0x1D);
    clientbound1_17->RegisterPacket(GameEvent::PACKET_ORDINAL, 0x1E);
    clientbound1_17->RegisterPacket(OpenHorseInventory::PACKET_ORDINAL, 0x1F);
    clientbound1_17->RegisterPacket(LegacyWorldBorder::PACKET_ORDINAL, 0x20);
    clientbound1_17->RegisterPacket(KeepAlive::PACKET_ORDINAL, 0x21);
    clientbound1_17->RegisterPacket(ChunkData::PACKET_ORDINAL, 0x22);
    clientbound1_17->RegisterPacket(EntitySoundEffect::PACKET_ORDINAL, 0x23);
    clientbound1_17->RegisterPacket(Particle::PACKET_ORDINAL, 0x24);
    clientbound1_17->RegisterPacket(ChunkLight::PACKET_ORDINAL, 0x25);
    clientbound1_17->RegisterPacket(JoinGame::PACKET_ORDINAL, 0x26);
    clientbound1_17->RegisterPacket(MapData::PACKET_ORDINAL, 0x27);
    clientbound1_17->RegisterPacket(TradeList::PACKET_ORDINAL, 0x28);
    //    clientbound1_17->RegisterPacket(EntityNotMoved::PACKET_ORDINAL, 0x28);
    clientbound1_17->RegisterPacket(EntityPosition::PACKET_ORDINAL, 0x29);
    clientbound1_17->RegisterPacket(EntityPositionAndRotation::PACKET_ORDINAL, 0x2A);
    clientbound1_17->RegisterPacket(EntityRotation::PACKET_ORDINAL, 0x2B);
    clientbound1_17->RegisterPacket(MoveVehicle::PACKET_ORDINAL, 0x2C);
    clientbound1_17->RegisterPacket(OpenBook::PACKET_ORDINAL, 0x2D);
    clientbound1_17->RegisterPacket(OpenInventory::PACKET_ORDINAL, 0x2E);
    clientbound1_17->RegisterPacket(OpenSignEditor::PACKET_ORDINAL, 0x2F);
    clientbound1_17->RegisterPacket(Ping::PACKET_ORDINAL, 0x30);
    clientbound1_17->RegisterPacket(CraftRecipeResponse::PACKET_ORDINAL, 0x31);
    clientbound1_17->RegisterPacket(PlayerAbilities::PACKET_ORDINAL, 0x32);
    //    clientbound1_17->RegisterPacket(EndCombatEvent::PACKET_ORDINAL, 0x33); //TODO: EndCombatEvent
    //    clientbound1_17->RegisterPacket(EnterCombatEvent::PACKET_ORDINAL, 0x34); //TODO: EnterCombatEvent
    //    clientbound1_17->RegisterPacket(DeathCombatEvent::PACKET_ORDINAL, 0x35); //TODO: DeathCombatEvent
    clientbound1_17->RegisterPacket(PlayerListItem::PACKET_ORDINAL, 0x36);
    clientbound1_17->RegisterPacket(PlayerFace::PACKET_ORDINAL, 0x37);
    clientbound1_17->RegisterPacket(PositionRotation::PACKET_ORDINAL, 0x38);
    clientbound1_17->RegisterPacket(UnlockRecipes::PACKET_ORDINAL, 0x39);
    clientbound1_17->RegisterPacket(EntityRemove::PACKET_ORDINAL, 0x3A);
    clientbound1_17->RegisterPacket(EntityEffectRemove::PACKET_ORDINAL, 0x3B);
    clientbound1_17->RegisterPacket(ResourcePackRequest::PACKET_ORDINAL, 0x3C);
    clientbound1_17->RegisterPacket(Respawn::PACKET_ORDINAL, 0x3D);
    clientbound1_17->RegisterPacket(EntityLookAt::PACKET_ORDINAL, 0x3E);
    clientbound1_17->RegisterPacket(SectionBlocks::PACKET_ORDINAL, 0x3F);
    clientbound1_17->RegisterPacket(SelectAdvancementsTab::PACKET_ORDINAL, 0x40);
    clientbound1_17->RegisterPacket(ActionBar::PACKET_ORDINAL, 0x41);
    clientbound1_17->RegisterPacket(BorderCenter::PACKET_ORDINAL, 0x42);
    clientbound1_17->RegisterPacket(BorderRadiusSpeed::PACKET_ORDINAL, 0x43);
    clientbound1_17->RegisterPacket(BorderRadius::PACKET_ORDINAL, 0x44);
    clientbound1_17->RegisterPacket(BorderWarningTime::PACKET_ORDINAL, 0x45);
    clientbound1_17->RegisterPacket(BorderWarningRadius::PACKET_ORDINAL, 0x46);
    clientbound1_17->RegisterPacket(Camera::PACKET_ORDINAL, 0x47);
    clientbound1_17->RegisterPacket(HeldSlot::PACKET_ORDINAL, 0x48);
    clientbound1_17->RegisterPacket(ViewPosition::PACKET_ORDINAL, 0x49);
    clientbound1_17->RegisterPacket(ViewDistance::PACKET_ORDINAL, 0x4A);
    clientbound1_17->RegisterPacket(DefaultSpawnPosition::PACKET_ORDINAL, 0x4B);
    clientbound1_17->RegisterPacket(DisplayObjective::PACKET_ORDINAL, 0x4C);
    clientbound1_17->RegisterPacket(EntityMetadata::PACKET_ORDINAL, 0x4D);
    clientbound1_17->RegisterPacket(LeadEntities::PACKET_ORDINAL, 0x4E);
    clientbound1_17->RegisterPacket(EntityVelocity::PACKET_ORDINAL, 0x4F);
    clientbound1_17->RegisterPacket(EntityEquipment::PACKET_ORDINAL, 0x50);
    clientbound1_17->RegisterPacket(Experience::PACKET_ORDINAL, 0x51);
    clientbound1_17->RegisterPacket(Health::PACKET_ORDINAL, 0x52);
    clientbound1_17->RegisterPacket(Objectives::PACKET_ORDINAL, 0x53);
    clientbound1_17->RegisterPacket(Passengers::PACKET_ORDINAL, 0x54);
    clientbound1_17->RegisterPacket(Teams::PACKET_ORDINAL, 0x55);
    clientbound1_17->RegisterPacket(Score::PACKET_ORDINAL, 0x56);
    clientbound1_17->RegisterPacket(Subtitle::PACKET_ORDINAL, 0x57);
    clientbound1_17->RegisterPacket(WorldTime::PACKET_ORDINAL, 0x58);
    clientbound1_17->RegisterPacket(Title::PACKET_ORDINAL, 0x59);
    clientbound1_17->RegisterPacket(TitleTimes::PACKET_ORDINAL, 0x5A);
    clientbound1_17->RegisterPacket(EntitySoundEffect::PACKET_ORDINAL, 0x5B);
    clientbound1_17->RegisterPacket(HardcodedSoundEffect::PACKET_ORDINAL, 0x5C);
    clientbound1_17->RegisterPacket(StopSound::PACKET_ORDINAL, 0x5D);
    clientbound1_17->RegisterPacket(TabHeaderFooter::PACKET_ORDINAL, 0x5E);
    clientbound1_17->RegisterPacket(TagQueryResponse::PACKET_ORDINAL, 0x5F);
    clientbound1_17->RegisterPacket(PickupItem::PACKET_ORDINAL, 0x60);
    clientbound1_17->RegisterPacket(EntityTeleport::PACKET_ORDINAL, 0x61);
    clientbound1_17->RegisterPacket(Advancements::PACKET_ORDINAL, 0x62);
    clientbound1_17->RegisterPacket(EntityProperties::PACKET_ORDINAL, 0x63);
    clientbound1_17->RegisterPacket(EntityEffect::PACKET_ORDINAL, 0x64);
    clientbound1_17->RegisterPacket(Recipes::PACKET_ORDINAL, 0x65);
    clientbound1_17->RegisterPacket(Tags::PACKET_ORDINAL, 0x66);

    VersionRegistry* serverboundRegistry = DirectionRegistry::NewVersionRegistry();
    VersionRegistry* serverbound1_12_2 = serverboundRegistry + ProtocolVersion::MINECRAFT_1_12_2.GetPacketIDOrdinal();
    serverbound1_12_2->RegisterPacket(ConfirmTeleport::PACKET_ORDINAL, 0x00);
    serverbound1_12_2->RegisterPacket(CommandSuggestionRequest::PACKET_ORDINAL, 0x01);
    serverbound1_12_2->RegisterPacket(LegacyChat::PACKET_ORDINAL, 0x02);
    serverbound1_12_2->RegisterPacket(ClientAction::PACKET_ORDINAL, 0x03);
    serverbound1_12_2->RegisterPacket(ClientSettings::PACKET_ORDINAL, 0x04);
    serverbound1_12_2->RegisterPacket(ConfirmTransaction::PACKET_ORDINAL, 0x05);
    serverbound1_12_2->RegisterPacket(LegacyEnchant::PACKET_ORDINAL, 0x06);
    serverbound1_12_2->RegisterPacket(ClickSlot::PACKET_ORDINAL, 0x07);
    serverbound1_12_2->RegisterPacket(CloseInventory::PACKET_ORDINAL, 0x08);
    serverbound1_12_2->RegisterPacket(PluginMessage::PACKET_ORDINAL, 0x09);
    serverbound1_12_2->RegisterPacket(EntityInteract::PACKET_ORDINAL, 0x0A);
    serverbound1_12_2->RegisterPacket(KeepAlive::PACKET_ORDINAL, 0x0B);
    serverbound1_12_2->RegisterPacket(MoveGroundOnly::PACKET_ORDINAL, 0x0C);
    serverbound1_12_2->RegisterPacket(MovePositionOnly::PACKET_ORDINAL, 0x0D);
    serverbound1_12_2->RegisterPacket(Move::PACKET_ORDINAL, 0x0E);
    serverbound1_12_2->RegisterPacket(MoveRotationOnly::PACKET_ORDINAL, 0x0F);
    serverbound1_12_2->RegisterPacket(MoveVehicle::PACKET_ORDINAL, 0x10);
    serverbound1_12_2->RegisterPacket(BoatPaddle::PACKET_ORDINAL, 0x11);
    serverbound1_12_2->RegisterPacket(CraftRecipeRequest::PACKET_ORDINAL, 0x12);
    serverbound1_12_2->RegisterPacket(PlayerAbilities::PACKET_ORDINAL, 0x13);
    serverbound1_12_2->RegisterPacket(Digging::PACKET_ORDINAL, 0x14);
    serverbound1_12_2->RegisterPacket(EntityAction::PACKET_ORDINAL, 0x15);
    serverbound1_12_2->RegisterPacket(PlayerInput::PACKET_ORDINAL, 0x16);
    serverbound1_12_2->RegisterPacket(LegacyRecipeBook::PACKET_ORDINAL, 0x17);
    serverbound1_12_2->RegisterPacket(ResourcePackResponse::PACKET_ORDINAL, 0x18);
    serverbound1_12_2->RegisterPacket(SelectAdvancementsTab::PACKET_ORDINAL, 0x19);
    serverbound1_12_2->RegisterPacket(HeldSlot::PACKET_ORDINAL, 0x1A);
    serverbound1_12_2->RegisterPacket(EditSign::PACKET_ORDINAL, 0x1B);
    serverbound1_12_2->RegisterPacket(SwingArm::PACKET_ORDINAL, 0x1C);
    serverbound1_12_2->RegisterPacket(Spectate::PACKET_ORDINAL, 0x1D);
    serverbound1_12_2->RegisterPacket(Camera::PACKET_ORDINAL, 0x1E);
    serverbound1_12_2->RegisterPacket(PlaceBlock::PACKET_ORDINAL, 0x1F);
    serverbound1_12_2->RegisterPacket(UseItem::PACKET_ORDINAL, 0x20);

    VersionRegistry* serverbound1_13 = serverboundRegistry + ProtocolVersion::MINECRAFT_1_13.GetPacketIDOrdinal();
    serverbound1_13->RegisterPacket(ConfirmTeleport::PACKET_ORDINAL, 0x00);
    serverbound1_13->RegisterPacket(BlockTagQueryRequest::PACKET_ORDINAL, 0x01);
    serverbound1_13->RegisterPacket(LegacyChat::PACKET_ORDINAL, 0x02);
    serverbound1_13->RegisterPacket(ClientAction::PACKET_ORDINAL, 0x03);
    serverbound1_13->RegisterPacket(ClientSettings::PACKET_ORDINAL, 0x04);
    serverbound1_13->RegisterPacket(CommandSuggestionRequest::PACKET_ORDINAL, 0x05);
    serverbound1_13->RegisterPacket(ConfirmTransaction::PACKET_ORDINAL, 0x06);
    serverbound1_13->RegisterPacket(LegacyEnchant::PACKET_ORDINAL, 0x07);
    serverbound1_13->RegisterPacket(ClickSlot::PACKET_ORDINAL, 0x08);
    serverbound1_13->RegisterPacket(CloseInventory::PACKET_ORDINAL, 0x09);
    serverbound1_13->RegisterPacket(PluginMessage::PACKET_ORDINAL, 0x0A);
    serverbound1_13->RegisterPacket(EditBook::PACKET_ORDINAL, 0x0B);
    serverbound1_13->RegisterPacket(TagQueryRequest::PACKET_ORDINAL, 0x0C);
    serverbound1_13->RegisterPacket(EntityInteract::PACKET_ORDINAL, 0x0D);
    serverbound1_13->RegisterPacket(KeepAlive::PACKET_ORDINAL, 0x0E);
    serverbound1_13->RegisterPacket(MoveGroundOnly::PACKET_ORDINAL, 0x0F);
    serverbound1_13->RegisterPacket(MovePositionOnly::PACKET_ORDINAL, 0x10);
    serverbound1_13->RegisterPacket(Move::PACKET_ORDINAL, 0x11);
    serverbound1_13->RegisterPacket(MoveRotationOnly::PACKET_ORDINAL, 0x12);
    serverbound1_13->RegisterPacket(MoveVehicle::PACKET_ORDINAL, 0x13);
    serverbound1_13->RegisterPacket(BoatPaddle::PACKET_ORDINAL, 0x14);
    serverbound1_13->RegisterPacket(PickItem::PACKET_ORDINAL, 0x15);
    serverbound1_13->RegisterPacket(CraftRecipeRequest::PACKET_ORDINAL, 0x16);
    serverbound1_13->RegisterPacket(PlayerAbilities::PACKET_ORDINAL, 0x17);
    serverbound1_13->RegisterPacket(Digging::PACKET_ORDINAL, 0x18);
    serverbound1_13->RegisterPacket(EntityAction::PACKET_ORDINAL, 0x19);
    serverbound1_13->RegisterPacket(PlayerInput::PACKET_ORDINAL, 0x1A);
    serverbound1_13->RegisterPacket(LegacyRecipeBook::PACKET_ORDINAL, 0x1B);
    serverbound1_13->RegisterPacket(RenameItem::PACKET_ORDINAL, 0x1C);
    serverbound1_13->RegisterPacket(ResourcePackResponse::PACKET_ORDINAL, 0x1D);
    serverbound1_13->RegisterPacket(SelectAdvancementsTab::PACKET_ORDINAL, 0x1E);
    serverbound1_13->RegisterPacket(SelectTrade::PACKET_ORDINAL, 0x1F);
    serverbound1_13->RegisterPacket(BeaconEffect::PACKET_ORDINAL, 0x20);
    serverbound1_13->RegisterPacket(HeldSlot::PACKET_ORDINAL, 0x21);
    serverbound1_13->RegisterPacket(ProgramCommandBlock::PACKET_ORDINAL, 0x22);
    serverbound1_13->RegisterPacket(ProgramCommandBlockMinecart::PACKET_ORDINAL, 0x23);
    serverbound1_13->RegisterPacket(CreativeSlot::PACKET_ORDINAL, 0x24);
    serverbound1_13->RegisterPacket(ProgramStructureBlock::PACKET_ORDINAL, 0x25);
    serverbound1_13->RegisterPacket(EditSign::PACKET_ORDINAL, 0x26);
    serverbound1_13->RegisterPacket(SwingArm::PACKET_ORDINAL, 0x27);
    serverbound1_13->RegisterPacket(Spectate::PACKET_ORDINAL, 0x28);
    serverbound1_13->RegisterPacket(PlaceBlock::PACKET_ORDINAL, 0x29);
    serverbound1_13->RegisterPacket(UseItem::PACKET_ORDINAL, 0x2A);

    VersionRegistry* serverbound1_14 = serverboundRegistry + ProtocolVersion::MINECRAFT_1_14.GetPacketIDOrdinal();
    serverbound1_14->RegisterPacket(ConfirmTeleport::PACKET_ORDINAL, 0x00);
    serverbound1_14->RegisterPacket(BlockTagQueryRequest::PACKET_ORDINAL, 0x01);
    serverbound1_14->RegisterPacket(ClientChangeDifficulty::PACKET_ORDINAL, 0x02);
    serverbound1_14->RegisterPacket(LegacyChat::PACKET_ORDINAL, 0x03);
    serverbound1_14->RegisterPacket(ClientAction::PACKET_ORDINAL, 0x04);
    serverbound1_14->RegisterPacket(ClientSettings::PACKET_ORDINAL, 0x05);
    serverbound1_14->RegisterPacket(CommandSuggestionRequest::PACKET_ORDINAL, 0x06);
    serverbound1_14->RegisterPacket(ConfirmTransaction::PACKET_ORDINAL, 0x07);
    serverbound1_14->RegisterPacket(ClickInventoryButton::PACKET_ORDINAL, 0x08);
    serverbound1_14->RegisterPacket(ClickSlot::PACKET_ORDINAL, 0x09);
    serverbound1_14->RegisterPacket(CloseInventory::PACKET_ORDINAL, 0x0A);
    serverbound1_14->RegisterPacket(PluginMessage::PACKET_ORDINAL, 0x0B);
    serverbound1_14->RegisterPacket(EditBook::PACKET_ORDINAL, 0x0C);
    serverbound1_14->RegisterPacket(TagQueryRequest::PACKET_ORDINAL, 0x0D);
    serverbound1_14->RegisterPacket(EntityInteract::PACKET_ORDINAL, 0x0E);
    serverbound1_14->RegisterPacket(KeepAlive::PACKET_ORDINAL, 0x0F);
    serverbound1_14->RegisterPacket(LockDifficulty::PACKET_ORDINAL, 0x10);
    serverbound1_14->RegisterPacket(MoveGroundOnly::PACKET_ORDINAL, 0x11);
    serverbound1_14->RegisterPacket(MovePositionOnly::PACKET_ORDINAL, 0x12);
    serverbound1_14->RegisterPacket(Move::PACKET_ORDINAL, 0x13);
    serverbound1_14->RegisterPacket(MoveRotationOnly::PACKET_ORDINAL, 0x14);
    serverbound1_14->RegisterPacket(MoveVehicle::PACKET_ORDINAL, 0x15);
    serverbound1_14->RegisterPacket(BoatPaddle::PACKET_ORDINAL, 0x16);
    serverbound1_14->RegisterPacket(PickItem::PACKET_ORDINAL, 0x17);
    serverbound1_14->RegisterPacket(CraftRecipeRequest::PACKET_ORDINAL, 0x18);
    serverbound1_14->RegisterPacket(PlayerAbilities::PACKET_ORDINAL, 0x19);
    serverbound1_14->RegisterPacket(Digging::PACKET_ORDINAL, 0x1A);
    serverbound1_14->RegisterPacket(EntityAction::PACKET_ORDINAL, 0x1B);
    serverbound1_14->RegisterPacket(PlayerInput::PACKET_ORDINAL, 0x1C);
    serverbound1_14->RegisterPacket(LegacyRecipeBook::PACKET_ORDINAL, 0x1D);
    serverbound1_14->RegisterPacket(RenameItem::PACKET_ORDINAL, 0x1E);
    serverbound1_14->RegisterPacket(ResourcePackResponse::PACKET_ORDINAL, 0x1F);
    serverbound1_14->RegisterPacket(SelectAdvancementsTab::PACKET_ORDINAL, 0x20);
    serverbound1_14->RegisterPacket(SelectTrade::PACKET_ORDINAL, 0x21);
    serverbound1_14->RegisterPacket(BeaconEffect::PACKET_ORDINAL, 0x22);
    serverbound1_14->RegisterPacket(HeldSlot::PACKET_ORDINAL, 0x23);
    serverbound1_14->RegisterPacket(ProgramCommandBlock::PACKET_ORDINAL, 0x24);
    serverbound1_14->RegisterPacket(ProgramCommandBlockMinecart::PACKET_ORDINAL, 0x25);
    serverbound1_14->RegisterPacket(CreativeSlot::PACKET_ORDINAL, 0x26);
    serverbound1_14->RegisterPacket(ProgramJigsawBlock::PACKET_ORDINAL, 0x27);
    serverbound1_14->RegisterPacket(ProgramStructureBlock::PACKET_ORDINAL, 0x28);
    serverbound1_14->RegisterPacket(EditSign::PACKET_ORDINAL, 0x29);
    serverbound1_14->RegisterPacket(SwingArm::PACKET_ORDINAL, 0x2A);
    serverbound1_14->RegisterPacket(Spectate::PACKET_ORDINAL, 0x2B);
    serverbound1_14->RegisterPacket(PlaceBlock::PACKET_ORDINAL, 0x2C);
    serverbound1_14->RegisterPacket(UseItem::PACKET_ORDINAL, 0x2D);

    VersionRegistry* serverbound1_15 = serverboundRegistry + ProtocolVersion::MINECRAFT_1_15.GetPacketIDOrdinal();
    serverbound1_15->RegisterPacket(ConfirmTeleport::PACKET_ORDINAL, 0x00);
    serverbound1_15->RegisterPacket(BlockTagQueryRequest::PACKET_ORDINAL, 0x01);
    serverbound1_15->RegisterPacket(ClientChangeDifficulty::PACKET_ORDINAL, 0x02);
    serverbound1_15->RegisterPacket(LegacyChat::PACKET_ORDINAL, 0x03);
    serverbound1_15->RegisterPacket(ClientAction::PACKET_ORDINAL, 0x04);
    serverbound1_15->RegisterPacket(ClientSettings::PACKET_ORDINAL, 0x05);
    serverbound1_15->RegisterPacket(CommandSuggestionRequest::PACKET_ORDINAL, 0x06);
    serverbound1_15->RegisterPacket(ConfirmTransaction::PACKET_ORDINAL, 0x07);
    serverbound1_15->RegisterPacket(ClickInventoryButton::PACKET_ORDINAL, 0x08);
    serverbound1_15->RegisterPacket(ClickSlot::PACKET_ORDINAL, 0x09);
    serverbound1_15->RegisterPacket(CloseInventory::PACKET_ORDINAL, 0x0A);
    serverbound1_15->RegisterPacket(PluginMessage::PACKET_ORDINAL, 0x0B);
    serverbound1_15->RegisterPacket(EditBook::PACKET_ORDINAL, 0x0C);
    serverbound1_15->RegisterPacket(TagQueryRequest::PACKET_ORDINAL, 0x0D);
    serverbound1_15->RegisterPacket(EntityInteract::PACKET_ORDINAL, 0x0E);
    serverbound1_15->RegisterPacket(KeepAlive::PACKET_ORDINAL, 0x0F);
    serverbound1_15->RegisterPacket(LockDifficulty::PACKET_ORDINAL, 0x10);
    serverbound1_15->RegisterPacket(MoveGroundOnly::PACKET_ORDINAL, 0x11);
    serverbound1_15->RegisterPacket(MovePositionOnly::PACKET_ORDINAL, 0x12);
    serverbound1_15->RegisterPacket(Move::PACKET_ORDINAL, 0x13);
    serverbound1_15->RegisterPacket(MoveRotationOnly::PACKET_ORDINAL, 0x14);
    serverbound1_15->RegisterPacket(MoveVehicle::PACKET_ORDINAL, 0x15);
    serverbound1_15->RegisterPacket(BoatPaddle::PACKET_ORDINAL, 0x16);
    serverbound1_15->RegisterPacket(PickItem::PACKET_ORDINAL, 0x17);
    serverbound1_15->RegisterPacket(CraftRecipeRequest::PACKET_ORDINAL, 0x18);
    serverbound1_15->RegisterPacket(PlayerAbilities::PACKET_ORDINAL, 0x19);
    serverbound1_15->RegisterPacket(Digging::PACKET_ORDINAL, 0x1A);
    serverbound1_15->RegisterPacket(EntityAction::PACKET_ORDINAL, 0x1B);
    serverbound1_15->RegisterPacket(PlayerInput::PACKET_ORDINAL, 0x1C);
    serverbound1_15->RegisterPacket(LegacyRecipeBook::PACKET_ORDINAL, 0x1D);
    serverbound1_15->RegisterPacket(RenameItem::PACKET_ORDINAL, 0x1E);
    serverbound1_15->RegisterPacket(ResourcePackResponse::PACKET_ORDINAL, 0x1F);
    serverbound1_15->RegisterPacket(SelectAdvancementsTab::PACKET_ORDINAL, 0x20);
    serverbound1_15->RegisterPacket(SelectTrade::PACKET_ORDINAL, 0x21);
    serverbound1_15->RegisterPacket(BeaconEffect::PACKET_ORDINAL, 0x22);
    serverbound1_15->RegisterPacket(HeldSlot::PACKET_ORDINAL, 0x23);
    serverbound1_15->RegisterPacket(ProgramCommandBlock::PACKET_ORDINAL, 0x24);
    serverbound1_15->RegisterPacket(ProgramCommandBlockMinecart::PACKET_ORDINAL, 0x25);
    serverbound1_15->RegisterPacket(CreativeSlot::PACKET_ORDINAL, 0x26);
    serverbound1_15->RegisterPacket(ProgramJigsawBlock::PACKET_ORDINAL, 0x27);
    serverbound1_15->RegisterPacket(ProgramStructureBlock::PACKET_ORDINAL, 0x28);
    serverbound1_15->RegisterPacket(EditSign::PACKET_ORDINAL, 0x29);
    serverbound1_15->RegisterPacket(SwingArm::PACKET_ORDINAL, 0x2A);
    serverbound1_15->RegisterPacket(Spectate::PACKET_ORDINAL, 0x2B);
    serverbound1_15->RegisterPacket(PlaceBlock::PACKET_ORDINAL, 0x2C);
    serverbound1_15->RegisterPacket(UseItem::PACKET_ORDINAL, 0x2D);

    // VersionRegistry* serverbound1_16 = serverboundRegistry + ProtocolVersion::MINECRAFT_1_16.GetPacketIDOrdinal();
    // serverbound1_16->RegisterPacket(ConfirmTeleport::PACKET_ORDINAL, 0x00);
    // serverbound1_16->RegisterPacket(BlockTagQueryRequest::PACKET_ORDINAL, 0x01);
    // serverbound1_16->RegisterPacket(ClientChangeDifficulty::PACKET_ORDINAL, 0x02);
    // serverbound1_16->RegisterPacket(LegacyChat::PACKET_ORDINAL, 0x03);
    // serverbound1_16->RegisterPacket(ClientAction::PACKET_ORDINAL, 0x04);
    // serverbound1_16->RegisterPacket(ClientSettings::PACKET_ORDINAL, 0x05);
    // serverbound1_16->RegisterPacket(CommandSuggestionRequest::PACKET_ORDINAL, 0x06);
    // serverbound1_16->RegisterPacket(ConfirmTransaction::PACKET_ORDINAL, 0x07);
    // serverbound1_16->RegisterPacket(ClickInventoryButton::PACKET_ORDINAL, 0x08);
    // serverbound1_16->RegisterPacket(ClickSlot::PACKET_ORDINAL, 0x09);
    // serverbound1_16->RegisterPacket(CloseInventory::PACKET_ORDINAL, 0x0A);
    // serverbound1_16->RegisterPacket(PluginMessage::PACKET_ORDINAL, 0x0B);
    // serverbound1_16->RegisterPacket(EditBook::PACKET_ORDINAL, 0x0C);
    // serverbound1_16->RegisterPacket(TagQueryRequest::PACKET_ORDINAL, 0x0D);
    // serverbound1_16->RegisterPacket(EntityInteract::PACKET_ORDINAL, 0x0E);
    // serverbound1_16->RegisterPacket(GenerateStructure::PACKET_ORDINAL, 0x0F);
    // serverbound1_16->RegisterPacket(KeepAlive::PACKET_ORDINAL, 0x10);
    // serverbound1_16->RegisterPacket(LockDifficulty::PACKET_ORDINAL, 0x11);
    // serverbound1_16->RegisterPacket(MovePositionOnly::PACKET_ORDINAL, 0x12);
    // serverbound1_16->RegisterPacket(Move::PACKET_ORDINAL, 0x13);
    // serverbound1_16->RegisterPacket(MoveRotationOnly::PACKET_ORDINAL, 0x14);
    // serverbound1_16->RegisterPacket(MoveVehicle::PACKET_ORDINAL, 0x15);
    // serverbound1_16->RegisterPacket(MoveGroundOnly::PACKET_ORDINAL, 0x16);
    // serverbound1_16->RegisterPacket(BoatPaddle::PACKET_ORDINAL, 0x17);
    // serverbound1_16->RegisterPacket(PickItem::PACKET_ORDINAL, 0x18);
    // serverbound1_16->RegisterPacket(CraftRecipeRequest::PACKET_ORDINAL, 0x19);
    // serverbound1_16->RegisterPacket(PlayerAbilities::PACKET_ORDINAL, 0x1A);
    // serverbound1_16->RegisterPacket(Digging::PACKET_ORDINAL, 0x1B);
    // serverbound1_16->RegisterPacket(EntityAction::PACKET_ORDINAL, 0x1C);
    // serverbound1_16->RegisterPacket(PlayerInput::PACKET_ORDINAL, 0x1D);
    // serverbound1_16->RegisterPacket(LegacyRecipeBook::PACKET_ORDINAL, 0x1E);
    // serverbound1_16->RegisterPacket(RenameItem::PACKET_ORDINAL, 0x1F);
    // serverbound1_16->RegisterPacket(ResourcePackResponse::PACKET_ORDINAL, 0x20);
    // serverbound1_16->RegisterPacket(SelectAdvancementsTab::PACKET_ORDINAL, 0x21);
    // serverbound1_16->RegisterPacket(SelectTrade::PACKET_ORDINAL, 0x22);
    // serverbound1_16->RegisterPacket(BeaconEffect::PACKET_ORDINAL, 0x23);
    // serverbound1_16->RegisterPacket(HeldSlot::PACKET_ORDINAL, 0x24);
    // serverbound1_16->RegisterPacket(ProgramCommandBlock::PACKET_ORDINAL, 0x25);
    // serverbound1_16->RegisterPacket(ProgramCommandBlockMinecart::PACKET_ORDINAL, 0x26);
    // serverbound1_16->RegisterPacket(CreativeSlot::PACKET_ORDINAL, 0x27);
    // serverbound1_16->RegisterPacket(ProgramJigsawBlock::PACKET_ORDINAL, 0x28);
    // serverbound1_16->RegisterPacket(ProgramStructureBlock::PACKET_ORDINAL, 0x29);
    // serverbound1_16->RegisterPacket(EditSign::PACKET_ORDINAL, 0x2A);
    // serverbound1_16->RegisterPacket(SwingArm::PACKET_ORDINAL, 0x2B);
    // serverbound1_16->RegisterPacket(Spectate::PACKET_ORDINAL, 0x2C);
    // serverbound1_16->RegisterPacket(PlaceBlock::PACKET_ORDINAL, 0x2D);
    // serverbound1_16->RegisterPacket(UseItem::PACKET_ORDINAL, 0x2E);

    VersionRegistry* serverbound1_16_2 = serverboundRegistry + ProtocolVersion::MINECRAFT_1_16_2.GetPacketIDOrdinal();
    serverbound1_16_2->RegisterPacket(ConfirmTeleport::PACKET_ORDINAL, 0x00);
    serverbound1_16_2->RegisterPacket(BlockTagQueryRequest::PACKET_ORDINAL, 0x01);
    serverbound1_16_2->RegisterPacket(ClientChangeDifficulty::PACKET_ORDINAL, 0x02);
    serverbound1_16_2->RegisterPacket(LegacyChat::PACKET_ORDINAL, 0x03);
    serverbound1_16_2->RegisterPacket(ClientAction::PACKET_ORDINAL, 0x04);
    serverbound1_16_2->RegisterPacket(ClientSettings::PACKET_ORDINAL, 0x05);
    serverbound1_16_2->RegisterPacket(CommandSuggestionRequest::PACKET_ORDINAL, 0x06);
    serverbound1_16_2->RegisterPacket(ConfirmTransaction::PACKET_ORDINAL, 0x07);
    serverbound1_16_2->RegisterPacket(ClickInventoryButton::PACKET_ORDINAL, 0x08);
    serverbound1_16_2->RegisterPacket(ClickSlot::PACKET_ORDINAL, 0x09);
    serverbound1_16_2->RegisterPacket(CloseInventory::PACKET_ORDINAL, 0x0A);
    serverbound1_16_2->RegisterPacket(PluginMessage::PACKET_ORDINAL, 0x0B);
    serverbound1_16_2->RegisterPacket(EditBook::PACKET_ORDINAL, 0x0C);
    serverbound1_16_2->RegisterPacket(TagQueryRequest::PACKET_ORDINAL, 0x0D);
    serverbound1_16_2->RegisterPacket(EntityInteract::PACKET_ORDINAL, 0x0E);
    serverbound1_16_2->RegisterPacket(GenerateStructure::PACKET_ORDINAL, 0x0F);
    serverbound1_16_2->RegisterPacket(KeepAlive::PACKET_ORDINAL, 0x10);
    serverbound1_16_2->RegisterPacket(LockDifficulty::PACKET_ORDINAL, 0x11);
    serverbound1_16_2->RegisterPacket(MovePositionOnly::PACKET_ORDINAL, 0x12);
    serverbound1_16_2->RegisterPacket(Move::PACKET_ORDINAL, 0x13);
    serverbound1_16_2->RegisterPacket(MoveRotationOnly::PACKET_ORDINAL, 0x14);
    serverbound1_16_2->RegisterPacket(MoveVehicle::PACKET_ORDINAL, 0x15);
    serverbound1_16_2->RegisterPacket(MoveGroundOnly::PACKET_ORDINAL, 0x16);
    serverbound1_16_2->RegisterPacket(BoatPaddle::PACKET_ORDINAL, 0x17);
    serverbound1_16_2->RegisterPacket(PickItem::PACKET_ORDINAL, 0x18);
    serverbound1_16_2->RegisterPacket(CraftRecipeRequest::PACKET_ORDINAL, 0x19);
    serverbound1_16_2->RegisterPacket(PlayerAbilities::PACKET_ORDINAL, 0x1A);
    serverbound1_16_2->RegisterPacket(Digging::PACKET_ORDINAL, 0x1B);
    serverbound1_16_2->RegisterPacket(EntityAction::PACKET_ORDINAL, 0x1C);
    serverbound1_16_2->RegisterPacket(PlayerInput::PACKET_ORDINAL, 0x1D);
    serverbound1_16_2->RegisterPacket(SeenRecipe::PACKET_ORDINAL, 0x1E);
    serverbound1_16_2->RegisterPacket(ChangeRecipeBookSettings::PACKET_ORDINAL, 0x1F);
    serverbound1_16_2->RegisterPacket(RenameItem::PACKET_ORDINAL, 0x20);
    serverbound1_16_2->RegisterPacket(ResourcePackResponse::PACKET_ORDINAL, 0x21);
    serverbound1_16_2->RegisterPacket(SelectAdvancementsTab::PACKET_ORDINAL, 0x22);
    serverbound1_16_2->RegisterPacket(SelectTrade::PACKET_ORDINAL, 0x23);
    serverbound1_16_2->RegisterPacket(BeaconEffect::PACKET_ORDINAL, 0x24);
    serverbound1_16_2->RegisterPacket(HeldSlot::PACKET_ORDINAL, 0x25);
    serverbound1_16_2->RegisterPacket(ProgramCommandBlock::PACKET_ORDINAL, 0x26);
    serverbound1_16_2->RegisterPacket(ProgramCommandBlockMinecart::PACKET_ORDINAL, 0x27);
    serverbound1_16_2->RegisterPacket(CreativeSlot::PACKET_ORDINAL, 0x28);
    serverbound1_16_2->RegisterPacket(ProgramJigsawBlock::PACKET_ORDINAL, 0x29);
    serverbound1_16_2->RegisterPacket(ProgramStructureBlock::PACKET_ORDINAL, 0x2A);
    serverbound1_16_2->RegisterPacket(EditSign::PACKET_ORDINAL, 0x2B);
    serverbound1_16_2->RegisterPacket(SwingArm::PACKET_ORDINAL, 0x2C);
    serverbound1_16_2->RegisterPacket(Spectate::PACKET_ORDINAL, 0x2D);
    serverbound1_16_2->RegisterPacket(PlaceBlock::PACKET_ORDINAL, 0x2E);
    serverbound1_16_2->RegisterPacket(UseItem::PACKET_ORDINAL, 0x2F);

    VersionRegistry* serverbound1_17 = serverboundRegistry + ProtocolVersion::MINECRAFT_1_17.GetPacketIDOrdinal();
    serverbound1_17->RegisterPacket(ConfirmTeleport::PACKET_ORDINAL, 0x00);
    serverbound1_17->RegisterPacket(BlockTagQueryRequest::PACKET_ORDINAL, 0x01);
    serverbound1_17->RegisterPacket(ClientChangeDifficulty::PACKET_ORDINAL, 0x02);
    serverbound1_17->RegisterPacket(LegacyChat::PACKET_ORDINAL, 0x03);
    serverbound1_17->RegisterPacket(ClientAction::PACKET_ORDINAL, 0x04);
    serverbound1_17->RegisterPacket(ClientSettings::PACKET_ORDINAL, 0x05);
    serverbound1_17->RegisterPacket(CommandSuggestionRequest::PACKET_ORDINAL, 0x06);
    //    serverbound1_17->RegisterPacket(ConfirmTransaction::PACKET_ORDINAL, 0x07);
    serverbound1_17->RegisterPacket(ClickInventoryButton::PACKET_ORDINAL, 0x07);
    serverbound1_17->RegisterPacket(ClickSlot::PACKET_ORDINAL, 0x08);
    serverbound1_17->RegisterPacket(CloseInventory::PACKET_ORDINAL, 0x09);
    serverbound1_17->RegisterPacket(PluginMessage::PACKET_ORDINAL, 0x0A);
    serverbound1_17->RegisterPacket(EditBook::PACKET_ORDINAL, 0x0B);
    serverbound1_17->RegisterPacket(TagQueryRequest::PACKET_ORDINAL, 0x0C);
    serverbound1_17->RegisterPacket(EntityInteract::PACKET_ORDINAL, 0x0D);
    serverbound1_17->RegisterPacket(GenerateStructure::PACKET_ORDINAL, 0x0E);
    serverbound1_17->RegisterPacket(KeepAlive::PACKET_ORDINAL, 0x0F); ///
    serverbound1_17->RegisterPacket(LockDifficulty::PACKET_ORDINAL, 0x10);
    serverbound1_17->RegisterPacket(MovePositionOnly::PACKET_ORDINAL, 0x11);
    serverbound1_17->RegisterPacket(Move::PACKET_ORDINAL, 0x12);
    serverbound1_17->RegisterPacket(MoveRotationOnly::PACKET_ORDINAL, 0x13);
    serverbound1_17->RegisterPacket(MoveGroundOnly::PACKET_ORDINAL, 0x14);
    serverbound1_17->RegisterPacket(MoveVehicle::PACKET_ORDINAL, 0x15);
    serverbound1_17->RegisterPacket(BoatPaddle::PACKET_ORDINAL, 0x16);
    serverbound1_17->RegisterPacket(PickItem::PACKET_ORDINAL, 0x17);
    serverbound1_17->RegisterPacket(CraftRecipeRequest::PACKET_ORDINAL, 0x18);
    serverbound1_17->RegisterPacket(PlayerAbilities::PACKET_ORDINAL, 0x19);
    serverbound1_17->RegisterPacket(Digging::PACKET_ORDINAL, 0x1A);
    serverbound1_17->RegisterPacket(EntityAction::PACKET_ORDINAL, 0x1B);
    serverbound1_17->RegisterPacket(PlayerInput::PACKET_ORDINAL, 0x1C);
    serverbound1_17->RegisterPacket(Ping::PACKET_ORDINAL, 0x1D);
    serverbound1_17->RegisterPacket(SeenRecipe::PACKET_ORDINAL, 0x1E);
    serverbound1_17->RegisterPacket(ChangeRecipeBookSettings::PACKET_ORDINAL, 0x1F);
    serverbound1_17->RegisterPacket(RenameItem::PACKET_ORDINAL, 0x20);
    serverbound1_17->RegisterPacket(ResourcePackResponse::PACKET_ORDINAL, 0x21);
    serverbound1_17->RegisterPacket(SelectAdvancementsTab::PACKET_ORDINAL, 0x22);
    serverbound1_17->RegisterPacket(SelectTrade::PACKET_ORDINAL, 0x23);
    serverbound1_17->RegisterPacket(BeaconEffect::PACKET_ORDINAL, 0x24);
    serverbound1_17->RegisterPacket(HeldSlot::PACKET_ORDINAL, 0x25);
    serverbound1_17->RegisterPacket(ProgramCommandBlock::PACKET_ORDINAL, 0x26);
    serverbound1_17->RegisterPacket(ProgramCommandBlockMinecart::PACKET_ORDINAL, 0x27);
    serverbound1_17->RegisterPacket(CreativeSlot::PACKET_ORDINAL, 0x28);
    serverbound1_17->RegisterPacket(ProgramJigsawBlock::PACKET_ORDINAL, 0x29);
    serverbound1_17->RegisterPacket(ProgramStructureBlock::PACKET_ORDINAL, 0x2A);
    serverbound1_17->RegisterPacket(EditSign::PACKET_ORDINAL, 0x2B);
    serverbound1_17->RegisterPacket(SwingArm::PACKET_ORDINAL, 0x2C);
    serverbound1_17->RegisterPacket(Spectate::PACKET_ORDINAL, 0x2D);
    serverbound1_17->RegisterPacket(PlaceBlock::PACKET_ORDINAL, 0x2E);
    serverbound1_17->RegisterPacket(UseItem::PACKET_ORDINAL, 0x2F);

    return {DirectionRegistry(clientboundRegistry), DirectionRegistry(serverboundRegistry)};
  }

  const PacketRegistry BuiltInPacketRegistry::HANDSHAKE = GetHandshakeRegistry();
  const PacketRegistry BuiltInPacketRegistry::STATUS = GetStatusRegistry();
  const PacketRegistry BuiltInPacketRegistry::LOGIN = GetLoginRegistry();
  const PacketRegistry BuiltInPacketRegistry::PLAY = GetPlayRegistry();
}