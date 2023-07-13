#pragma once

#include "../../../../../lib/ShipNet/src/protocol/Protocol.hpp"
#include "../../../../../lib/ShipNet/src/utils/ordinal/OrdinalRegistry.hpp"
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

  class LongMetadataEntry : public MetadataEntry {
   private:
    uint32_t value{};

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

  class RotationMetadataEntry : public MetadataEntry {
   private:
    float x{};
    float y{};
    float z{};

   public:
    static inline const uint32_t ORDINAL = MinecraftOrdinalRegistry::MetadataEntryRegistry.RegisterOrdinal();

    RotationMetadataEntry() = default;
    explicit RotationMetadataEntry(float x, float y, float z);

    Errorable<bool> Write(const ProtocolVersion* version, ByteBuffer* buffer) const override;
    static Errorable<RotationMetadataEntry> Instantiate(const ProtocolVersion* version, ByteBuffer* buffer);
    [[nodiscard]] MetadataEntryType GetType() const override;
    [[nodiscard]] uint32_t GetOrdinal() const override;

    [[nodiscard]] float GetX() const;
    void SetX(float value);
    [[nodiscard]] float GetY() const;
    void SetY(float value);
    [[nodiscard]] float GetZ() const;
    void SetZ(float value);

    void Get(float& outX, float& outY, float& outZ) const;
    void Set(float newX, float newY, float newZ);
  };
  CreateInvalidArgumentErrorable(InvalidRotationMetadataEntryErrorable, RotationMetadataEntry, "Invalid RotationMetadataEntry read");

  class PositionMetadataEntry : public MetadataEntry {
   private:
    Position position{};

   public:
    static inline const uint32_t ORDINAL = MinecraftOrdinalRegistry::MetadataEntryRegistry.RegisterOrdinal();

    PositionMetadataEntry() = default;
    explicit PositionMetadataEntry(Position position);

    Errorable<bool> Write(const ProtocolVersion* version, ByteBuffer* buffer) const override;
    static Errorable<PositionMetadataEntry> Instantiate(const ProtocolVersion* version, ByteBuffer* buffer);
    [[nodiscard]] MetadataEntryType GetType() const override;
    [[nodiscard]] uint32_t GetOrdinal() const override;

    [[nodiscard]] Position GetPosition() const;
    void SetPosition(Position value);

    void Get(Position& position) const;
    void Set(Position position);
  };
  CreateInvalidArgumentErrorable(InvalidPositionMetadataEntryErrorable, PositionMetadataEntry, "Invalid PositionMetadataEntry read");

  class OptPositionMetadataEntry : public MetadataEntry {
   private:
    bool present;
    Position position;

   public:
    static inline const uint32_t ORDINAL = MinecraftOrdinalRegistry::MetadataEntryRegistry.RegisterOrdinal();

    OptPositionMetadataEntry();
    explicit OptPositionMetadataEntry(Position position);

    Errorable<bool> Write(const ProtocolVersion* version, ByteBuffer* buffer) const override;
    static Errorable<OptPositionMetadataEntry> Instantiate(const ProtocolVersion* version, ByteBuffer* buffer);
    [[nodiscard]] MetadataEntryType GetType() const override;
    [[nodiscard]] uint32_t GetOrdinal() const override;

    [[nodiscard]] bool IsPresent() const;
    void SetPresent(bool value);
    [[nodiscard]] Position GetPosition() const;
    void SetPosition(Position value);

    void Get(bool& outPresent, Position& out) const;
    void Set(Position position);
    void Reset();
  };
  CreateInvalidArgumentErrorable(InvalidOptPositionMetadataEntryErrorable, OptPositionMetadataEntry, "Invalid OptPositionMetadataEntry read");

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

  class VillagerDataMetadataEntry : public MetadataEntry {
   private:
    VillagerType type{};
    VillagerProfession profession{};
    uint32_t level{};

   public:
    static inline const uint32_t ORDINAL = MinecraftOrdinalRegistry::MetadataEntryRegistry.RegisterOrdinal();

    VillagerDataMetadataEntry() = default;
    VillagerDataMetadataEntry(const VillagerType& type, const VillagerProfession& profession, uint32_t level);

    Errorable<bool> Write(const ProtocolVersion* version, ByteBuffer* buffer) const override;
    static Errorable<VillagerDataMetadataEntry> Instantiate(const ProtocolVersion* version, ByteBuffer* buffer);
    [[nodiscard]] MetadataEntryType GetType() const override;
    [[nodiscard]] uint32_t GetOrdinal() const override;

    [[nodiscard]] VillagerType GetVillagerType() const;
    void SetVillagerType(VillagerType newValue);
    [[nodiscard]] VillagerProfession GetProfession() const;
    void SetProfession(VillagerProfession newValue);
    [[nodiscard]] uint32_t GetLevel() const;
    void SetLevel(uint32_t newValue);
  };
  CreateInvalidArgumentErrorable(InvalidVillagerDataMetadataEntryErrorable, VillagerDataMetadataEntry, "Invalid VillagerDataMetadataEntry read");

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

  class GlobalPosMetadataEntry : public MetadataEntry {
   private:
    std::string dimension;
    Position position;

   public:
    static inline const uint32_t ORDINAL = MinecraftOrdinalRegistry::MetadataEntryRegistry.RegisterOrdinal();

    GlobalPosMetadataEntry() = default;
    explicit GlobalPosMetadataEntry(std::string dimension, Position position);

    Errorable<bool> Write(const ProtocolVersion* version, ByteBuffer* buffer) const override;
    static Errorable<GlobalPosMetadataEntry> Instantiate(const ProtocolVersion* version, ByteBuffer* buffer);
    [[nodiscard]] MetadataEntryType GetType() const override;
    [[nodiscard]] uint32_t GetOrdinal() const override;

    [[nodiscard]] std::string GetDimension() const;
    void SetDimension(const std::string& value);
    [[nodiscard]] Position GetPosition() const;
    void SetPosition(Position value);

    void Get(std::string& outDimension, Position& position) const;
    void Set(const std::string& newDimension, Position position);
  };
  CreateInvalidArgumentErrorable(InvalidGlobalPosMetadataEntryErrorable, GlobalPosMetadataEntry, "Invalid GlobalPosMetadataEntry read");

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

  class Metadata {
   private:
    std::map<uint8_t, MetadataEntry*> entries;

   public:
    Metadata() = default;
    Metadata(std::map<uint8_t, MetadataEntry*> entries);
    static Errorable<Metadata> Instantiate(const ProtocolVersion* version, ByteBuffer* buffer);

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

    [[nodiscard]] std::optional<uint8_t> GetByte(uint8_t index) const;
    [[nodiscard]] std::optional<uint32_t> GetVarInt(uint8_t index) const;
    [[nodiscard]] std::optional<uint64_t> GetLong(uint8_t index) const;
    [[nodiscard]] std::optional<float> GetFloat(uint8_t index) const;
    [[nodiscard]] std::optional<std::string> GetString(uint8_t index) const;
    [[nodiscard]] std::optional<std::string> GetChat(uint8_t index) const;
    [[nodiscard]] std::optional<std::optional<std::string>> GetOptChat(uint8_t index) const;
    [[nodiscard]] std::optional<ItemStack> GetItemStack(uint8_t index) const;
    [[nodiscard]] std::optional<bool> GetBoolean(uint8_t index) const;
    bool GetRotation(uint8_t index, float& x, float& y, float& z) const;
    bool GetPosition(uint8_t index, int& x, int& y, int& z) const;
    bool GetOptPosition(uint8_t index, bool& present, int& x, int& y, int& z) const;
    [[nodiscard]] std::optional<Direction> GetDirection(uint8_t index) const;
    [[nodiscard]] std::optional<std::optional<UUID>> GetOptUUID(uint8_t index) const;
    [[nodiscard]] std::optional<uint32_t> GetBlockID(uint8_t index) const;
    [[nodiscard]] std::optional<NBT*> GetNBT(uint8_t index) const;
    [[nodiscard]] std::optional<AbstractParticle*> GetParticle(uint8_t index) const;
    bool GetVillagerData(uint8_t index, VillagerType& type, VillagerProfession& profession, uint32_t& level) const;
    [[nodiscard]] std::optional<std::optional<uint32_t>> GetOptVarInt(uint8_t index) const;
    [[nodiscard]] std::optional<Pose> GetPose(uint8_t index) const;
    [[nodiscard]] std::optional<CatVariant> GetCatVariant(uint8_t index) const;
    [[nodiscard]] std::optional<FrogVariant> GetFrogVariant(uint8_t index) const;
    bool GetGlobalPos(uint8_t index, std::string& dimension, int& x, int& y, int& z) const;
    [[nodiscard]] std::optional<PaintingVariant> GetPaintingVariant(uint8_t index) const;
  };
  CreateInvalidArgumentErrorable(InvalidMetadataErrorable, Metadata, "Invalid Metadata read");

  extern const ConstructorRegistry<MetadataEntry> METADATA_ENTRY_REGISTRY;

  extern const EnumRegistry<CatVariant> CAT_VARIANT_REGISTRY;
  extern const EnumRegistry<FrogVariant> FROG_VARIANT_REGISTRY;
  extern const EnumRegistry<PaintingVariant> PAINTING_VARIANT_REGISTRY;
}