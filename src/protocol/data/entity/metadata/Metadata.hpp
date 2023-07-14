#pragma once

#include "ShipNet/protocol/Protocol.hpp"
#include "ShipNet/utils/ordinal/OrdinalRegistry.hpp"
#include "../../../MinecraftProtocol.hpp"
#include "../../ItemStack.hpp"
#include "../../particle/Particle.hpp"
#include "VillagerData.hpp"
#include <map>
#include <optional>

namespace Ship {

  enum class Pose : uint32_t {
    STANDING = 0,
    FALL_FLYING = 1,
    SLEEPING = 2,
    SWIMMING = 3,
    SPIN_ATTACK = 4,
    SNEAKING = 5,
    LONG_JUMPING = 6,
    DYING = 7,
    CROAKING = 8,
    USING_TONGUE = 9,
    ROARING = 10,
    SNIFFING = 11,
    EMERGING = 12,
    DIGGING = 13,
  };

  enum class CatVariant : uint32_t {
    TABBY = 0,
    BLACK = 1,
    RED = 2,
    SIAMESE = 3,
    BRITISH_SHORTHAIR = 4,
    CALICO = 5,
    PERSIAN = 6,
    RAGDOLL = 7,
    WHITE = 8,
    JELLIE = 9,
    ALL_BLACK = 10,
  };

  enum class FrogVariant : uint32_t {
    TEMPERATE = 0,
    WARM = 1,
    COLD = 2,
  };

  enum class PaintingVariant : uint32_t {
    KEBAB,
    AZTEC,
    ALBAN,
    AZTEC2,
    BOMB,
    PLANT,
    WASTELAND,
    POOL,
    COURBET,
    SEA,
    SUNSET,
    CREEBET,
    WANDERER,
    GRAHAM,
    MATCH,
    BUST,
    STAGE,
    VOID,
    SKULL_AND_ROSES,
    WITHER,
    FIGHTERS,
    POINTER,
    PIGSCENE,
    BURNING_SKULL,
    SKELETON,
    EARTH,
    WIND,
    WATER,
    FIRE,
    DONKEY_KONG,
  };

  enum class MetadataEntryType {
    BYTE,
    VARINT,
    LONG,
    FLOAT,
    STRING,
    CHAT,
    OPT_CHAT,
    ITEM_STACK,
    BOOLEAN,
    ROTATION,
    POSITION,
    OPT_POSITION,
    DIRECTION,
    OPT_UUID,
    BLOCK_ID,
    NBT,
    PARTICLE,
    VILLAGER_DATA,
    OPT_VARINT,
    POSE,
    CAT_VARIANT,
    FROG_VARIANT,
    GLOBAL_POS,
    PAINTING_VARIANT,
  };

  class MetadataEntry : public Serializable {
   public:
    ~MetadataEntry() override = default;

    [[nodiscard]] virtual MetadataEntryType GetType() const = 0;
    [[nodiscard]] virtual uint32_t GetOrdinal() const = 0;
  };

  class ByteMetadataEntry : public MetadataEntry {
   private:
    uint8_t value{};

   public:
    static inline const uint32_t ORDINAL = MinecraftOrdinalRegistry::MetadataEntryRegistry.RegisterOrdinal();

    ByteMetadataEntry() = default;
    explicit ByteMetadataEntry(uint8_t value);

    Errorable<bool> Write(const ProtocolVersion* version, ByteBuffer* buffer) const override;
    static Errorable<ByteMetadataEntry> Instantiate(const ProtocolVersion* version, ByteBuffer* buffer);
    [[nodiscard]] MetadataEntryType GetType() const override;
    [[nodiscard]] uint32_t GetOrdinal() const override;

    [[nodiscard]] uint8_t GetValue() const;
    void SetValue(uint8_t newValue);
  };
  CreateInvalidArgumentErrorable(InvalidByteMetadataEntryErrorable, ByteMetadataEntry, "Invalid ByteMetadataEntry read");
  CreateInvalidArgumentErrorable(MismatchByteMetadataEntryErrorable, uint8_t, "The requested type (Byte) doesn't match the actual type");
  CreateInvalidArgumentErrorable(NoSuchByteMetadataEntryErrorable, uint8_t, "No metadata entry (Byte requested) can be found on provided index");

  class VarIntMetadataEntry : public MetadataEntry {
   private:
    uint32_t value{};

   public:
    static inline const uint32_t ORDINAL = MinecraftOrdinalRegistry::MetadataEntryRegistry.RegisterOrdinal();

    VarIntMetadataEntry() = default;
    explicit VarIntMetadataEntry(uint32_t value);

    Errorable<bool> Write(const ProtocolVersion* version, ByteBuffer* buffer) const override;
    static Errorable<VarIntMetadataEntry> Instantiate(const ProtocolVersion* version, ByteBuffer* buffer);
    [[nodiscard]] MetadataEntryType GetType() const override;
    [[nodiscard]] uint32_t GetOrdinal() const override;

    [[nodiscard]] uint32_t GetValue() const;
    void SetValue(uint32_t newValue);
  };
  CreateInvalidArgumentErrorable(InvalidVarIntMetadataEntryErrorable, VarIntMetadataEntry, "Invalid VarIntMetadataEntry read");
  CreateInvalidArgumentErrorable(MismatchVarIntMetadataEntryErrorable, uint32_t, "The requested type (VarInt) doesn't match the actual type");
  CreateInvalidArgumentErrorable(NoSuchVarIntMetadataEntryErrorable, uint32_t, "No metadata entry (VarInt requested) can be found on provided index");

  class LongMetadataEntry : public MetadataEntry {
   private:
    uint64_t value{};

   public:
    static inline const uint32_t ORDINAL = MinecraftOrdinalRegistry::MetadataEntryRegistry.RegisterOrdinal();

    LongMetadataEntry() = default;
    explicit LongMetadataEntry(uint64_t value);

    Errorable<bool> Write(const ProtocolVersion* version, ByteBuffer* buffer) const override;
    static Errorable<LongMetadataEntry> Instantiate(const ProtocolVersion* version, ByteBuffer* buffer);
    [[nodiscard]] MetadataEntryType GetType() const override;
    [[nodiscard]] uint32_t GetOrdinal() const override;

    [[nodiscard]] uint64_t GetValue() const;
    void SetValue(uint64_t newValue);
  };
  CreateInvalidArgumentErrorable(InvalidLongMetadataEntryErrorable, LongMetadataEntry, "Invalid LongMetadataEntry read");
  CreateInvalidArgumentErrorable(MismatchLongMetadataEntryErrorable, uint64_t, "The requested type (Long) doesn't match the actual type");
  CreateInvalidArgumentErrorable(NoSuchLongMetadataEntryErrorable, uint64_t, "No metadata entry (Long requested) can be found on provided index");

  class FloatMetadataEntry : public MetadataEntry {
   private:
    float value{};

   public:
    static inline const uint32_t ORDINAL = MinecraftOrdinalRegistry::MetadataEntryRegistry.RegisterOrdinal();

    FloatMetadataEntry() = default;
    explicit FloatMetadataEntry(float value);

    Errorable<bool> Write(const ProtocolVersion* version, ByteBuffer* buffer) const override;
    static Errorable<FloatMetadataEntry> Instantiate(const ProtocolVersion* version, ByteBuffer* buffer);
    [[nodiscard]] MetadataEntryType GetType() const override;
    [[nodiscard]] uint32_t GetOrdinal() const override;

    [[nodiscard]] float GetValue() const;
    void SetValue(float newValue);
  };
  CreateInvalidArgumentErrorable(InvalidFloatMetadataEntryErrorable, FloatMetadataEntry, "Invalid FloatMetadataEntry read");
  CreateInvalidArgumentErrorable(MismatchFloatMetadataEntryErrorable, float, "The requested type (Float) doesn't match the actual type");
  CreateInvalidArgumentErrorable(NoSuchFloatMetadataEntryErrorable, float, "No metadata entry (Float requested) can be found on provided index");

  class StringMetadataEntry : public MetadataEntry {
   private:
    std::string value;

   public:
    static inline const uint32_t ORDINAL = MinecraftOrdinalRegistry::MetadataEntryRegistry.RegisterOrdinal();

    StringMetadataEntry() = default;
    explicit StringMetadataEntry(std::string value);

    Errorable<bool> Write(const ProtocolVersion* version, ByteBuffer* buffer) const override;
    static Errorable<StringMetadataEntry> Instantiate(const ProtocolVersion* version, ByteBuffer* buffer);
    [[nodiscard]] MetadataEntryType GetType() const override;
    [[nodiscard]] uint32_t GetOrdinal() const override;

    [[nodiscard]] std::string GetValue() const;
    void SetValue(std::string newValue);
  };
  CreateInvalidArgumentErrorable(InvalidStringMetadataEntryErrorable, StringMetadataEntry, "Invalid StringMetadataEntry read");
  CreateInvalidArgumentErrorable(MismatchStringMetadataEntryErrorable, std::string, "The requested type (String) doesn't match the actual type");
  CreateInvalidArgumentErrorable(NoSuchStringMetadataEntryErrorable, std::string, "No metadata entry (String requested) can be found on provided index");

  class ChatMetadataEntry : public MetadataEntry {
   private:
    std::string value; // TODO: Chat components

   public:
    static inline const uint32_t ORDINAL = MinecraftOrdinalRegistry::MetadataEntryRegistry.RegisterOrdinal();

    ChatMetadataEntry() = default;
    explicit ChatMetadataEntry(std::string value);

    Errorable<bool> Write(const ProtocolVersion* version, ByteBuffer* buffer) const override;
    static Errorable<ChatMetadataEntry> Instantiate(const ProtocolVersion* version, ByteBuffer* buffer);
    [[nodiscard]] MetadataEntryType GetType() const override;
    [[nodiscard]] uint32_t GetOrdinal() const override;

    [[nodiscard]] std::string GetValue() const;
    void SetValue(std::string newValue);
  };
  CreateInvalidArgumentErrorable(InvalidChatMetadataEntryErrorable, ChatMetadataEntry, "Invalid ChatMetadataEntry read");
  CreateInvalidArgumentErrorable(MismatchChatMetadataEntryErrorable, std::string, "The requested type (Chat) doesn't match the actual type");
  CreateInvalidArgumentErrorable(NoSuchChatMetadataEntryErrorable, std::string, "No metadata entry (Chat requested) can be found on provided index");

  class OptChatMetadataEntry : public MetadataEntry {
   private:
    std::optional<std::string> optValue; // TODO: Chat components

   public:
    static inline const uint32_t ORDINAL = MinecraftOrdinalRegistry::MetadataEntryRegistry.RegisterOrdinal();

    OptChatMetadataEntry();
    explicit OptChatMetadataEntry(std::optional<std::string> optValue);

    Errorable<bool> Write(const ProtocolVersion* version, ByteBuffer* buffer) const override;
    static Errorable<OptChatMetadataEntry> Instantiate(const ProtocolVersion* version, ByteBuffer* buffer);
    [[nodiscard]] MetadataEntryType GetType() const override;
    [[nodiscard]] uint32_t GetOrdinal() const override;

    [[nodiscard]] std::optional<std::string> GetValue() const;
    void SetValue(const std::optional<std::string>& newValue);
  };
  CreateInvalidArgumentErrorable(InvalidOptChatMetadataEntryErrorable, OptChatMetadataEntry, "Invalid OptChatMetadataEntry read");
  CreateInvalidArgumentErrorable(MismatchOptChatMetadataEntryErrorable, std::optional<std::string>, "The requested type (OptChat) doesn't match the actual type");
  CreateInvalidArgumentErrorable(NoSuchOptChatMetadataEntryErrorable, std::optional<std::string>, "No metadata entry (OptChat requested) can be found on provided index");

  class ItemStackMetadataEntry : public MetadataEntry {
   private:
    ItemStack value{};

   public:
    static inline const uint32_t ORDINAL = MinecraftOrdinalRegistry::MetadataEntryRegistry.RegisterOrdinal();

    ItemStackMetadataEntry() = default;
    explicit ItemStackMetadataEntry(const ItemStack& value);

    Errorable<bool> Write(const ProtocolVersion* version, ByteBuffer* buffer) const override;
    static Errorable<ItemStackMetadataEntry> Instantiate(const ProtocolVersion* version, ByteBuffer* buffer);
    [[nodiscard]] MetadataEntryType GetType() const override;
    [[nodiscard]] uint32_t GetOrdinal() const override;

    [[nodiscard]] ItemStack GetValue() const;
    void SetValue(const ItemStack& newValue);
  };
  CreateInvalidArgumentErrorable(InvalidItemStackMetadataEntryErrorable, ItemStackMetadataEntry, "Invalid ItemStackMetadataEntry read");
  CreateInvalidArgumentErrorable(MismatchItemStackMetadataEntryErrorable, ItemStack, "The requested type (ItemStack) doesn't match the actual type");
  CreateInvalidArgumentErrorable(NoSuchItemStackMetadataEntryErrorable, ItemStack, "No metadata entry (ItemStack requested) can be found on provided index");

  class BooleanMetadataEntry : public MetadataEntry {
   private:
    bool value{};

   public:
    static inline const uint32_t ORDINAL = MinecraftOrdinalRegistry::MetadataEntryRegistry.RegisterOrdinal();

    BooleanMetadataEntry() = default;
    explicit BooleanMetadataEntry(bool value);

    Errorable<bool> Write(const ProtocolVersion* version, ByteBuffer* buffer) const override;
    static Errorable<BooleanMetadataEntry> Instantiate(const ProtocolVersion* version, ByteBuffer* buffer);
    [[nodiscard]] MetadataEntryType GetType() const override;
    [[nodiscard]] uint32_t GetOrdinal() const override;

    [[nodiscard]] bool GetValue() const;
    void SetValue(bool newValue);
  };
  CreateInvalidArgumentErrorable(InvalidBooleanMetadataEntryErrorable, BooleanMetadataEntry, "Invalid BooleanMetadataEntry read");
  CreateInvalidArgumentErrorable(MismatchBooleanMetadataEntryErrorable, bool, "The requested type (Boolean) doesn't match the actual type");
  CreateInvalidArgumentErrorable(NoSuchBooleanMetadataEntryErrorable, bool, "No metadata entry (Boolean requested) can be found on provided index");

  class RotationMetadataEntry : public MetadataEntry {
   private:
    Rotation value{};

   public:
    static inline const uint32_t ORDINAL = MinecraftOrdinalRegistry::MetadataEntryRegistry.RegisterOrdinal();

    RotationMetadataEntry() = default;
    explicit RotationMetadataEntry(Rotation rotation);

    Errorable<bool> Write(const ProtocolVersion* version, ByteBuffer* buffer) const override;
    static Errorable<RotationMetadataEntry> Instantiate(const ProtocolVersion* version, ByteBuffer* buffer);
    [[nodiscard]] MetadataEntryType GetType() const override;
    [[nodiscard]] uint32_t GetOrdinal() const override;

    [[nodiscard]] Rotation GetValue() const;
    void SetValue(Rotation newValue);
  };
  CreateInvalidArgumentErrorable(InvalidRotationMetadataEntryErrorable, RotationMetadataEntry, "Invalid RotationMetadataEntry read");
  CreateInvalidArgumentErrorable(MismatchRotationMetadataEntryErrorable, Rotation, "The requested type (Rotation) doesn't match the actual type");
  CreateInvalidArgumentErrorable(NoSuchRotationMetadataEntryErrorable, Rotation, "No metadata entry (Rotation requested) can be found on provided index");

  class PositionMetadataEntry : public MetadataEntry {
   private:
    Position value{};

   public:
    static inline const uint32_t ORDINAL = MinecraftOrdinalRegistry::MetadataEntryRegistry.RegisterOrdinal();

    PositionMetadataEntry() = default;
    explicit PositionMetadataEntry(Position position);

    Errorable<bool> Write(const ProtocolVersion* version, ByteBuffer* buffer) const override;
    static Errorable<PositionMetadataEntry> Instantiate(const ProtocolVersion* version, ByteBuffer* buffer);
    [[nodiscard]] MetadataEntryType GetType() const override;
    [[nodiscard]] uint32_t GetOrdinal() const override;

    [[nodiscard]] Position GetValue() const;
    void SetValue(Position value);
  };
  CreateInvalidArgumentErrorable(InvalidPositionMetadataEntryErrorable, PositionMetadataEntry, "Invalid PositionMetadataEntry read");
  CreateInvalidArgumentErrorable(MismatchPositionMetadataEntryErrorable, Position, "The requested type (Position) doesn't match the actual type");
  CreateInvalidArgumentErrorable(NoSuchPositionMetadataEntryErrorable, Position, "No metadata entry (Position requested) can be found on provided index");

  class OptPositionMetadataEntry : public MetadataEntry {
   private:
    std::optional<Position> optValue;

   public:
    static inline const uint32_t ORDINAL = MinecraftOrdinalRegistry::MetadataEntryRegistry.RegisterOrdinal();

    OptPositionMetadataEntry();
    explicit OptPositionMetadataEntry(Position position);

    Errorable<bool> Write(const ProtocolVersion* version, ByteBuffer* buffer) const override;
    static Errorable<OptPositionMetadataEntry> Instantiate(const ProtocolVersion* version, ByteBuffer* buffer);
    [[nodiscard]] MetadataEntryType GetType() const override;
    [[nodiscard]] uint32_t GetOrdinal() const override;

    [[nodiscard]] std::optional<Position> GetValue() const;
    void SetValue(const std::optional<Position>& value);

    void Reset();
  };
  CreateInvalidArgumentErrorable(InvalidOptPositionMetadataEntryErrorable, OptPositionMetadataEntry, "Invalid OptPositionMetadataEntry read");
  CreateInvalidArgumentErrorable(MismatchOptPositionMetadataEntryErrorable, std::optional<Position>, "The requested type (OptPosition) doesn't match the actual type");
  CreateInvalidArgumentErrorable(NoSuchOptPositionMetadataEntryErrorable, std::optional<Position>, "No metadata entry (OptPosition requested) can be found on provided index");

  class DirectionMetadataEntry : public MetadataEntry {
   private:
    Direction value{};

   public:
    static inline const uint32_t ORDINAL = MinecraftOrdinalRegistry::MetadataEntryRegistry.RegisterOrdinal();

    DirectionMetadataEntry() = default;
    explicit DirectionMetadataEntry(const Direction& value);

    Errorable<bool> Write(const ProtocolVersion* version, ByteBuffer* buffer) const override;
    static Errorable<DirectionMetadataEntry> Instantiate(const ProtocolVersion* version, ByteBuffer* buffer);
    [[nodiscard]] MetadataEntryType GetType() const override;
    [[nodiscard]] uint32_t GetOrdinal() const override;

    [[nodiscard]] Direction GetValue() const;
    void SetValue(const Direction& newValue);
  };
  CreateInvalidArgumentErrorable(InvalidDirectionMetadataEntryErrorable, DirectionMetadataEntry, "Invalid DirectionMetadataEntry read");
  CreateInvalidArgumentErrorable(MismatchDirectionMetadataEntryErrorable, Direction, "The requested type (Direction) doesn't match the actual type");
  CreateInvalidArgumentErrorable(NoSuchDirectionMetadataEntryErrorable, Direction, "No metadata entry (Direction requested) can be found on provided index");

  class OptUUIDMetadataEntry : public MetadataEntry {
   private:
    std::optional<UUID> optValue;

   public:
    static inline const uint32_t ORDINAL = MinecraftOrdinalRegistry::MetadataEntryRegistry.RegisterOrdinal();

    OptUUIDMetadataEntry();
    explicit OptUUIDMetadataEntry(const std::optional<UUID>& optValue);

    Errorable<bool> Write(const ProtocolVersion* version, ByteBuffer* buffer) const override;
    static Errorable<OptUUIDMetadataEntry> Instantiate(const ProtocolVersion* version, ByteBuffer* buffer);
    [[nodiscard]] MetadataEntryType GetType() const override;
    [[nodiscard]] uint32_t GetOrdinal() const override;

    [[nodiscard]] std::optional<UUID> GetValue() const;
    void SetValue(const std::optional<UUID>& newValue);
  };
  CreateInvalidArgumentErrorable(InvalidOptUUIDMetadataEntryErrorable, OptUUIDMetadataEntry, "Invalid OptUUIDMetadataEntry read");
  CreateInvalidArgumentErrorable(MismatchOptUUIDMetadataEntryErrorable, std::optional<UUID>, "The requested type (OptUUID) doesn't match the actual type");
  CreateInvalidArgumentErrorable(NoSuchOptUUIDMetadataEntryErrorable, std::optional<UUID>, "No metadata entry (OptUUID requested) can be found on provided index");

  class BlockIDMetadataEntry : public MetadataEntry {
   private:
    uint32_t value{};

   public:
    static inline const uint32_t ORDINAL = MinecraftOrdinalRegistry::MetadataEntryRegistry.RegisterOrdinal();

    BlockIDMetadataEntry() = default;
    explicit BlockIDMetadataEntry(uint32_t value);

    Errorable<bool> Write(const ProtocolVersion* version, ByteBuffer* buffer) const override;
    static Errorable<BlockIDMetadataEntry> Instantiate(const ProtocolVersion* version, ByteBuffer* buffer);
    [[nodiscard]] MetadataEntryType GetType() const override;
    [[nodiscard]] uint32_t GetOrdinal() const override;

    [[nodiscard]] uint32_t GetValue() const;
    void SetValue(uint32_t newValue);
  };
  CreateInvalidArgumentErrorable(InvalidBlockIDMetadataEntryErrorableErrorable, BlockIDMetadataEntry, "Invalid BlockIDMetadataEntry read");
  CreateInvalidArgumentErrorable(MismatchBlockIDMetadataEntryErrorable, uint32_t, "The requested type (BlockID) doesn't match the actual type");
  CreateInvalidArgumentErrorable(NoSuchBlockIDMetadataEntryErrorable, uint32_t, "No metadata entry (BlockID requested) can be found on provided index");


  class NBTMetadataEntry : public MetadataEntry {
   private:
    NBT* value{};

   public:
    static inline const uint32_t ORDINAL = MinecraftOrdinalRegistry::MetadataEntryRegistry.RegisterOrdinal();

    NBTMetadataEntry() = default;
    explicit NBTMetadataEntry(NBT* value);
    static Errorable<NBTMetadataEntry> Instantiate(const ProtocolVersion* version, ByteBuffer* buffer);

    ~NBTMetadataEntry() override;

    Errorable<bool> Write(const ProtocolVersion* version, ByteBuffer* buffer) const override;
    [[nodiscard]] MetadataEntryType GetType() const override;
    [[nodiscard]] uint32_t GetOrdinal() const override;

    [[nodiscard]] NBT* GetValue() const;
    void SetValue(NBT* newValue);
  };
  CreateInvalidArgumentErrorable(InvalidNBTMetadataEntryErrorable, NBTMetadataEntry, "Invalid NBTMetadataEntry read");
  CreateInvalidArgumentErrorable(MismatchNBTMetadataEntryErrorable, NBT*, "The requested type (NBT) doesn't match the actual type");
  CreateInvalidArgumentErrorable(NoSuchNBTMetadataEntryErrorable, NBT*, "No metadata entry (NBT requested) can be found on provided index");

  class ParticleMetadataEntry : public MetadataEntry {
   private:
    AbstractParticle* value{};

   public:
    static inline const uint32_t ORDINAL = MinecraftOrdinalRegistry::MetadataEntryRegistry.RegisterOrdinal();

    ParticleMetadataEntry() = default;
    explicit ParticleMetadataEntry(AbstractParticle* value);
    static Errorable<ParticleMetadataEntry> Instantiate(const ProtocolVersion* version, ByteBuffer* buffer);

    ~ParticleMetadataEntry() override;

    Errorable<bool> Write(const ProtocolVersion* version, ByteBuffer* buffer) const override;
    [[nodiscard]] MetadataEntryType GetType() const override;
    [[nodiscard]] uint32_t GetOrdinal() const override;

    [[nodiscard]] AbstractParticle* GetValue() const;
    void SetValue(AbstractParticle* newValue);
  };
  CreateInvalidArgumentErrorable(InvalidParticleMetadataEntryErrorable, ParticleMetadataEntry, "Invalid ParticleMetadataEntry read");
  CreateInvalidArgumentErrorable(MismatchParticleMetadataEntryErrorable, AbstractParticle*, "The requested type (Particle) doesn't match the actual type");
  CreateInvalidArgumentErrorable(NoSuchParticleMetadataEntryErrorable, AbstractParticle*, "No metadata entry (Particle requested) can be found on provided index");

  class VillagerDataMetadataEntry : public MetadataEntry {
   private:
    VillagerData value;

   public:
    static inline const uint32_t ORDINAL = MinecraftOrdinalRegistry::MetadataEntryRegistry.RegisterOrdinal();

    VillagerDataMetadataEntry() = default;
    VillagerDataMetadataEntry(VillagerData value);

    Errorable<bool> Write(const ProtocolVersion* version, ByteBuffer* buffer) const override;
    static Errorable<VillagerDataMetadataEntry> Instantiate(const ProtocolVersion* version, ByteBuffer* buffer);
    [[nodiscard]] MetadataEntryType GetType() const override;
    [[nodiscard]] uint32_t GetOrdinal() const override;

    [[nodiscard]] VillagerData GetValue() const;
    void SetValue(VillagerData newValue);
  };
  CreateInvalidArgumentErrorable(InvalidVillagerDataMetadataEntryErrorable, VillagerDataMetadataEntry, "Invalid VillagerDataMetadataEntry read");
  CreateInvalidArgumentErrorable(MismatchVillagerDataMetadataEntryErrorable, VillagerData, "The requested type (VillagerData) doesn't match the actual type");
  CreateInvalidArgumentErrorable(NoSuchVillagerDataMetadataEntryErrorable, VillagerData, "No metadata entry (VillagerData requested) can be found on provided index");

  class OptVarIntMetadataEntry : public MetadataEntry {
   private:
    std::optional<uint32_t> optValue;

   public:
    static inline const uint32_t ORDINAL = MinecraftOrdinalRegistry::MetadataEntryRegistry.RegisterOrdinal();

    OptVarIntMetadataEntry();
    explicit OptVarIntMetadataEntry(const std::optional<uint32_t>& optValue);

    Errorable<bool> Write(const ProtocolVersion* version, ByteBuffer* buffer) const override;
    static Errorable<OptVarIntMetadataEntry> Instantiate(const ProtocolVersion* version, ByteBuffer* buffer);
    [[nodiscard]] MetadataEntryType GetType() const override;
    [[nodiscard]] uint32_t GetOrdinal() const override;

    [[nodiscard]] std::optional<uint32_t> GetValue() const;
    void SetValue(const std::optional<uint32_t>& newValue);
  };
  CreateInvalidArgumentErrorable(InvalidOptVarIntMetadataEntryErrorable, OptVarIntMetadataEntry, "Invalid OptVarIntMetadataEntry read");
  CreateInvalidArgumentErrorable(MismatchOptVarIntMetadataEntryErrorable, std::optional<uint32_t>, "The requested type (OptVarInt) doesn't match the actual type");
  CreateInvalidArgumentErrorable(NoSuchOptVarIntMetadataEntryErrorable, std::optional<uint32_t>, "No metadata entry (OptVarInt requested) can be found on provided index");

  class PoseMetadataEntry : public MetadataEntry {
   private:
    Pose value{};

   public:
    static inline const uint32_t ORDINAL = MinecraftOrdinalRegistry::MetadataEntryRegistry.RegisterOrdinal();

    PoseMetadataEntry() = default;
    explicit PoseMetadataEntry(const Pose& value);

    Errorable<bool> Write(const ProtocolVersion* version, ByteBuffer* buffer) const override;
    static Errorable<PoseMetadataEntry> Instantiate(const ProtocolVersion* version, ByteBuffer* buffer);
    [[nodiscard]] MetadataEntryType GetType() const override;
    [[nodiscard]] uint32_t GetOrdinal() const override;

    [[nodiscard]] Pose GetValue() const;
    void SetValue(const Pose& newValue);
  };
  CreateInvalidArgumentErrorable(InvalidPoseMetadataEntryErrorable, PoseMetadataEntry, "Invalid PoseMetadataEntry read");
  CreateInvalidArgumentErrorable(MismatchPoseMetadataEntryErrorable, Pose, "The requested type (Pose) doesn't match the actual type");
  CreateInvalidArgumentErrorable(NoSuchPoseMetadataEntryErrorable, Pose, "No metadata entry (Pose requested) can be found on provided index");

  class CatVariantMetadataEntry : public MetadataEntry {
   private:
    CatVariant value{};

   public:
    static inline const uint32_t ORDINAL = MinecraftOrdinalRegistry::MetadataEntryRegistry.RegisterOrdinal();

    CatVariantMetadataEntry() = default;
    explicit CatVariantMetadataEntry(const CatVariant& value);

    Errorable<bool> Write(const ProtocolVersion* version, ByteBuffer* buffer) const override;
    static Errorable<CatVariantMetadataEntry> Instantiate(const ProtocolVersion* version, ByteBuffer* buffer);
    [[nodiscard]] MetadataEntryType GetType() const override;
    [[nodiscard]] uint32_t GetOrdinal() const override;

    [[nodiscard]] CatVariant GetValue() const;
    void SetValue(const CatVariant& newValue);
  };
  CreateInvalidArgumentErrorable(InvalidCatVariantMetadataEntryErrorable, CatVariantMetadataEntry, "Invalid CatVariantMetadataEntry read");
  CreateInvalidArgumentErrorable(MismatchCatVariantMetadataEntryErrorable, CatVariant, "The requested type (CatVariant) doesn't match the actual type");
  CreateInvalidArgumentErrorable(NoSuchCatVariantMetadataEntryErrorable, CatVariant, "No metadata entry (CatVariant requested) can be found on provided index");

  class FrogVariantMetadataEntry : public MetadataEntry {
   private:
    FrogVariant value{};

   public:
    static inline const uint32_t ORDINAL = MinecraftOrdinalRegistry::MetadataEntryRegistry.RegisterOrdinal();

    FrogVariantMetadataEntry() = default;
    explicit FrogVariantMetadataEntry(const FrogVariant& value);

    Errorable<bool> Write(const ProtocolVersion* version, ByteBuffer* buffer) const override;
    static Errorable<FrogVariantMetadataEntry> Instantiate(const ProtocolVersion* version, ByteBuffer* buffer);
    [[nodiscard]] MetadataEntryType GetType() const override;
    [[nodiscard]] uint32_t GetOrdinal() const override;

    [[nodiscard]] FrogVariant GetValue() const;
    void SetValue(const FrogVariant& newValue);
  };
  CreateInvalidArgumentErrorable(InvalidFrogVariantMetadataEntryErrorable, FrogVariantMetadataEntry, "Invalid FrogVariantMetadataEntry read");
  CreateInvalidArgumentErrorable(MismatchFrogVariantMetadataEntryErrorable, FrogVariant, "The requested type (FrogVariant) doesn't match the actual type");
  CreateInvalidArgumentErrorable(NoSuchFrogVariantMetadataEntryErrorable, FrogVariant, "No metadata entry (FrogVariant requested) can be found on provided index");

  class GlobalPosMetadataEntry : public MetadataEntry {
   private:
    GlobalPos value;

   public:
    static inline const uint32_t ORDINAL = MinecraftOrdinalRegistry::MetadataEntryRegistry.RegisterOrdinal();

    GlobalPosMetadataEntry() = default;
    explicit GlobalPosMetadataEntry(GlobalPos position);

    Errorable<bool> Write(const ProtocolVersion* version, ByteBuffer* buffer) const override;
    static Errorable<GlobalPosMetadataEntry> Instantiate(const ProtocolVersion* version, ByteBuffer* buffer);
    [[nodiscard]] MetadataEntryType GetType() const override;
    [[nodiscard]] uint32_t GetOrdinal() const override;

    [[nodiscard]] GlobalPos GetValue() const;
    void SetValue(GlobalPos value);
  };
  CreateInvalidArgumentErrorable(InvalidGlobalPosMetadataEntryErrorable, GlobalPosMetadataEntry, "Invalid GlobalPosMetadataEntry read");
  CreateInvalidArgumentErrorable(MismatchGlobalPosMetadataEntryErrorable, GlobalPos, "The requested type (GlobalPos) doesn't match the actual type");
  CreateInvalidArgumentErrorable(NoSuchGlobalPosMetadataEntryErrorable, GlobalPos, "No metadata entry (GlobalPos requested) can be found on provided index");

  class PaintingVariantMetadataEntry : public MetadataEntry {
   private:
    PaintingVariant value{};

   public:
    static inline const uint32_t ORDINAL = MinecraftOrdinalRegistry::MetadataEntryRegistry.RegisterOrdinal();

    PaintingVariantMetadataEntry() = default;
    explicit PaintingVariantMetadataEntry(const PaintingVariant& value);

    Errorable<bool> Write(const ProtocolVersion* version, ByteBuffer* buffer) const override;
    static Errorable<PaintingVariantMetadataEntry> Instantiate(const ProtocolVersion* version, ByteBuffer* buffer);
    [[nodiscard]] MetadataEntryType GetType() const override;
    [[nodiscard]] uint32_t GetOrdinal() const override;

    [[nodiscard]] PaintingVariant GetValue() const;
    void SetValue(const PaintingVariant& newValue);
  };
  CreateInvalidArgumentErrorable(InvalidPaintingVariantMetadataEntryErrorable, PaintingVariantMetadataEntry, "Invalid PaintingVariantMetadataEntry read");
  CreateInvalidArgumentErrorable(MismatchPaintingVariantMetadataEntryErrorable, PaintingVariant, "The requested type (PaintingVariant) doesn't match the actual type");
  CreateInvalidArgumentErrorable(NoSuchPaintingVariantMetadataEntryErrorable, PaintingVariant, "No metadata entry (PaintingVariant requested) can be found on provided index");

  class Metadata {
   private:
    std::map<uint8_t, MetadataEntry*> entries;

   public:
    Metadata() = default;
    Metadata(std::map<uint8_t, MetadataEntry*> entries);
    static Errorable<Metadata*> Instantiate(const ProtocolVersion* version, ByteBuffer* buffer);

    virtual ~Metadata() {
      for (auto& entry : entries) {
        delete entry.second;
      }
    }

    Errorable<bool> Write(const ProtocolVersion* version, ByteBuffer* buffer) const;
    [[nodiscard]] uint32_t Size(const ProtocolVersion* version) const;

    void Set(uint8_t index, MetadataEntry* value);

    template<typename T = MetadataEntry>
    T* Get(uint8_t index) const {
      auto it = entries.find(index);
      if (it == entries.end()) {
        return nullptr;
      }

      return (T*) it->second;
    }

    [[nodiscard]] Errorable<uint8_t> GetByte(uint8_t index) const;
    [[nodiscard]] Errorable<uint32_t> GetVarInt(uint8_t index) const;
    [[nodiscard]] Errorable<uint64_t> GetLong(uint8_t index) const;
    [[nodiscard]] Errorable<float> GetFloat(uint8_t index) const;
    [[nodiscard]] Errorable<std::string> GetString(uint8_t index) const;
    [[nodiscard]] Errorable<std::string> GetChat(uint8_t index) const;
    [[nodiscard]] Errorable<std::optional<std::string>> GetOptChat(uint8_t index) const;
    [[nodiscard]] Errorable<ItemStack> GetItemStack(uint8_t index) const;
    [[nodiscard]] Errorable<bool> GetBoolean(uint8_t index) const;
    [[nodiscard]] Errorable<Rotation> GetRotation(uint8_t index) const;
    [[nodiscard]] Errorable<Position> GetPosition(uint8_t) const;
    [[nodiscard]] Errorable<std::optional<Position>> GetOptPosition(uint8_t index) const;
    [[nodiscard]] Errorable<Direction> GetDirection(uint8_t index) const;
    [[nodiscard]] Errorable<std::optional<UUID>> GetOptUUID(uint8_t index) const;
    [[nodiscard]] Errorable<uint32_t> GetBlockID(uint8_t index) const;
    [[nodiscard]] Errorable<NBT*> GetNBT(uint8_t index) const;
    [[nodiscard]] Errorable<AbstractParticle*> GetParticle(uint8_t index) const;
    [[nodiscard]] Errorable<VillagerData> GetVillagerData(uint8_t index) const;
    [[nodiscard]] Errorable<std::optional<uint32_t>> GetOptVarInt(uint8_t index) const;
    [[nodiscard]] Errorable<Pose> GetPose(uint8_t index) const;
    [[nodiscard]] Errorable<CatVariant> GetCatVariant(uint8_t index) const;
    [[nodiscard]] Errorable<FrogVariant> GetFrogVariant(uint8_t index) const;
    [[nodiscard]] Errorable<GlobalPos> GetGlobalPos(uint8_t index) const;
    [[nodiscard]] Errorable<PaintingVariant> GetPaintingVariant(uint8_t index) const;
  };
  CreateInvalidArgumentErrorable(InvalidMetadataErrorable, Metadata*, "Invalid Metadata read");

  extern const ConstructorRegistry<MetadataEntry> METADATA_ENTRY_REGISTRY;

  extern const EnumRegistry<CatVariant> CAT_VARIANT_REGISTRY;
  extern const EnumRegistry<FrogVariant> FROG_VARIANT_REGISTRY;
  extern const EnumRegistry<PaintingVariant> PAINTING_VARIANT_REGISTRY;
}