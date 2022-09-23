#pragma once

#include "../../../../utils/ordinal/OrdinalRegistry.hpp"
#include "../../../Protocol.hpp"
#include "../../../registry/DataTypeRegistry.hpp"
#include "../../ItemStack.hpp"
#include "../../particle/Particle.hpp"
#include "VillagerData.hpp"
#include <map>
#include <optional>

namespace Ship {

  enum class Pose {
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

  enum class CatVariant {
    TABBY,
    BLACK,
    RED,
    SIAMESE,
    BRITISH_SHORTHAIR,
    CALICO,
    PERSIAN,
    RAGDOLL,
    WHITE,
    JELLIE,
    ALL_BLACK,
  };

  enum class FrogVariant {
    TEMPERATE = 0,
    WARM = 1,
    COLD = 2,
  };

  enum class PaintingVariant {
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

  class MetadataEntry {
   public:
    virtual ~MetadataEntry() = default;

    virtual void Write(const ProtocolVersion* version, ByteBuffer* buffer) = 0;
    virtual void Read(const ProtocolVersion* version, ByteBuffer* buffer) = 0;
    [[nodiscard]] virtual uint32_t Size(const ProtocolVersion* version) const = 0;
    [[nodiscard]] virtual MetadataEntryType GetType() const = 0;
    [[nodiscard]] virtual uint32_t GetOrdinal() const = 0;
  };

  class ByteMetadataEntry : public MetadataEntry {
   private:
    uint8_t value;

   public:
    static inline const uint32_t ORDINAL = OrdinalRegistry::MetadataEntryRegistry.RegisterOrdinal();

    explicit ByteMetadataEntry(uint8_t value);

    void Write(const ProtocolVersion* version, ByteBuffer* buffer) override;
    void Read(const ProtocolVersion* version, ByteBuffer* buffer) override;
    [[nodiscard]] uint32_t Size(const ProtocolVersion* version) const override;
    [[nodiscard]] MetadataEntryType GetType() const override;
    [[nodiscard]] uint32_t GetOrdinal() const override;

    [[nodiscard]] uint8_t GetValue() const;
    void SetValue(uint8_t newValue);
  };

  class VarIntMetadataEntry : public MetadataEntry {
   private:
    uint32_t value;

   public:
    static inline const uint32_t ORDINAL = OrdinalRegistry::MetadataEntryRegistry.RegisterOrdinal();

    explicit VarIntMetadataEntry(uint32_t value);

    void Write(const ProtocolVersion* version, ByteBuffer* buffer) override;
    void Read(const ProtocolVersion* version, ByteBuffer* buffer) override;
    [[nodiscard]] uint32_t Size(const ProtocolVersion* version) const override;
    [[nodiscard]] MetadataEntryType GetType() const override;
    [[nodiscard]] uint32_t GetOrdinal() const override;

    [[nodiscard]] uint32_t GetValue() const;
    void SetValue(uint32_t newValue);
  };

  class FloatMetadataEntry : public MetadataEntry {
   private:
    float value;

   public:
    static inline const uint32_t ORDINAL = OrdinalRegistry::MetadataEntryRegistry.RegisterOrdinal();

    explicit FloatMetadataEntry(float value);

    void Write(const ProtocolVersion* version, ByteBuffer* buffer) override;
    void Read(const ProtocolVersion* version, ByteBuffer* buffer) override;
    [[nodiscard]] uint32_t Size(const ProtocolVersion* version) const override;
    [[nodiscard]] MetadataEntryType GetType() const override;
    [[nodiscard]] uint32_t GetOrdinal() const override;

    [[nodiscard]] float GetValue() const;
    void SetValue(float newValue);
  };

  class StringMetadataEntry : public MetadataEntry {
   private:
    std::string value;

   public:
    static inline const uint32_t ORDINAL = OrdinalRegistry::MetadataEntryRegistry.RegisterOrdinal();

    explicit StringMetadataEntry(std::string value);

    void Write(const ProtocolVersion* version, ByteBuffer* buffer) override;
    void Read(const ProtocolVersion* version, ByteBuffer* buffer) override;
    [[nodiscard]] uint32_t Size(const ProtocolVersion* version) const override;
    [[nodiscard]] MetadataEntryType GetType() const override;
    [[nodiscard]] uint32_t GetOrdinal() const override;

    [[nodiscard]] std::string GetValue() const;
    void SetValue(std::string newValue);
  };

  class ChatMetadataEntry : public MetadataEntry {
   private:
    std::string value; // TODO: Chat components

   public:
    static inline const uint32_t ORDINAL = OrdinalRegistry::MetadataEntryRegistry.RegisterOrdinal();

    explicit ChatMetadataEntry(std::string value);

    void Write(const ProtocolVersion* version, ByteBuffer* buffer) override;
    void Read(const ProtocolVersion* version, ByteBuffer* buffer) override;
    [[nodiscard]] uint32_t Size(const ProtocolVersion* version) const override;
    [[nodiscard]] MetadataEntryType GetType() const override;
    [[nodiscard]] uint32_t GetOrdinal() const override;

    [[nodiscard]] std::string GetValue() const;
    void SetValue(std::string newValue);
  };

  class OptChatMetadataEntry : public MetadataEntry {
   private:
    std::optional<std::string> optValue; // TODO: Chat components

   public:
    static inline const uint32_t ORDINAL = OrdinalRegistry::MetadataEntryRegistry.RegisterOrdinal();

    OptChatMetadataEntry();
    explicit OptChatMetadataEntry(std::optional<std::string> optValue);

    void Write(const ProtocolVersion* version, ByteBuffer* buffer) override;
    void Read(const ProtocolVersion* version, ByteBuffer* buffer) override;
    [[nodiscard]] uint32_t Size(const ProtocolVersion* version) const override;
    [[nodiscard]] MetadataEntryType GetType() const override;
    [[nodiscard]] uint32_t GetOrdinal() const override;

    [[nodiscard]] std::optional<std::string> GetValue() const;
    void SetValue(const std::optional<std::string>& newValue);
  };

  class ItemStackMetadataEntry : public MetadataEntry {
   private:
    ItemStack value;

   public:
    static inline const uint32_t ORDINAL = OrdinalRegistry::MetadataEntryRegistry.RegisterOrdinal();

    explicit ItemStackMetadataEntry(const ItemStack& value);

    void Write(const ProtocolVersion* version, ByteBuffer* buffer) override;
    void Read(const ProtocolVersion* version, ByteBuffer* buffer) override;
    [[nodiscard]] uint32_t Size(const ProtocolVersion* version) const override;
    [[nodiscard]] MetadataEntryType GetType() const override;
    [[nodiscard]] uint32_t GetOrdinal() const override;

    [[nodiscard]] ItemStack GetValue() const;
    void SetValue(const ItemStack& newValue);
  };

  class BooleanMetadataEntry : public MetadataEntry {
   private:
    bool value;

   public:
    static inline const uint32_t ORDINAL = OrdinalRegistry::MetadataEntryRegistry.RegisterOrdinal();

    explicit BooleanMetadataEntry(bool value);

    void Write(const ProtocolVersion* version, ByteBuffer* buffer) override;
    void Read(const ProtocolVersion* version, ByteBuffer* buffer) override;
    [[nodiscard]] uint32_t Size(const ProtocolVersion* version) const override;
    [[nodiscard]] MetadataEntryType GetType() const override;
    [[nodiscard]] uint32_t GetOrdinal() const override;

    [[nodiscard]] bool GetValue() const;
    void SetValue(bool newValue);
  };

  class RotationMetadataEntry : public MetadataEntry {
   private:
    float x;
    float y;
    float z;

   public:
    static inline const uint32_t ORDINAL = OrdinalRegistry::MetadataEntryRegistry.RegisterOrdinal();

    explicit RotationMetadataEntry(float x, float y, float z);

    void Write(const ProtocolVersion* version, ByteBuffer* buffer) override;
    void Read(const ProtocolVersion* version, ByteBuffer* buffer) override;
    [[nodiscard]] uint32_t Size(const ProtocolVersion* version) const override;
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

  class PositionMetadataEntry : public MetadataEntry {
   private:
    int x;
    int y;
    int z;

   public:
    static inline const uint32_t ORDINAL = OrdinalRegistry::MetadataEntryRegistry.RegisterOrdinal();

    explicit PositionMetadataEntry(int x, int y, int z);

    void Write(const ProtocolVersion* version, ByteBuffer* buffer) override;
    void Read(const ProtocolVersion* version, ByteBuffer* buffer) override;
    [[nodiscard]] uint32_t Size(const ProtocolVersion* version) const override;
    [[nodiscard]] MetadataEntryType GetType() const override;
    [[nodiscard]] uint32_t GetOrdinal() const override;

    [[nodiscard]] int GetX() const;
    void SetX(int value);
    [[nodiscard]] int GetY() const;
    void SetY(int value);
    [[nodiscard]] int GetZ() const;
    void SetZ(int value);

    void Get(int& outX, int& outY, int& outZ) const;
    void Set(int newX, int newY, int newZ);
  };

  class OptPositionMetadataEntry : public MetadataEntry {
   private:
    bool present;
    int x;
    int y;
    int z;

   public:
    static inline const uint32_t ORDINAL = OrdinalRegistry::MetadataEntryRegistry.RegisterOrdinal();

    OptPositionMetadataEntry();
    explicit OptPositionMetadataEntry(int x, int y, int z);

    void Write(const ProtocolVersion* version, ByteBuffer* buffer) override;
    void Read(const ProtocolVersion* version, ByteBuffer* buffer) override;
    [[nodiscard]] uint32_t Size(const ProtocolVersion* version) const override;
    [[nodiscard]] MetadataEntryType GetType() const override;
    [[nodiscard]] uint32_t GetOrdinal() const override;

    [[nodiscard]] bool IsPresent() const;
    void SetPresent(bool value);
    [[nodiscard]] int GetX() const;
    void SetX(int value);
    [[nodiscard]] int GetY() const;
    void SetY(int value);
    [[nodiscard]] int GetZ() const;
    void SetZ(int value);

    void Get(bool& outPresent, int& outX, int& outY, int& outZ) const;
    void Set(int newX, int newY, int newZ);
    void Reset();
  };

  class DirectionMetadataEntry : public MetadataEntry {
   private:
    Direction value;

   public:
    static inline const uint32_t ORDINAL = OrdinalRegistry::MetadataEntryRegistry.RegisterOrdinal();

    explicit DirectionMetadataEntry(const Direction& value);

    void Write(const ProtocolVersion* version, ByteBuffer* buffer) override;
    void Read(const ProtocolVersion* version, ByteBuffer* buffer) override;
    [[nodiscard]] uint32_t Size(const ProtocolVersion* version) const override;
    [[nodiscard]] MetadataEntryType GetType() const override;
    [[nodiscard]] uint32_t GetOrdinal() const override;

    [[nodiscard]] Direction GetValue() const;
    void SetValue(const Direction& newValue);
  };

  class OptUUIDMetadataEntry : public MetadataEntry {
   private:
    std::optional<UUID> optValue;

   public:
    static inline const uint32_t ORDINAL = OrdinalRegistry::MetadataEntryRegistry.RegisterOrdinal();

    OptUUIDMetadataEntry();
    explicit OptUUIDMetadataEntry(const std::optional<UUID>& optValue);

    void Write(const ProtocolVersion* version, ByteBuffer* buffer) override;
    void Read(const ProtocolVersion* version, ByteBuffer* buffer) override;
    [[nodiscard]] uint32_t Size(const ProtocolVersion* version) const override;
    [[nodiscard]] MetadataEntryType GetType() const override;
    [[nodiscard]] uint32_t GetOrdinal() const override;

    [[nodiscard]] std::optional<UUID> GetValue() const;
    void SetValue(const std::optional<UUID>& newValue);
  };

  class BlockIDMetadataEntry : public MetadataEntry {
   private:
    uint32_t value;

   public:
    static inline const uint32_t ORDINAL = OrdinalRegistry::MetadataEntryRegistry.RegisterOrdinal();

    BlockIDMetadataEntry();
    explicit BlockIDMetadataEntry(uint32_t value);

    void Write(const ProtocolVersion* version, ByteBuffer* buffer) override;
    void Read(const ProtocolVersion* version, ByteBuffer* buffer) override;
    [[nodiscard]] uint32_t Size(const ProtocolVersion* version) const override;
    [[nodiscard]] MetadataEntryType GetType() const override;
    [[nodiscard]] uint32_t GetOrdinal() const override;

    [[nodiscard]] uint32_t GetValue() const;
    void SetValue(uint32_t newValue);
  };

  class NBTMetadataEntry : public MetadataEntry {
   private:
    NBT* value;

   public:
    static inline const uint32_t ORDINAL = OrdinalRegistry::MetadataEntryRegistry.RegisterOrdinal();

    explicit NBTMetadataEntry(NBT* value);

    ~NBTMetadataEntry() override;

    void Write(const ProtocolVersion* version, ByteBuffer* buffer) override;
    void Read(const ProtocolVersion* version, ByteBuffer* buffer) override;
    [[nodiscard]] uint32_t Size(const ProtocolVersion* version) const override;
    [[nodiscard]] MetadataEntryType GetType() const override;
    [[nodiscard]] uint32_t GetOrdinal() const override;

    [[nodiscard]] NBT* GetValue() const;
    void SetValue(NBT* newValue);
  };

  class ParticleMetadataEntry : public MetadataEntry {
   private:
    AbstractParticle* value;

   public:
    static inline const uint32_t ORDINAL = OrdinalRegistry::MetadataEntryRegistry.RegisterOrdinal();

    explicit ParticleMetadataEntry(AbstractParticle* value);

    ~ParticleMetadataEntry() override;

    void Write(const ProtocolVersion* version, ByteBuffer* buffer) override;
    void Read(const ProtocolVersion* version, ByteBuffer* buffer) override;
    [[nodiscard]] uint32_t Size(const ProtocolVersion* version) const override;
    [[nodiscard]] MetadataEntryType GetType() const override;
    [[nodiscard]] uint32_t GetOrdinal() const override;

    [[nodiscard]] AbstractParticle* GetValue() const;
    void SetValue(AbstractParticle* newValue);
  };

  class VillagerDataMetadataEntry : public MetadataEntry {
   private:
    VillagerType type;
    VillagerProfession profession;
    uint32_t level;

   public:
    static inline const uint32_t ORDINAL = OrdinalRegistry::MetadataEntryRegistry.RegisterOrdinal();

    VillagerDataMetadataEntry(const VillagerType& type, const VillagerProfession& profession, uint32_t level);

    void Write(const ProtocolVersion* version, ByteBuffer* buffer) override;
    void Read(const ProtocolVersion* version, ByteBuffer* buffer) override;
    [[nodiscard]] uint32_t Size(const ProtocolVersion* version) const override;
    [[nodiscard]] MetadataEntryType GetType() const override;
    [[nodiscard]] uint32_t GetOrdinal() const override;

    [[nodiscard]] VillagerType GetVillagerType() const;
    void SetVillagerType(VillagerType newValue);
    [[nodiscard]] VillagerProfession GetProfession() const;
    void SetProfession(VillagerProfession newValue);
    [[nodiscard]] uint32_t GetLevel() const;
    void SetLevel(uint32_t newValue);
  };

  class OptVarIntMetadataEntry : public MetadataEntry {
   private:
    std::optional<uint32_t> optValue;

   public:
    static inline const uint32_t ORDINAL = OrdinalRegistry::MetadataEntryRegistry.RegisterOrdinal();

    OptVarIntMetadataEntry();
    explicit OptVarIntMetadataEntry(const std::optional<uint32_t>& optValue);

    void Write(const ProtocolVersion* version, ByteBuffer* buffer) override;
    void Read(const ProtocolVersion* version, ByteBuffer* buffer) override;
    [[nodiscard]] uint32_t Size(const ProtocolVersion* version) const override;
    [[nodiscard]] MetadataEntryType GetType() const override;
    [[nodiscard]] uint32_t GetOrdinal() const override;

    [[nodiscard]] std::optional<uint32_t> GetValue() const;
    void SetValue(const std::optional<uint32_t>& newValue);
  };

  class PoseMetadataEntry : public MetadataEntry {
   private:
    Pose value;

   public:
    static inline const uint32_t ORDINAL = OrdinalRegistry::MetadataEntryRegistry.RegisterOrdinal();

    explicit PoseMetadataEntry(const Pose& value);

    void Write(const ProtocolVersion* version, ByteBuffer* buffer) override;
    void Read(const ProtocolVersion* version, ByteBuffer* buffer) override;
    [[nodiscard]] uint32_t Size(const ProtocolVersion* version) const override;
    [[nodiscard]] MetadataEntryType GetType() const override;
    [[nodiscard]] uint32_t GetOrdinal() const override;

    [[nodiscard]] Pose GetValue() const;
    void SetValue(const Pose& newValue);
  };

  class CatVariantMetadataEntry : public MetadataEntry {
   private:
    CatVariant value;

   public:
    static inline const uint32_t ORDINAL = OrdinalRegistry::MetadataEntryRegistry.RegisterOrdinal();

    explicit CatVariantMetadataEntry(const CatVariant& value);

    void Write(const ProtocolVersion* version, ByteBuffer* buffer) override;
    void Read(const ProtocolVersion* version, ByteBuffer* buffer) override;
    [[nodiscard]] uint32_t Size(const ProtocolVersion* version) const override;
    [[nodiscard]] MetadataEntryType GetType() const override;
    [[nodiscard]] uint32_t GetOrdinal() const override;

    [[nodiscard]] CatVariant GetValue() const;
    void SetValue(const CatVariant& newValue);
  };

  class FrogVariantMetadataEntry : public MetadataEntry {
   private:
    FrogVariant value;

   public:
    static inline const uint32_t ORDINAL = OrdinalRegistry::MetadataEntryRegistry.RegisterOrdinal();

    explicit FrogVariantMetadataEntry(const FrogVariant& value);

    void Write(const ProtocolVersion* version, ByteBuffer* buffer) override;
    void Read(const ProtocolVersion* version, ByteBuffer* buffer) override;
    [[nodiscard]] uint32_t Size(const ProtocolVersion* version) const override;
    [[nodiscard]] MetadataEntryType GetType() const override;
    [[nodiscard]] uint32_t GetOrdinal() const override;

    [[nodiscard]] FrogVariant GetValue() const;
    void SetValue(const FrogVariant& newValue);
  };

  class GlobalPosMetadataEntry : public MetadataEntry {
   private:
    std::string dimension;
    int x;
    int y;
    int z;

   public:
    static inline const uint32_t ORDINAL = OrdinalRegistry::MetadataEntryRegistry.RegisterOrdinal();

    explicit GlobalPosMetadataEntry(std::string dimension, int x, int y, int z);

    void Write(const ProtocolVersion* version, ByteBuffer* buffer) override;
    void Read(const ProtocolVersion* version, ByteBuffer* buffer) override;
    [[nodiscard]] uint32_t Size(const ProtocolVersion* version) const override;
    [[nodiscard]] MetadataEntryType GetType() const override;
    [[nodiscard]] uint32_t GetOrdinal() const override;

    [[nodiscard]] std::string GetDimension() const;
    void SetDimension(const std::string& value);
    [[nodiscard]] int GetX() const;
    void SetX(int value);
    [[nodiscard]] int GetY() const;
    void SetY(int value);
    [[nodiscard]] int GetZ() const;
    void SetZ(int value);

    void Get(std::string& outDimension, int& outX, int& outY, int& outZ) const;
    void Set(const std::string& newDimension, int newX, int newY, int newZ);
  };

  class PaintingVariantMetadataEntry : public MetadataEntry {
   private:
    PaintingVariant value;

   public:
    static inline const uint32_t ORDINAL = OrdinalRegistry::MetadataEntryRegistry.RegisterOrdinal();

    explicit PaintingVariantMetadataEntry(const PaintingVariant& value);

    void Write(const ProtocolVersion* version, ByteBuffer* buffer) override;
    void Read(const ProtocolVersion* version, ByteBuffer* buffer) override;
    [[nodiscard]] uint32_t Size(const ProtocolVersion* version) const override;
    [[nodiscard]] MetadataEntryType GetType() const override;
    [[nodiscard]] uint32_t GetOrdinal() const override;

    [[nodiscard]] PaintingVariant GetValue() const;
    void SetValue(const PaintingVariant& newValue);
  };

  class Metadata {
   private:
    std::map<uint8_t, MetadataEntry*> entries;

   public:
    virtual ~Metadata() {
      for (auto& entry : entries) {
        delete entry.second;
      }
    }

    void Read(const ProtocolVersion* version, ByteBuffer* buffer);
    void Write(const ProtocolVersion* version, ByteBuffer* buffer);
    [[nodiscard]] uint32_t Size(const ProtocolVersion* version) const;

    MetadataEntry* Get(uint8_t index);
    void Set(uint8_t index, MetadataEntry* value);
  };

  extern const DataTypeRegistry<MetadataEntry> METADATA_ENTRY_REGISTRY;

  extern const EnumRegistry<CatVariant> CAT_VARIANT_REGISTRY;
  extern const EnumRegistry<FrogVariant> FROG_VARIANT_REGISTRY;
  extern const EnumRegistry<PaintingVariant> PAINTING_VARIANT_REGISTRY;
}