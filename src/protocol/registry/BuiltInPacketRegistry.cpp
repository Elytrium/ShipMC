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
#include "../packets/play/ServerChatPreview.hpp"
#include "../packets/play/ServerData.hpp"
#include "../packets/play/ServerPlayerAbilities.hpp"
#include "../packets/play/ServerPlayerChat.hpp"
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
    VersionRegistry* serverboundRegistry = DirectionRegistry::NewVersionRegistry();

    for (uint32_t i = ProtocolVersion::MINIMUM_VERSION.GetPacketIDOrdinal(); i <= ProtocolVersion::MAXIMUM_VERSION.GetPacketIDOrdinal(); ++i) {
      serverboundRegistry[i].Register(Handshake::PACKET_ORDINAL, 0x00);
    }

    auto* serverbound = new DirectionRegistry(serverboundRegistry);

    serverbound->RegisterPacketConstructor(Handshake::PACKET_ORDINAL, CreateConstructor<Handshake>());

    return {nullptr, serverbound};
  }

  PacketRegistry GetStatusRegistry() {
    VersionRegistry* clientboundRegistry = DirectionRegistry::NewVersionRegistry();

    for (uint32_t i = ProtocolVersion::MINIMUM_VERSION.GetPacketIDOrdinal(); i <= ProtocolVersion::MAXIMUM_VERSION.GetPacketIDOrdinal(); ++i) {
      clientboundRegistry[i].Register(StatusResponse::PACKET_ORDINAL, 0x00);
      clientboundRegistry[i].Register(StatusPing::PACKET_ORDINAL, 0x01);
    }

    VersionRegistry* serverboundRegistry = DirectionRegistry::NewVersionRegistry();

    for (uint32_t i = ProtocolVersion::MINIMUM_VERSION.GetPacketIDOrdinal(); i <= ProtocolVersion::MAXIMUM_VERSION.GetPacketIDOrdinal(); ++i) {
      serverboundRegistry[i].Register(StatusRequest::PACKET_ORDINAL, 0x00);
      serverboundRegistry[i].Register(StatusPing::PACKET_ORDINAL, 0x01);
    }

    auto* clientbound = new DirectionRegistry(clientboundRegistry);

    clientbound->RegisterPacketConstructor(StatusResponse::PACKET_ORDINAL, CreateConstructor<StatusResponse>(std::string {}));
    clientbound->RegisterPacketConstructor(StatusPing::PACKET_ORDINAL, CreateConstructor<StatusPing>(0));

    auto* serverbound = new DirectionRegistry(serverboundRegistry);

    serverbound->RegisterPacketConstructor(StatusRequest::PACKET_ORDINAL, CreateConstructor<StatusRequest>());
    serverbound->RegisterPacketConstructor(StatusPing::PACKET_ORDINAL, CreateConstructor<StatusPing>(0));

    return {clientbound, serverbound};
  }

  PacketRegistry GetLoginRegistry() {
    VersionRegistry* clientboundRegistry = DirectionRegistry::NewVersionRegistry();

    for (uint32_t i = ProtocolVersion::MINIMUM_VERSION.GetPacketIDOrdinal(); i <= ProtocolVersion::MAXIMUM_VERSION.GetPacketIDOrdinal(); ++i) {
      clientboundRegistry[i].Register(Disconnect::PACKET_ORDINAL, 0x00);
      clientboundRegistry[i].Register(EncryptionRequest::PACKET_ORDINAL, 0x01);
      clientboundRegistry[i].Register(LoginSuccess::PACKET_ORDINAL, 0x02);
      clientboundRegistry[i].Register(SetCompression::PACKET_ORDINAL, 0x03);
      clientboundRegistry[i].Register(LoginPluginMessage::PACKET_ORDINAL, 0x04);
    }

    VersionRegistry* serverboundRegistry = DirectionRegistry::NewVersionRegistry();

    for (uint32_t i = ProtocolVersion::MINIMUM_VERSION.GetPacketIDOrdinal(); i <= ProtocolVersion::MAXIMUM_VERSION.GetPacketIDOrdinal(); ++i) {
      serverboundRegistry[i].Register(LoginStart::PACKET_ORDINAL, 0x00);
      serverboundRegistry[i].Register(EncryptionResponse::PACKET_ORDINAL, 0x01);
      serverboundRegistry[i].Register(LoginPluginResponse::PACKET_ORDINAL, 0x02);
    }

    auto* clientbound = new DirectionRegistry(clientboundRegistry);

    clientbound->RegisterPacketConstructor(Disconnect::PACKET_ORDINAL, CreateConstructor<Disconnect>(std::string {}));
    clientbound->RegisterPacketConstructor(EncryptionRequest::PACKET_ORDINAL, CreateConstructor<EncryptionRequest>());
    clientbound->RegisterPacketConstructor(
      LoginSuccess::PACKET_ORDINAL, CreateConstructor<LoginSuccess>(UUID {}, std::string {}, std::vector<GameProfileProperty> {}));
    clientbound->RegisterPacketConstructor(SetCompression::PACKET_ORDINAL, CreateConstructor<SetCompression>(0));
    clientbound->RegisterPacketConstructor(LoginPluginMessage::PACKET_ORDINAL, CreateConstructor<LoginPluginMessage>());

    auto* serverbound = new DirectionRegistry(serverboundRegistry);

    serverbound->RegisterPacketConstructor(LoginStart::PACKET_ORDINAL, CreateConstructor<LoginStart>(std::string {}, false, 0, 0, nullptr, 0, nullptr));
    serverbound->RegisterPacketConstructor(EncryptionResponse::PACKET_ORDINAL, CreateConstructor<EncryptionResponse>());
    serverbound->RegisterPacketConstructor(LoginPluginResponse::PACKET_ORDINAL, CreateConstructor<LoginPluginResponse>());

    return {clientbound, serverbound};
  }

  PacketRegistry GetPlayRegistry() {
    VersionRegistry* clientboundRegistry = DirectionRegistry::NewVersionRegistry();

    VersionRegistry* clientbound1_12_2 = clientboundRegistry + ProtocolVersion::MINECRAFT_1_12_2.GetPacketIDOrdinal();
    clientbound1_12_2->Register(SpawnEntity::PACKET_ORDINAL, 0x00);
    clientbound1_12_2->Register(SpawnExperienceOrb::PACKET_ORDINAL, 0x01);
    clientbound1_12_2->Register(SpawnThunderbolt::PACKET_ORDINAL, 0x02);
    clientbound1_12_2->Register(SpawnEntity::PACKET_ORDINAL, 0x03);
    clientbound1_12_2->Register(SpawnPainting::PACKET_ORDINAL, 0x04);
    clientbound1_12_2->Register(SpawnPlayer::PACKET_ORDINAL, 0x05);
    clientbound1_12_2->Register(EntityAnimation::PACKET_ORDINAL, 0x06);
    clientbound1_12_2->Register(AwardStatistics::PACKET_ORDINAL, 0x07);
    clientbound1_12_2->Register(BlockDestroyStage::PACKET_ORDINAL, 0x08);
    clientbound1_12_2->Register(BlockEntityData::PACKET_ORDINAL, 0x09);
    clientbound1_12_2->Register(BlockAction::PACKET_ORDINAL, 0x0A);
    clientbound1_12_2->Register(BlockUpdate::PACKET_ORDINAL, 0x0B);
    clientbound1_12_2->Register(BossBar::PACKET_ORDINAL, 0x0C);
    clientbound1_12_2->Register(ServerChangeDifficulty::PACKET_ORDINAL, 0x0D);
    clientbound1_12_2->Register(CommandSuggestionResponse::PACKET_ORDINAL, 0x0E);
    clientbound1_12_2->Register(LegacyChat::PACKET_ORDINAL, 0x0F);
    clientbound1_12_2->Register(SectionBlocks::PACKET_ORDINAL, 0x10);
    clientbound1_12_2->Register(ConfirmTransaction::PACKET_ORDINAL, 0x11);
    clientbound1_12_2->Register(CloseInventory::PACKET_ORDINAL, 0x12);
    clientbound1_12_2->Register(OpenInventory::PACKET_ORDINAL, 0x13);
    clientbound1_12_2->Register(InventoryContent::PACKET_ORDINAL, 0x14);
    clientbound1_12_2->Register(InventoryProperty::PACKET_ORDINAL, 0x15);
    clientbound1_12_2->Register(InventorySlot::PACKET_ORDINAL, 0x16);
    clientbound1_12_2->Register(Cooldown::PACKET_ORDINAL, 0x17);
    clientbound1_12_2->Register(PluginMessage::PACKET_ORDINAL, 0x18);
    clientbound1_12_2->Register(CustomSoundEffect::PACKET_ORDINAL, 0x19);
    clientbound1_12_2->Register(Disconnect::PACKET_ORDINAL, 0x1A);
    clientbound1_12_2->Register(EntityAnimation::PACKET_ORDINAL, 0x1B);
    clientbound1_12_2->Register(Explosion::PACKET_ORDINAL, 0x1C);
    clientbound1_12_2->Register(UnloadChunk::PACKET_ORDINAL, 0x1D);
    clientbound1_12_2->Register(GameEvent::PACKET_ORDINAL, 0x1E);
    clientbound1_12_2->Register(KeepAlive::PACKET_ORDINAL, 0x1F);
    clientbound1_12_2->Register(ChunkData::PACKET_ORDINAL, 0x20);
    clientbound1_12_2->Register(WorldEvent::PACKET_ORDINAL, 0x21);
    clientbound1_12_2->Register(Particle::PACKET_ORDINAL, 0x22);
    clientbound1_12_2->Register(JoinGame::PACKET_ORDINAL, 0x23);
    clientbound1_12_2->Register(MapData::PACKET_ORDINAL, 0x24);
    clientbound1_12_2->Register(EntityNotMoved::PACKET_ORDINAL, 0x25);
    clientbound1_12_2->Register(EntityPosition::PACKET_ORDINAL, 0x26);
    clientbound1_12_2->Register(EntityPositionAndRotation::PACKET_ORDINAL, 0x27);
    clientbound1_12_2->Register(EntityRotation::PACKET_ORDINAL, 0x28);
    clientbound1_12_2->Register(MoveVehicle::PACKET_ORDINAL, 0x29);
    clientbound1_12_2->Register(OpenSignEditor::PACKET_ORDINAL, 0x2A);
    clientbound1_12_2->Register(LegacyCraftRecipeResponse::PACKET_ORDINAL, 0x2B);
    clientbound1_12_2->Register(ServerPlayerAbilities::PACKET_ORDINAL, 0x2C);
    clientbound1_12_2->Register(CombatEvent::PACKET_ORDINAL, 0x2D);
    clientbound1_12_2->Register(PlayerListItem::PACKET_ORDINAL, 0x2E);
    clientbound1_12_2->Register(PositionRotation::PACKET_ORDINAL, 0x2F);
    clientbound1_12_2->Register(UseBed::PACKET_ORDINAL, 0x30);
    clientbound1_12_2->Register(UnlockRecipes::PACKET_ORDINAL, 0x31);
    clientbound1_12_2->Register(EntityRemove::PACKET_ORDINAL, 0x32);
    clientbound1_12_2->Register(EntityEffectRemove::PACKET_ORDINAL, 0x33);
    clientbound1_12_2->Register(ResourcePackRequest::PACKET_ORDINAL, 0x34);
    clientbound1_12_2->Register(Respawn::PACKET_ORDINAL, 0x35);
    clientbound1_12_2->Register(EntityLookAt::PACKET_ORDINAL, 0x36);
    clientbound1_12_2->Register(SelectAdvancementsTab::PACKET_ORDINAL, 0x37);
    clientbound1_12_2->Register(LegacyWorldBorder::PACKET_ORDINAL, 0x38);
    clientbound1_12_2->Register(Camera::PACKET_ORDINAL, 0x39);
    clientbound1_12_2->Register(HeldSlot::PACKET_ORDINAL, 0x3A);
    clientbound1_12_2->Register(DisplayObjective::PACKET_ORDINAL, 0x3B);
    clientbound1_12_2->Register(EntityMetadata::PACKET_ORDINAL, 0x3C);
    clientbound1_12_2->Register(LeadEntities::PACKET_ORDINAL, 0x3D);
    clientbound1_12_2->Register(EntityVelocity::PACKET_ORDINAL, 0x3E);
    clientbound1_12_2->Register(EntityEquipment::PACKET_ORDINAL, 0x3F);
    clientbound1_12_2->Register(Experience::PACKET_ORDINAL, 0x40);
    clientbound1_12_2->Register(Health::PACKET_ORDINAL, 0x41);
    clientbound1_12_2->Register(Objectives::PACKET_ORDINAL, 0x42);
    clientbound1_12_2->Register(Passengers::PACKET_ORDINAL, 0x43);
    clientbound1_12_2->Register(Teams::PACKET_ORDINAL, 0x44);
    clientbound1_12_2->Register(Score::PACKET_ORDINAL, 0x45);
    clientbound1_12_2->Register(DefaultSpawnPosition::PACKET_ORDINAL, 0x46);
    clientbound1_12_2->Register(WorldTime::PACKET_ORDINAL, 0x47);
    clientbound1_12_2->Register(LegacyTitle::PACKET_ORDINAL, 0x48);
    clientbound1_12_2->Register(HardcodedSoundEffect::PACKET_ORDINAL, 0x49);
    clientbound1_12_2->Register(TabHeaderFooter::PACKET_ORDINAL, 0x4A);
    clientbound1_12_2->Register(PickupItem::PACKET_ORDINAL, 0x4B);
    clientbound1_12_2->Register(EntityTeleport::PACKET_ORDINAL, 0x4C);
    clientbound1_12_2->Register(Advancements::PACKET_ORDINAL, 0x4D);
    clientbound1_12_2->Register(EntityProperties::PACKET_ORDINAL, 0x4E);
    clientbound1_12_2->Register(EntityEffect::PACKET_ORDINAL, 0x4F);

    VersionRegistry* clientbound1_13 = clientboundRegistry + ProtocolVersion::MINECRAFT_1_13.GetPacketIDOrdinal();
    clientbound1_13->Register(SpawnEntity::PACKET_ORDINAL, 0x00);
    clientbound1_13->Register(SpawnExperienceOrb::PACKET_ORDINAL, 0x01);
    clientbound1_13->Register(SpawnThunderbolt::PACKET_ORDINAL, 0x02);
    clientbound1_13->Register(SpawnEntity::PACKET_ORDINAL, 0x03);
    clientbound1_13->Register(SpawnPainting::PACKET_ORDINAL, 0x04);
    clientbound1_13->Register(SpawnPlayer::PACKET_ORDINAL, 0x05);
    clientbound1_13->Register(EntityAnimation::PACKET_ORDINAL, 0x06);
    clientbound1_13->Register(AwardStatistics::PACKET_ORDINAL, 0x07);
    clientbound1_13->Register(BlockDestroyStage::PACKET_ORDINAL, 0x08);
    clientbound1_13->Register(BlockEntityData::PACKET_ORDINAL, 0x09);
    clientbound1_13->Register(BlockAction::PACKET_ORDINAL, 0x0A);
    clientbound1_13->Register(BlockUpdate::PACKET_ORDINAL, 0x0B);
    clientbound1_13->Register(BossBar::PACKET_ORDINAL, 0x0C);
    clientbound1_13->Register(ServerChangeDifficulty::PACKET_ORDINAL, 0x0D);
    clientbound1_13->Register(LegacyChat::PACKET_ORDINAL, 0x0E);
    clientbound1_13->Register(SectionBlocks::PACKET_ORDINAL, 0x0F);
    clientbound1_13->Register(CommandSuggestionResponse::PACKET_ORDINAL, 0x10);
    clientbound1_13->Register(DeclareCommands::PACKET_ORDINAL, 0x11);
    clientbound1_13->Register(ConfirmTransaction::PACKET_ORDINAL, 0x12);
    clientbound1_13->Register(CloseInventory::PACKET_ORDINAL, 0x13);
    clientbound1_13->Register(OpenInventory::PACKET_ORDINAL, 0x14);
    clientbound1_13->Register(InventoryContent::PACKET_ORDINAL, 0x15);
    clientbound1_13->Register(InventoryProperty::PACKET_ORDINAL, 0x16);
    clientbound1_13->Register(InventorySlot::PACKET_ORDINAL, 0x17);
    clientbound1_13->Register(Cooldown::PACKET_ORDINAL, 0x18);
    clientbound1_13->Register(PluginMessage::PACKET_ORDINAL, 0x19);
    clientbound1_13->Register(CustomSoundEffect::PACKET_ORDINAL, 0x1A);
    clientbound1_13->Register(Disconnect::PACKET_ORDINAL, 0x1B);
    clientbound1_13->Register(EntityAnimation::PACKET_ORDINAL, 0x1C);
    clientbound1_13->Register(TagQueryResponse::PACKET_ORDINAL, 0x1D);
    clientbound1_13->Register(Explosion::PACKET_ORDINAL, 0x1E);
    clientbound1_13->Register(UnloadChunk::PACKET_ORDINAL, 0x1F);
    clientbound1_13->Register(GameEvent::PACKET_ORDINAL, 0x20);
    clientbound1_13->Register(KeepAlive::PACKET_ORDINAL, 0x21);
    clientbound1_13->Register(ChunkData::PACKET_ORDINAL, 0x22);
    clientbound1_13->Register(WorldEvent::PACKET_ORDINAL, 0x23);
    clientbound1_13->Register(Particle::PACKET_ORDINAL, 0x24);
    clientbound1_13->Register(JoinGame::PACKET_ORDINAL, 0x25);
    clientbound1_13->Register(MapData::PACKET_ORDINAL, 0x26);
    clientbound1_13->Register(EntityNotMoved::PACKET_ORDINAL, 0x27);
    clientbound1_13->Register(EntityPosition::PACKET_ORDINAL, 0x28);
    clientbound1_13->Register(EntityPositionAndRotation::PACKET_ORDINAL, 0x29);
    clientbound1_13->Register(EntityRotation::PACKET_ORDINAL, 0x2A);
    clientbound1_13->Register(MoveVehicle::PACKET_ORDINAL, 0x2B);
    clientbound1_13->Register(OpenSignEditor::PACKET_ORDINAL, 0x2C);
    clientbound1_13->Register(CraftRecipeResponse::PACKET_ORDINAL, 0x2D);
    clientbound1_13->Register(ServerPlayerAbilities::PACKET_ORDINAL, 0x2E);
    clientbound1_13->Register(CombatEvent::PACKET_ORDINAL, 0x2F);
    clientbound1_13->Register(PlayerListItem::PACKET_ORDINAL, 0x30);
    clientbound1_13->Register(PlayerFace::PACKET_ORDINAL, 0x31);
    clientbound1_13->Register(PositionRotation::PACKET_ORDINAL, 0x32);
    clientbound1_13->Register(UseBed::PACKET_ORDINAL, 0x33);
    clientbound1_13->Register(UnlockRecipes::PACKET_ORDINAL, 0x34);
    clientbound1_13->Register(EntityRemove::PACKET_ORDINAL, 0x35);
    clientbound1_13->Register(EntityEffectRemove::PACKET_ORDINAL, 0x36);
    clientbound1_13->Register(ResourcePackRequest::PACKET_ORDINAL, 0x37);
    clientbound1_13->Register(Respawn::PACKET_ORDINAL, 0x38);
    clientbound1_13->Register(EntityLookAt::PACKET_ORDINAL, 0x39);
    clientbound1_13->Register(SelectAdvancementsTab::PACKET_ORDINAL, 0x3A);
    clientbound1_13->Register(LegacyWorldBorder::PACKET_ORDINAL, 0x3B);
    clientbound1_13->Register(Camera::PACKET_ORDINAL, 0x3C);
    clientbound1_13->Register(HeldSlot::PACKET_ORDINAL, 0x3D);
    clientbound1_13->Register(DisplayObjective::PACKET_ORDINAL, 0x3E);
    clientbound1_13->Register(EntityMetadata::PACKET_ORDINAL, 0x3F);
    clientbound1_13->Register(LeadEntities::PACKET_ORDINAL, 0x40);
    clientbound1_13->Register(EntityVelocity::PACKET_ORDINAL, 0x41);
    clientbound1_13->Register(EntityEquipment::PACKET_ORDINAL, 0x42);
    clientbound1_13->Register(Experience::PACKET_ORDINAL, 0x43);
    clientbound1_13->Register(Health::PACKET_ORDINAL, 0x44);
    clientbound1_13->Register(Objectives::PACKET_ORDINAL, 0x45);
    clientbound1_13->Register(Passengers::PACKET_ORDINAL, 0x46);
    clientbound1_13->Register(Teams::PACKET_ORDINAL, 0x47);
    clientbound1_13->Register(Score::PACKET_ORDINAL, 0x48);
    clientbound1_13->Register(DefaultSpawnPosition::PACKET_ORDINAL, 0x49);
    clientbound1_13->Register(WorldTime::PACKET_ORDINAL, 0x4A);
    clientbound1_13->Register(LegacyTitle::PACKET_ORDINAL, 0x4B);
    clientbound1_13->Register(StopSound::PACKET_ORDINAL, 0x4C);
    clientbound1_13->Register(HardcodedSoundEffect::PACKET_ORDINAL, 0x4D);
    clientbound1_13->Register(TabHeaderFooter::PACKET_ORDINAL, 0x4E);
    clientbound1_13->Register(PickupItem::PACKET_ORDINAL, 0x4F);
    clientbound1_13->Register(EntityTeleport::PACKET_ORDINAL, 0x50);
    clientbound1_13->Register(Advancements::PACKET_ORDINAL, 0x51);
    clientbound1_13->Register(EntityProperties::PACKET_ORDINAL, 0x52);
    clientbound1_13->Register(EntityEffect::PACKET_ORDINAL, 0x53);
    clientbound1_13->Register(Recipes::PACKET_ORDINAL, 0x53);
    clientbound1_13->Register(Tags::PACKET_ORDINAL, 0x53);

    VersionRegistry* clientbound1_14 = clientboundRegistry + ProtocolVersion::MINECRAFT_1_14.GetPacketIDOrdinal();
    clientbound1_14->Register(SpawnEntity::PACKET_ORDINAL, 0x00);
    clientbound1_14->Register(SpawnExperienceOrb::PACKET_ORDINAL, 0x01);
    clientbound1_14->Register(SpawnThunderbolt::PACKET_ORDINAL, 0x02);
    clientbound1_14->Register(SpawnEntity::PACKET_ORDINAL, 0x03);
    clientbound1_14->Register(SpawnPainting::PACKET_ORDINAL, 0x04);
    clientbound1_14->Register(SpawnPlayer::PACKET_ORDINAL, 0x05);
    clientbound1_14->Register(EntityAnimation::PACKET_ORDINAL, 0x06);
    clientbound1_14->Register(AwardStatistics::PACKET_ORDINAL, 0x07);
    clientbound1_14->Register(BlockDestroyStage::PACKET_ORDINAL, 0x08);
    clientbound1_14->Register(BlockEntityData::PACKET_ORDINAL, 0x09);
    clientbound1_14->Register(BlockAction::PACKET_ORDINAL, 0x0A);
    clientbound1_14->Register(BlockUpdate::PACKET_ORDINAL, 0x0B);
    clientbound1_14->Register(BossBar::PACKET_ORDINAL, 0x0C);
    clientbound1_14->Register(ServerChangeDifficulty::PACKET_ORDINAL, 0x0D);
    clientbound1_14->Register(LegacyChat::PACKET_ORDINAL, 0x0E);
    clientbound1_14->Register(SectionBlocks::PACKET_ORDINAL, 0x0F);
    clientbound1_14->Register(CommandSuggestionResponse::PACKET_ORDINAL, 0x10);
    clientbound1_14->Register(DeclareCommands::PACKET_ORDINAL, 0x11);
    clientbound1_14->Register(ConfirmTransaction::PACKET_ORDINAL, 0x12);
    clientbound1_14->Register(CloseInventory::PACKET_ORDINAL, 0x13);
    clientbound1_14->Register(InventoryContent::PACKET_ORDINAL, 0x14);
    clientbound1_14->Register(InventoryProperty::PACKET_ORDINAL, 0x15);
    clientbound1_14->Register(InventorySlot::PACKET_ORDINAL, 0x16);
    clientbound1_14->Register(Cooldown::PACKET_ORDINAL, 0x17);
    clientbound1_14->Register(PluginMessage::PACKET_ORDINAL, 0x18);
    clientbound1_14->Register(CustomSoundEffect::PACKET_ORDINAL, 0x19);
    clientbound1_14->Register(Disconnect::PACKET_ORDINAL, 0x1A);
    clientbound1_14->Register(EntityAnimation::PACKET_ORDINAL, 0x1B);
    clientbound1_14->Register(Explosion::PACKET_ORDINAL, 0x1C);
    clientbound1_14->Register(UnloadChunk::PACKET_ORDINAL, 0x1D);
    clientbound1_14->Register(GameEvent::PACKET_ORDINAL, 0x1E);
    clientbound1_14->Register(KeepAlive::PACKET_ORDINAL, 0x1F);
    clientbound1_14->Register(OpenHorseInventory::PACKET_ORDINAL, 0x20);
    clientbound1_14->Register(ChunkData::PACKET_ORDINAL, 0x21);
    clientbound1_14->Register(WorldEvent::PACKET_ORDINAL, 0x22);
    clientbound1_14->Register(Particle::PACKET_ORDINAL, 0x23);
    clientbound1_14->Register(ChunkLight::PACKET_ORDINAL, 0x24);
    clientbound1_14->Register(JoinGame::PACKET_ORDINAL, 0x25);
    clientbound1_14->Register(MapData::PACKET_ORDINAL, 0x26);
    clientbound1_14->Register(TradeList::PACKET_ORDINAL, 0x27);
    clientbound1_14->Register(EntityNotMoved::PACKET_ORDINAL, 0x28);
    clientbound1_14->Register(EntityPosition::PACKET_ORDINAL, 0x29);
    clientbound1_14->Register(EntityPositionAndRotation::PACKET_ORDINAL, 0x2A);
    clientbound1_14->Register(EntityRotation::PACKET_ORDINAL, 0x2B);
    clientbound1_14->Register(MoveVehicle::PACKET_ORDINAL, 0x2C);
    clientbound1_14->Register(OpenBook::PACKET_ORDINAL, 0x2D);
    clientbound1_14->Register(OpenInventory::PACKET_ORDINAL, 0x2E);
    clientbound1_14->Register(OpenSignEditor::PACKET_ORDINAL, 0x2F);
    clientbound1_14->Register(CraftRecipeResponse::PACKET_ORDINAL, 0x30);
    clientbound1_14->Register(ServerPlayerAbilities::PACKET_ORDINAL, 0x31);
    clientbound1_14->Register(CombatEvent::PACKET_ORDINAL, 0x32);
    clientbound1_14->Register(PlayerListItem::PACKET_ORDINAL, 0x33);
    clientbound1_14->Register(PlayerFace::PACKET_ORDINAL, 0x34);
    clientbound1_14->Register(PositionRotation::PACKET_ORDINAL, 0x35);
    clientbound1_14->Register(UnlockRecipes::PACKET_ORDINAL, 0x36);
    clientbound1_14->Register(EntityRemove::PACKET_ORDINAL, 0x37);
    clientbound1_14->Register(EntityEffectRemove::PACKET_ORDINAL, 0x38);
    clientbound1_14->Register(ResourcePackRequest::PACKET_ORDINAL, 0x39);
    clientbound1_14->Register(Respawn::PACKET_ORDINAL, 0x3A);
    clientbound1_14->Register(EntityLookAt::PACKET_ORDINAL, 0x3B);
    clientbound1_14->Register(SelectAdvancementsTab::PACKET_ORDINAL, 0x3C);
    clientbound1_14->Register(LegacyWorldBorder::PACKET_ORDINAL, 0x3D);
    clientbound1_14->Register(Camera::PACKET_ORDINAL, 0x3E);
    clientbound1_14->Register(HeldSlot::PACKET_ORDINAL, 0x3F);
    clientbound1_14->Register(ViewPosition::PACKET_ORDINAL, 0x40);
    clientbound1_14->Register(ViewDistance::PACKET_ORDINAL, 0x41);
    clientbound1_14->Register(DisplayObjective::PACKET_ORDINAL, 0x42);
    clientbound1_14->Register(EntityMetadata::PACKET_ORDINAL, 0x43);
    clientbound1_14->Register(LeadEntities::PACKET_ORDINAL, 0x44);
    clientbound1_14->Register(EntityVelocity::PACKET_ORDINAL, 0x45);
    clientbound1_14->Register(EntityEquipment::PACKET_ORDINAL, 0x46);
    clientbound1_14->Register(Experience::PACKET_ORDINAL, 0x47);
    clientbound1_14->Register(Health::PACKET_ORDINAL, 0x48);
    clientbound1_14->Register(Objectives::PACKET_ORDINAL, 0x49);
    clientbound1_14->Register(Passengers::PACKET_ORDINAL, 0x4A);
    clientbound1_14->Register(Teams::PACKET_ORDINAL, 0x4B);
    clientbound1_14->Register(Score::PACKET_ORDINAL, 0x4C);
    clientbound1_14->Register(DefaultSpawnPosition::PACKET_ORDINAL, 0x4D);
    clientbound1_14->Register(WorldTime::PACKET_ORDINAL, 0x4E);
    clientbound1_14->Register(LegacyTitle::PACKET_ORDINAL, 0x4F);
    clientbound1_14->Register(EntitySoundEffect::PACKET_ORDINAL, 0x50);
    clientbound1_14->Register(HardcodedSoundEffect::PACKET_ORDINAL, 0x51);
    clientbound1_14->Register(StopSound::PACKET_ORDINAL, 0x52);
    clientbound1_14->Register(TabHeaderFooter::PACKET_ORDINAL, 0x53);
    clientbound1_14->Register(TagQueryResponse::PACKET_ORDINAL, 0x54);
    clientbound1_14->Register(PickupItem::PACKET_ORDINAL, 0x55);
    clientbound1_14->Register(EntityTeleport::PACKET_ORDINAL, 0x56);
    clientbound1_14->Register(Advancements::PACKET_ORDINAL, 0x57);
    clientbound1_14->Register(EntityProperties::PACKET_ORDINAL, 0x58);
    clientbound1_14->Register(EntityEffect::PACKET_ORDINAL, 0x59);
    clientbound1_14->Register(Recipes::PACKET_ORDINAL, 0x5A);
    clientbound1_14->Register(Tags::PACKET_ORDINAL, 0x5B);
    clientbound1_14->Register(AcknowledgePlayerDigging::PACKET_ORDINAL, 0x5C);

    VersionRegistry* clientbound1_15 = clientboundRegistry + ProtocolVersion::MINECRAFT_1_15.GetPacketIDOrdinal();
    clientbound1_15->Register(SpawnEntity::PACKET_ORDINAL, 0x00);
    clientbound1_15->Register(SpawnExperienceOrb::PACKET_ORDINAL, 0x01);
    clientbound1_15->Register(SpawnThunderbolt::PACKET_ORDINAL, 0x02);
    clientbound1_15->Register(SpawnEntity::PACKET_ORDINAL, 0x03);
    clientbound1_15->Register(SpawnPainting::PACKET_ORDINAL, 0x04);
    clientbound1_15->Register(SpawnPlayer::PACKET_ORDINAL, 0x05);
    clientbound1_15->Register(EntityAnimation::PACKET_ORDINAL, 0x06);
    clientbound1_15->Register(AwardStatistics::PACKET_ORDINAL, 0x07);
    clientbound1_15->Register(AcknowledgePlayerDigging::PACKET_ORDINAL, 0x08);
    clientbound1_15->Register(BlockDestroyStage::PACKET_ORDINAL, 0x09);
    clientbound1_15->Register(BlockEntityData::PACKET_ORDINAL, 0x0A);
    clientbound1_15->Register(BlockAction::PACKET_ORDINAL, 0x0B);
    clientbound1_15->Register(BlockUpdate::PACKET_ORDINAL, 0x0C);
    clientbound1_15->Register(BossBar::PACKET_ORDINAL, 0x0D);
    clientbound1_15->Register(ServerChangeDifficulty::PACKET_ORDINAL, 0x0E);
    clientbound1_15->Register(LegacyChat::PACKET_ORDINAL, 0x0F);
    clientbound1_15->Register(SectionBlocks::PACKET_ORDINAL, 0x10);
    clientbound1_15->Register(CommandSuggestionResponse::PACKET_ORDINAL, 0x11);
    clientbound1_15->Register(DeclareCommands::PACKET_ORDINAL, 0x12);
    clientbound1_15->Register(ConfirmTransaction::PACKET_ORDINAL, 0x13);
    clientbound1_15->Register(CloseInventory::PACKET_ORDINAL, 0x14);
    clientbound1_15->Register(InventoryContent::PACKET_ORDINAL, 0x15);
    clientbound1_15->Register(InventoryProperty::PACKET_ORDINAL, 0x16);
    clientbound1_15->Register(InventorySlot::PACKET_ORDINAL, 0x17);
    clientbound1_15->Register(Cooldown::PACKET_ORDINAL, 0x18);
    clientbound1_15->Register(PluginMessage::PACKET_ORDINAL, 0x19);
    clientbound1_15->Register(CustomSoundEffect::PACKET_ORDINAL, 0x1A);
    clientbound1_15->Register(Disconnect::PACKET_ORDINAL, 0x1B);
    clientbound1_15->Register(EntityAnimation::PACKET_ORDINAL, 0x1C);
    clientbound1_15->Register(Explosion::PACKET_ORDINAL, 0x1D);
    clientbound1_15->Register(UnloadChunk::PACKET_ORDINAL, 0x1E);
    clientbound1_15->Register(GameEvent::PACKET_ORDINAL, 0x1F);
    clientbound1_15->Register(KeepAlive::PACKET_ORDINAL, 0x20);
    clientbound1_15->Register(OpenHorseInventory::PACKET_ORDINAL, 0x21);
    clientbound1_15->Register(ChunkData::PACKET_ORDINAL, 0x22);
    clientbound1_15->Register(WorldEvent::PACKET_ORDINAL, 0x23);
    clientbound1_15->Register(Particle::PACKET_ORDINAL, 0x24);
    clientbound1_15->Register(ChunkLight::PACKET_ORDINAL, 0x25);
    clientbound1_15->Register(JoinGame::PACKET_ORDINAL, 0x26);
    clientbound1_15->Register(MapData::PACKET_ORDINAL, 0x27);
    clientbound1_15->Register(TradeList::PACKET_ORDINAL, 0x28);
    clientbound1_15->Register(EntityNotMoved::PACKET_ORDINAL, 0x29);
    clientbound1_15->Register(EntityPosition::PACKET_ORDINAL, 0x2A);
    clientbound1_15->Register(EntityPositionAndRotation::PACKET_ORDINAL, 0x2B);
    clientbound1_15->Register(EntityRotation::PACKET_ORDINAL, 0x2C);
    clientbound1_15->Register(MoveVehicle::PACKET_ORDINAL, 0x2D);
    clientbound1_15->Register(OpenBook::PACKET_ORDINAL, 0x2E);
    clientbound1_15->Register(OpenInventory::PACKET_ORDINAL, 0x2D);
    clientbound1_15->Register(OpenSignEditor::PACKET_ORDINAL, 0x30);
    clientbound1_15->Register(CraftRecipeResponse::PACKET_ORDINAL, 0x31);
    clientbound1_15->Register(ServerPlayerAbilities::PACKET_ORDINAL, 0x32);
    clientbound1_15->Register(CombatEvent::PACKET_ORDINAL, 0x33);
    clientbound1_15->Register(PlayerListItem::PACKET_ORDINAL, 0x34);
    clientbound1_15->Register(PlayerFace::PACKET_ORDINAL, 0x35);
    clientbound1_15->Register(PositionRotation::PACKET_ORDINAL, 0x36);
    clientbound1_15->Register(UnlockRecipes::PACKET_ORDINAL, 0x37);
    clientbound1_15->Register(EntityRemove::PACKET_ORDINAL, 0x38);
    clientbound1_15->Register(EntityEffectRemove::PACKET_ORDINAL, 0x39);
    clientbound1_15->Register(ResourcePackRequest::PACKET_ORDINAL, 0x3A);
    clientbound1_15->Register(Respawn::PACKET_ORDINAL, 0x3B);
    clientbound1_15->Register(EntityLookAt::PACKET_ORDINAL, 0x3C);
    clientbound1_15->Register(SelectAdvancementsTab::PACKET_ORDINAL, 0x3D);
    clientbound1_15->Register(LegacyWorldBorder::PACKET_ORDINAL, 0x3E);
    clientbound1_15->Register(Camera::PACKET_ORDINAL, 0x3F);
    clientbound1_15->Register(HeldSlot::PACKET_ORDINAL, 0x40);
    clientbound1_15->Register(ViewPosition::PACKET_ORDINAL, 0x41);
    clientbound1_15->Register(ViewDistance::PACKET_ORDINAL, 0x42);
    clientbound1_15->Register(DisplayObjective::PACKET_ORDINAL, 0x43);
    clientbound1_15->Register(EntityMetadata::PACKET_ORDINAL, 0x44);
    clientbound1_15->Register(LeadEntities::PACKET_ORDINAL, 0x45);
    clientbound1_15->Register(EntityVelocity::PACKET_ORDINAL, 0x46);
    clientbound1_15->Register(EntityEquipment::PACKET_ORDINAL, 0x47);
    clientbound1_15->Register(Experience::PACKET_ORDINAL, 0x48);
    clientbound1_15->Register(Health::PACKET_ORDINAL, 0x49);
    clientbound1_15->Register(Objectives::PACKET_ORDINAL, 0x4A);
    clientbound1_15->Register(Passengers::PACKET_ORDINAL, 0x4B);
    clientbound1_15->Register(Teams::PACKET_ORDINAL, 0x4C);
    clientbound1_15->Register(Score::PACKET_ORDINAL, 0x4D);
    clientbound1_15->Register(DefaultSpawnPosition::PACKET_ORDINAL, 0x4E);
    clientbound1_15->Register(WorldTime::PACKET_ORDINAL, 0x4F);
    clientbound1_15->Register(LegacyTitle::PACKET_ORDINAL, 0x50);
    clientbound1_15->Register(EntitySoundEffect::PACKET_ORDINAL, 0x51);
    clientbound1_15->Register(HardcodedSoundEffect::PACKET_ORDINAL, 0x52);
    clientbound1_15->Register(StopSound::PACKET_ORDINAL, 0x53);
    clientbound1_15->Register(TabHeaderFooter::PACKET_ORDINAL, 0x54);
    clientbound1_15->Register(TagQueryResponse::PACKET_ORDINAL, 0x55);
    clientbound1_15->Register(PickupItem::PACKET_ORDINAL, 0x56);
    clientbound1_15->Register(EntityTeleport::PACKET_ORDINAL, 0x57);
    clientbound1_15->Register(Advancements::PACKET_ORDINAL, 0x58);
    clientbound1_15->Register(EntityProperties::PACKET_ORDINAL, 0x59);
    clientbound1_15->Register(EntityEffect::PACKET_ORDINAL, 0x5A);
    clientbound1_15->Register(Recipes::PACKET_ORDINAL, 0x5B);
    clientbound1_15->Register(Tags::PACKET_ORDINAL, 0x5C);

    // VersionRegistry* clientbound1_16 = clientboundRegistry + ProtocolVersion::MINECRAFT_1_16.GetPacketIDOrdinal();
    // clientbound1_16->Register(SpawnEntity::PACKET_ORDINAL, 0x00);
    // clientbound1_16->Register(SpawnExperienceOrb::PACKET_ORDINAL, 0x01);
    // clientbound1_16->Register(SpawnEntity::PACKET_ORDINAL, 0x02);
    // clientbound1_16->Register(SpawnPainting::PACKET_ORDINAL, 0x03);
    // clientbound1_16->Register(SpawnPlayer::PACKET_ORDINAL, 0x04);
    // clientbound1_16->Register(EntityAnimation::PACKET_ORDINAL, 0x05);
    // clientbound1_16->Register(AwardStatistics::PACKET_ORDINAL, 0x06);
    // clientbound1_16->Register(AcknowledgePlayerDigging::PACKET_ORDINAL, 0x07);
    // clientbound1_16->Register(BlockDestroyStage::PACKET_ORDINAL, 0x08);
    // clientbound1_16->Register(BlockEntityData::PACKET_ORDINAL, 0x09);
    // clientbound1_16->Register(BlockAction::PACKET_ORDINAL, 0x0A);
    // clientbound1_16->Register(BlockUpdate::PACKET_ORDINAL, 0x0B);
    // clientbound1_16->Register(BossBar::PACKET_ORDINAL, 0x0C);
    // clientbound1_16->Register(ServerChangeDifficulty::PACKET_ORDINAL, 0x0D);
    // clientbound1_16->Register(LegacyChat::PACKET_ORDINAL, 0x0E);
    // clientbound1_16->Register(SectionBlocks::PACKET_ORDINAL, 0x0F);
    // clientbound1_16->Register(CommandSuggestionResponse::PACKET_ORDINAL, 0x10);
    // clientbound1_16->Register(DeclareCommands::PACKET_ORDINAL, 0x11);
    // clientbound1_16->Register(ConfirmTransaction::PACKET_ORDINAL, 0x12);
    // clientbound1_16->Register(CloseInventory::PACKET_ORDINAL, 0x13);
    // clientbound1_16->Register(InventoryContent::PACKET_ORDINAL, 0x14);
    // clientbound1_16->Register(InventoryProperty::PACKET_ORDINAL, 0x15);
    // clientbound1_16->Register(InventorySlot::PACKET_ORDINAL, 0x16);
    // clientbound1_16->Register(Cooldown::PACKET_ORDINAL, 0x17);
    // clientbound1_16->Register(PluginMessage::PACKET_ORDINAL, 0x18);
    // clientbound1_16->Register(CustomSoundEffect::PACKET_ORDINAL, 0x19);
    // clientbound1_16->Register(Disconnect::PACKET_ORDINAL, 0x1A);
    // clientbound1_16->Register(EntityAnimation::PACKET_ORDINAL, 0x1B);
    // clientbound1_16->Register(Explosion::PACKET_ORDINAL, 0x1C);
    // clientbound1_16->Register(UnloadChunk::PACKET_ORDINAL, 0x1D);
    // clientbound1_16->Register(GameEvent::PACKET_ORDINAL, 0x1E);
    // clientbound1_16->Register(KeepAlive::PACKET_ORDINAL, 0x1F);
    // clientbound1_16->Register(OpenHorseInventory::PACKET_ORDINAL, 0x20);
    // clientbound1_16->Register(ChunkData::PACKET_ORDINAL, 0x21);
    // clientbound1_16->Register(WorldEvent::PACKET_ORDINAL, 0x22);
    // clientbound1_16->Register(Particle::PACKET_ORDINAL, 0x23);
    // clientbound1_16->Register(ChunkLight::PACKET_ORDINAL, 0x24);
    // clientbound1_16->Register(JoinGame::PACKET_ORDINAL, 0x25);
    // clientbound1_16->Register(MapData::PACKET_ORDINAL, 0x26);
    // clientbound1_16->Register(TradeList::PACKET_ORDINAL, 0x27);
    // clientbound1_16->Register(EntityNotMoved::PACKET_ORDINAL, 0x28);
    // clientbound1_16->Register(EntityPosition::PACKET_ORDINAL, 0x29);
    // clientbound1_16->Register(EntityPositionAndRotation::PACKET_ORDINAL, 0x2A);
    // clientbound1_16->Register(EntityRotation::PACKET_ORDINAL, 0x2B);
    // clientbound1_16->Register(MoveVehicle::PACKET_ORDINAL, 0x2C);
    // clientbound1_16->Register(OpenBook::PACKET_ORDINAL, 0x2D);
    // clientbound1_16->Register(OpenInventory::PACKET_ORDINAL, 0x2E);
    // clientbound1_16->Register(OpenSignEditor::PACKET_ORDINAL, 0x2D);
    // clientbound1_16->Register(CraftRecipeResponse::PACKET_ORDINAL, 0x30);
    // clientbound1_16->Register(ServerPlayerAbilities::PACKET_ORDINAL, 0x31);
    // clientbound1_16->Register(CombatEvent::PACKET_ORDINAL, 0x32);
    // clientbound1_16->Register(PlayerListItem::PACKET_ORDINAL, 0x33);
    // clientbound1_16->Register(PlayerFace::PACKET_ORDINAL, 0x34);
    // clientbound1_16->Register(PositionRotation::PACKET_ORDINAL, 0x35);
    // clientbound1_16->Register(UnlockRecipes::PACKET_ORDINAL, 0x36);
    // clientbound1_16->Register(EntityRemove::PACKET_ORDINAL, 0x37);
    // clientbound1_16->Register(EntityEffectRemove::PACKET_ORDINAL, 0x38);
    // clientbound1_16->Register(ResourcePackRequest::PACKET_ORDINAL, 0x39);
    // clientbound1_16->Register(Respawn::PACKET_ORDINAL, 0x3A);
    // clientbound1_16->Register(EntityLookAt::PACKET_ORDINAL, 0x3B);
    // clientbound1_16->Register(SelectAdvancementsTab::PACKET_ORDINAL, 0x3C);
    // clientbound1_16->Register(LegacyWorldBorder::PACKET_ORDINAL, 0x3D);
    // clientbound1_16->Register(Camera::PACKET_ORDINAL, 0x3E);
    // clientbound1_16->Register(HeldSlot::PACKET_ORDINAL, 0x3F);
    // clientbound1_16->Register(ViewPosition::PACKET_ORDINAL, 0x40);
    // clientbound1_16->Register(ViewDistance::PACKET_ORDINAL, 0x41);
    // clientbound1_16->Register(DisplayObjective::PACKET_ORDINAL, 0x42);
    // clientbound1_16->Register(EntityMetadata::PACKET_ORDINAL, 0x43);
    // clientbound1_16->Register(LeadEntities::PACKET_ORDINAL, 0x44);
    // clientbound1_16->Register(EntityVelocity::PACKET_ORDINAL, 0x45);
    // clientbound1_16->Register(EntityEquipment::PACKET_ORDINAL, 0x46);
    // clientbound1_16->Register(Experience::PACKET_ORDINAL, 0x47);
    // clientbound1_16->Register(Health::PACKET_ORDINAL, 0x48);
    // clientbound1_16->Register(Objectives::PACKET_ORDINAL, 0x49);
    // clientbound1_16->Register(Passengers::PACKET_ORDINAL, 0x4A);
    // clientbound1_16->Register(Teams::PACKET_ORDINAL, 0x4B);
    // clientbound1_16->Register(Score::PACKET_ORDINAL, 0x4C);
    // clientbound1_16->Register(DefaultSpawnPosition::PACKET_ORDINAL, 0x4D);
    // clientbound1_16->Register(WorldTime::PACKET_ORDINAL, 0x4E);
    // clientbound1_16->Register(LegacyTitle::PACKET_ORDINAL, 0x4F);
    // clientbound1_16->Register(EntitySoundEffect::PACKET_ORDINAL, 0x50);
    // clientbound1_16->Register(HardcodedSoundEffect::PACKET_ORDINAL, 0x51);
    // clientbound1_16->Register(StopSound::PACKET_ORDINAL, 0x52);
    // clientbound1_16->Register(TabHeaderFooter::PACKET_ORDINAL, 0x53);
    // clientbound1_16->Register(TagQueryResponse::PACKET_ORDINAL, 0x54);
    // clientbound1_16->Register(PickupItem::PACKET_ORDINAL, 0x55);
    // clientbound1_16->Register(EntityTeleport::PACKET_ORDINAL, 0x56);
    // clientbound1_16->Register(Advancements::PACKET_ORDINAL, 0x57);
    // clientbound1_16->Register(EntityProperties::PACKET_ORDINAL, 0x58);
    // clientbound1_16->Register(EntityEffect::PACKET_ORDINAL, 0x59);
    // clientbound1_16->Register(Recipes::PACKET_ORDINAL, 0x5A);
    // clientbound1_16->Register(Tags::PACKET_ORDINAL, 0x5B);

    VersionRegistry* clientbound1_16_2 = clientboundRegistry + ProtocolVersion::MINECRAFT_1_16_2.GetPacketIDOrdinal();
    clientbound1_16_2->Register(SpawnEntity::PACKET_ORDINAL, 0x00);
    clientbound1_16_2->Register(SpawnExperienceOrb::PACKET_ORDINAL, 0x01);
    clientbound1_16_2->Register(SpawnEntity::PACKET_ORDINAL, 0x02);
    clientbound1_16_2->Register(SpawnPainting::PACKET_ORDINAL, 0x03);
    clientbound1_16_2->Register(SpawnPlayer::PACKET_ORDINAL, 0x04);
    clientbound1_16_2->Register(EntityAnimation::PACKET_ORDINAL, 0x05);
    clientbound1_16_2->Register(AwardStatistics::PACKET_ORDINAL, 0x06);
    clientbound1_16_2->Register(AcknowledgePlayerDigging::PACKET_ORDINAL, 0x07);
    clientbound1_16_2->Register(BlockDestroyStage::PACKET_ORDINAL, 0x08);
    clientbound1_16_2->Register(BlockEntityData::PACKET_ORDINAL, 0x09);
    clientbound1_16_2->Register(BlockAction::PACKET_ORDINAL, 0x0A);
    clientbound1_16_2->Register(BlockUpdate::PACKET_ORDINAL, 0x0B);
    clientbound1_16_2->Register(BossBar::PACKET_ORDINAL, 0x0C);
    clientbound1_16_2->Register(ServerChangeDifficulty::PACKET_ORDINAL, 0x0D);
    clientbound1_16_2->Register(LegacyChat::PACKET_ORDINAL, 0x0E);
    clientbound1_16_2->Register(SectionBlocks::PACKET_ORDINAL, 0x0F);
    clientbound1_16_2->Register(CommandSuggestionResponse::PACKET_ORDINAL, 0x10);
    clientbound1_16_2->Register(DeclareCommands::PACKET_ORDINAL, 0x11);
    clientbound1_16_2->Register(ConfirmTransaction::PACKET_ORDINAL, 0x12);
    clientbound1_16_2->Register(CloseInventory::PACKET_ORDINAL, 0x13);
    clientbound1_16_2->Register(InventoryContent::PACKET_ORDINAL, 0x14);
    clientbound1_16_2->Register(InventoryProperty::PACKET_ORDINAL, 0x15);
    clientbound1_16_2->Register(InventorySlot::PACKET_ORDINAL, 0x16);
    clientbound1_16_2->Register(Cooldown::PACKET_ORDINAL, 0x17);
    clientbound1_16_2->Register(PluginMessage::PACKET_ORDINAL, 0x18);
    clientbound1_16_2->Register(CustomSoundEffect::PACKET_ORDINAL, 0x19);
    clientbound1_16_2->Register(Disconnect::PACKET_ORDINAL, 0x1A);
    clientbound1_16_2->Register(EntityAnimation::PACKET_ORDINAL, 0x1B);
    clientbound1_16_2->Register(Explosion::PACKET_ORDINAL, 0x1C);
    clientbound1_16_2->Register(UnloadChunk::PACKET_ORDINAL, 0x1D);
    clientbound1_16_2->Register(GameEvent::PACKET_ORDINAL, 0x1E);
    clientbound1_16_2->Register(KeepAlive::PACKET_ORDINAL, 0x1F);
    clientbound1_16_2->Register(OpenHorseInventory::PACKET_ORDINAL, 0x20);
    clientbound1_16_2->Register(ChunkData::PACKET_ORDINAL, 0x21);
    clientbound1_16_2->Register(WorldEvent::PACKET_ORDINAL, 0x22);
    clientbound1_16_2->Register(Particle::PACKET_ORDINAL, 0x23);
    clientbound1_16_2->Register(ChunkLight::PACKET_ORDINAL, 0x24);
    clientbound1_16_2->Register(JoinGame::PACKET_ORDINAL, 0x25);
    clientbound1_16_2->Register(MapData::PACKET_ORDINAL, 0x26);
    clientbound1_16_2->Register(TradeList::PACKET_ORDINAL, 0x27);
    clientbound1_16_2->Register(EntityNotMoved::PACKET_ORDINAL, 0x28);
    clientbound1_16_2->Register(EntityPosition::PACKET_ORDINAL, 0x29);
    clientbound1_16_2->Register(EntityPositionAndRotation::PACKET_ORDINAL, 0x2A);
    clientbound1_16_2->Register(EntityRotation::PACKET_ORDINAL, 0x2B);
    clientbound1_16_2->Register(MoveVehicle::PACKET_ORDINAL, 0x2C);
    clientbound1_16_2->Register(OpenBook::PACKET_ORDINAL, 0x2D);
    clientbound1_16_2->Register(OpenInventory::PACKET_ORDINAL, 0x2E);
    clientbound1_16_2->Register(OpenSignEditor::PACKET_ORDINAL, 0x2D);
    clientbound1_16_2->Register(CraftRecipeResponse::PACKET_ORDINAL, 0x30);
    clientbound1_16_2->Register(ServerPlayerAbilities::PACKET_ORDINAL, 0x31);
    clientbound1_16_2->Register(CombatEvent::PACKET_ORDINAL, 0x32);
    clientbound1_16_2->Register(PlayerListItem::PACKET_ORDINAL, 0x33);
    clientbound1_16_2->Register(PlayerFace::PACKET_ORDINAL, 0x34);
    clientbound1_16_2->Register(PositionRotation::PACKET_ORDINAL, 0x35);
    clientbound1_16_2->Register(UnlockRecipes::PACKET_ORDINAL, 0x36);
    clientbound1_16_2->Register(EntityRemove::PACKET_ORDINAL, 0x37);
    clientbound1_16_2->Register(EntityEffectRemove::PACKET_ORDINAL, 0x38);
    clientbound1_16_2->Register(ResourcePackRequest::PACKET_ORDINAL, 0x39);
    clientbound1_16_2->Register(Respawn::PACKET_ORDINAL, 0x3A);
    clientbound1_16_2->Register(EntityLookAt::PACKET_ORDINAL, 0x3B);
    clientbound1_16_2->Register(SelectAdvancementsTab::PACKET_ORDINAL, 0x3C);
    clientbound1_16_2->Register(LegacyWorldBorder::PACKET_ORDINAL, 0x3D);
    clientbound1_16_2->Register(Camera::PACKET_ORDINAL, 0x3E);
    clientbound1_16_2->Register(HeldSlot::PACKET_ORDINAL, 0x3F);
    clientbound1_16_2->Register(ViewPosition::PACKET_ORDINAL, 0x40);
    clientbound1_16_2->Register(ViewDistance::PACKET_ORDINAL, 0x41);
    clientbound1_16_2->Register(DisplayObjective::PACKET_ORDINAL, 0x42);
    clientbound1_16_2->Register(EntityMetadata::PACKET_ORDINAL, 0x43);
    clientbound1_16_2->Register(LeadEntities::PACKET_ORDINAL, 0x44);
    clientbound1_16_2->Register(EntityVelocity::PACKET_ORDINAL, 0x45);
    clientbound1_16_2->Register(EntityEquipment::PACKET_ORDINAL, 0x46);
    clientbound1_16_2->Register(Experience::PACKET_ORDINAL, 0x47);
    clientbound1_16_2->Register(Health::PACKET_ORDINAL, 0x48);
    clientbound1_16_2->Register(Objectives::PACKET_ORDINAL, 0x49);
    clientbound1_16_2->Register(Passengers::PACKET_ORDINAL, 0x4A);
    clientbound1_16_2->Register(Teams::PACKET_ORDINAL, 0x4B);
    clientbound1_16_2->Register(Score::PACKET_ORDINAL, 0x4C);
    clientbound1_16_2->Register(DefaultSpawnPosition::PACKET_ORDINAL, 0x4D);
    clientbound1_16_2->Register(WorldTime::PACKET_ORDINAL, 0x4E);
    clientbound1_16_2->Register(LegacyTitle::PACKET_ORDINAL, 0x4F);
    clientbound1_16_2->Register(EntitySoundEffect::PACKET_ORDINAL, 0x50);
    clientbound1_16_2->Register(HardcodedSoundEffect::PACKET_ORDINAL, 0x51);
    clientbound1_16_2->Register(StopSound::PACKET_ORDINAL, 0x52);
    clientbound1_16_2->Register(TabHeaderFooter::PACKET_ORDINAL, 0x53);
    clientbound1_16_2->Register(TagQueryResponse::PACKET_ORDINAL, 0x54);
    clientbound1_16_2->Register(PickupItem::PACKET_ORDINAL, 0x55);
    clientbound1_16_2->Register(EntityTeleport::PACKET_ORDINAL, 0x56);
    clientbound1_16_2->Register(Advancements::PACKET_ORDINAL, 0x57);
    clientbound1_16_2->Register(EntityProperties::PACKET_ORDINAL, 0x58);
    clientbound1_16_2->Register(EntityEffect::PACKET_ORDINAL, 0x59);
    clientbound1_16_2->Register(Recipes::PACKET_ORDINAL, 0x5A);
    clientbound1_16_2->Register(Tags::PACKET_ORDINAL, 0x5B);

    VersionRegistry* clientbound1_17 = clientboundRegistry + ProtocolVersion::MINECRAFT_1_17.GetPacketIDOrdinal();
    clientbound1_17->Register(SpawnEntity::PACKET_ORDINAL, 0x00);
    clientbound1_17->Register(SpawnExperienceOrb::PACKET_ORDINAL, 0x01);
    clientbound1_17->Register(SpawnEntity::PACKET_ORDINAL, 0x02);
    clientbound1_17->Register(SpawnPainting::PACKET_ORDINAL, 0x03);
    clientbound1_17->Register(SpawnPlayer::PACKET_ORDINAL, 0x04);
    //    clientbound1_17->Register(SkulkVibration::PACKET_ORDINAL, 0x05); //TODO: SkulkVibration
    clientbound1_17->Register(EntityAnimation::PACKET_ORDINAL, 0x06);
    clientbound1_17->Register(AwardStatistics::PACKET_ORDINAL, 0x07);
    clientbound1_17->Register(AcknowledgePlayerDigging::PACKET_ORDINAL, 0x08);
    clientbound1_17->Register(BlockDestroyStage::PACKET_ORDINAL, 0x09);
    clientbound1_17->Register(BlockEntityData::PACKET_ORDINAL, 0x0A);
    clientbound1_17->Register(BlockAction::PACKET_ORDINAL, 0x0B);
    clientbound1_17->Register(BlockUpdate::PACKET_ORDINAL, 0x0C);
    clientbound1_17->Register(BossBar::PACKET_ORDINAL, 0x0D);
    clientbound1_17->Register(ServerChangeDifficulty::PACKET_ORDINAL, 0x0E);
    clientbound1_17->Register(LegacyChat::PACKET_ORDINAL, 0x0F);
    clientbound1_17->Register(ClearTitle::PACKET_ORDINAL, 0x10);
    clientbound1_17->Register(CommandSuggestionResponse::PACKET_ORDINAL, 0x11);
    clientbound1_17->Register(DeclareCommands::PACKET_ORDINAL, 0x12);
    clientbound1_17->Register(CloseInventory::PACKET_ORDINAL, 0x13);
    clientbound1_17->Register(InventoryContent::PACKET_ORDINAL, 0x14);
    clientbound1_17->Register(InventoryProperty::PACKET_ORDINAL, 0x15);
    clientbound1_17->Register(InventorySlot::PACKET_ORDINAL, 0x16);
    clientbound1_17->Register(Cooldown::PACKET_ORDINAL, 0x17);
    clientbound1_17->Register(PluginMessage::PACKET_ORDINAL, 0x18);
    clientbound1_17->Register(CustomSoundEffect::PACKET_ORDINAL, 0x19);
    clientbound1_17->Register(Disconnect::PACKET_ORDINAL, 0x1A);
    clientbound1_17->Register(EntityAnimation::PACKET_ORDINAL, 0x1B);
    clientbound1_17->Register(Explosion::PACKET_ORDINAL, 0x1C);
    clientbound1_17->Register(UnloadChunk::PACKET_ORDINAL, 0x1D);
    clientbound1_17->Register(GameEvent::PACKET_ORDINAL, 0x1E);
    clientbound1_17->Register(OpenHorseInventory::PACKET_ORDINAL, 0x1F);
    clientbound1_17->Register(InitializeWorldBorder::PACKET_ORDINAL, 0x20);
    clientbound1_17->Register(KeepAlive::PACKET_ORDINAL, 0x21);
    clientbound1_17->Register(ChunkData::PACKET_ORDINAL, 0x22);
    clientbound1_17->Register(WorldEvent::PACKET_ORDINAL, 0x23);
    clientbound1_17->Register(Particle::PACKET_ORDINAL, 0x24);
    clientbound1_17->Register(ChunkLight::PACKET_ORDINAL, 0x25);
    clientbound1_17->Register(JoinGame::PACKET_ORDINAL, 0x26);
    clientbound1_17->Register(MapData::PACKET_ORDINAL, 0x27);
    clientbound1_17->Register(TradeList::PACKET_ORDINAL, 0x28);
    clientbound1_17->Register(EntityPosition::PACKET_ORDINAL, 0x29);
    clientbound1_17->Register(EntityPositionAndRotation::PACKET_ORDINAL, 0x2A);
    clientbound1_17->Register(EntityRotation::PACKET_ORDINAL, 0x2B);
    clientbound1_17->Register(MoveVehicle::PACKET_ORDINAL, 0x2C);
    clientbound1_17->Register(OpenBook::PACKET_ORDINAL, 0x2D);
    clientbound1_17->Register(OpenInventory::PACKET_ORDINAL, 0x2E);
    clientbound1_17->Register(OpenSignEditor::PACKET_ORDINAL, 0x2F);
    clientbound1_17->Register(Ping::PACKET_ORDINAL, 0x30);
    clientbound1_17->Register(CraftRecipeResponse::PACKET_ORDINAL, 0x31);
    clientbound1_17->Register(ServerPlayerAbilities::PACKET_ORDINAL, 0x32);
    clientbound1_17->Register(EndCombatEvent::PACKET_ORDINAL, 0x33);
    clientbound1_17->Register(EnterCombatEvent::PACKET_ORDINAL, 0x34);
    clientbound1_17->Register(DeathCombatEvent::PACKET_ORDINAL, 0x35);
    clientbound1_17->Register(PlayerListItem::PACKET_ORDINAL, 0x36);
    clientbound1_17->Register(PlayerFace::PACKET_ORDINAL, 0x37);
    clientbound1_17->Register(PositionRotation::PACKET_ORDINAL, 0x38);
    clientbound1_17->Register(UnlockRecipes::PACKET_ORDINAL, 0x39);
    clientbound1_17->Register(EntityRemove::PACKET_ORDINAL, 0x3A);
    clientbound1_17->Register(EntityEffectRemove::PACKET_ORDINAL, 0x3B);
    clientbound1_17->Register(ResourcePackRequest::PACKET_ORDINAL, 0x3C);
    clientbound1_17->Register(Respawn::PACKET_ORDINAL, 0x3D);
    clientbound1_17->Register(EntityLookAt::PACKET_ORDINAL, 0x3E);
    clientbound1_17->Register(SectionBlocks::PACKET_ORDINAL, 0x3F);
    clientbound1_17->Register(SelectAdvancementsTab::PACKET_ORDINAL, 0x40);
    clientbound1_17->Register(ActionBar::PACKET_ORDINAL, 0x41);
    clientbound1_17->Register(BorderCenter::PACKET_ORDINAL, 0x42);
    clientbound1_17->Register(BorderRadiusSpeed::PACKET_ORDINAL, 0x43);
    clientbound1_17->Register(BorderRadius::PACKET_ORDINAL, 0x44);
    clientbound1_17->Register(BorderWarningTime::PACKET_ORDINAL, 0x45);
    clientbound1_17->Register(BorderWarningRadius::PACKET_ORDINAL, 0x46);
    clientbound1_17->Register(Camera::PACKET_ORDINAL, 0x47);
    clientbound1_17->Register(HeldSlot::PACKET_ORDINAL, 0x48);
    clientbound1_17->Register(ViewPosition::PACKET_ORDINAL, 0x49);
    clientbound1_17->Register(ViewDistance::PACKET_ORDINAL, 0x4A);
    clientbound1_17->Register(DefaultSpawnPosition::PACKET_ORDINAL, 0x4B);
    clientbound1_17->Register(DisplayObjective::PACKET_ORDINAL, 0x4C);
    clientbound1_17->Register(EntityMetadata::PACKET_ORDINAL, 0x4D);
    clientbound1_17->Register(LeadEntities::PACKET_ORDINAL, 0x4E);
    clientbound1_17->Register(EntityVelocity::PACKET_ORDINAL, 0x4F);
    clientbound1_17->Register(EntityEquipment::PACKET_ORDINAL, 0x50);
    clientbound1_17->Register(Experience::PACKET_ORDINAL, 0x51);
    clientbound1_17->Register(Health::PACKET_ORDINAL, 0x52);
    clientbound1_17->Register(Objectives::PACKET_ORDINAL, 0x53);
    clientbound1_17->Register(Passengers::PACKET_ORDINAL, 0x54);
    clientbound1_17->Register(Teams::PACKET_ORDINAL, 0x55);
    clientbound1_17->Register(Score::PACKET_ORDINAL, 0x56);
    clientbound1_17->Register(Subtitle::PACKET_ORDINAL, 0x57);
    clientbound1_17->Register(WorldTime::PACKET_ORDINAL, 0x58);
    clientbound1_17->Register(Title::PACKET_ORDINAL, 0x59);
    clientbound1_17->Register(TitleTimes::PACKET_ORDINAL, 0x5A);
    clientbound1_17->Register(EntitySoundEffect::PACKET_ORDINAL, 0x5B);
    clientbound1_17->Register(HardcodedSoundEffect::PACKET_ORDINAL, 0x5C);
    clientbound1_17->Register(StopSound::PACKET_ORDINAL, 0x5D);
    clientbound1_17->Register(TabHeaderFooter::PACKET_ORDINAL, 0x5E);
    clientbound1_17->Register(TagQueryResponse::PACKET_ORDINAL, 0x5F);
    clientbound1_17->Register(PickupItem::PACKET_ORDINAL, 0x60);
    clientbound1_17->Register(EntityTeleport::PACKET_ORDINAL, 0x61);
    clientbound1_17->Register(Advancements::PACKET_ORDINAL, 0x62);
    clientbound1_17->Register(EntityProperties::PACKET_ORDINAL, 0x63);
    clientbound1_17->Register(EntityEffect::PACKET_ORDINAL, 0x64);
    clientbound1_17->Register(Recipes::PACKET_ORDINAL, 0x65);
    clientbound1_17->Register(Tags::PACKET_ORDINAL, 0x66);

    VersionRegistry* clientbound1_18 = clientboundRegistry + ProtocolVersion::MINECRAFT_1_18.GetPacketIDOrdinal();
    clientbound1_18->Register(SpawnEntity::PACKET_ORDINAL, 0x00);
    clientbound1_18->Register(SpawnExperienceOrb::PACKET_ORDINAL, 0x01);
    clientbound1_18->Register(SpawnEntity::PACKET_ORDINAL, 0x02);
    clientbound1_18->Register(SpawnPainting::PACKET_ORDINAL, 0x03);
    clientbound1_18->Register(SpawnPlayer::PACKET_ORDINAL, 0x04);
    //    clientbound1_18->Register(SkulkVibration::PACKET_ORDINAL, 0x05); //TODO: SkulkVibration
    clientbound1_18->Register(EntityAnimation::PACKET_ORDINAL, 0x06);
    clientbound1_18->Register(AwardStatistics::PACKET_ORDINAL, 0x07);
    clientbound1_18->Register(AcknowledgePlayerDigging::PACKET_ORDINAL, 0x08);
    clientbound1_18->Register(BlockDestroyStage::PACKET_ORDINAL, 0x09);
    clientbound1_18->Register(BlockEntityData::PACKET_ORDINAL, 0x0A);
    clientbound1_18->Register(BlockAction::PACKET_ORDINAL, 0x0B);
    clientbound1_18->Register(BlockUpdate::PACKET_ORDINAL, 0x0C);
    clientbound1_18->Register(BossBar::PACKET_ORDINAL, 0x0D);
    clientbound1_18->Register(ServerChangeDifficulty::PACKET_ORDINAL, 0x0E);
    clientbound1_18->Register(LegacyChat::PACKET_ORDINAL, 0x0F);
    clientbound1_18->Register(ClearTitle::PACKET_ORDINAL, 0x10);
    clientbound1_18->Register(CommandSuggestionResponse::PACKET_ORDINAL, 0x11);
    clientbound1_18->Register(DeclareCommands::PACKET_ORDINAL, 0x12);
    clientbound1_18->Register(CloseInventory::PACKET_ORDINAL, 0x13);
    clientbound1_18->Register(InventoryContent::PACKET_ORDINAL, 0x14);
    clientbound1_18->Register(InventoryProperty::PACKET_ORDINAL, 0x15);
    clientbound1_18->Register(InventorySlot::PACKET_ORDINAL, 0x16);
    clientbound1_18->Register(Cooldown::PACKET_ORDINAL, 0x17);
    clientbound1_18->Register(PluginMessage::PACKET_ORDINAL, 0x18);
    clientbound1_18->Register(CustomSoundEffect::PACKET_ORDINAL, 0x19);
    clientbound1_18->Register(Disconnect::PACKET_ORDINAL, 0x1A);
    clientbound1_18->Register(EntityAnimation::PACKET_ORDINAL, 0x1B);
    clientbound1_18->Register(Explosion::PACKET_ORDINAL, 0x1C);
    clientbound1_18->Register(UnloadChunk::PACKET_ORDINAL, 0x1D);
    clientbound1_18->Register(GameEvent::PACKET_ORDINAL, 0x1E);
    clientbound1_18->Register(OpenHorseInventory::PACKET_ORDINAL, 0x1F);
    clientbound1_18->Register(InitializeWorldBorder::PACKET_ORDINAL, 0x20);
    clientbound1_18->Register(KeepAlive::PACKET_ORDINAL, 0x21);
    clientbound1_18->Register(ChunkData::PACKET_ORDINAL, 0x22);
    clientbound1_18->Register(WorldEvent::PACKET_ORDINAL, 0x23);
    clientbound1_18->Register(Particle::PACKET_ORDINAL, 0x24);
    clientbound1_18->Register(ChunkLight::PACKET_ORDINAL, 0x25);
    clientbound1_18->Register(JoinGame::PACKET_ORDINAL, 0x26);
    clientbound1_18->Register(MapData::PACKET_ORDINAL, 0x27);
    clientbound1_18->Register(TradeList::PACKET_ORDINAL, 0x28);
    clientbound1_18->Register(EntityPosition::PACKET_ORDINAL, 0x29);
    clientbound1_18->Register(EntityPositionAndRotation::PACKET_ORDINAL, 0x2A);
    clientbound1_18->Register(EntityRotation::PACKET_ORDINAL, 0x2B);
    clientbound1_18->Register(MoveVehicle::PACKET_ORDINAL, 0x2C);
    clientbound1_18->Register(OpenBook::PACKET_ORDINAL, 0x2D);
    clientbound1_18->Register(OpenInventory::PACKET_ORDINAL, 0x2E);
    clientbound1_18->Register(OpenSignEditor::PACKET_ORDINAL, 0x2F);
    clientbound1_18->Register(Ping::PACKET_ORDINAL, 0x30);
    clientbound1_18->Register(CraftRecipeResponse::PACKET_ORDINAL, 0x31);
    clientbound1_18->Register(ServerPlayerAbilities::PACKET_ORDINAL, 0x32);
    clientbound1_18->Register(EndCombatEvent::PACKET_ORDINAL, 0x33);
    clientbound1_18->Register(EnterCombatEvent::PACKET_ORDINAL, 0x34);
    clientbound1_18->Register(DeathCombatEvent::PACKET_ORDINAL, 0x35);
    clientbound1_18->Register(PlayerListItem::PACKET_ORDINAL, 0x36);
    clientbound1_18->Register(PlayerFace::PACKET_ORDINAL, 0x37);
    clientbound1_18->Register(PositionRotation::PACKET_ORDINAL, 0x38);
    clientbound1_18->Register(UnlockRecipes::PACKET_ORDINAL, 0x39);
    clientbound1_18->Register(EntityRemove::PACKET_ORDINAL, 0x3A);
    clientbound1_18->Register(EntityEffectRemove::PACKET_ORDINAL, 0x3B);
    clientbound1_18->Register(ResourcePackRequest::PACKET_ORDINAL, 0x3C);
    clientbound1_18->Register(Respawn::PACKET_ORDINAL, 0x3D);
    clientbound1_18->Register(EntityLookAt::PACKET_ORDINAL, 0x3E);
    clientbound1_18->Register(SectionBlocks::PACKET_ORDINAL, 0x3F);
    clientbound1_18->Register(SelectAdvancementsTab::PACKET_ORDINAL, 0x40);
    clientbound1_18->Register(ActionBar::PACKET_ORDINAL, 0x41);
    clientbound1_18->Register(BorderCenter::PACKET_ORDINAL, 0x42);
    clientbound1_18->Register(BorderRadiusSpeed::PACKET_ORDINAL, 0x43);
    clientbound1_18->Register(BorderRadius::PACKET_ORDINAL, 0x44);
    clientbound1_18->Register(BorderWarningTime::PACKET_ORDINAL, 0x45);
    clientbound1_18->Register(BorderWarningRadius::PACKET_ORDINAL, 0x46);
    clientbound1_18->Register(Camera::PACKET_ORDINAL, 0x47);
    clientbound1_18->Register(HeldSlot::PACKET_ORDINAL, 0x48);
    clientbound1_18->Register(ViewPosition::PACKET_ORDINAL, 0x49);
    clientbound1_18->Register(ViewDistance::PACKET_ORDINAL, 0x4A);
    clientbound1_18->Register(DefaultSpawnPosition::PACKET_ORDINAL, 0x4B);
    clientbound1_18->Register(DisplayObjective::PACKET_ORDINAL, 0x4C);
    clientbound1_18->Register(EntityMetadata::PACKET_ORDINAL, 0x4D);
    clientbound1_18->Register(LeadEntities::PACKET_ORDINAL, 0x4E);
    clientbound1_18->Register(EntityVelocity::PACKET_ORDINAL, 0x4F);
    clientbound1_18->Register(EntityEquipment::PACKET_ORDINAL, 0x50);
    clientbound1_18->Register(Experience::PACKET_ORDINAL, 0x51);
    clientbound1_18->Register(Health::PACKET_ORDINAL, 0x52);
    clientbound1_18->Register(Objectives::PACKET_ORDINAL, 0x53);
    clientbound1_18->Register(Passengers::PACKET_ORDINAL, 0x54);
    clientbound1_18->Register(Teams::PACKET_ORDINAL, 0x55);
    clientbound1_18->Register(Score::PACKET_ORDINAL, 0x56);
    clientbound1_18->Register(SimulationDistance::PACKET_ORDINAL, 0x57);
    clientbound1_18->Register(Subtitle::PACKET_ORDINAL, 0x58);
    clientbound1_18->Register(WorldTime::PACKET_ORDINAL, 0x59);
    clientbound1_18->Register(Title::PACKET_ORDINAL, 0x5A);
    clientbound1_18->Register(TitleTimes::PACKET_ORDINAL, 0x5B);
    clientbound1_18->Register(EntitySoundEffect::PACKET_ORDINAL, 0x5C);
    clientbound1_18->Register(HardcodedSoundEffect::PACKET_ORDINAL, 0x5D);
    clientbound1_18->Register(StopSound::PACKET_ORDINAL, 0x5E);
    clientbound1_18->Register(TabHeaderFooter::PACKET_ORDINAL, 0x5F);
    clientbound1_18->Register(TagQueryResponse::PACKET_ORDINAL, 0x60);
    clientbound1_18->Register(PickupItem::PACKET_ORDINAL, 0x61);
    clientbound1_18->Register(EntityTeleport::PACKET_ORDINAL, 0x62);
    clientbound1_18->Register(Advancements::PACKET_ORDINAL, 0x63);
    clientbound1_18->Register(EntityProperties::PACKET_ORDINAL, 0x64);
    clientbound1_18->Register(EntityEffect::PACKET_ORDINAL, 0x65);
    clientbound1_18->Register(Recipes::PACKET_ORDINAL, 0x66);
    clientbound1_18->Register(Tags::PACKET_ORDINAL, 0x67);

    VersionRegistry* clientbound1_19 = clientboundRegistry + ProtocolVersion::MINECRAFT_1_19.GetPacketIDOrdinal();
    clientbound1_19->Register(SpawnEntity::PACKET_ORDINAL, 0x00);
    clientbound1_19->Register(SpawnExperienceOrb::PACKET_ORDINAL, 0x01);
    clientbound1_19->Register(SpawnPlayer::PACKET_ORDINAL, 0x02);
    clientbound1_19->Register(EntityAnimation::PACKET_ORDINAL, 0x03);
    clientbound1_19->Register(AwardStatistics::PACKET_ORDINAL, 0x04);
    clientbound1_19->Register(AcknowledgeBlockChange::PACKET_ORDINAL, 0x05);
    clientbound1_19->Register(BlockDestroyStage::PACKET_ORDINAL, 0x06);
    clientbound1_19->Register(BlockEntityData::PACKET_ORDINAL, 0x07);
    clientbound1_19->Register(BlockAction::PACKET_ORDINAL, 0x08);
    clientbound1_19->Register(BlockUpdate::PACKET_ORDINAL, 0x09);
    clientbound1_19->Register(BossBar::PACKET_ORDINAL, 0x0A);
    clientbound1_19->Register(ServerChangeDifficulty::PACKET_ORDINAL, 0x0B);
    clientbound1_19->Register(ServerChatPreview::PACKET_ORDINAL, 0x0C);
    clientbound1_19->Register(ClearTitle::PACKET_ORDINAL, 0x1D);
    clientbound1_19->Register(CommandSuggestionResponse::PACKET_ORDINAL, 0x1E);
    clientbound1_19->Register(DeclareCommands::PACKET_ORDINAL, 0x1F);
    clientbound1_19->Register(CloseInventory::PACKET_ORDINAL, 0x10);
    clientbound1_19->Register(InventoryContent::PACKET_ORDINAL, 0x11);
    clientbound1_19->Register(InventoryProperty::PACKET_ORDINAL, 0x12);
    clientbound1_19->Register(InventorySlot::PACKET_ORDINAL, 0x13);
    clientbound1_19->Register(Cooldown::PACKET_ORDINAL, 0x14);
    clientbound1_19->Register(PluginMessage::PACKET_ORDINAL, 0x15);
    clientbound1_19->Register(CustomSoundEffect::PACKET_ORDINAL, 0x16);
    clientbound1_19->Register(Disconnect::PACKET_ORDINAL, 0x17);
    clientbound1_19->Register(EntityAnimation::PACKET_ORDINAL, 0x18);
    clientbound1_19->Register(Explosion::PACKET_ORDINAL, 0x19);
    clientbound1_19->Register(UnloadChunk::PACKET_ORDINAL, 0x1A);
    clientbound1_19->Register(GameEvent::PACKET_ORDINAL, 0x1B);
    clientbound1_19->Register(OpenHorseInventory::PACKET_ORDINAL, 0x1C);
    clientbound1_19->Register(InitializeWorldBorder::PACKET_ORDINAL, 0x1D);
    clientbound1_19->Register(KeepAlive::PACKET_ORDINAL, 0x1E);
    clientbound1_19->Register(ChunkData::PACKET_ORDINAL, 0x1F);
    clientbound1_19->Register(WorldEvent::PACKET_ORDINAL, 0x20);
    clientbound1_19->Register(Particle::PACKET_ORDINAL, 0x21);
    clientbound1_19->Register(ChunkLight::PACKET_ORDINAL, 0x22);
    clientbound1_19->Register(JoinGame::PACKET_ORDINAL, 0x23);
    clientbound1_19->Register(MapData::PACKET_ORDINAL, 0x24);
    clientbound1_19->Register(TradeList::PACKET_ORDINAL, 0x25);
    clientbound1_19->Register(EntityPosition::PACKET_ORDINAL, 0x26);
    clientbound1_19->Register(EntityPositionAndRotation::PACKET_ORDINAL, 0x27);
    clientbound1_19->Register(EntityRotation::PACKET_ORDINAL, 0x28);
    clientbound1_19->Register(MoveVehicle::PACKET_ORDINAL, 0x29);
    clientbound1_19->Register(OpenBook::PACKET_ORDINAL, 0x2A);
    clientbound1_19->Register(OpenInventory::PACKET_ORDINAL, 0x2B);
    clientbound1_19->Register(OpenSignEditor::PACKET_ORDINAL, 0x2C);
    clientbound1_19->Register(Ping::PACKET_ORDINAL, 0x2D);
    clientbound1_19->Register(CraftRecipeResponse::PACKET_ORDINAL, 0x2E);
    clientbound1_19->Register(ServerPlayerAbilities::PACKET_ORDINAL, 0x2F);
    clientbound1_19->Register(ServerPlayerChat::PACKET_ORDINAL, 0x30);
    clientbound1_19->Register(EndCombatEvent::PACKET_ORDINAL, 0x31);
    clientbound1_19->Register(EnterCombatEvent::PACKET_ORDINAL, 0x32);
    clientbound1_19->Register(DeathCombatEvent::PACKET_ORDINAL, 0x33);
    clientbound1_19->Register(PlayerListItem::PACKET_ORDINAL, 0x34);
    clientbound1_19->Register(PlayerFace::PACKET_ORDINAL, 0x35);
    clientbound1_19->Register(PositionRotation::PACKET_ORDINAL, 0x36);
    clientbound1_19->Register(UnlockRecipes::PACKET_ORDINAL, 0x37);
    clientbound1_19->Register(EntityRemove::PACKET_ORDINAL, 0x38);
    clientbound1_19->Register(EntityEffectRemove::PACKET_ORDINAL, 0x39);
    clientbound1_19->Register(ResourcePackRequest::PACKET_ORDINAL, 0x3A);
    clientbound1_19->Register(Respawn::PACKET_ORDINAL, 0x3B);
    clientbound1_19->Register(EntityLookAt::PACKET_ORDINAL, 0x3C);
    clientbound1_19->Register(SectionBlocks::PACKET_ORDINAL, 0x3D);
    clientbound1_19->Register(SelectAdvancementsTab::PACKET_ORDINAL, 0x3E);
    clientbound1_19->Register(ServerData::PACKET_ORDINAL, 0x3F);
    clientbound1_19->Register(ActionBar::PACKET_ORDINAL, 0x40);
    clientbound1_19->Register(BorderCenter::PACKET_ORDINAL, 0x41);
    clientbound1_19->Register(BorderRadiusSpeed::PACKET_ORDINAL, 0x42);
    clientbound1_19->Register(BorderRadius::PACKET_ORDINAL, 0x43);
    clientbound1_19->Register(BorderWarningTime::PACKET_ORDINAL, 0x44);
    clientbound1_19->Register(BorderWarningRadius::PACKET_ORDINAL, 0x45);
    clientbound1_19->Register(Camera::PACKET_ORDINAL, 0x46);
    clientbound1_19->Register(HeldSlot::PACKET_ORDINAL, 0x47);
    clientbound1_19->Register(ViewPosition::PACKET_ORDINAL, 0x48);
    clientbound1_19->Register(ViewDistance::PACKET_ORDINAL, 0x49);
    clientbound1_19->Register(DefaultSpawnPosition::PACKET_ORDINAL, 0x4A);
    clientbound1_19->Register(DisplayObjective::PACKET_ORDINAL, 0x4B);
    clientbound1_19->Register(EntityMetadata::PACKET_ORDINAL, 0x4C);
    clientbound1_19->Register(LeadEntities::PACKET_ORDINAL, 0x4D);
    clientbound1_19->Register(EntityVelocity::PACKET_ORDINAL, 0x4E);
    clientbound1_19->Register(EntityEquipment::PACKET_ORDINAL, 0x4F);
    clientbound1_19->Register(Experience::PACKET_ORDINAL, 0x50);
    clientbound1_19->Register(Health::PACKET_ORDINAL, 0x52);
    clientbound1_19->Register(Objectives::PACKET_ORDINAL, 0x53);
    clientbound1_19->Register(Passengers::PACKET_ORDINAL, 0x54);
    clientbound1_19->Register(Teams::PACKET_ORDINAL, 0x55);
    clientbound1_19->Register(Score::PACKET_ORDINAL, 0x56);
    clientbound1_19->Register(SimulationDistance::PACKET_ORDINAL, 0x57);
    clientbound1_19->Register(Subtitle::PACKET_ORDINAL, 0x58);
    clientbound1_19->Register(WorldTime::PACKET_ORDINAL, 0x59);
    clientbound1_19->Register(Title::PACKET_ORDINAL, 0x5A);
    clientbound1_19->Register(TitleTimes::PACKET_ORDINAL, 0x5B);
    clientbound1_19->Register(EntitySoundEffect::PACKET_ORDINAL, 0x5C);
    clientbound1_19->Register(HardcodedSoundEffect::PACKET_ORDINAL, 0x5D);
    clientbound1_19->Register(StopSound::PACKET_ORDINAL, 0x5E);
    clientbound1_19->Register(SystemChat::PACKET_ORDINAL, 0x5F);
    clientbound1_19->Register(TabHeaderFooter::PACKET_ORDINAL, 0x60);
    clientbound1_19->Register(TagQueryResponse::PACKET_ORDINAL, 0x61);
    clientbound1_19->Register(PickupItem::PACKET_ORDINAL, 0x62);
    clientbound1_19->Register(EntityTeleport::PACKET_ORDINAL, 0x63);
    clientbound1_19->Register(Advancements::PACKET_ORDINAL, 0x64);
    clientbound1_19->Register(EntityProperties::PACKET_ORDINAL, 0x65);
    clientbound1_19->Register(EntityEffect::PACKET_ORDINAL, 0x66);
    clientbound1_19->Register(Recipes::PACKET_ORDINAL, 0x67);
    clientbound1_19->Register(Tags::PACKET_ORDINAL, 0x68);

    VersionRegistry* clientbound1_19_1 = clientboundRegistry + ProtocolVersion::MINECRAFT_1_19_1.GetPacketIDOrdinal();
    clientbound1_19_1->Register(SpawnEntity::PACKET_ORDINAL, 0x00);
    clientbound1_19_1->Register(SpawnExperienceOrb::PACKET_ORDINAL, 0x01);
    clientbound1_19_1->Register(SpawnPlayer::PACKET_ORDINAL, 0x02);
    clientbound1_19_1->Register(EntityAnimation::PACKET_ORDINAL, 0x03);
    clientbound1_19_1->Register(AwardStatistics::PACKET_ORDINAL, 0x04);
    clientbound1_19_1->Register(AcknowledgeBlockChange::PACKET_ORDINAL, 0x05);
    clientbound1_19_1->Register(BlockDestroyStage::PACKET_ORDINAL, 0x06);
    clientbound1_19_1->Register(BlockEntityData::PACKET_ORDINAL, 0x07);
    clientbound1_19_1->Register(BlockAction::PACKET_ORDINAL, 0x08);
    clientbound1_19_1->Register(BlockUpdate::PACKET_ORDINAL, 0x09);
    clientbound1_19_1->Register(BossBar::PACKET_ORDINAL, 0x0A);
    clientbound1_19_1->Register(ServerChangeDifficulty::PACKET_ORDINAL, 0x0B);
    clientbound1_19_1->Register(ServerChatPreview::PACKET_ORDINAL, 0x0C);
    clientbound1_19_1->Register(ClearTitle::PACKET_ORDINAL, 0x1D);
    clientbound1_19_1->Register(CommandSuggestionResponse::PACKET_ORDINAL, 0x1E);
    clientbound1_19_1->Register(DeclareCommands::PACKET_ORDINAL, 0x1F);
    clientbound1_19_1->Register(CloseInventory::PACKET_ORDINAL, 0x10);
    clientbound1_19_1->Register(InventoryContent::PACKET_ORDINAL, 0x11);
    clientbound1_19_1->Register(InventoryProperty::PACKET_ORDINAL, 0x12);
    clientbound1_19_1->Register(InventorySlot::PACKET_ORDINAL, 0x13);
    clientbound1_19_1->Register(Cooldown::PACKET_ORDINAL, 0x14);
    clientbound1_19_1->Register(ChatSuggestions::PACKET_ORDINAL, 0x15);
    clientbound1_19_1->Register(PluginMessage::PACKET_ORDINAL, 0x16);
    clientbound1_19_1->Register(CustomSoundEffect::PACKET_ORDINAL, 0x17);
    clientbound1_19_1->Register(HideMessage::PACKET_ORDINAL, 0x18);
    clientbound1_19_1->Register(Disconnect::PACKET_ORDINAL, 0x19);
    clientbound1_19_1->Register(EntityEvent::PACKET_ORDINAL, 0x1A);
    clientbound1_19_1->Register(Explosion::PACKET_ORDINAL, 0x1B);
    clientbound1_19_1->Register(UnloadChunk::PACKET_ORDINAL, 0x1C);
    clientbound1_19_1->Register(GameEvent::PACKET_ORDINAL, 0x1D);
    clientbound1_19_1->Register(OpenHorseInventory::PACKET_ORDINAL, 0x1E);
    clientbound1_19_1->Register(InitializeWorldBorder::PACKET_ORDINAL, 0x1F);
    clientbound1_19_1->Register(KeepAlive::PACKET_ORDINAL, 0x20);
    clientbound1_19_1->Register(ChunkData::PACKET_ORDINAL, 0x21);
    clientbound1_19_1->Register(WorldEvent::PACKET_ORDINAL, 0x22);
    clientbound1_19_1->Register(Particle::PACKET_ORDINAL, 0x23);
    clientbound1_19_1->Register(ChunkLight::PACKET_ORDINAL, 0x24);
    clientbound1_19_1->Register(JoinGame::PACKET_ORDINAL, 0x25);
    clientbound1_19_1->Register(MapData::PACKET_ORDINAL, 0x26);
    clientbound1_19_1->Register(TradeList::PACKET_ORDINAL, 0x27);
    clientbound1_19_1->Register(EntityPosition::PACKET_ORDINAL, 0x28);
    clientbound1_19_1->Register(EntityPositionAndRotation::PACKET_ORDINAL, 0x29);
    clientbound1_19_1->Register(EntityRotation::PACKET_ORDINAL, 0x2A);
    clientbound1_19_1->Register(MoveVehicle::PACKET_ORDINAL, 0x2B);
    clientbound1_19_1->Register(OpenBook::PACKET_ORDINAL, 0x2C);
    clientbound1_19_1->Register(OpenInventory::PACKET_ORDINAL, 0x2D);
    clientbound1_19_1->Register(OpenSignEditor::PACKET_ORDINAL, 0x2E);
    clientbound1_19_1->Register(Ping::PACKET_ORDINAL, 0x2F);
    clientbound1_19_1->Register(CraftRecipeResponse::PACKET_ORDINAL, 0x30);
    clientbound1_19_1->Register(ServerPlayerAbilities::PACKET_ORDINAL, 0x31);
    clientbound1_19_1->Register(MessageHeader::PACKET_ORDINAL, 0x32);
    clientbound1_19_1->Register(ServerPlayerChat::PACKET_ORDINAL, 0x33);
    clientbound1_19_1->Register(EndCombatEvent::PACKET_ORDINAL, 0x34);
    clientbound1_19_1->Register(EnterCombatEvent::PACKET_ORDINAL, 0x35);
    clientbound1_19_1->Register(DeathCombatEvent::PACKET_ORDINAL, 0x36);
    clientbound1_19_1->Register(PlayerListItem::PACKET_ORDINAL, 0x37);
    clientbound1_19_1->Register(PlayerFace::PACKET_ORDINAL, 0x38);
    clientbound1_19_1->Register(PositionRotation::PACKET_ORDINAL, 0x39);
    clientbound1_19_1->Register(UnlockRecipes::PACKET_ORDINAL, 0x3A);
    clientbound1_19_1->Register(EntityRemove::PACKET_ORDINAL, 0x3B);
    clientbound1_19_1->Register(EntityEffectRemove::PACKET_ORDINAL, 0x3C);
    clientbound1_19_1->Register(ResourcePackRequest::PACKET_ORDINAL, 0x3D);
    clientbound1_19_1->Register(Respawn::PACKET_ORDINAL, 0x3E);
    clientbound1_19_1->Register(EntityLookAt::PACKET_ORDINAL, 0x3F);
    clientbound1_19_1->Register(SectionBlocks::PACKET_ORDINAL, 0x40);
    clientbound1_19_1->Register(SelectAdvancementsTab::PACKET_ORDINAL, 0x41);
    clientbound1_19_1->Register(ServerData::PACKET_ORDINAL, 0x42);
    clientbound1_19_1->Register(ActionBar::PACKET_ORDINAL, 0x43);
    clientbound1_19_1->Register(BorderCenter::PACKET_ORDINAL, 0x44);
    clientbound1_19_1->Register(BorderRadiusSpeed::PACKET_ORDINAL, 0x45);
    clientbound1_19_1->Register(BorderRadius::PACKET_ORDINAL, 0x46);
    clientbound1_19_1->Register(BorderWarningTime::PACKET_ORDINAL, 0x47);
    clientbound1_19_1->Register(BorderWarningRadius::PACKET_ORDINAL, 0x48);
    clientbound1_19_1->Register(Camera::PACKET_ORDINAL, 0x49);
    clientbound1_19_1->Register(HeldSlot::PACKET_ORDINAL, 0x4A);
    clientbound1_19_1->Register(ViewPosition::PACKET_ORDINAL, 0x4B);
    clientbound1_19_1->Register(ViewDistance::PACKET_ORDINAL, 0x4C);
    clientbound1_19_1->Register(DefaultSpawnPosition::PACKET_ORDINAL, 0x4D);
    //    clientbound1_19_1->Register(SetDisplayChatPreview::PACKET_ORDINAL, 0x4E); //TODO: SetDisplayChatPreview
    clientbound1_19_1->Register(DisplayObjective::PACKET_ORDINAL, 0x4F);
    clientbound1_19_1->Register(EntityMetadata::PACKET_ORDINAL, 0x50);
    clientbound1_19_1->Register(LeadEntities::PACKET_ORDINAL, 0x51);
    clientbound1_19_1->Register(EntityVelocity::PACKET_ORDINAL, 0x52);
    clientbound1_19_1->Register(EntityEquipment::PACKET_ORDINAL, 0x53);
    clientbound1_19_1->Register(Experience::PACKET_ORDINAL, 0x54);
    clientbound1_19_1->Register(Health::PACKET_ORDINAL, 0x55);
    clientbound1_19_1->Register(Objectives::PACKET_ORDINAL, 0x56);
    clientbound1_19_1->Register(Passengers::PACKET_ORDINAL, 0x57);
    clientbound1_19_1->Register(Teams::PACKET_ORDINAL, 0x58);
    clientbound1_19_1->Register(Score::PACKET_ORDINAL, 0x59);
    clientbound1_19_1->Register(SimulationDistance::PACKET_ORDINAL, 0x5A);
    clientbound1_19_1->Register(Subtitle::PACKET_ORDINAL, 0x5B);
    clientbound1_19_1->Register(WorldTime::PACKET_ORDINAL, 0x5C);
    clientbound1_19_1->Register(Title::PACKET_ORDINAL, 0x5D);
    clientbound1_19_1->Register(TitleTimes::PACKET_ORDINAL, 0x5E);
    clientbound1_19_1->Register(EntitySoundEffect::PACKET_ORDINAL, 0x5F);
    clientbound1_19_1->Register(HardcodedSoundEffect::PACKET_ORDINAL, 0x60);
    clientbound1_19_1->Register(StopSound::PACKET_ORDINAL, 0x61);
    clientbound1_19_1->Register(SystemChat::PACKET_ORDINAL, 0x62);
    clientbound1_19_1->Register(TabHeaderFooter::PACKET_ORDINAL, 0x63);
    clientbound1_19_1->Register(TagQueryResponse::PACKET_ORDINAL, 0x64);
    clientbound1_19_1->Register(PickupItem::PACKET_ORDINAL, 0x65);
    clientbound1_19_1->Register(EntityTeleport::PACKET_ORDINAL, 0x66);
    clientbound1_19_1->Register(Advancements::PACKET_ORDINAL, 0x67);
    clientbound1_19_1->Register(EntityProperties::PACKET_ORDINAL, 0x68);
    clientbound1_19_1->Register(EntityEffect::PACKET_ORDINAL, 0x69);
    clientbound1_19_1->Register(Recipes::PACKET_ORDINAL, 0x6A);
    clientbound1_19_1->Register(Tags::PACKET_ORDINAL, 0x6B);

    VersionRegistry* serverboundRegistry = DirectionRegistry::NewVersionRegistry();
    VersionRegistry* serverbound1_12_2 = serverboundRegistry + ProtocolVersion::MINECRAFT_1_12_2.GetPacketIDOrdinal();
    serverbound1_12_2->Register(ConfirmTeleport::PACKET_ORDINAL, 0x00);
    serverbound1_12_2->Register(CommandSuggestionRequest::PACKET_ORDINAL, 0x01);
    serverbound1_12_2->Register(LegacyChat::PACKET_ORDINAL, 0x02);
    serverbound1_12_2->Register(ClientAction::PACKET_ORDINAL, 0x03);
    serverbound1_12_2->Register(ClientSettings::PACKET_ORDINAL, 0x04);
    serverbound1_12_2->Register(ConfirmTransaction::PACKET_ORDINAL, 0x05);
    serverbound1_12_2->Register(LegacyEnchant::PACKET_ORDINAL, 0x06);
    serverbound1_12_2->Register(ClickSlot::PACKET_ORDINAL, 0x07);
    serverbound1_12_2->Register(CloseInventory::PACKET_ORDINAL, 0x08);
    serverbound1_12_2->Register(PluginMessage::PACKET_ORDINAL, 0x09);
    serverbound1_12_2->Register(EntityInteract::PACKET_ORDINAL, 0x0A);
    serverbound1_12_2->Register(KeepAlive::PACKET_ORDINAL, 0x0B);
    serverbound1_12_2->Register(MoveGroundOnly::PACKET_ORDINAL, 0x0C);
    serverbound1_12_2->Register(MovePositionOnly::PACKET_ORDINAL, 0x0D);
    serverbound1_12_2->Register(Move::PACKET_ORDINAL, 0x0E);
    serverbound1_12_2->Register(MoveRotationOnly::PACKET_ORDINAL, 0x0F);
    serverbound1_12_2->Register(MoveVehicle::PACKET_ORDINAL, 0x10);
    serverbound1_12_2->Register(BoatPaddle::PACKET_ORDINAL, 0x11);
    serverbound1_12_2->Register(CraftRecipeRequest::PACKET_ORDINAL, 0x12);
    serverbound1_12_2->Register(ClientPlayerAbilities::PACKET_ORDINAL, 0x13);
    serverbound1_12_2->Register(Digging::PACKET_ORDINAL, 0x14);
    serverbound1_12_2->Register(EntityAction::PACKET_ORDINAL, 0x15);
    serverbound1_12_2->Register(PlayerInput::PACKET_ORDINAL, 0x16);
    serverbound1_12_2->Register(LegacyRecipeBook::PACKET_ORDINAL, 0x17);
    serverbound1_12_2->Register(ResourcePackResponse::PACKET_ORDINAL, 0x18);
    serverbound1_12_2->Register(SelectAdvancementsTab::PACKET_ORDINAL, 0x19);
    serverbound1_12_2->Register(HeldSlot::PACKET_ORDINAL, 0x1A);
    serverbound1_12_2->Register(EditSign::PACKET_ORDINAL, 0x1B);
    serverbound1_12_2->Register(SwingArm::PACKET_ORDINAL, 0x1C);
    serverbound1_12_2->Register(Spectate::PACKET_ORDINAL, 0x1D);
    serverbound1_12_2->Register(Camera::PACKET_ORDINAL, 0x1E);
    serverbound1_12_2->Register(PlaceBlock::PACKET_ORDINAL, 0x1F);
    serverbound1_12_2->Register(UseItem::PACKET_ORDINAL, 0x20);

    VersionRegistry* serverbound1_13 = serverboundRegistry + ProtocolVersion::MINECRAFT_1_13.GetPacketIDOrdinal();
    serverbound1_13->Register(ConfirmTeleport::PACKET_ORDINAL, 0x00);
    serverbound1_13->Register(BlockTagQueryRequest::PACKET_ORDINAL, 0x01);
    serverbound1_13->Register(LegacyChat::PACKET_ORDINAL, 0x02);
    serverbound1_13->Register(ClientAction::PACKET_ORDINAL, 0x03);
    serverbound1_13->Register(ClientSettings::PACKET_ORDINAL, 0x04);
    serverbound1_13->Register(CommandSuggestionRequest::PACKET_ORDINAL, 0x05);
    serverbound1_13->Register(ConfirmTransaction::PACKET_ORDINAL, 0x06);
    serverbound1_13->Register(LegacyEnchant::PACKET_ORDINAL, 0x07);
    serverbound1_13->Register(ClickSlot::PACKET_ORDINAL, 0x08);
    serverbound1_13->Register(CloseInventory::PACKET_ORDINAL, 0x09);
    serverbound1_13->Register(PluginMessage::PACKET_ORDINAL, 0x0A);
    serverbound1_13->Register(EditBook::PACKET_ORDINAL, 0x0B);
    serverbound1_13->Register(TagQueryRequest::PACKET_ORDINAL, 0x0C);
    serverbound1_13->Register(EntityInteract::PACKET_ORDINAL, 0x0D);
    serverbound1_13->Register(KeepAlive::PACKET_ORDINAL, 0x0E);
    serverbound1_13->Register(MoveGroundOnly::PACKET_ORDINAL, 0x0F);
    serverbound1_13->Register(MovePositionOnly::PACKET_ORDINAL, 0x10);
    serverbound1_13->Register(Move::PACKET_ORDINAL, 0x11);
    serverbound1_13->Register(MoveRotationOnly::PACKET_ORDINAL, 0x12);
    serverbound1_13->Register(MoveVehicle::PACKET_ORDINAL, 0x13);
    serverbound1_13->Register(BoatPaddle::PACKET_ORDINAL, 0x14);
    serverbound1_13->Register(PickItem::PACKET_ORDINAL, 0x15);
    serverbound1_13->Register(CraftRecipeRequest::PACKET_ORDINAL, 0x16);
    serverbound1_13->Register(ClientPlayerAbilities::PACKET_ORDINAL, 0x17);
    serverbound1_13->Register(Digging::PACKET_ORDINAL, 0x18);
    serverbound1_13->Register(EntityAction::PACKET_ORDINAL, 0x19);
    serverbound1_13->Register(PlayerInput::PACKET_ORDINAL, 0x1A);
    serverbound1_13->Register(LegacyRecipeBook::PACKET_ORDINAL, 0x1B);
    serverbound1_13->Register(RenameItem::PACKET_ORDINAL, 0x1C);
    serverbound1_13->Register(ResourcePackResponse::PACKET_ORDINAL, 0x1D);
    serverbound1_13->Register(SelectAdvancementsTab::PACKET_ORDINAL, 0x1E);
    serverbound1_13->Register(SelectTrade::PACKET_ORDINAL, 0x1F);
    serverbound1_13->Register(BeaconEffect::PACKET_ORDINAL, 0x20);
    serverbound1_13->Register(HeldSlot::PACKET_ORDINAL, 0x21);
    serverbound1_13->Register(ProgramCommandBlock::PACKET_ORDINAL, 0x22);
    serverbound1_13->Register(ProgramCommandBlockMinecart::PACKET_ORDINAL, 0x23);
    serverbound1_13->Register(CreativeSlot::PACKET_ORDINAL, 0x24);
    serverbound1_13->Register(ProgramStructureBlock::PACKET_ORDINAL, 0x25);
    serverbound1_13->Register(EditSign::PACKET_ORDINAL, 0x26);
    serverbound1_13->Register(SwingArm::PACKET_ORDINAL, 0x27);
    serverbound1_13->Register(Spectate::PACKET_ORDINAL, 0x28);
    serverbound1_13->Register(PlaceBlock::PACKET_ORDINAL, 0x29);
    serverbound1_13->Register(UseItem::PACKET_ORDINAL, 0x2A);

    VersionRegistry* serverbound1_14 = serverboundRegistry + ProtocolVersion::MINECRAFT_1_14.GetPacketIDOrdinal();
    serverbound1_14->Register(ConfirmTeleport::PACKET_ORDINAL, 0x00);
    serverbound1_14->Register(BlockTagQueryRequest::PACKET_ORDINAL, 0x01);
    serverbound1_14->Register(ClientChangeDifficulty::PACKET_ORDINAL, 0x02);
    serverbound1_14->Register(LegacyChat::PACKET_ORDINAL, 0x03);
    serverbound1_14->Register(ClientAction::PACKET_ORDINAL, 0x04);
    serverbound1_14->Register(ClientSettings::PACKET_ORDINAL, 0x05);
    serverbound1_14->Register(CommandSuggestionRequest::PACKET_ORDINAL, 0x06);
    serverbound1_14->Register(ConfirmTransaction::PACKET_ORDINAL, 0x07);
    serverbound1_14->Register(ClickInventoryButton::PACKET_ORDINAL, 0x08);
    serverbound1_14->Register(ClickSlot::PACKET_ORDINAL, 0x09);
    serverbound1_14->Register(CloseInventory::PACKET_ORDINAL, 0x0A);
    serverbound1_14->Register(PluginMessage::PACKET_ORDINAL, 0x0B);
    serverbound1_14->Register(EditBook::PACKET_ORDINAL, 0x0C);
    serverbound1_14->Register(TagQueryRequest::PACKET_ORDINAL, 0x0D);
    serverbound1_14->Register(EntityInteract::PACKET_ORDINAL, 0x0E);
    serverbound1_14->Register(KeepAlive::PACKET_ORDINAL, 0x0F);
    serverbound1_14->Register(LockDifficulty::PACKET_ORDINAL, 0x10);
    serverbound1_14->Register(MoveGroundOnly::PACKET_ORDINAL, 0x11);
    serverbound1_14->Register(MovePositionOnly::PACKET_ORDINAL, 0x12);
    serverbound1_14->Register(Move::PACKET_ORDINAL, 0x13);
    serverbound1_14->Register(MoveRotationOnly::PACKET_ORDINAL, 0x14);
    serverbound1_14->Register(MoveVehicle::PACKET_ORDINAL, 0x15);
    serverbound1_14->Register(BoatPaddle::PACKET_ORDINAL, 0x16);
    serverbound1_14->Register(PickItem::PACKET_ORDINAL, 0x17);
    serverbound1_14->Register(CraftRecipeRequest::PACKET_ORDINAL, 0x18);
    serverbound1_14->Register(ClientPlayerAbilities::PACKET_ORDINAL, 0x19);
    serverbound1_14->Register(Digging::PACKET_ORDINAL, 0x1A);
    serverbound1_14->Register(EntityAction::PACKET_ORDINAL, 0x1B);
    serverbound1_14->Register(PlayerInput::PACKET_ORDINAL, 0x1C);
    serverbound1_14->Register(LegacyRecipeBook::PACKET_ORDINAL, 0x1D);
    serverbound1_14->Register(RenameItem::PACKET_ORDINAL, 0x1E);
    serverbound1_14->Register(ResourcePackResponse::PACKET_ORDINAL, 0x1F);
    serverbound1_14->Register(SelectAdvancementsTab::PACKET_ORDINAL, 0x20);
    serverbound1_14->Register(SelectTrade::PACKET_ORDINAL, 0x21);
    serverbound1_14->Register(BeaconEffect::PACKET_ORDINAL, 0x22);
    serverbound1_14->Register(HeldSlot::PACKET_ORDINAL, 0x23);
    serverbound1_14->Register(ProgramCommandBlock::PACKET_ORDINAL, 0x24);
    serverbound1_14->Register(ProgramCommandBlockMinecart::PACKET_ORDINAL, 0x25);
    serverbound1_14->Register(CreativeSlot::PACKET_ORDINAL, 0x26);
    serverbound1_14->Register(ProgramJigsawBlock::PACKET_ORDINAL, 0x27);
    serverbound1_14->Register(ProgramStructureBlock::PACKET_ORDINAL, 0x28);
    serverbound1_14->Register(EditSign::PACKET_ORDINAL, 0x29);
    serverbound1_14->Register(SwingArm::PACKET_ORDINAL, 0x2A);
    serverbound1_14->Register(Spectate::PACKET_ORDINAL, 0x2B);
    serverbound1_14->Register(PlaceBlock::PACKET_ORDINAL, 0x2C);
    serverbound1_14->Register(UseItem::PACKET_ORDINAL, 0x2D);

    VersionRegistry* serverbound1_15 = serverboundRegistry + ProtocolVersion::MINECRAFT_1_15.GetPacketIDOrdinal();
    serverbound1_15->Register(ConfirmTeleport::PACKET_ORDINAL, 0x00);
    serverbound1_15->Register(BlockTagQueryRequest::PACKET_ORDINAL, 0x01);
    serverbound1_15->Register(ClientChangeDifficulty::PACKET_ORDINAL, 0x02);
    serverbound1_15->Register(LegacyChat::PACKET_ORDINAL, 0x03);
    serverbound1_15->Register(ClientAction::PACKET_ORDINAL, 0x04);
    serverbound1_15->Register(ClientSettings::PACKET_ORDINAL, 0x05);
    serverbound1_15->Register(CommandSuggestionRequest::PACKET_ORDINAL, 0x06);
    serverbound1_15->Register(ConfirmTransaction::PACKET_ORDINAL, 0x07);
    serverbound1_15->Register(ClickInventoryButton::PACKET_ORDINAL, 0x08);
    serverbound1_15->Register(ClickSlot::PACKET_ORDINAL, 0x09);
    serverbound1_15->Register(CloseInventory::PACKET_ORDINAL, 0x0A);
    serverbound1_15->Register(PluginMessage::PACKET_ORDINAL, 0x0B);
    serverbound1_15->Register(EditBook::PACKET_ORDINAL, 0x0C);
    serverbound1_15->Register(TagQueryRequest::PACKET_ORDINAL, 0x0D);
    serverbound1_15->Register(EntityInteract::PACKET_ORDINAL, 0x0E);
    serverbound1_15->Register(KeepAlive::PACKET_ORDINAL, 0x0F);
    serverbound1_15->Register(LockDifficulty::PACKET_ORDINAL, 0x10);
    serverbound1_15->Register(MoveGroundOnly::PACKET_ORDINAL, 0x11);
    serverbound1_15->Register(MovePositionOnly::PACKET_ORDINAL, 0x12);
    serverbound1_15->Register(Move::PACKET_ORDINAL, 0x13);
    serverbound1_15->Register(MoveRotationOnly::PACKET_ORDINAL, 0x14);
    serverbound1_15->Register(MoveVehicle::PACKET_ORDINAL, 0x15);
    serverbound1_15->Register(BoatPaddle::PACKET_ORDINAL, 0x16);
    serverbound1_15->Register(PickItem::PACKET_ORDINAL, 0x17);
    serverbound1_15->Register(CraftRecipeRequest::PACKET_ORDINAL, 0x18);
    serverbound1_15->Register(ClientPlayerAbilities::PACKET_ORDINAL, 0x19);
    serverbound1_15->Register(Digging::PACKET_ORDINAL, 0x1A);
    serverbound1_15->Register(EntityAction::PACKET_ORDINAL, 0x1B);
    serverbound1_15->Register(PlayerInput::PACKET_ORDINAL, 0x1C);
    serverbound1_15->Register(LegacyRecipeBook::PACKET_ORDINAL, 0x1D);
    serverbound1_15->Register(RenameItem::PACKET_ORDINAL, 0x1E);
    serverbound1_15->Register(ResourcePackResponse::PACKET_ORDINAL, 0x1F);
    serverbound1_15->Register(SelectAdvancementsTab::PACKET_ORDINAL, 0x20);
    serverbound1_15->Register(SelectTrade::PACKET_ORDINAL, 0x21);
    serverbound1_15->Register(BeaconEffect::PACKET_ORDINAL, 0x22);
    serverbound1_15->Register(HeldSlot::PACKET_ORDINAL, 0x23);
    serverbound1_15->Register(ProgramCommandBlock::PACKET_ORDINAL, 0x24);
    serverbound1_15->Register(ProgramCommandBlockMinecart::PACKET_ORDINAL, 0x25);
    serverbound1_15->Register(CreativeSlot::PACKET_ORDINAL, 0x26);
    serverbound1_15->Register(ProgramJigsawBlock::PACKET_ORDINAL, 0x27);
    serverbound1_15->Register(ProgramStructureBlock::PACKET_ORDINAL, 0x28);
    serverbound1_15->Register(EditSign::PACKET_ORDINAL, 0x29);
    serverbound1_15->Register(SwingArm::PACKET_ORDINAL, 0x2A);
    serverbound1_15->Register(Spectate::PACKET_ORDINAL, 0x2B);
    serverbound1_15->Register(PlaceBlock::PACKET_ORDINAL, 0x2C);
    serverbound1_15->Register(UseItem::PACKET_ORDINAL, 0x2D);

    // VersionRegistry* serverbound1_16 = serverboundRegistry + ProtocolVersion::MINECRAFT_1_16.GetPacketIDOrdinal();
    // serverbound1_16->Register(ConfirmTeleport::PACKET_ORDINAL, 0x00);
    // serverbound1_16->Register(BlockTagQueryRequest::PACKET_ORDINAL, 0x01);
    // serverbound1_16->Register(ClientChangeDifficulty::PACKET_ORDINAL, 0x02);
    // serverbound1_16->Register(LegacyChat::PACKET_ORDINAL, 0x03);
    // serverbound1_16->Register(ClientAction::PACKET_ORDINAL, 0x04);
    // serverbound1_16->Register(ClientSettings::PACKET_ORDINAL, 0x05);
    // serverbound1_16->Register(CommandSuggestionRequest::PACKET_ORDINAL, 0x06);
    // serverbound1_16->Register(ConfirmTransaction::PACKET_ORDINAL, 0x07);
    // serverbound1_16->Register(ClickInventoryButton::PACKET_ORDINAL, 0x08);
    // serverbound1_16->Register(ClickSlot::PACKET_ORDINAL, 0x09);
    // serverbound1_16->Register(CloseInventory::PACKET_ORDINAL, 0x0A);
    // serverbound1_16->Register(PluginMessage::PACKET_ORDINAL, 0x0B);
    // serverbound1_16->Register(EditBook::PACKET_ORDINAL, 0x0C);
    // serverbound1_16->Register(TagQueryRequest::PACKET_ORDINAL, 0x0D);
    // serverbound1_16->Register(EntityInteract::PACKET_ORDINAL, 0x0E);
    // serverbound1_16->Register(GenerateStructure::PACKET_ORDINAL, 0x0F);
    // serverbound1_16->Register(KeepAlive::PACKET_ORDINAL, 0x10);
    // serverbound1_16->Register(LockDifficulty::PACKET_ORDINAL, 0x11);
    // serverbound1_16->Register(MovePositionOnly::PACKET_ORDINAL, 0x12);
    // serverbound1_16->Register(Move::PACKET_ORDINAL, 0x13);
    // serverbound1_16->Register(MoveRotationOnly::PACKET_ORDINAL, 0x14);
    // serverbound1_16->Register(MoveVehicle::PACKET_ORDINAL, 0x15);
    // serverbound1_16->Register(MoveGroundOnly::PACKET_ORDINAL, 0x16);
    // serverbound1_16->Register(BoatPaddle::PACKET_ORDINAL, 0x17);
    // serverbound1_16->Register(PickItem::PACKET_ORDINAL, 0x18);
    // serverbound1_16->Register(CraftRecipeRequest::PACKET_ORDINAL, 0x19);
    // serverbound1_16->Register(ClientPlayerAbilities::PACKET_ORDINAL, 0x1A);
    // serverbound1_16->Register(Digging::PACKET_ORDINAL, 0x1B);
    // serverbound1_16->Register(EntityAction::PACKET_ORDINAL, 0x1C);
    // serverbound1_16->Register(PlayerInput::PACKET_ORDINAL, 0x1D);
    // serverbound1_16->Register(LegacyRecipeBook::PACKET_ORDINAL, 0x1E);
    // serverbound1_16->Register(RenameItem::PACKET_ORDINAL, 0x1F);
    // serverbound1_16->Register(ResourcePackResponse::PACKET_ORDINAL, 0x20);
    // serverbound1_16->Register(SelectAdvancementsTab::PACKET_ORDINAL, 0x21);
    // serverbound1_16->Register(SelectTrade::PACKET_ORDINAL, 0x22);
    // serverbound1_16->Register(BeaconEffect::PACKET_ORDINAL, 0x23);
    // serverbound1_16->Register(HeldSlot::PACKET_ORDINAL, 0x24);
    // serverbound1_16->Register(ProgramCommandBlock::PACKET_ORDINAL, 0x25);
    // serverbound1_16->Register(ProgramCommandBlockMinecart::PACKET_ORDINAL, 0x26);
    // serverbound1_16->Register(CreativeSlot::PACKET_ORDINAL, 0x27);
    // serverbound1_16->Register(ProgramJigsawBlock::PACKET_ORDINAL, 0x28);
    // serverbound1_16->Register(ProgramStructureBlock::PACKET_ORDINAL, 0x29);
    // serverbound1_16->Register(EditSign::PACKET_ORDINAL, 0x2A);
    // serverbound1_16->Register(SwingArm::PACKET_ORDINAL, 0x2B);
    // serverbound1_16->Register(Spectate::PACKET_ORDINAL, 0x2C);
    // serverbound1_16->Register(PlaceBlock::PACKET_ORDINAL, 0x2D);
    // serverbound1_16->Register(UseItem::PACKET_ORDINAL, 0x2E);

    VersionRegistry* serverbound1_16_2 = serverboundRegistry + ProtocolVersion::MINECRAFT_1_16_2.GetPacketIDOrdinal();
    serverbound1_16_2->Register(ConfirmTeleport::PACKET_ORDINAL, 0x00);
    serverbound1_16_2->Register(BlockTagQueryRequest::PACKET_ORDINAL, 0x01);
    serverbound1_16_2->Register(ClientChangeDifficulty::PACKET_ORDINAL, 0x02);
    serverbound1_16_2->Register(LegacyChat::PACKET_ORDINAL, 0x03);
    serverbound1_16_2->Register(ClientAction::PACKET_ORDINAL, 0x04);
    serverbound1_16_2->Register(ClientSettings::PACKET_ORDINAL, 0x05);
    serverbound1_16_2->Register(CommandSuggestionRequest::PACKET_ORDINAL, 0x06);
    serverbound1_16_2->Register(ConfirmTransaction::PACKET_ORDINAL, 0x07);
    serverbound1_16_2->Register(ClickInventoryButton::PACKET_ORDINAL, 0x08);
    serverbound1_16_2->Register(ClickSlot::PACKET_ORDINAL, 0x09);
    serverbound1_16_2->Register(CloseInventory::PACKET_ORDINAL, 0x0A);
    serverbound1_16_2->Register(PluginMessage::PACKET_ORDINAL, 0x0B);
    serverbound1_16_2->Register(EditBook::PACKET_ORDINAL, 0x0C);
    serverbound1_16_2->Register(TagQueryRequest::PACKET_ORDINAL, 0x0D);
    serverbound1_16_2->Register(EntityInteract::PACKET_ORDINAL, 0x0E);
    serverbound1_16_2->Register(GenerateStructure::PACKET_ORDINAL, 0x0F);
    serverbound1_16_2->Register(KeepAlive::PACKET_ORDINAL, 0x10);
    serverbound1_16_2->Register(LockDifficulty::PACKET_ORDINAL, 0x11);
    serverbound1_16_2->Register(MovePositionOnly::PACKET_ORDINAL, 0x12);
    serverbound1_16_2->Register(Move::PACKET_ORDINAL, 0x13);
    serverbound1_16_2->Register(MoveRotationOnly::PACKET_ORDINAL, 0x14);
    serverbound1_16_2->Register(MoveVehicle::PACKET_ORDINAL, 0x15);
    serverbound1_16_2->Register(MoveGroundOnly::PACKET_ORDINAL, 0x16);
    serverbound1_16_2->Register(BoatPaddle::PACKET_ORDINAL, 0x17);
    serverbound1_16_2->Register(PickItem::PACKET_ORDINAL, 0x18);
    serverbound1_16_2->Register(CraftRecipeRequest::PACKET_ORDINAL, 0x19);
    serverbound1_16_2->Register(ClientPlayerAbilities::PACKET_ORDINAL, 0x1A);
    serverbound1_16_2->Register(Digging::PACKET_ORDINAL, 0x1B);
    serverbound1_16_2->Register(EntityAction::PACKET_ORDINAL, 0x1C);
    serverbound1_16_2->Register(PlayerInput::PACKET_ORDINAL, 0x1D);
    serverbound1_16_2->Register(SeenRecipe::PACKET_ORDINAL, 0x1E);
    serverbound1_16_2->Register(ChangeRecipeBookSettings::PACKET_ORDINAL, 0x1F);
    serverbound1_16_2->Register(RenameItem::PACKET_ORDINAL, 0x20);
    serverbound1_16_2->Register(ResourcePackResponse::PACKET_ORDINAL, 0x21);
    serverbound1_16_2->Register(SelectAdvancementsTab::PACKET_ORDINAL, 0x22);
    serverbound1_16_2->Register(SelectTrade::PACKET_ORDINAL, 0x23);
    serverbound1_16_2->Register(BeaconEffect::PACKET_ORDINAL, 0x24);
    serverbound1_16_2->Register(HeldSlot::PACKET_ORDINAL, 0x25);
    serverbound1_16_2->Register(ProgramCommandBlock::PACKET_ORDINAL, 0x26);
    serverbound1_16_2->Register(ProgramCommandBlockMinecart::PACKET_ORDINAL, 0x27);
    serverbound1_16_2->Register(CreativeSlot::PACKET_ORDINAL, 0x28);
    serverbound1_16_2->Register(ProgramJigsawBlock::PACKET_ORDINAL, 0x29);
    serverbound1_16_2->Register(ProgramStructureBlock::PACKET_ORDINAL, 0x2A);
    serverbound1_16_2->Register(EditSign::PACKET_ORDINAL, 0x2B);
    serverbound1_16_2->Register(SwingArm::PACKET_ORDINAL, 0x2C);
    serverbound1_16_2->Register(Spectate::PACKET_ORDINAL, 0x2D);
    serverbound1_16_2->Register(PlaceBlock::PACKET_ORDINAL, 0x2E);
    serverbound1_16_2->Register(UseItem::PACKET_ORDINAL, 0x2F);

    VersionRegistry* serverbound1_17 = serverboundRegistry + ProtocolVersion::MINECRAFT_1_17.GetPacketIDOrdinal();
    serverbound1_17->Register(ConfirmTeleport::PACKET_ORDINAL, 0x00);
    serverbound1_17->Register(BlockTagQueryRequest::PACKET_ORDINAL, 0x01);
    serverbound1_17->Register(ClientChangeDifficulty::PACKET_ORDINAL, 0x02);
    serverbound1_17->Register(LegacyChat::PACKET_ORDINAL, 0x03);
    serverbound1_17->Register(ClientAction::PACKET_ORDINAL, 0x04);
    serverbound1_17->Register(ClientSettings::PACKET_ORDINAL, 0x05);
    serverbound1_17->Register(CommandSuggestionRequest::PACKET_ORDINAL, 0x06);
    serverbound1_17->Register(ClickInventoryButton::PACKET_ORDINAL, 0x07);
    serverbound1_17->Register(ClickSlot::PACKET_ORDINAL, 0x08);
    serverbound1_17->Register(CloseInventory::PACKET_ORDINAL, 0x09);
    serverbound1_17->Register(PluginMessage::PACKET_ORDINAL, 0x0A);
    serverbound1_17->Register(EditBook::PACKET_ORDINAL, 0x0B);
    serverbound1_17->Register(TagQueryRequest::PACKET_ORDINAL, 0x0C);
    serverbound1_17->Register(EntityInteract::PACKET_ORDINAL, 0x0D);
    serverbound1_17->Register(GenerateStructure::PACKET_ORDINAL, 0x0E);
    serverbound1_17->Register(KeepAlive::PACKET_ORDINAL, 0x0F);
    serverbound1_17->Register(LockDifficulty::PACKET_ORDINAL, 0x10);
    serverbound1_17->Register(MovePositionOnly::PACKET_ORDINAL, 0x11);
    serverbound1_17->Register(Move::PACKET_ORDINAL, 0x12);
    serverbound1_17->Register(MoveRotationOnly::PACKET_ORDINAL, 0x13);
    serverbound1_17->Register(MoveGroundOnly::PACKET_ORDINAL, 0x14);
    serverbound1_17->Register(MoveVehicle::PACKET_ORDINAL, 0x15);
    serverbound1_17->Register(BoatPaddle::PACKET_ORDINAL, 0x16);
    serverbound1_17->Register(PickItem::PACKET_ORDINAL, 0x17);
    serverbound1_17->Register(CraftRecipeRequest::PACKET_ORDINAL, 0x18);
    serverbound1_17->Register(ClientPlayerAbilities::PACKET_ORDINAL, 0x19);
    serverbound1_17->Register(Digging::PACKET_ORDINAL, 0x1A);
    serverbound1_17->Register(EntityAction::PACKET_ORDINAL, 0x1B);
    serverbound1_17->Register(PlayerInput::PACKET_ORDINAL, 0x1C);
    serverbound1_17->Register(Ping::PACKET_ORDINAL, 0x1D);
    serverbound1_17->Register(SeenRecipe::PACKET_ORDINAL, 0x1E);
    serverbound1_17->Register(ChangeRecipeBookSettings::PACKET_ORDINAL, 0x1F);
    serverbound1_17->Register(RenameItem::PACKET_ORDINAL, 0x20);
    serverbound1_17->Register(ResourcePackResponse::PACKET_ORDINAL, 0x21);
    serverbound1_17->Register(SelectAdvancementsTab::PACKET_ORDINAL, 0x22);
    serverbound1_17->Register(SelectTrade::PACKET_ORDINAL, 0x23);
    serverbound1_17->Register(BeaconEffect::PACKET_ORDINAL, 0x24);
    serverbound1_17->Register(HeldSlot::PACKET_ORDINAL, 0x25);
    serverbound1_17->Register(ProgramCommandBlock::PACKET_ORDINAL, 0x26);
    serverbound1_17->Register(ProgramCommandBlockMinecart::PACKET_ORDINAL, 0x27);
    serverbound1_17->Register(CreativeSlot::PACKET_ORDINAL, 0x28);
    serverbound1_17->Register(ProgramJigsawBlock::PACKET_ORDINAL, 0x29);
    serverbound1_17->Register(ProgramStructureBlock::PACKET_ORDINAL, 0x2A);
    serverbound1_17->Register(EditSign::PACKET_ORDINAL, 0x2B);
    serverbound1_17->Register(SwingArm::PACKET_ORDINAL, 0x2C);
    serverbound1_17->Register(Spectate::PACKET_ORDINAL, 0x2D);
    serverbound1_17->Register(PlaceBlock::PACKET_ORDINAL, 0x2E);
    serverbound1_17->Register(UseItem::PACKET_ORDINAL, 0x2F);

    VersionRegistry* serverbound1_18 = serverboundRegistry + ProtocolVersion::MINECRAFT_1_18.GetPacketIDOrdinal();
    serverbound1_18->Register(ConfirmTeleport::PACKET_ORDINAL, 0x00);
    serverbound1_18->Register(BlockTagQueryRequest::PACKET_ORDINAL, 0x01);
    serverbound1_18->Register(ClientChangeDifficulty::PACKET_ORDINAL, 0x02);
    serverbound1_18->Register(LegacyChat::PACKET_ORDINAL, 0x03);
    serverbound1_18->Register(ClientAction::PACKET_ORDINAL, 0x04);
    serverbound1_18->Register(ClientSettings::PACKET_ORDINAL, 0x05);
    serverbound1_18->Register(CommandSuggestionRequest::PACKET_ORDINAL, 0x06);
    serverbound1_18->Register(ClickInventoryButton::PACKET_ORDINAL, 0x07);
    serverbound1_18->Register(ClickSlot::PACKET_ORDINAL, 0x08);
    serverbound1_18->Register(CloseInventory::PACKET_ORDINAL, 0x09);
    serverbound1_18->Register(PluginMessage::PACKET_ORDINAL, 0x0A);
    serverbound1_18->Register(EditBook::PACKET_ORDINAL, 0x0B);
    serverbound1_18->Register(TagQueryRequest::PACKET_ORDINAL, 0x0C);
    serverbound1_18->Register(EntityInteract::PACKET_ORDINAL, 0x0D);
    serverbound1_18->Register(GenerateStructure::PACKET_ORDINAL, 0x0E);
    serverbound1_18->Register(KeepAlive::PACKET_ORDINAL, 0x0F);
    serverbound1_18->Register(LockDifficulty::PACKET_ORDINAL, 0x10);
    serverbound1_18->Register(MovePositionOnly::PACKET_ORDINAL, 0x11);
    serverbound1_18->Register(Move::PACKET_ORDINAL, 0x12);
    serverbound1_18->Register(MoveRotationOnly::PACKET_ORDINAL, 0x13);
    serverbound1_18->Register(MoveGroundOnly::PACKET_ORDINAL, 0x14);
    serverbound1_18->Register(MoveVehicle::PACKET_ORDINAL, 0x15);
    serverbound1_18->Register(BoatPaddle::PACKET_ORDINAL, 0x16);
    serverbound1_18->Register(PickItem::PACKET_ORDINAL, 0x17);
    serverbound1_18->Register(CraftRecipeRequest::PACKET_ORDINAL, 0x18);
    serverbound1_18->Register(ClientPlayerAbilities::PACKET_ORDINAL, 0x19);
    serverbound1_18->Register(Digging::PACKET_ORDINAL, 0x1A);
    serverbound1_18->Register(EntityAction::PACKET_ORDINAL, 0x1B);
    serverbound1_18->Register(PlayerInput::PACKET_ORDINAL, 0x1C);
    serverbound1_18->Register(Ping::PACKET_ORDINAL, 0x1D);
    serverbound1_18->Register(SeenRecipe::PACKET_ORDINAL, 0x1E);
    serverbound1_18->Register(ChangeRecipeBookSettings::PACKET_ORDINAL, 0x1F);
    serverbound1_18->Register(RenameItem::PACKET_ORDINAL, 0x20);
    serverbound1_18->Register(ResourcePackResponse::PACKET_ORDINAL, 0x21);
    serverbound1_18->Register(SelectAdvancementsTab::PACKET_ORDINAL, 0x22);
    serverbound1_18->Register(SelectTrade::PACKET_ORDINAL, 0x23);
    serverbound1_18->Register(BeaconEffect::PACKET_ORDINAL, 0x24);
    serverbound1_18->Register(HeldSlot::PACKET_ORDINAL, 0x25);
    serverbound1_18->Register(ProgramCommandBlock::PACKET_ORDINAL, 0x26);
    serverbound1_18->Register(ProgramCommandBlockMinecart::PACKET_ORDINAL, 0x27);
    serverbound1_18->Register(CreativeSlot::PACKET_ORDINAL, 0x28);
    serverbound1_18->Register(ProgramJigsawBlock::PACKET_ORDINAL, 0x29);
    serverbound1_18->Register(ProgramStructureBlock::PACKET_ORDINAL, 0x2A);
    serverbound1_18->Register(EditSign::PACKET_ORDINAL, 0x2B);
    serverbound1_18->Register(SwingArm::PACKET_ORDINAL, 0x2C);
    serverbound1_18->Register(Spectate::PACKET_ORDINAL, 0x2D);
    serverbound1_18->Register(PlaceBlock::PACKET_ORDINAL, 0x2E);
    serverbound1_18->Register(UseItem::PACKET_ORDINAL, 0x2F);

    VersionRegistry* serverbound1_19 = serverboundRegistry + ProtocolVersion::MINECRAFT_1_19.GetPacketIDOrdinal();
    serverbound1_19->Register(ConfirmTeleport::PACKET_ORDINAL, 0x00);
    serverbound1_19->Register(BlockTagQueryRequest::PACKET_ORDINAL, 0x01);
    serverbound1_19->Register(ClientChangeDifficulty::PACKET_ORDINAL, 0x02);
    serverbound1_19->Register(Command::PACKET_ORDINAL, 0x03);
    serverbound1_19->Register(ClientPlayerChat::PACKET_ORDINAL, 0x04);
    serverbound1_19->Register(ClientChatPreview::PACKET_ORDINAL, 0x05);
    serverbound1_19->Register(ClientAction::PACKET_ORDINAL, 0x06);
    serverbound1_19->Register(ClientSettings::PACKET_ORDINAL, 0x07);
    serverbound1_19->Register(CommandSuggestionRequest::PACKET_ORDINAL, 0x08);
    serverbound1_19->Register(ClickInventoryButton::PACKET_ORDINAL, 0x09);
    serverbound1_19->Register(ClickSlot::PACKET_ORDINAL, 0x0A);
    serverbound1_19->Register(CloseInventory::PACKET_ORDINAL, 0x0B);
    serverbound1_19->Register(PluginMessage::PACKET_ORDINAL, 0x0C);
    serverbound1_19->Register(EditBook::PACKET_ORDINAL, 0x0D);
    serverbound1_19->Register(TagQueryRequest::PACKET_ORDINAL, 0x0E);
    serverbound1_19->Register(EntityInteract::PACKET_ORDINAL, 0x0F);
    serverbound1_19->Register(GenerateStructure::PACKET_ORDINAL, 0x10);
    serverbound1_19->Register(KeepAlive::PACKET_ORDINAL, 0x11);
    serverbound1_19->Register(LockDifficulty::PACKET_ORDINAL, 0x12);
    serverbound1_19->Register(MovePositionOnly::PACKET_ORDINAL, 0x13);
    serverbound1_19->Register(Move::PACKET_ORDINAL, 0x14);
    serverbound1_19->Register(MoveRotationOnly::PACKET_ORDINAL, 0x15);
    serverbound1_19->Register(MoveGroundOnly::PACKET_ORDINAL, 0x16);
    serverbound1_19->Register(MoveVehicle::PACKET_ORDINAL, 0x17);
    serverbound1_19->Register(BoatPaddle::PACKET_ORDINAL, 0x18);
    serverbound1_19->Register(PickItem::PACKET_ORDINAL, 0x19);
    serverbound1_19->Register(CraftRecipeRequest::PACKET_ORDINAL, 0x1A);
    serverbound1_19->Register(ClientPlayerAbilities::PACKET_ORDINAL, 0x1B);
    serverbound1_19->Register(Digging::PACKET_ORDINAL, 0x1C);
    serverbound1_19->Register(EntityAction::PACKET_ORDINAL, 0x1D);
    serverbound1_19->Register(PlayerInput::PACKET_ORDINAL, 0x1E);
    serverbound1_19->Register(Ping::PACKET_ORDINAL, 0x1F);
    serverbound1_19->Register(SeenRecipe::PACKET_ORDINAL, 0x20);
    serverbound1_19->Register(ChangeRecipeBookSettings::PACKET_ORDINAL, 0x21);
    serverbound1_19->Register(RenameItem::PACKET_ORDINAL, 0x22);
    serverbound1_19->Register(ResourcePackResponse::PACKET_ORDINAL, 0x23);
    serverbound1_19->Register(SelectAdvancementsTab::PACKET_ORDINAL, 0x24);
    serverbound1_19->Register(SelectTrade::PACKET_ORDINAL, 0x25);
    serverbound1_19->Register(BeaconEffect::PACKET_ORDINAL, 0x26);
    serverbound1_19->Register(HeldSlot::PACKET_ORDINAL, 0x27);
    serverbound1_19->Register(ProgramCommandBlock::PACKET_ORDINAL, 0x28);
    serverbound1_19->Register(ProgramCommandBlockMinecart::PACKET_ORDINAL, 0x29);
    serverbound1_19->Register(CreativeSlot::PACKET_ORDINAL, 0x2A);
    serverbound1_19->Register(ProgramJigsawBlock::PACKET_ORDINAL, 0x2B);
    serverbound1_19->Register(ProgramStructureBlock::PACKET_ORDINAL, 0x2C);
    serverbound1_19->Register(EditSign::PACKET_ORDINAL, 0x2D);
    serverbound1_19->Register(SwingArm::PACKET_ORDINAL, 0x2E);
    serverbound1_19->Register(Spectate::PACKET_ORDINAL, 0x2F);
    serverbound1_19->Register(PlaceBlock::PACKET_ORDINAL, 0x30);
    serverbound1_19->Register(UseItem::PACKET_ORDINAL, 0x31);

    VersionRegistry* serverbound1_19_1 = serverboundRegistry + ProtocolVersion::MINECRAFT_1_19_1.GetPacketIDOrdinal();
    serverbound1_19_1->Register(ConfirmTeleport::PACKET_ORDINAL, 0x00);
    serverbound1_19_1->Register(BlockTagQueryRequest::PACKET_ORDINAL, 0x01);
    serverbound1_19_1->Register(ClientChangeDifficulty::PACKET_ORDINAL, 0x02);
    //    serverbound1_19_1->Register(MessageAcknowledgment::PACKET_ORDINAL, 0x03); //TODO: MessageAcknowledgment
    serverbound1_19_1->Register(Command::PACKET_ORDINAL, 0x04);
    serverbound1_19_1->Register(ClientPlayerChat::PACKET_ORDINAL, 0x05);
    serverbound1_19_1->Register(ClientChatPreview::PACKET_ORDINAL, 0x06);
    serverbound1_19_1->Register(ClientAction::PACKET_ORDINAL, 0x07);
    serverbound1_19_1->Register(ClientSettings::PACKET_ORDINAL, 0x08);
    serverbound1_19_1->Register(CommandSuggestionRequest::PACKET_ORDINAL, 0x09);
    serverbound1_19_1->Register(ClickInventoryButton::PACKET_ORDINAL, 0x0A);
    serverbound1_19_1->Register(ClickSlot::PACKET_ORDINAL, 0x0B);
    serverbound1_19_1->Register(CloseInventory::PACKET_ORDINAL, 0x0C);
    serverbound1_19_1->Register(PluginMessage::PACKET_ORDINAL, 0x0D);
    serverbound1_19_1->Register(EditBook::PACKET_ORDINAL, 0x0E);
    serverbound1_19_1->Register(TagQueryRequest::PACKET_ORDINAL, 0x0F);
    serverbound1_19_1->Register(EntityInteract::PACKET_ORDINAL, 0x10);
    serverbound1_19_1->Register(GenerateStructure::PACKET_ORDINAL, 0x11);
    serverbound1_19_1->Register(KeepAlive::PACKET_ORDINAL, 0x12);
    serverbound1_19_1->Register(LockDifficulty::PACKET_ORDINAL, 0x13);
    serverbound1_19_1->Register(MovePositionOnly::PACKET_ORDINAL, 0x14);
    serverbound1_19_1->Register(Move::PACKET_ORDINAL, 0x15);
    serverbound1_19_1->Register(MoveRotationOnly::PACKET_ORDINAL, 0x16);
    serverbound1_19_1->Register(MoveGroundOnly::PACKET_ORDINAL, 0x17);
    serverbound1_19_1->Register(MoveVehicle::PACKET_ORDINAL, 0x18);
    serverbound1_19_1->Register(BoatPaddle::PACKET_ORDINAL, 0x19);
    serverbound1_19_1->Register(PickItem::PACKET_ORDINAL, 0x1A);
    serverbound1_19_1->Register(CraftRecipeRequest::PACKET_ORDINAL, 0x1B);
    serverbound1_19_1->Register(ClientPlayerAbilities::PACKET_ORDINAL, 0x1C);
    serverbound1_19_1->Register(Digging::PACKET_ORDINAL, 0x1D);
    serverbound1_19_1->Register(EntityAction::PACKET_ORDINAL, 0x1E);
    serverbound1_19_1->Register(PlayerInput::PACKET_ORDINAL, 0x1F);
    serverbound1_19_1->Register(Ping::PACKET_ORDINAL, 0x20);
    serverbound1_19_1->Register(SeenRecipe::PACKET_ORDINAL, 0x21);
    serverbound1_19_1->Register(ChangeRecipeBookSettings::PACKET_ORDINAL, 0x22);
    serverbound1_19_1->Register(RenameItem::PACKET_ORDINAL, 0x23);
    serverbound1_19_1->Register(ResourcePackResponse::PACKET_ORDINAL, 0x24);
    serverbound1_19_1->Register(SelectAdvancementsTab::PACKET_ORDINAL, 0x25);
    serverbound1_19_1->Register(SelectTrade::PACKET_ORDINAL, 0x26);
    serverbound1_19_1->Register(BeaconEffect::PACKET_ORDINAL, 0x27);
    serverbound1_19_1->Register(HeldSlot::PACKET_ORDINAL, 0x28);
    serverbound1_19_1->Register(ProgramCommandBlock::PACKET_ORDINAL, 0x29);
    serverbound1_19_1->Register(ProgramCommandBlockMinecart::PACKET_ORDINAL, 0x2A);
    serverbound1_19_1->Register(CreativeSlot::PACKET_ORDINAL, 0x2B);
    serverbound1_19_1->Register(ProgramJigsawBlock::PACKET_ORDINAL, 0x2C);
    serverbound1_19_1->Register(ProgramStructureBlock::PACKET_ORDINAL, 0x2D);
    serverbound1_19_1->Register(EditSign::PACKET_ORDINAL, 0x2E);
    serverbound1_19_1->Register(SwingArm::PACKET_ORDINAL, 0x2F);
    serverbound1_19_1->Register(Spectate::PACKET_ORDINAL, 0x30);
    serverbound1_19_1->Register(PlaceBlock::PACKET_ORDINAL, 0x31);
    serverbound1_19_1->Register(UseItem::PACKET_ORDINAL, 0x32);

    auto* clientbound = new DirectionRegistry(clientboundRegistry);

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

    auto* serverbound = new DirectionRegistry(serverboundRegistry);

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

    return {clientbound, serverbound};
  }

  const PacketRegistry BuiltInPacketRegistry::HANDSHAKE = GetHandshakeRegistry();
  const PacketRegistry BuiltInPacketRegistry::STATUS = GetStatusRegistry();
  const PacketRegistry BuiltInPacketRegistry::LOGIN = GetLoginRegistry();
  const PacketRegistry BuiltInPacketRegistry::PLAY = GetPlayRegistry();
}